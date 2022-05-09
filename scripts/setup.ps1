# script which downloads all necessary files, which are licensed or take a lot of space

# move to the main app directory
Set-Location $PSScriptRoot/../app

# download font
wget -O frontend/assets/viga.ttf -nc -q -o /dev/null https://fonts.gstatic.com/s/viga/v12/xMQbuFFdSaiX_QI.ttf

### download and install all node packages

# global ones
npm install -g --save-dev electron cmake-js less node-gyp

# local ones
npm install --save-dev node-addon-api

Set-Location ..

# done!