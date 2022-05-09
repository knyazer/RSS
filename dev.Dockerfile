FROM node:latest

# install electron dependencies or more if your library has other dependencies
RUN export DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install \
    cmake libx11-xcb1 libxcb-dri3-0 libxtst6 libnss3 libatk-bridge2.0-0 libcanberra-gtk-module libcanberra-gtk3-module \
    libgtk-3-0 libxss1 libasound2 libdrm-dev build-essential libgtk2.0-0 libgbm-dev curl \
    -yq

# Install infer
RUN VERSION=1.1.0; \
    curl -sSL "https://github.com/facebook/infer/releases/download/v$VERSION/infer-linux64-v$VERSION.tar.xz" \
    | tar -C /opt -xJ && \
    ln -s "/opt/infer-linux64-v$VERSION/bin/infer" /usr/local/bin/infer

# copy the source into /workspace
WORKDIR /workspace
ADD app /workspace/app
ADD engine /workspace/engine

RUN npm install -g electron cmake-js less

# Node addon api if installed not locally has some problems, idk why
RUN pwd && cd /workspace/app && npm install node-addon-api && sh install.sh && cd ..

CMD bash