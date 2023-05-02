#ifndef LIPIEC_PROJEKT_1_CHAR_STACK_H
#define LIPIEC_PROJEKT_1_CHAR_STACK_H

typedef struct charStackItem{
    char key;
    struct charStackItem* pNext;
} CharStackItem;

CharStackItem** createCharStack();
void push_char(CharStackItem** pStack, char x);//włóż na stos
char pop_char(CharStackItem** pStack); //zdejmij ze stosu i zwróć
char top_char(CharStackItem** pStack); //zwróć szczytowy element stosu;
void del_char(CharStackItem** pStack); //usuń szczytowy;
int isEmpty_char(CharStackItem** pStack);//zwraca 1, jeśli stos pusty

// Extra ode mnie
void printCharStack(CharStackItem **pStack);

#endif
