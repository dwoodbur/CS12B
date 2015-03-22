#Dylan Woodbury (dwoodbur) 
# $Id: Makefile,v 1.2 2013-01-08 13:37:18-08 - - $

ALLSOURCE  = README Makefile numsort.c linesort.c inssort.h inssort.c
MAINCLASS  = 
CLASSES    = 
JARFILE    = 
LISTING    = ../lab9c-voidstar-generic
SUBMITDIR  = cmps012b-wm.w13 lab9
GCC        = gcc -g -O0 -Wall -Wextra -std=gnu99
NEXECBIN = numsort
SEXECBIN = linesort
EXECBINS = ${NEXECBIN} ${SEXECBIN}

all : ${JARFILE}
	- checksource ${ALLSOURCE}

%.o : %.c
	- checksource $<
	${GCC}$< -o $@


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

