#pragma once

#include <stdbool.h>

char* convertToReversePolishNotation(char* input);
double getResultOfExpression(const char* input, bool* inputIsCorrect);
double calculate(char* input, bool* inputIsCorrect);