#include <iostream>
using namespace std;
//#include "learning classes.h"

class myClass
{
public:
    int rapeSack();
public:
};

int myClass::rapeSack()
{
    int rape = 10;
    cout << "Rape Sack has RUN!\n";
    return rape;
}


int main(void)
{
    cout << "running rapeSack()...\n";
    myClass gay;
    int val = gay.rapeSack();
    cout << "rape = " << val << "\n";
}
