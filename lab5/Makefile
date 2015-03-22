#Dylan Woodbury (dwoodbur) 
# $Id: Makefile,v 1.2 2013-01-08 13:37:18-08 - - $

ALLSOURCE  = part01.typescript part02.typescript part03.typescript part04.typescript part05.typescript part06.typescript part07.typescript part08.typescript part09.typescript part10.typescript list2.c list3.c list4.c environ.c
MAINCLASS  = 
CLASSES    = list2 list3 list4 environ
JARFILE    = 
LISTING    = ../lab5c-gdb-valgrind
SUBMITDIR  = cmps012b-wm.w13 lab5

all : ${JARFILE}
	- checksource ${ALLSOURCE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- cid + $<
	javac $<

clean :
	- rm ${JARCLASSES}

spotless : clean
	- rm ${JARFILE}

ci : ${ALLSOURCE}
	checksource ${ALLSOURCE}
	cid + ${ALLSOURCE}

lis : ${ALLSOURCE}
	mkpspdf ${LISTING} ${ALLSOURCE}

submit : ${ALLSOURCE}
	submit ${SUBMITDIR} ${ALLSOURCE}

again : ${ALLSOURCE}
	gmake spotless ci all lis

