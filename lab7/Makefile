# $Id: Makefile,v 1.5 2012-11-01 19:33:32-07 - - $
MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS   = gcc -MM
GRIND    = valgrind --leak-check=full

CHEADER   =        queue.h
CSOURCE   = main.c queue.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = catqueue
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}
LISTSRC   = ${SOURCES} ${DEPSFILE}
LISTING   = Listing.catqueue.ps
OUTPUT    = output*.lis
SUBMITDIR = cmps012b-wm.w13 lab7

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}

check: ${SOURCES}
	- checksource ${SOURCES}

ident : ${SOURCES}
	ident ${SOURCES}

lis : ${SOURCES} test
	mkpspdf ${LISTING} ${LISTSRC} test*.lis

clean :
	- rm ${OBJECTS} ${DEPSFILE} core test*.lis

spotless : clean
	- rm ${EXECBIN} ${LISTING:.ps=.p*}

test : ${EXECBIN}
	runprogram.perl -x testa.lis ${EXECBIN}
	valgrind --leak-check=full ${EXECBIN} >testb.lis 2>&1

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps

submit: check ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again :
	gmake spotless deps ci all lis

ifeq ("${NEEDINCL}","")
include ${DEPSFILE}
endif

