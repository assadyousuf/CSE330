#include "q.h"
void start_thread(void (*function)(void), TCB_t *head){
    void *stackP=(void *)malloc(8192);
    if(head->payload!=0){
        TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
        init_TCB(tcb,function,stackP,8192);
        tcb->payload=1;
        AddQueue(head,tcb);
    }else {
        printf("\n Entering the else \n");
        init_TCB(head,function,stackP,8192);
        head->payload=1;
        
    }
    
    
}

void run(TCB_t *head){
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(head->context));
    printf("\n Done get context: %d\n",head->payload);
}

void yield(TCB_t *head)
{
    TCB_t *temp = (TCB_t*) malloc(sizeof(TCB_t));
    temp->context=head->context;
    temp->next=head->next;
    temp->prev=head->prev;
    temp->payload=head->payload;
    Rotate(head);
    head=head->next;
    swapcontext(&(temp->context), & (head->context));
    
}
