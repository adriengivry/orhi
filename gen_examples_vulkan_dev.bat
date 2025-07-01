@echo off
SET version=%~1%
if "%~1"=="" SET version="vs2022"

SET premake_path="%~dp0\tools\premake5.exe"

pushd "%~dp0\examples"
call %premake_path% %version% --compile-vulkan --gfxapi=vulkan
popd
