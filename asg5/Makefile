# $Id: Makefile,v 1.1 2012-11-16 18:04:00-08 - - $

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
EXECBIN   = hashfn
HASHSRC   = hashfn.c ../code/strhash.c
LISFILES  = hashfn.c ../code/strhash.h ../code/strhash.c \
	    Makefile pspell.perl
LISTING   = Listing.misc.ps
HASHOUT   = hashfn.out

TESTDATA  = 0 9 A Z a z foo bar baz qux \
            quux quuux quuuux quuuuux quuuuuux quuuuuuux quuuuuuuux

CHEADER   = debugf.h hashset.h strhash.h yyextern.h
CSOURCE   = debugf.c hashset.c spellchk.c strhash.c

SUBMITS   = ${CHEADER} ${CSOURCE} Makefile README scanner.l
PROJECT   = cmps012b-wm.w13 asg5

all : ${EXECBIN}

% : %.c
	- cid + $<
	- checksource $<
	${GCC} -o $@ ${HASHSRC}

ci : ${LISFILES}
	- checksource ${LISFILES}
	- cid + ${LISFILES}

lis : ${LISFILES} ${HASHOUT}
	mkpspdf ${LISTING} ${LISFILES} ${HASHOUT}

${HASHOUT} : hashfn
	hashfn ${TESTDATA} * >${HASHOUT}

spotless :
	- rm ${EXECBIN} ${HASHOUT}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}
