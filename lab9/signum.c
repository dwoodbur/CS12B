// $Id: signum.c,v 1.7 2013-03-08 18:32:11-08 - - $

#include <math.h>
#include <stdio.h>
#include <values.h>

int signum (int num) {
   return (num > 0) - (num < 0);
}

int fsignum (double num) {
   return (num > 0) - (num < 0);
}

void test (int num) {
   printf ("signum (%d) = %d\n", num, signum (num));
}

void ftest (double num) {
   printf ("fsignum (%.16g) = %d\n", num, fsignum (num));
}

char *strbool (int value) {
   return value ? "true" : "false";
}

int main() {
   test (30);
   test (-5);
   test (10);
   test (INT_MIN);
   test (0);
   test (INT_MAX);
   ftest (M_PI);
   ftest (M_E);
   ftest (6.02e23);
   ftest (DBL_MIN);
   ftest (0);
   ftest (DBL_MAX);
   ftest (-INFINITY);
   ftest (INFINITY);
   ftest (NAN);
   printf ("(NAN == NAN) = %s\n", strbool (NAN == NAN));
   printf ("(NAN != NAN) = %s\n", strbool (NAN != NAN));
   return 0;
}
