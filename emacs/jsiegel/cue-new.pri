ls      dir /ogn $*
-       popd $*
pd      pushd $*

up      if "$*"=="" (cd ..) else (for /L %i in (1,1,$*) do cd ..)
..      cd ..\$*
...     cd ..\..\$*
....    cd ..\..\..\$*

d       pushd %userprofile%\desktop\$*

root    pushd c:\repos\$*
r       pushd c:\repos\$*
torino  pushd C:\repos\torino\$*
spd     pushd C:\repos\torino\src\lib\spd\$*
traders pushd C:\repos\traders\$*
sb      pushd C:\repos\traders\stormbirds\$*
src     pushd C:\repos\traders\stormbirds\src\$*
inc     pushd C:\repos\torino\release\include\$*
