@echo off

set file=rep

if exist %file%.obj del %file%.obj 
if exist %file%.exe del %file%.exe

c:\masm32\bin\ml.exe /c /coff /Cp %file%.asm
c:\masm32\bin\link.exe /SECTION:.text,RWE /SUBSYSTEM:WINDOWS,4.0 %file%.obj

dir %file%*.*
pause