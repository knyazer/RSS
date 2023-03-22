#!/bin/bash

cd addon

node-gyp configure

# Compile addon
node-gyp build

# Download viga font
wget -O frontend/assets/viga.ttf -nc -q -o /dev/null https://fonts.gstatic.com/s/viga/v12/xMQbuFFdSaiX_QI.ttf

# Compile less to css
lessc frontend/styles.less frontend/assets/styles.css
