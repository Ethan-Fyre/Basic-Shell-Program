/* project1.c
 * January 31, 2018
 * Ethan Sayles
 * 
 * Purpose: Create a basic shell
 */

#include <stdio.h>        
#include <stdlib.h>    /* malloc */
#include <sys/types.h> /* for fork */
#include <sys/wait.h>  /* for waitpid */
#include <unistd.h>    /* for fork and execvp */
#include <string.h>    /* string libraries */

#define STR_SIZE 256  /* size of a string */
#define MAX_NUM_ARGS 256
#define BUFFER_LEN 256

int main(void)
{
    /* Variable declarations */
    char **input_args = NULL;    // array for user input
    int i = 0;                   // loop variable
    int pid = 0;
    int ret_val = 0;
    char input = ' ';
    int input_amount = 0;
    char c = ' ';
    int spot = 0;
    int spot2 = 0;
    int evenodd = 0;

    //Assign memory for all the parts of the input_args array
    if (input_args != NULL)
    { 
        for (i=0; i < MAX_NUM_ARGS; i++)
        {
            free(input_args[i]);
        }
        free(input_args);
        input_args = NULL;
    }
    input_args = (char **)malloc(sizeof(char *) *BUFFER_LEN);
    if (input_args == NULL)
    {
        exit(0);
    }
    
    for (i = 0; i < MAX_NUM_ARGS; i++)
    {
        input_args[i] = NULL;
        input_args[i] = (char*)malloc(sizeof(char) *BUFFER_LEN);
        if (input_args[i] == NULL)
        {
            exit(0);
        }
        input_args[i] = "";
    }    
    
    //Shell prompt 
    printf("Ethan's Shell: ");
     while (c != '\n')
    {
        c = getc(stdin);
        if (c != ' ')
        {
            input_args[spot][spot2] = c;
            input_args[spot][spot2+1] = '\0';
            spot2 += 1;
        }
        if (evenodd % 2 == 0)
        {
            if (c == ' ')
            {   
                evenodd += 1;
                spot += 1;
            }
        }
    } 
    input_args[spot] = NULL; 
    
    //Test the shell for capability to run commands
    /* input_args[0] = "ls\0";
    input_args[1] = "-al\0";
    input_args[2] = NULL; */

    //Make a child and have that child perform a test run
    pid = fork();
    if (pid == 0)
    { 
        ret_val = execvp(input_args[0], input_args);
        exit(0);
    }
    if (pid != 0)
    {
        pid = waitpid(-1,&pid, 0);
        exit(0);
    } 
   


    exit(0);
} 
