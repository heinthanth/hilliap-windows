@echo off
@title Hilliap Installer
cls

echo.
echo Hi11i4P - Apache24, PHP7 Package for Windows
type hilliap-ascii-art.txt
echo This Script will install Hilliap Package to your PC
echo.
@pause

xcopy /E %~dp0MinGW C:\MinGW\
xcopy /E %~dp0Apache24 C:\Apache24\
xcopy /E %~dp0php C:\php\

setx path "%path%;C:\MinGW\bin;C:\Apache24\bin;C:\php"
set path="%path%;C:\MinGW\bin;C:\Apache24\bin;C:\php"

C:\Apache24\bin\httpd.exe -k install
C:\Apache24\bin\httpd.exe -k start

echo Installation Complete!
echo.
@pause