#ifndef LIPIEC_PROJEKT_1_INT_STACK_H
#define LIPIEC_PROJEKT_1_INT_STACK_H

typedef struct tagStackItem{
    int key;
    struct tagStackItem* pNext;
} IntStackItem;

IntStackItem** createIntStack();
void push_int(IntStackItem** pStack, int x);//włóż na stos
int pop_int(IntStackItem** pStack); //zdejmij ze stosu i zwróć
int top_int(IntStackItem** pStack); //zwróć szczytowy element stosu;
void del_int(IntStackItem** pStack); //usuń szczytowy;
int isEmpty_int(IntStackItem** pStack);//zwraca 1, jeśli stos pusty

// Extra ode mnie
void printIntStack(IntStackItem **pStack);

#endif //LIPIEC_PROJEKT_1_INT_STACK_H