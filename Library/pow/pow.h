#pragma once

struct _FLOAT
{
    float data;
    _FLOAT(float f) : data(f){}
} typedef FLOAT;

float operator ^(FLOAT a, int b);