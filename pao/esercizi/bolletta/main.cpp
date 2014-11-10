#include <iostream>
#include "bolletta.h"
#include "telefonata.h"
#include "orario.h"

using namespace std;

int main()
{
    orario o1 = orario(12);
    orario o2 = orario(14, 30);

    telefonata t = telefonata(o1, o2, 339395683);
    cout << t << endl;

    bolletta bol;


    return 0;
}

