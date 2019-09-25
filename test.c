#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

pid_t p1_pid,p2_pid,p3_pid,p4_pid,p5_pid;

int pip13[2];
    
    pipe(pip13);

    char buffer[100];
    if ((p1_pid = fork())== 0) {
        
        dup2(pip13[1],1);
        
        close(pip13[0]);
        
        printf("I am P1 and I am proud of it.\n");
        
    } else {
        
        close(pip13[1]);
        
        if ((p2_pid = fork()) == 0) {
            
            printf("I am P2 and want children!\n");
            
            if ((p3_pid = fork()) == 0) {
                
                dup2(pip13[0],0);
                
                read(pip13[0],buffer,sizeof(buffer));
                
                
                printf("P3 has received : %s",buffer);
             //   printf("I am P3. I like it.\n");
                
            } else {
                
                close(pip13[0]);
                
                wait(p1_pid);
                
                if ((p4_pid = fork()) == 0) {
                    
                    printf("I am P4. Get used to it.\n");
                    
                } else {
                    
                    printf("I am P2 and have two children!\n");
                    
                }
                
            }
            
        } else {
            
            close(pip13[0]);
            
            close(pip13[1]);
            
            printf("I am the parent process, obey or die!\n");
            
        }
        
    }

}
