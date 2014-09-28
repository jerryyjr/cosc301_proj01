/*
 *
 * author name(s), date, and other info here
 *Junrui Ye, September 28
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>

char** tokenify(const char *s) {

	
	char *str;
	str=strdup(s);
	char *t="  ";
	int index=0;
	char **array = malloc(strlen(str)*sizeof(t));
	
	t=strtok(str," \t\n");
	if (t!=NULL){
		array[0]=strdup(t);
	}
	for (int i=1;t!=NULL;i++){
		t=strtok(NULL," \t\n");	
		if (t!=NULL){	
		array[i]=strdup(t);
		}
		index=i;
    }
	array[index]=NULL;
	free(t);
	free(str);
	return array;

}

bool check_float(const char *token){
	for (int i=0;i<strlen(token);i++){
		if(token[i]=='.'){
			return false;
		}			
	}
	return true;
}

bool check_negative(const char *token){
	char *str;
	str=strdup(token);
	char *t;
	t=strtok(str,"-");

	if(isdigit(*t)){
		free(str);
		return true;
	}
	free(str);
	return false;
}

int check_valid(char *token){
	if (token==NULL){
		return 0;
	}else{
		if(token[0]=='#'){
			return 1;
		}
		if(isdigit(*token)){
			if (check_float(token)){
				
				return 2;                     //valid
			}
		}else{
			if (check_negative(token)){
				return 2;
			}
			return 3;                     //invalid
		}
	}
	

}

void append_int(struct node **head,char **tokens){
	
	int i=0;
	while (check_valid(tokens[i])!=0){
		if (check_valid(tokens[i])==1){
			break;
		}
		if (check_valid(tokens[i])==2){
			char *tmp=strdup(tokens[i]);
			list_appendsort(atoi(tmp),head);
			free(tmp);
		}
		i++;
	}
}



void process_data(FILE *input_file) {
    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function
	char input[100];
	
	struct node *head=NULL;//malloc(sizeof(struct node));
	
	while(fgets(input,100,input_file)!=NULL){
		
		char **tokens=tokenify(input);
		append_int(&head,tokens);
	}
	
	list_print(head);
	list_clear(head);
	
}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
	int who = RUSAGE_SELF;
	struct rusage usage;
	int a;

	a=getrusage(who,&usage);
	
	time_t usec;
	time_t ksec;
	usec=(usage.ru_utime.tv_usec);
	ksec=(usage.ru_stime.tv_usec);
	printf("User time: %fs\n",((double)usec)*0.000001);
	printf("System time: %fs\n",((double)ksec)*0.000001);
	
	
	
    return 0;
}
#endif
