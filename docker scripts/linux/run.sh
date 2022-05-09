#!/bin/bash

# https://github.com/jessfraz/dockerfiles/issues/4
xhost local:root

docker run -v /tmp/.X11-unix:/tmp/.X11-unix --rm -e DISPLAY=$DISPLAY \
    -v "$(pwd)"/engine:/workspace/engine \
    -v "$(pwd)"/app:/workspace/app \
    -v /workspace/app/build \
    -v /workspace/app/node_modules \
    -v /workspace/engine/build \
    -v /workspace/app/frontend/assets \
    -it rss-dev bash

# sometimes run " docker system prune -a " to clean memory