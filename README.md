# RSS
Rapid Simple (Soccer) Simulator

It is an attempt to make a convenient and really slimple to use robotics simulator. Under development for now

## What to do

To build a docker container with development evironment execute ```build.sh```:
``` 
sh build.sh
``` 
or using docker command:
```
docker build -t rss-dev - < dev.Dockerfile
```

To start container with GUI available (container must be built already):
```
sh run.sh
```
To launch the app from inside the container execute the ```app/start.sh``` from the ```app``` folder:
```
cd /workspace/app
sh start.sh
```
Then you will see the GUI and some logs in console, which show that C++ addons loaded succesfully. There could be a huge number of errors, because of the docker, you can simply ignore them.


### TODOs
* Remove unnecessary AABBs from shapes
* Add support of complicated (combined) convex shapes in Shape class
* Precise collision detection (not with precision of one step)
* Impulse based collision resolution
* Angular velocities support
* Make GUI better with Mantine, probably (lowest priority for now)