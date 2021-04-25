// C program to demonstrate use of fork() and pipe() 
// Alonte Cuffee
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 

  
    int fd1[2]; 
    int fd2[2];  
  
    char fixed_str[] = "howard.edu";
    char fixed_str2[] = "test.com";
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    printf("Enter a string to concatenate:");
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        char concat_str[100];
        close(fd1[0]);  
  

        write(fd1[1], input_str, strlen(input_str)+1); 
        close(fd1[1]);
  

        wait(NULL); 
  
        close(fd2[1]); 
      
      
      char temp[100];
      read(fd2[0], temp, 100);
      close(fd2[0]);
      printf("Concatenated string 1: %s\n", temp);
      
      int x;
      
     for (x = 0; x < strlen(temp); x++){
       concat_str[x] = temp[x];
     }
      
      int i = strlen(concat_str);
      int j;
      
      for(j = 0; j < strlen(fixed_str2); j++){
        concat_str[i++] = fixed_str2[j];
      }
      
      concat_str[i] = '\0';
      printf("Resulting string %s\n", concat_str);
      
    } 
  
    // child process 
    else
    { 
        char concat_str[100]; 
        close(fd1[1]);  
      

        read(fd1[0], concat_str, 100); 
        close(fd1[0]);
      

        int k = strlen(concat_str); 
        int i; 
        for (i=0; i<strlen(fixed_str); i++) 
            concat_str[k++] = fixed_str[i]; 
  
        concat_str[k] = '\0';   
      
        close(fd2[0]);
  

        write(fd2[1], concat_str, strlen(concat_str)+1);
        close(fd2[1]); 

  
        exit(0); 
    } 
} 