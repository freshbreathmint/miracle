@echo off

echo Making directories...
mkdir ..\src

echo Copying Workspace file...
copy "application\miracle.code-workspace" "..\"
echo Workspace file copied. Please open the workspace in Visual Studio Code.