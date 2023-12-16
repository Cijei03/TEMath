cd..

clear
Write-Host "Clean build started." -ForegroundColor Cyan

if (Test-Path -Path "./buildCache") 
{
    Remove-Item -Path "./buildCache/*" -Recurse
}
else
{
    mkdir "buildCache" | Out-Null
}

cd buildCache

Write-Host "Starting Debug build..." -ForegroundColor Cyan
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja

Write-Host "Starting Release build..." -ForegroundColor Cyan
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja

cd..

cd win64