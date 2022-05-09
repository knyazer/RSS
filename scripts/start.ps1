# script to start the application, needed to be ran only after setup

Set-Location $PSScriptRoot/../app/addon

node-gyp configure
node-gyp build

Set-Location $PSScriptRoot/../app

lessc frontend/styles.less frontend/assets/styles.css

electron .

Set-Location $PSScriptRoot/..
