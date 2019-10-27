#include <iostream>

using namespace std;


#include "test.h"
#include<time.h>




int main()
{
    srand(time(NULL));
    setbuf(stdout, NULL);
    test();
    return 0;
}
