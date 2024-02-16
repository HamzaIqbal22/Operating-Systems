/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: h6iqbal
 *
 * Created on February 6, 2022, 7:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX 50
/*
 * 
 */
int main(int argc, char** argv) {
    
    for(;;) {
        printf("Your Command>");
        char inpCmd[MAX];
        fgets(inpCmd,MAX,stdin);
        
        pid_t pid=0;
        int end = strlen(inpCmd) - 1;
        char endChar = inpCmd[end-1];
        
        int i;
        for(i=0; i<1; i++)
        {
            //parent id calling fork
            pid_t pid = fork();               
            waitpid(pid,NULL,0);
            
            if(pid != 0)
            {
                printf("PARENT, Where process id is %d\n\n", pid);
                continue;       
            }
            else
            {   
                printf("CHILD, Where process id is %d\n", pid); 
                system(inpCmd);
                if(endChar == '&')
                {
                    printf("Not Waiting for child to complete\n");
                } 
                else 
                {   
                    for(i=0; i<1; i++)
                    {
                        waitpid(pid,NULL,0); 
                    }
                    printf(" Parent waiting for child to complete\n");
                }
                exit(0);     
            }
        }  
    }
}











