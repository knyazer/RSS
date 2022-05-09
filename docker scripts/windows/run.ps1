# You need to follow this tutorial https://dev.to/darksmile92/run-gui-app-in-linux-docker-container-on-windows-host-4kde
# To succesfully run the developer container on Windows

# Replace 172.28.128.1 with your ip
set-variable -name DISPLAY -value 172.21.11.195:1.0
set-variable -name PATH_TO_ENGINE -value (-join($pwd.path, "\engine") -replace '[\\/]', '/')
set-variable -name PATH_TO_APP -value (-join($pwd.path, "\app") -replace '[\\/]', '/') 
docker run -ti --rm -e DISPLAY=$DISPLAY -v ${PATH_TO_ENGINE}:/workspace/engine -v ${PATH_TO_APP}:/workspace/app -v /workspace/app/build -v /workspace/app/node_modules -v /workspace/engine/build -v /workspace/app/frontend/assets -it rss-dev bash