#Dylan Woodbury (dwoodbur) 
# $Id: Makefile,v 1.2 2013-01-08 13:37:18-08 - - $

JAVASRC    = files.found grep.submit quota.size Makefile  exit255.java\
	java.libs shell.count exit1.java mkexit1 privacy
ALLSOURCE  = ${JAVASRC} Makefile README
MAINCLASS  = exit1
CLASSES    = exit1.class exit255.class
JARCLASSES = ${CLASSES}
JARFILE    = exit1
LISTING    = ../lab2u-unix-shells.ps
SUBMITDIR  = cmps012b-wm.w13 lab2

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

test : ${ALLSOURCE}
	java exit255 >255.output
	
