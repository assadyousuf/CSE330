#include "threads.h"
#include <unistd.h>


TCB_t head;
int globalVar=0;
void thread1(void){ 
   	
    int localVar=0;
    while(1){
  
            head=*head.next;
        
        globalVar=globalVar+1;
        localVar=localVar+1;
        printf("\n This is %d th execution of thread 1 with global var value %d \n",localVar,globalVar);
        sleep(1);
        yield(&head);
    }
    
}

void thread2(void){
    int localVar=0;
    while(1){
        head=*head.next;
        globalVar=globalVar+2;
        localVar=localVar+1;
        printf("\n This is %d th execution of thread 2 with global var value %d \n",localVar,globalVar);
        sleep(1);
        yield(&head);
    }
}

void thread3(void){
    int localVar=0;
    while(1){
        head=*head.next;
        globalVar=globalVar+3;
        localVar=localVar+1;
        printf("\n This is %d th execution of thread 2 with global var value %d \n",localVar,globalVar);
        sleep(1);
        yield(&head);
    }
}

int main(){
    InitQueue(&head);
    printf("\n Done with initalization\n");
    start_thread(&thread1, &head);
    start_thread(&thread2, &head);
    start_thread(&thread3, &head);
    
    run(&head);
    
}
