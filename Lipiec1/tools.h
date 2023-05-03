#ifndef TOOLS_H
#define TOOLS_H
#include "char_stack.h"

char *getMathEquationFromUser();

CharStackItem **transformUserInputIntoStack(char *userInput);

int charToInt(char c);

float executeSimpleMathOperation(char operation, float arg1, float arg2);

int isSimpleMathOperator(char c);

#endif