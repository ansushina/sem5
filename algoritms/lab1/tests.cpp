#include "tests.h"
#include <cstdlib>
#include <stdio.h>

#include "finddistance.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}


void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[std::rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void test() {
     srand(time(NULL));

     setbuf(stdout, NULL);
    Livinshtein finder;
    DamerauLiv finder2;
    DamerauLivRec finder3;

    // time
    std::cout << "Тестирование по времени..."<< std::endl;
    printf("%2s %15s %15s %15s\n", "N" , "Livinshtein", "DamerauLiv", "RecDamerauLiv");
    unsigned int time = 0;
    for (int j = 1; j < 15; j++) {
        char s1[j], s2[j];
        printf("%2d", j);
        time = 0;
        for (int i = 0; i < 100 ; i++)
        {
            gen_random(s1,j);
            gen_random(s2,j);
            unsigned int tick1 = tick();
            finder.count(s1,s2);
            unsigned int tick2 = tick();
            time += tick2-tick1;
        }
        printf("%15d", time/100);
        time = 0;
        for (int i = 0; i < 100 ; i++)
        {
            gen_random(s1,j);
            gen_random(s2,j);
            unsigned int tick1 = tick();
            finder2.count(s1,s2);
            unsigned int tick2 = tick();
            time += tick2-tick1;
        }
        printf("%15d", time/100);
        time = 0;
        for (int i = 0; i < 100 ; i++)
        {
            gen_random(s1,j);
            gen_random(s2,j);
            unsigned int tick1 = tick();
            finder3.count(s1,s2);
            unsigned int tick2 = tick();
            time += tick2-tick1;
        }
        printf("%15d\n", time/100);
    }
}
