@echo off
SET version=%~1%
if "%~1"=="" SET version="vs2022"

SET premake_path="%~dp0\tools\premake5.exe"

pushd "%~dp0"
call %premake_path% %version% --compile-vulkan --compile-mock --gfxapi=vulkan
popd
