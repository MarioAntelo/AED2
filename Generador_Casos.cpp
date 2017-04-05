#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alfabeto) - 1;

char genRandom()
{

    return alfabeto[rand() % stringLength];
}

int main()
{
    srand(time(0));
    std::string Str;
    for(unsigned int i = 0; i < 20; ++i)
    {
    Str += genRandom();

    }
    cout << Str << endl;
    


}

    return 0;

}