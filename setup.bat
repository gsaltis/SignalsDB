@echo off
doskey m=make -j 4 -f Makefile.Release $T make -j 4 -f Makefile.Debug
doskey mr=make -j 4 -f Makefile.Release
doskey sik=pskill SignalsDB
doskey md=make -j 4 -f Makefile.Debug
doskey mc=make cleanall
doskey mq=qmake
doskey si=release\SignalsDB $*
doskey sid=color 07 $t gdb debug\SignalsDB $*
title Signals Database
git status | head -1 | gawk "{print $3;}"> .branch.txt
set /p P=<.branch.txt
prompt SignalsDB [%p%] : 
del .branch.txt

