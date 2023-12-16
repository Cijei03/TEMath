cd..
cd..

clear
Write-Host "Build started." -ForegroundColor Cyan

cd buildCache

Write-Host "Starting Debug build..." -ForegroundColor Cyan
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja

cd ../scripts/win64