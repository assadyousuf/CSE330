#define _XOPEN_SOURCE 600
#include <ucontext.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TCB_t {
    struct TCB_t *next;
    struct TCB_t *prev;
    ucontext_t context;
    int payload;
} TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);// context is now cooked
}
