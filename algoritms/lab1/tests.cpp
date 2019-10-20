#include "tests.h"
#include <cstdlib>
#include <stdio.h>
#include <time.h>

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

     test_lev();
     test_dam_lev();
     test_dam_lev_rec();
    Livinshtein finder;
    DamerauLiv finder2;
    DamerauLivRec finder3;


    // time
    std::cout << "Тестирование по времени..."<< std::endl;
    printf("%2s %15s %15s %15s\n", "N" , "Livinshtein", "DamerauLiv", "RecDamerauLiv");
    unsigned int time = 0;
    for (int j = 1; j < 11; j++) {
        char s1[j], s2[j];
        printf("%2d", j);
        time = 0;
        for (int i = 0; i < 100 ; i++)
        {
            gen_random(s1,j);
            //printf("%s\n", s1);
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



    printf("%2s %15s %15s\n", "N" , "Livinshtein", "DamerauLiv");
    for (int j = 100; j <= 1000; j+=100) {
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

        printf("%15d\n", time/100);
    }

}



void test_lev() {
    printf("TEST LEVENSHTEIN\n");
     Livinshtein finder;
    {
        printf("test 1: ");
        std::string s1 = "skat";
        std::string s2 = "kot";
        int answ = 2;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 2: ");
        std::string s1 = "skat";
        std::string s2 = "";
        int answ = 4;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 3: ");
        std::string s1 = "";
        std::string s2 = "kot";
        int answ = 3;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 4: ");
        std::string s1 = "kot";
        std::string s2 = "kot";
        int answ = 0;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 5: ");
        std::string s1 = "";
        std::string s2 = "";
        int answ = 0;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 6: ");
        std::string s1 = "skot";
        std::string s2 = "ksot";
        int answ = 2;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 7: ");
        std::string s1 = "sksksk";
        std::string s2 = "ksksks";
        int answ = 2;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 8: ");
        std::string s1 = "aaaaaa";
        std::string s2 = "kot";
        int answ = 6;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 9: ");
        std::string s1 = "kt kt kt";
        std::string s2 = "tk tk tk";
        int answ = 6;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
}

void test_dam_lev() {
    printf("TEST DAMERAU LEVENSHTEIN\n");
    DamerauLiv  finder;
    {
        printf("test 1: ");
        std::string s1 = "skat";
        std::string s2 = "kot";
        int answ = 2;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 2: ");
        std::string s1 = "skat";
        std::string s2 = "";
        int answ = 4;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 3: ");
        std::string s1 = "";
        std::string s2 = "kot";
        int answ = 3;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 4: ");
        std::string s1 = "kot";
        std::string s2 = "kot";
        int answ = 0;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 5: ");
        std::string s1 = "";
        std::string s2 = "";
        int answ = 0;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 6: ");
        std::string s1 = "skot";
        std::string s2 = "ksot";
        int answ = 1;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 7: ");
        std::string s1 = "sksksk";
        std::string s2 = "ksksks";
        int answ = 2;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 8: ");
        std::string s1 = "aaaaaa";
        std::string s2 = "kot";
        int answ = 6;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 9: ");
        std::string s1 = "kt kt kt";
        std::string s2 = "tk tk tk";
        int answ = 3;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
}

void test_dam_lev_rec() {
    printf("TEST DAMERAU LEVENSHTEIN REC\n");
     DamerauLivRec finder;
    {
        printf("test 1: ");
        std::string s1 = "skat";
        std::string s2 = "kot";
        int answ = 2;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 2: ");
        std::string s1 = "skat";
        std::string s2 = "";
        int answ = 4;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 3: ");
        std::string s1 = "";
        std::string s2 = "kot";
        int answ = 3;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 4: ");
        std::string s1 = "kot";
        std::string s2 = "kot";
        int answ = 0;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 5: ");
        std::string s1 = "";
        std::string s2 = "";
        int answ = 0;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 6: ");
        std::string s1 = "skot";
        std::string s2 = "ksot";
        int answ = 1;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 7: ");
        std::string s1 = "sksksk";
        std::string s2 = "ksksks";
        int answ = 2;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 8: ");
        std::string s1 = "aaaaaa";
        std::string s2 = "kot";
        int answ = 6;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
    {
        printf("test 9: ");
        std::string s1 = "kt kt kt";
        std::string s2 = "tk tk tk";
        int answ = 3;

        int n = finder.count(s1,s2);
        if (n != answ)
            printf("failed\n");
        else
            printf("ok\n");
    }
}
