@echo off
Echo "Building Everything..."

pushd library
Echo "Building lib..."
CALL build.bat
popd
if %ERRORLEVEL% NEQ 0 (echo Error Level: %ERRORLEVEL% && exit)

pushd program
Echo "Building prog..."
CALL build.bat
popd
if %ERRORLEVEL% NEQ 0 (echo Error Level: %ERRORLEVEL% && exit)


Echo "All binaries built successfully..."