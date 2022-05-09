#include <include/addon.hpp>

namespace addon
{
	Value step(const CallbackInfo& info)
	{
		Env env = info.Env();
		
		int repeats = 0;
		if (info.Length() != 0 && info[0].IsNumber())
			repeats = info[0].As<Napi::Number>().Int32Value();
		
		for (int i = 0; i < repeats; i++)
			environment.step();

		return env.Null();
	}

	Value reset(const CallbackInfo& info)
	{
		Env env = info.Env();

		environment.reset();

		return env.Null();
	}

	Object observe(const CallbackInfo& info)
	{
		Env env = info.Env();
		return wrap(env, environment.world);
	}

	Object shape(const CallbackInfo& info)
	{
		Env env = info.Env();
        Object parts = Object::New(env);

		size_t index = 0;
		if (info.Length() != 0 && info[0].IsNumber())
			index = info[0].As<Napi::Number>().Int32Value();
		
		size_t resolution = 50;
		double step = 2 * M_PI / (double)(resolution);
		
		rss::Object object = environment.world.objects[index];

		for (size_t i = 0; i < object.shape.parts.size(); i++)
		{
			std::shared_ptr<rss::ConvexShape> shape = object.shape.parts[i];
			std::vector<rss::Vec2> points;
			double angle = rss::randf() * 2 * M_PI;

			for (size_t j = 0; j < resolution; j++)
			{
				rss::Vec2 point = shape->getFarthestPointInDirection(rss::Vec2(cos(angle), sin(angle)));
				angle += step;

				if (points.size() != 0 && (points[0] == point || points[points.size() - 1] == point))
					continue;
				
				points.push_back(point);
			}

			Object nPoints = Object::New(env);
			for (size_t j = 0; j < points.size(); j++)
				nPoints.Set(j, wrap(env, points[j]));
			
			parts.Set(i, nPoints);
		}

		return parts;
	}

	Object Init(Env env, Object exports) 
	{
		exports.Set("step", Function::New(env, step));
		exports.Set("reset", Function::New(env, reset));
		exports.Set("observe", Function::New(env, observe));
		exports.Set("shape", Function::New(env, shape));

		return exports;
	}
}