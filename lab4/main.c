/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: h6iqbal
 *
 * Created on February 15, 2022, 1:37 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX 100 

int i;
int j=0;
int k=0;

int set = 0;
int size;

char inp[MAX];
char cmd1[MAX];
char cmd2[MAX];

int main(int argc, char** argv)
{
    printf(" Enter Pipe Command: ");
    fgets(inp, MAX, stdin);
    size = strlen(inp) - 1;
     
    for (i=0; i<size;i++)
    {
        if (inp [i] == '|')
        {
		set =1;
		i++;
        }
        
        else if ( inp [i] != '|' && set ==0) 
        {
            cmd1[j] = inp [i];
            j++;
        }
        else {
            cmd2[k] = inp[i];
            k++;
        }
    }

    int fd[2];
    pipe(fd);
    
    if(pipe(fd)<0)
    {
        fprintf(stderr,"Error. Unable to create pipe");
        exit(1);
    }
    
    if (fork()!=0)
    {
        dup2(fd[0],0);
        close(fd[1]);
        system(cmd2);
    }
    else
    {
        dup2(fd[1],1);
        close(fd[0]);
        system(cmd1);
        exit(0);
    }
    
    return (EXIT_SUCCESS);
}
