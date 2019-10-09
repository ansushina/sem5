#include <iostream>
#include <stdio.h>
#include "tests.h"

#include "finddistance.h"


using namespace std;

int main()
{
    setlocale(LC_ALL,"Russian");
    cout << "Хотите запустить тесты? y/n"<< endl;
    char str;
    cin >> str;

    if (str == 'y')
        test();
    Livinshtein finder;
    DamerauLiv finder2;
    DamerauLivRec finder3;
    std::string s1, s2;
    cout << "Input str1:";
    cin >> s1;
    cout << "Input str2:";
    cin >> s2;
    cout << "Ливинштейна "<< endl;
    int a = finder.count(s1,s2,1);
    cout << "Ответ: " << (a) << std::endl << std::endl;
    cout << "Домерау-ливинштейна "<< endl;
    a = finder2.count(s1,s2,1);
    cout << "Ответ: " << (a) << std::endl << std::endl;
    cout << "Домерау-Ливинштейна рукурсивно "<<endl;
    a = finder3.count(s1,s2);
    cout << "Ответ: " << (a) << std::endl << std::endl;

    cout << "Измерим время работы алгоритмов в тиках" << std::endl;

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

    cout << "Домерау-Ливинштейна рекурсивно(в тиках) " << time/100 << endl;

    return 0;
}
