#include <include/custom/ObservableState.hpp>

namespace soccer
{
    ObservableState::ObservableState(World world)
    {
        Object wBall = world.getObjectByName("ball");
        Object wRobot = world.getObjectByName("robot");

        robot.position = wRobot.position;
        robot.angle = wRobot.angle;
        if (wRobot.ghost)
        {
            robot.angle = 0;
            robot.position = Vec2(0, 0);
        }

        ball.position = wBall.position - wRobot.position;
        if (wBall.ghost)
            ball.position = Vec2(0, 0);
    }
}