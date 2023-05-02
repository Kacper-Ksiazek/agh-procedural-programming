#include "tools.h"
#include "char_stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "config.h"

char *getMathEquationFromUser(){
    char *userInput = malloc(sizeof(char) * MAX_STACK_LENGTH);
    printf("Podaj dzialanie matematyczne: ");
    // Objasnienie co to znaczy:
    // 1. Spacja przed znakiem procenta- mowi, ze scanf_s ma ominac wszystkie znaki biale (spacje/taby) z poczatku string
    // 2. [^\n] - czytaj wszystko az (^) az do znaku nowej lini (\n)
    scanf_s(" %[^\n]", userInput);

    return userInput;
}

void validateCharacter(char c){
    // Sprawdzamy czy znak to cyfra lub operator
    if('0' <= c && c<='9' || isSimpleMathOperator(c)) return;

    // W przeciwnym razie wyrzucamy blad
    printf("Niedozwolony znak: %c !!!!",c);
    exit(1);
}

CharStackItem **transformUserInputIntoStack(char *userInput){
    CharStackItem **result = createCharStack();

    int i = 0;
    char c;

    while((c = userInput[i++])){
        if(c == ' ') continue; // Omijamy spacje
        validateCharacter(c);
        push_char(result,c);
    }

    // Sprawdzamy, czy ostatnim znakiem nie jest operator
    if(isSimpleMathOperator(top_char(result))){
        printf("Dzialanie matematyczne nie moze konczyc sie operatorem !!!");
        exit(1);
    }

    // Sprawdzamy, czy pierwszym znakiem nie jest operator
    if(isSimpleMathOperator(result[0]->key)){
        printf("Dzialanie matematyczne nie moze zaczynac sie operatorem !!!");
        exit(1);
    }

    return result;

}

int charToInt(char c) {
    return c - 48;
}

int isSimpleMathOperator(char c){
    if(c == '+' || c=='-' || c=='/' || c =='*') return 1;
    return 0;
}

float executeSimpleMathOperation(char operation, float arg1, float arg2){
    if(operation == '+') return arg1 + arg2;
    if(operation == '-') return arg1 - arg2;
    if(operation == '*') return arg1 * arg2;
    if(operation == '/'){
        if(arg2 == 0) {
            printf("Nie mozna dzielic przez 0!!!");
            exit(1);
        }
        return arg1 / arg2;
    }

    printf("Proba wykonania operacji innej niz prosta!");
    exit(1);
}