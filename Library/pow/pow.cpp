#include "pow.h"

float operator ^(FLOAT a, int b)
{
    float temp = 1;
    for (char i = 0; i < b; i++)
    {
        temp *= a.data;
    }
    return temp;
}