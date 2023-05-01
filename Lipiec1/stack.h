#ifndef LIPIEC_PROJEKT_1_STACK_H
#define LIPIEC_PROJEKT_1_STACK_H

#define MAX_STACK_LENGTH 64

typedef struct tagStackItem{
    char key;
    struct tagStackItem* pNext;
} StackItem;

StackItem** createStack();
void push(StackItem** pStack, char x);//włóż na stos
char pop(StackItem** pStack); //zdejmij ze stosu i zwróć
char top(StackItem** pStack); //zwróć szczytowy element stosu;
void del(StackItem** pStack); //usuń szczytowy;
int isEmpty(StackItem** pStack);//zwraca 1, jeśli stos pusty

#endif
