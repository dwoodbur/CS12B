#Dylan Woodbury (dwoodbur) 
# $Id: Makefile,v 1.2 2013-01-08 13:37:18-08 - - $

ALLSOURCE  = README Makefile l8stat.c
MAINCLASS  = 
CLASSES    = 
JARFILE    = 
LISTING    = ../lab8s-voidstar-generic
SUBMITDIR  = cmps012b-wm.w13 lab8

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

