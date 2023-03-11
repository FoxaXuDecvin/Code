@echo off
if %RUN%A == AA goto FAILED
:BACKUI
cls
set RUN=A
echo= Select Mode
echo= a   -Create CA
echo= b   -MakeCert
set/p "A=>"
if %A%==a goto CAMode
if %A%==b goto MKCT
goto BACKUI

:CAMode
set/p "CN=CN >"
set/p "Email=Email >"
set/p "EndDate=EndDate mm/dd/yyyy >"
set/p "Password=Password >"
set/p "SavePath=SavePath >"
start cmd /c makecert -r -pe -n "CN=%CN%,Email=%Email%" -ss CA -sr CurrentUser -a sha256 -cy authority -sky signature -sv %SavePath%~Key.pvk %SavePath%~Cert.cer /e %EndDate% 1>nul 0>nul
pause
start cmd /c pvk2pfx -pvk %SavePath%~Key.pvk -spc %SavePath%~Cert.cer -pfx %SavePath% -po %Password% 1>nul 0>nul

echo= SUCC
pause
exit

:MKCT
set/p "CAPVK=CA PVK file >"
set/p "CACER=CA CER file >"
set/p "CN=CN >"
set/p "Email=Email >"
set/p "EndDate=EndDate mm/dd/yyyy >"
set/p "Password=Password >"
set/p "SavePath=SavePath >"
start cmd /c makecert -pe -n "CN=%CN%,Email=%Email%" -a sha256 -cy end -sky signature -ic %CACER% -iv %CAPVK% -sv %SavePath%~Key.pvk %SavePath%~Cert.cer /e %EndDate% 1>nul 0>nul
pause
start cmd /c pvk2pfx -pvk %SavePath%~Key.pvk -spc %SavePath%~Cert.cer -pfx %SavePath% -po %Password% 1>nul 0>nul

echo= SUCC
pause
exit

:FAILED
cls
echo= ERROR RESET
pause
exit