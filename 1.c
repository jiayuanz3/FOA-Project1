

/* Solution to comp10002 Assignment 1, 2019 semester 2.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Jiayuan Zhu 1067734
   Dated:     13/09/2019

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#define MAXCHARS 200     /* Max characters per word */
#define MAXWORDS 10000   /* Max words */
#define LINECHAR 999 /* Max characters per input line */
#define MAXLINE 50    /* Initial max words per line*/
#define MARGIN 4    /* Initial margin */
#define NEWLINE 1   /* one "\n" is needed to start new line */
#define NEWPARAGRAPH 2  /* two "\n" are needed to start new paragraph */
#define NUMSTART 3   /* text or number start in position 3 */
#define HEADSTART 5    /* text start in position 5 in heading function */
#define TRUE 1    /* statement is true */
#define FALSE 0    /* statement is false */
#define EQUAL 0    /* return zero when two strings are equal */
#define MAXTITLE 5 /* Maxium five level headings */

typedef char word_t[MAXCHARS + 1];
int getword(word_t W, int limit, int *newline);
int mygetchar();
int change(char *string);
void printspace(int margin, int *alreadyprint, int *front);
void title(char *string, int head[], int margin, int maxline, int *alreadyprint, 
	int *front, int *perline);
void central(char *string, int *margin, int *maxline, int *alreadyprint, 
	int *front, int *perline);
void countnewline(char *string, int *margin, int *maxline, int *printline, 
	int *boccur, int *poccur);
void printnewline(int *printline, int *alreadyprint, int *front, int *perline, 
	int margin, int *boccur, int *poccur, char *string, int i, int word, 
	int maxline, int stop);
void printnewword(int stop, char *string, int *perline, int *alreadyprint, 
	int *i);
void headingarray(int A[], int n);
void removespace(char *string);
void heading1(int maxline, int margin);
void allheadings(char *string, int head[], int maxline, int margin);
int others(char* string, int *stop, int *margin, int *maxline, int *printline, 
	int *boccur, int *poccur);
void printmargin(int margin, int *alreadyprint, int *front);
int getsingleword(word_t W, int limit, char *string, int *k);




int
/* Format text inculding some commmands */
main(int argc, char *argv[]) {
	word_t one_word, single_word, all_words[MAXWORDS];
	int word = 0, i = 0;
	int perline = 0, printline = 0, alreadyprint = 2;
	int stop = FALSE, front = FALSE;
	int maxline = MAXLINE, margin = MARGIN;  
    int boccur = FALSE, poccur = FALSE; 
    int head[MAXTITLE];
    int line_character = 0;
    int newline = TRUE;
    int k;
    int singlespace=1;
    headingarray(head, MAXTITLE);
	

	while (getword(one_word, MAXCHARS, &newline) != EOF) {
			
			if (one_word[0] == '.') {
			if ((one_word[1] == 'h')) {
				title(one_word, head, margin, maxline, &alreadyprint, 
        	    &front, &perline);
        	}
            else if (one_word[1] == 'c') {
    	        central(one_word, &margin, &maxline, &alreadyprint, 
		    	   &front, &perline);
	        }
	        else if (one_word[1] == 'l') {
	        	margin = change(one_word);
	        	printspace(margin, &alreadyprint, &front);
	        	perline =0;
	        }
	        else if (one_word[1] == 'w') {
	        	maxline = change(one_word);
	        	printspace(margin, &alreadyprint, &front);
	        	perline=0;
	        }
	        else if (one_word[1] == 'b') {
	        	if ((alreadyprint <2) && (boccur == 0)) {
	        	printf("\n");
	        	boccur =1;
	        	perline=0;
	        	front =0;
	        }
	        }
	        else if (one_word[1] == 'p') {
	        	if (poccur == 0) {
	        		printspace(margin, &alreadyprint, &front);
	        	}
	        	perline =0;
	        }
	      }
	      else {
	      	  k=0;
	      	  boccur =0;
	      	  
	      	  while (k<strlen(one_word)) {
	      	  	  if (front == 0) {
	      	  	  	  printmargin(margin, &alreadyprint, &front);
	      	  	  	  singlespace = 1;
	      	  	  	  front = 1;
	      	  	  }  
	      	  	  if (singlespace ==0) {
	      	  	  	  printf(" ");
	      	  	  	  perline +=1;
	      	  	  	 }
	      	      getsingleword(single_word, MAXCHARS, one_word, &k);
	      	      if (perline + strlen(single_word) <= maxline) {
	      	          printf("%s", single_word);
	      	          perline = perline +strlen(single_word);
	      	          singlespace = 0;
	      	          alreadyprint = 0;
	      	       }
	      	       else {
	      	       	   printf("\n");
	      	       	   front = 0;
	      	       	   printmargin(margin, &alreadyprint, &front);
	      	       	   printf("%s", single_word);
	      	           perline = strlen(single_word);
	      	           singlespace =0;
	      	           alreadyprint =0;
	      	       }
	      	  
	}}}

	return 0;
}


int
getsingleword(char W[], int limit, char *string, int *k) {
	int len=0, maxk;
	maxk = strlen(string);
	while (((string[*k] == ' ' )|| (string[*k]=='	')) && (*k<maxk)) {
		*k +=1;
	}
	
	while ((string[*k] != ' ') && (string[*k] !='	') && (*k<maxk)) {
		W[len++] = string[*k];
		*k +=1;
	}
	W[len]='\0';
	
	return 0;
}
	
	

	



/* Author: Alistair Moffat, adapted to read each word and the whole command line
Source: https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/getword.c */
int
/* Get seperate words or whole commands and put into an array */
getword(char W[], int limit, int *newline) {
	int c, len = 0;
	/* Skip over blanks and tabs */
	while (((c = mygetchar()) != EOF) && (c=='\n')) {	
	}
	if (c==EOF) {
		return EOF;
	}
	W[len++] = c;
	while (len < limit && (c = mygetchar()) != EOF && (c != '\n')) {
		
		W[len++] = c;
		}
	
    W[len] = '\0';		
	return 0;
}



void
/* Determine how to start new paragraph */
printspace(int margin, int *alreadyprint, int *front) {
	while (*alreadyprint <2) {
		printf("\n");
		*alreadyprint +=1;
		*front = FALSE;
	}
 }	
 
 
void
printmargin(int margin, int *alreadyprint, int *front) {
	int i;
	/* Print margin for the new strat paragraph */
	if (*front == FALSE) {
	    for (i = 0; i < margin; i++) {
		    printf(" ");
        }
        *front = TRUE;
    }
}


void
/* Initialize ordinal number of headings */
headingarray(int A[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		A[i] = 0;
	}
}

void
/* Print boundary for first level heading */
heading1(int maxline, int margin) {
	int j;
	/* Print heading boundary */
	for (j = 0; j < maxline; j++) {
        printf("-");
	}
	printf("\n");
    /* Print margin and ordinal number */
    for (j = 0; j < margin; j++) {
	    printf(" ");
    }
}
           



void
/* Print ordinal number when it's a heading */
allheadings(char *string, int head[], int maxline, int margin) {
	int j, level;
	level = string[NUMSTART] - '0';
	if (level == 1) {
		heading1(maxline, margin);
	}
	head[level - 1] += 1;
	/* Set the backword headings to 0 */
	for (j = MAXTITLE; j >= level; j--) {
	   	head[j] = 0;
	}
	/* Print the ordinal number */
    for (j = 0; j < level - 1; j++) {
	    printf("%d.", head[j]);
	} 	
	printf("%d ", head[level - 1]);
}
	


	
void 
/* Turn tab or multiple spaces into single space and print heading */
removespace(char *string) {
	int space =TRUE, i;
	i = HEADSTART;
	/* Skip tab or multiple spaces at start */
	while ((string[i] == ' ') || (string[i] == '	')) {
		i++;
	}
	/* If multiple whitespaces exist, just print one */
	while (i < strlen(string)) {		
		if (((string[i] == '	') || (string[i] == ' ')) && (space == FALSE)) {
			printf(" ");
		    space = TRUE;
	    }
	    /* Print the word */
	    else if ((string[i] != '	') && (string[i] != ' ')){
		    printf("%c", string[i]);
		    space = FALSE;
		}
		i++;
    }
} 




void
/* Determine how to execute heading command */
title(char *string, int head[], int margin, int maxline, int *alreadyprint, 
	int *front, int *perline) {
    printspace(margin, alreadyprint, front);
    printmargin(margin, alreadyprint, front);
    /* Print ordinal number when it's a heading */
	allheadings(string, head, maxline, margin);  	
    /* Turn tab or multiple spaces into single space and print heading */			
	removespace(string);
	*alreadyprint = 0;
    /* Start new paragraph */
	printspace(margin, alreadyprint, front);
    *alreadyprint = 2;
    *perline = 0;
}

void
/* Make sentence in the middle */
central(char *string, int *margin, int *maxline, int *alreadyprint, 
	int *front, int *perline) {
	int j, k, m = 0, middle, space = TRUE;
	char A[MAXCHARS];	
	/* If already has no "\n", then starts the new line */
	if (*alreadyprint == 0) {
	   	printf("\n");
	   	*front = FALSE;
    }      
    /* If no margin has printed, then print margin */
	if (*front == FALSE){
		for (j = 0; j < *margin; j++) {
		    printf(" ");
		}
		*front = TRUE;
    }       
    k = NUMSTART;
    /* Skip tab or multiple spaces at start */
	while ((string[k] == ' ') || (string[k] == '	')) {
		k++;
	}
	/* Turn tab or multiple spaces into single space and then put into array */
	while (k < strlen(string)) {
		if (((string[k] == '	') || (string[k] == ' ')) && (space == FALSE)) {
			A[m++] = ' ';
			space = TRUE;
		}
	    else if ((string[k] != '	') && (string[k] != ' ')){
			A[m++] = string[k];
			space = FALSE;
		}
		k++;
    }
    A[m] = '\0';   
    /* Calculate number of spaces before title and print title */
    middle = (*maxline - (strlen(A))) / 2;
    for (j = 0; j < middle ; j++) {
		printf(" ");
    } 
    printf("%s", A);
    /* Start a new line */
    printf("\n");
    *alreadyprint = 1;
    *perline = 0;
    *front = FALSE;
}


int
/* Determine new margin or max words per line */
change(char *string) {
	int totalnum, i = 0, j = 0;
	char A[MAXCHARS];	
	/* Find the start of first digit */
	while (i < strlen(string)) {
		if (isdigit(string[i])) {
			break;
		}
		i++;
	}
	/* Find the whole digit and put into an array */
	while (isdigit(string[i])) {
		A[j++] = string[i];
		i++;
	}
	A[j] = '\0';
	/* Get the number form from string */
	totalnum = atoi(A);
	return totalnum;
}


/* Author: Alistair Moffat, 
Source: https://people.eng.unimelb.edu.au/ammoffat/teaching/10002/ass1/ */
int
/* Resolve trouble with newline characters */
mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
	}
	return c;
}

/* algorithms are fun */