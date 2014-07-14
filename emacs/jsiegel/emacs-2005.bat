set HOSTNAME=chijsiegel490xp
set PATH=C:\local\emacs-21.3\bin;%PATH%
set HOME=C:\
cd /D "C:\Program Files\Microsoft Visual Studio 8\VC"
call .\vcvarsall x86
set TORINO=C:\repos\torino
cd /D %TORINO%
runemacs.exe
