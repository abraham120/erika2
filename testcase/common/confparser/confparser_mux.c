/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * CONFPARSER_MUX
 *
 * This program receives its input from the command line and prints
 * out a permutation of its imputs.
 *
 * Example: confparser_mux VAR1=a,b VAR2=c
 *
 * (note: identifiers passed through the command line may only be
 * alfanumeric)
 *
 * Output: VAR1_a_VAR2_c VAR1_b_VAR2_c
 *
 * I know this implementation is not so efficient, but it doesn't
 * matter ;-)
 */

#define MAX_VARS 100
#define MAX_CONF 10
#define MAX_STRING 200

#define NOPRINT

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* note: strings are taken directly from the command line arguments :-) */

struct variable_t {
  char *name;
  char *conf[MAX_CONF];
  int nconf;
};

struct variable_t variables[MAX_VARS];
int nvariables;

void parse_commandline(int argc, char **argv);
void print_permutations(void);
void usage(void);

int main(int argc, char **argv)
{
  parse_commandline(argc,argv);

  if (nvariables) {
    print_permutations();
    return 0;
  }
  else {
    usage();
    return 1;
  }
}

/* --------------------------- */

/* 
   This function parses the command line and puts appropriate pointers inside the "variables" array.
   If an error occurred, nvariables is set to 0, otherwise it is set to the number ov variables read.
*/
void parse_commandline(int argc, char **argv)
{
  int i; /* index on the arguments */

  for (i=1; i<argc; i++) {
    /* argv[i] is the current parameter */
    int l;   /* length of the current parameter */
    int j;   /* index inside the current parameter */
    int ok;  /* a flag */
    char *c; /* scratch pointer */
    int c_count; /* counter of chars into a configuration */
      
    l = strlen(argv[i]);

    /* all starts with a variable */
    variables[nvariables].name = argv[i];

    /* searches for "=" */
    /* ----------------------------------------- */
    j = 0;
    ok = 0;
    do {
      if (isalnum((int)argv[i][j]))
	j++;
      else if (argv[i][j] == '=') {
	argv[i][j] = 0; /* isolate the string */
	j++;
	ok = 1;
      }
      else
	goto error;

    } while (argv[i][j] && !ok);

    /* there must be always a "=", and the string must not end after the '=' */
    if (!argv[i][j]) goto error;
    if (!ok) goto error;
    

    /* searches for "," */
    /* ----------------------------------------- */
    variables[nvariables].nconf = 0;

    c = &argv[i][j];
    c_count=0;
    do {
      if (isalnum((int)argv[i][j]))
	j++, c_count++;
      else if (argv[i][j] == ',') {
	argv[i][j] = 0; /* isolate the string */
	j++;
	variables[nvariables].conf[variables[nvariables].nconf] = c;
	variables[nvariables].nconf++;
	c = &argv[i][j];
	c_count=0;
      }
      else
	goto error;

    } while (argv[i][j]);

    if (c_count) {
      /* last configuration */
      variables[nvariables].conf[variables[nvariables].nconf] = c;
      variables[nvariables].nconf++;
    }
    else
      goto error;

    nvariables++;
  }

  return;

  /* ugly, I know! */
 error:
  nvariables = 0;
}


void print_permutations_recursive(int n, int end, char *s);

/* For each variable, print all the possible combinations */
void print_permutations(void)
{
  char *s = "";
#ifndef NOPRINT
  fprintf(stderr,"MUX: \"");
#endif
  print_permutations_recursive(0, nvariables, s);
#ifndef NOPRINT
  fprintf(stderr,"\"\n");
#endif
}

void print_permutations_recursive(int n, int end, char *s)
{
  int i;
  char mystring[MAX_STRING];

  for (i=0; i<variables[n].nconf; i++) {
    strcpy(mystring,s);
    strcat(mystring, variables[n].name);
    strcat(mystring,"_");
    strcat(mystring, variables[n].conf[i]);
    if (n+1<end) {
      strcat(mystring,"_");
      print_permutations_recursive(n+1, end, mystring);
    }
    else {
#ifndef NOPRINT
      fprintf(stderr,"%s ", mystring);
#endif
      printf("%s\n", mystring);
    }
  }
}

void usage(void)
{
  fprintf(stderr,
	  "---------------------------------------------------------------------------\n"
	  "CONFPARSER\n\n"
	  "Usage: This program receives its input from the command line\n"
	  "and prints out a permutation of its inputs.\n\n"
	  "Example: confparser_mux VAR1=a,b VAR2=c\n\n"
	  "(note: identifiers passed through the command line may only be alfanumeric)\n\n"
	  "Output: VAR1_a_VAR2_c VAR1_b_VAR2_c\n"
	  "---------------------------------------------------------------------------\n");
}
