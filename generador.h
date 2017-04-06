#ifndef __GENERADOR
#define __GENERADOR

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
static const int stringLength = sizeof(alfabeto) - 1;

string generador(int size);
char genRandom();

#endif