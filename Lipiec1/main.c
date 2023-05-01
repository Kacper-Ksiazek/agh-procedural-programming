#include "stdio.h"
#include "stack.h"
#include "stdlib.h"

void printStack(StackItem **pStack){
    printf("\n");
    StackItem *element = pStack[0];

    while(element != NULL){
        printf("%c", element->key);
        element = element->pNext;
    }
}

int isSimpleMathOperator(char c){
    if(c == '+' || c=='-' || c=='/' || c =='*') return 1;
    return 0;
}

void validateCharacter(char c){
    // Sprawdzamy czy znak to cyfra lub operator
    if('1' <= c && c<='9' || isSimpleMathOperator(c)) return;

    // W przeciwnym razie wyrzucamy blad
    printf("Niedozwolony znak: %c !!!!",c);
    exit(1);
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
}

int charToInt(char c) {
    return c - 48;
}

int main(){
    StackItem **stack = createStack();

    char userInput[MAX_STACK_LENGTH];
    printf("Podaj dzialanie matematyczne: ");
    // Objasnienie co to znaczy:
    // 1. Spacja przed znakiem procenta- mowi, ze scanf_s ma ominac wszystkie znaki biale (spacje/taby) z poczatku string
    // 2. [^\n] - czytaj wszystko az (^) az do znaku nowej lini (\n)
    scanf_s(" %[^\n]", userInput);

    int i = 0;
    char c;

    while((c = userInput[i++])){
        if(c == ' ') continue; // Omijamy spacje

        validateCharacter(c);
        push(stack,c);
    }

    // Sprawdzamy, czy ostatnim znakiem nie jest operator
    if(isSimpleMathOperator(top(stack))){
        printf("Dzialanie matematyczne nie moze konczyc sie operatorem !!!");
        exit(1);
    }

    // Sprawdzamy, czy pierwszym znakiem nie jest operator
    if(isSimpleMathOperator(stack[0]->key)){
        printf("Dzialanie matematyczne nie moze zaczynac sie operatorem !!!");
        exit(1);
    }

    // Wykonujemy dzialanie matematyczne
    float result = 0;
    float arg1=0;
    float arg2=0;
    char operator = 0;
//    char c;

    int power = 1; // Potega liczby 10
    int currentCharacterIsOperator;

    while(isEmpty(stack) == 0){
        c = pop(stack);
        currentCharacterIsOperator = isSimpleMathOperator(c);

        // Jezeli nie mamy jeszcze zlapanego operatora, to cyfry wlatuja do argumentu pierwszego
        if(operator == 0 && currentCharacterIsOperator==0){
            arg1+= (float)(charToInt(c) * power); // Ten zapis (float)NAWIAS zamienia wartosc NAWIASU na float'a
            power*=10;
        }

        // Jezeli pojawi sie nam operator, a nie mamy zadnego wczesniejszego zapisanego
        else if(operator == 0 && currentCharacterIsOperator == 1){
            power = 1; // Bedziemy teraz przypisywac wartosc innego argumentu, wiec wracamy do 1. wielokrotnosci 10

            if(c == '+' || c == '-'){
                result += executeSimpleMathOperation(c,result,arg1);
                arg1= 0;
            }
            else operator = c;
        }

        // Jezeli mamy juz zlapany operator, to cyfry wlatuja do argumentu drugiego
        else if(operator!=0 && currentCharacterIsOperator == 0){
            arg2+= (float)(charToInt(c) * power);
            power*10;

        }
        // Jezeli mamy obydwa argumenty i dostaniemy kolejny operator, to dwa argumenty lacza sie w jeden
        else if(operator!=0 && currentCharacterIsOperator){
            power = 1;
            if(c == '+' || c =='-'){
                result+= executeSimpleMathOperation(operator,arg2,arg1);
                operator = 0;
                arg1=0;
                arg2=0;
            } else{
                arg1 = executeSimpleMathOperation(operator,arg2,arg1);
                operator = c;
                arg2=0;
            }
        }
    }

    if(operator != 0) result+=executeSimpleMathOperation(operator,arg2,arg1);

    printf("\nWYNIK: %f", result);

    return 0;
}