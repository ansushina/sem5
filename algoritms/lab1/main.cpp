#include <iostream>
#include <stdio.h>
#include "tests.h"

#include "finddistance.h"


using namespace std;

int main()
{
    setlocale(LC_ALL,"Russian");
    cout << "Do you want to run tests? y/n"<< endl;
    char str;
    cin >> str;

    if (str == 'y'){
        test();
        return 0;
    }
    Livinshtein finder;
    DamerauLiv finder2;
    DamerauLivRec finder3;
    std::string s1, s2;
    cout << "Input str1:";
    cin >> s1;
    cout << "Input str2:";
    cin >> s2;
    cout << "Leveshtein "<< endl;
    int a = finder.count(s1,s2,1);
    cout << "answer: " << (a) << std::endl << std::endl;
    cout << "Damerau Levenshtein "<< endl;
    a = finder2.count(s1,s2,1);
    cout << "answer: " << (a) << std::endl << std::endl;
    cout << "Damerau Levenshtein Rec "<<endl;
    a = finder3.count(s1,s2);
    cout << "answer: " << (a) << std::endl << std::endl;

    /*cout << "Измерим время работы алгоритмов в тиках" << std::endl;

    unsigned int time = 0;
    for (int i = 0; i < 100 ; i++)
    {
        unsigned int tick1 = tick();
        finder.count(s1,s2);
        unsigned int tick2 = tick();
        time += tick2-tick1;
    }

    cout << "Ливинштейна(в тиках) " << time/100 << endl;

   time = 0;
    for (int i = 0; i < 100 ; i++)
    {
        unsigned int tick1 = tick();
        finder2.count(s1,s2);
        unsigned int tick2 = tick();
        time += tick2-tick1;
    }

    cout << "Домерау-Ливинштейна(в тиках) " << time/100 << endl;

    time = 0;
    for (int i = 0; i < 100 ; i++)
    {
        unsigned int tick1 = tick();
        finder3.count(s1,s2);
        unsigned int tick2 = tick();
        time += tick2-tick1;
    }

    cout << "Домерау-Ливинштейна рекурсивно(в тиках) " << time/100 << endl;*/

    return 0;
}
