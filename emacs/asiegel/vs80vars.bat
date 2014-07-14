@echo off

set JAVA_HOME=C:/Program Files/Java/jdk1.5.0_11
set JAVADIR=C:/Program Files/Java/jdk1.5.0_11
set TORINO=F:\torino
set CLASSPATH=C:/TIBCO/TIBRV/lib/tibrvj.jar;F:/torino/release/java_d;F:/torino/temp/test/java_d
set PATH=C:\Program Files\Java\jdk1.5.0_11\bin;C:\Python;%TORINO%\release\bin\win32;%TORINO%\release\sbin\win32;%TORINO%\temp\test\bin\win32;%PATH%
set LIB=%TORINO%\release\lib\win32
set INCLUDE=%TORINO%\release\include
cd /D F:\

set VSINSTALLDIR=F:\Program Files\Microsoft Visual Studio 8
set VS80COMNTOOLS=F:\Program Files\Microsoft Visual Studio 8\Common7\Tools\

if "%1" == "" goto x86
if not "%2" == "" goto usage

if /i %1 == x86       goto x86
if /i %1 == amd64     goto amd64
if /i %1 == x64       goto amd64
if /i %1 == ia64      goto ia64
if /i %1 == x86_amd64 goto x86_amd64
if /i %1 == x86_ia64  goto x86_ia64
goto usage

:x86
if not exist "%VSINSTALLDIR%\VC\bin\vcvars32.bat" goto missing
call "%VSINSTALLDIR%\VC\bin\vcvars32.bat"
goto :eof

:amd64
if not exist "%VSINSTALLDIR%\VC\bin\amd64\vcvarsamd64.bat" goto missing
call "%VSINSTALLDIR%\VC\bin\amd64\vcvarsamd64.bat"
goto :eof

:ia64
if not exist "%VSINSTALLDIR%\VC\bin\ia64\vcvarsia64.bat" goto missing
call "%VSINSTALLDIR%\VC\bin\ia64\vcvarsia64.bat"
goto :eof

:x86_amd64
if not exist "%VSINSTALLDIR%\VC\bin\x86_amd64\vcvarsx86_amd64.bat" goto missing
call "%VSINSTALLDIR%\VC\bin\x86_amd64\vcvarsx86_amd64.bat"
goto :eof

:x86_ia64
if not exist "%VSINSTALLDIR%\VC\bin\x86_ia64\vcvarsx86_ia64.bat" goto missing
call "%VSINSTALLDIR%\VC\bin\x86_ia64\vcvarsx86_ia64.bat"
goto :eof

:usage
echo Error in script usage. The correct usage is:
echo     %0 [option]
echo where [option] is: x86 ^| ia64 ^| amd64 ^| x86_amd64 ^| x86_ia64
echo:
echo For example:
echo     %0 x86_ia64
goto :eof

:missing
echo The specified configuration type is missing.  The tools for the
echo configuration might not be installed.
goto :eof

:eof
