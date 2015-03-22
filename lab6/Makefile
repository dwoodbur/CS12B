# $Id: Makefile,v 1.9 2013-02-07 19:09:28-08 - - $

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
CSOURCES = lsort.c
SOURCES  = ${CSOURCES} Makefile
EXECBINS = lsort
LISTING  =
SUBMIT   = submit cmps012b-wm.w13 lab6

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

