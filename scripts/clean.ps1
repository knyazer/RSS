# script which cleans the majority of files downloaded using setup.ps1

# move to the main app directory
Set-Location $PSScriptRoot/../app

# download font
Remove-Item frontend/assets/viga.ttf

### remove local node packages only
npm uninstall node-addon-api

# remove folder with node modules completely
Remove-Item .\node_modules -Recurse -Force -Confirm:$false

Set-Location ..

# done!