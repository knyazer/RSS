#include <include/custom/Environment.hpp>

namespace soccer
{
    void Environment::reset()
    {
		std::cout << "hell" << std::endl;
        Object ball = Object(Shape(Circle(0.039, Vec2(0, 0))), Vec2(0, 0), "ball");
		ball.restitution = 1;
		ball.mass = 0.95;
		ball.friction = 0.3;
		ball.angularFriction = 0.8;

		double gapAngle = 0.7 * M_PI, rad = 0.11;
		double dx = cos(gapAngle / 2) * rad, dy = sin(gapAngle) * rad * 0.6;
		Object robot = Object(Shape(SegmentShape(Vec2(0, 0), rad, M_PI / 2, gapAngle)), Vec2(-0.4, 0), "robot");
		robot.shape.add(SegmentShape(Vec2(0, 0), rad, -M_PI / 2, gapAngle));
		robot.shape.add(Rect(Vec2(-dx, -dy), Vec2(dx, dy)));

		robot.velocity = Vec2(-0.2, 0);
		robot.angle = M_PI / 2;
		robot.restitution = 0.3;
		robot.mass = 2.2;
        robot.controllable = true;
		robot.friction = 0.9;
		robot.angularFriction = 0.9;

		double borderSize = 0.02;
		Vec2 insideBorder = Vec2(1.0, 0.7);
		Vec2 outsideBorder = insideBorder + borderSize;
		
		Object fieldBorders("borders");
		fieldBorders.shape.add(Rect(outsideBorder, 			    insideBorder.xr()));
		fieldBorders.shape.add(Rect(outsideBorder.xr(), 	    insideBorder.xr().yr()));
		fieldBorders.shape.add(Rect(outsideBorder.xr().yr(),    insideBorder.yr()));
		fieldBorders.shape.add(Rect(outsideBorder.yr(), 	    insideBorder));
		fieldBorders.restitution = 0.2;
		fieldBorders.fix();

		double goalsX = 0.8;
		double goalsHeight = 0.6;
		double goalsWidth = 0.1;

		Object blueGoals("blue goals");
		blueGoals.shape.add(Rect(	Vec2(goalsX, goalsHeight / 2 + borderSize), 
									Vec2(goalsX + goalsWidth, goalsHeight / 2)));
		blueGoals.shape.add(Rect(	Vec2(goalsX + goalsWidth, goalsHeight / 2 + borderSize), 
									Vec2(goalsX + goalsWidth + borderSize, -goalsHeight / 2 - borderSize)));
		blueGoals.shape.add(Rect(	Vec2(goalsX, -goalsHeight / 2 - borderSize), 
									Vec2(goalsX + goalsWidth, -goalsHeight / 2)));
		blueGoals.fix();

		Object yellowGoals("yellow goals");
		for (size_t i = 0; i < blueGoals.shape.parts.size(); i++)
			yellowGoals.shape.add(Rect( blueGoals.shape.parts[i]->aabb.min.xr(), 
										blueGoals.shape.parts[i]->aabb.max.xr()));
		yellowGoals.fix();


		fieldBorders.finalize();
		ball.finalize();
		robot.finalize();
		blueGoals.finalize();
		yellowGoals.finalize();

        world.objects.clear();
		world.objects.push_back(ball);
		world.objects.push_back(robot);
		world.objects.push_back(fieldBorders);
		world.objects.push_back(blueGoals);
		world.objects.push_back(yellowGoals);

		world.dt = 0.01;

		for (Object& object : world.objects)
			unghostTimer[object.name] = time;
		
		observable.ball.setup(world.getObjectByName("ball"));
		observable.robot.setup(world.getObjectByName("robot"));
    }

    RawControls Environment::control(ObservableState state)
    {
        return RawControls(state.ball.position.norm() * 3, 
				(state.ball.position.toAngle() - state.robot.angle).radRel() * 4);
    }

    ObservableState Environment::observe(World world)
    {
        return ObservableState(world);
    }

    void Environment::applyControl(Object& object, RawControls controls)
    {
		Vec2 accDirection = controls.velocity.norm();
        object.acceleration = accDirection * min(5.0, accDirection.size());
		std::cout << controls.angularVelocity << std::endl;
        object.angularAcceleration = sign(controls.angularVelocity) * \
						min(2 * M_PI * 5.0, abs(controls.angularVelocity));
		std::cout << "suck suck" << std::endl;
    }

    void Environment::step()
    {
		ObservableState state = observe(world);
        for (size_t i = 0; i < world.objects.size(); i++)
            if (world.objects[i].controllable && !world.objects[i].ghost)
                applyControl(world.objects[i], control(state));

		//ballSuckingControl();
		
        world.step();

		time += world.dt;
		
		noProgressControl();
		outOfBoundsControl();
		goalControl();

		for (Object& object : world.objects)
			if (unghostTimer[object.name] < time)
				object.ghost = false;

		world.resolve();

		observable.ball.update(world.getObjectByName("ball"), world.dt);
		observable.robot.update(world.getObjectByName("robot"), world.dt);
    }

	void Environment::outOfBoundsControl()
	{

	}

	void Environment::ballSuckingControl()
	{
		Object& robot = world.getObjectByName("robot");
		Object& ball = world.getObjectByName("ball");

		Vec2 penetrationVector = Collision::getPenetrationVector(ball, ConvexShapeWrapper(robot.shape.parts[3], \
										robot.angle, robot.position));
		if (!penetrationVector.isZero())
		{
			ball.acceleration += penetrationVector.norm() * 10;
		}
	}

	void Environment::goalControl()
	{
		Object ball = world.getObjectByName("ball");
		Object yellowGoals = world.getObjectByName("yellow goals");

		// If ball touches back of the goals while its center being in goals aabb (being inside goals)
		if (	yellowGoals.aabb.hasInside(ball.position) && Collision::exists(ball, \
				ConvexShapeWrapper(yellowGoals.shape.parts[1], yellowGoals.angle, yellowGoals.position)))
			std::cout << "yellow goal" << time << std::endl;
		
		Object& blueGoals = world.getObjectByName("blue goals");
		if (	blueGoals.aabb.hasInside(ball.position) && Collision::exists(ball, \
				ConvexShapeWrapper(blueGoals.shape.parts[1], blueGoals.angle, blueGoals.position)))
			std::cout << "blue goal" << time << std::endl;
	}

	void Environment::noProgressControl()
	{
		static double timer = 0;

		if (unghostTimer[std::string("ball")] > time + 1)
			return;
		
		Object& ball = world.getObjectByName("ball");

		// Condition of no progress
		if (observable.ball.avgVelocity.size() <= 0.01)
			timer += world.dt;
		else
			timer = 0;
		

		if (timer > 5)
		{
			timer = 0;
			unghostTimer[ball.name] = time + 1;
			
			ball.ghost = true;
			ball.velocity = Vec2(0, 0);
			ball.angularVelocity = 0;
			ball.angle = 0;
			ball.position = findNearestEmptyZone(ball.position);
		}
	}

	Vec2 Environment::findNearestEmptyZone(Vec2 position)
	{
		std::vector<Vec2> zones = {Vec2(0,0), Vec2(0.5, 0.5), Vec2(0.5, -0.5), Vec2(-0.5, -0.5), Vec2(-0.5, 0.5)};
		std::sort(zones.begin(), zones.end(), [position](Vec2 lhs, Vec2 rhs)
		{
			return (lhs - position).size() < (rhs - position).size();
		});

		for (Vec2& zone : zones)
		{
			bool empty = true;

			if ((zone - position).size() <= 0.04)
				continue;

			for (Object& object : world.objects)
			{
				if (object.position == position)
					continue;

				if (object.aabb.hasInside(position))
				{
					for (size_t k = 0; k < object.shape.parts.size(); k++)
					{
						if ((object.shape.parts[k]->aabb).hasInside(position))
						{
							if (Collision::exists(GJK::PointWrapper(zone), 
								ConvexShapeWrapper(std::make_shared<ConvexShape>(*object.shape.parts[k]), object.angle, object.position)))
							{
								empty = false;
								break;
							}
						}
					}
				}

				if (!empty)
					break;	
			}

			if (empty)
				return zone;
		}

		// If on each point is something (impossible actually)
		return Vec2(0, 0);
	}
}