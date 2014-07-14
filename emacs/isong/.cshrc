
setenv TROLLTECH /usr/local/Trolltech/Qt-4.4.0-beta1

setenv MPIDIR /opt/vltmpi/OPENIB/mpi
setenv LD_LIBRARY_PATH "/usr/tibco/tibrv/lib:/usr/lib/debug:.:/usr/lib/atlas:/home/isong/repos/torino/release/lib/linux"

setenv ROOT /home/isong/repos/mercury
setenv THIRDPARTY /home/isong/repos/ThirdParty

# setenv JUMPDATA /import/data/data
setenv DISPLAY chiisong490tt:0.0

#setenv DISPLAY 10.2.20.97:0.0
setenv HOSTNAME `hostname`
alias postcmd echo -n "]2\;${HOSTNAME}:${user}"

# setenv LSAPI_KEYDIR /home/isong/repos/torino/src/service/eCBOT/ECBOTPriceServerV2.0/ECBOTRelease/Keys
#setenv LSAPI_KEYDIR /home/isong/repos/services/archive3/matif
setenv LSAPI_KEYDIR /home/isong/repos/services/archive5/ecbot

if ( ! ${?TORINO} ) then

setenv TORINO ~/repos/torino

foreach i ( $TORINO/release/{lib,sbin,bin}/{linux,x86_64} /usr/local/lib /usr/lib /lib /usr/tibco/tibrv/lib /home/isong/repos/ThirdParty/TIBCO/7.5.1/linux24gl23/TIBRV/lib /usr/local/jump/gcc-4.2.0/lib)
    setenv LD_LIBRARY_PATH "${i}:${LD_LIBRARY_PATH}"
end

# setenv LSAPI_KEYDIR /home/isong/repos/torino/src/service/eCBOT/ECBOTPriceServerV2.0/ECBOTRelease/prodkeys
# Construct PATH environment variable
setenv PATH "."
foreach i ( $TROLLTECH/bin /home/isong/repos/mercury/bin $MPIDIR/bin  /opt/SUNWspro/bin /usr/openwin/bin /usr/ccs/bin /usr/sfw/bin /usr/tibco/tibrv/bin $TORINO/tools/misc $TORINO/{tmp/test,release}/{bin,sbin}/{linux,x86_64} /usr/X11R6/bin /usr/bin /usr/sbin /bin /sbin /usr/local/bin /usr/local/jump/bin /home/isong/bin /usr/local/jump/bison/bin )
    setenv PATH "${i}:${PATH}"
end

setenv MANPATH /usr/man
foreach i ( /usr/share/man /usr/X11R6/man /usr/local/man  )
    setenv MANPATH "${i}:${MANPATH}"
end

setenv JUMPDISCOVERYOPTS "srcAddr=eth0"


# Setup java
foreach i ( /usr/local/java1.5.x /usr/java/jdk1.5.0_10)
  if ( -e $i ) then
    set i=`csh -c "cd $i;pwd"`
#    echo JAVA at $i
    setenv JAVADIR $i
    setenv JAVA_HOME $i
    setenv PATH "${JAVADIR}/bin:${PATH}"
    setenv CLASSPATH ".:${TORINO}/release/java"
    foreach j ( `find ${TORINO} -name java_d -print` $JAVADIR/jre/lib/*.jar )
      if ( -e $j ) then
        setenv CLASSPATH "${CLASSPATH}:${j}"
      endif
    end
    break
  endif
end

setenv EDITOR /usr/bin/vim
setenv JoshSiegel 1
setenv BUILDTAG devel

endif

limit core 0

set history=100 notify showdots filec symlinks=ignore
set autolist=beepnever listmax=50 correct=cmd autoexpand
set fignore = ( .o .dvi .bbl .aux .log .blg .dlog .ps \~ .orig .elc .mak .vcp )
set time = ( 2 "user=%U secs  system=%S secs  elapsed=%E secs  memory=%K Kb" )
if ( ${?prompt} ) then
  set prompt = "[%n@%m %c2] "
endif

alias start 'xterm -title "$shell:t @ $HOST" &'
