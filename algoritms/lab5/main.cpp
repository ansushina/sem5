#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

using namespace std;

typedef string input_t;

static queue<input_t> queue1;
static queue<input_t> queue2;
static queue<input_t> queue3;

static vector<input_t> objvec;
static vector<input_t> res;

static mutex m1, m2, m3, resm;

static int n = 10;

FILE *f;


static clock_t main_time = clock();

static clock_t mtime = clock();

class Logger {
public:
    Logger() {}
    static void print(int step, string str, int i, clock_t time = 0){
        fprintf(f,"[%d] step item%d time: %ld (%ld)  value: %s\n", step, i, time, time - mtime, str.c_str());
        std::cout << step <<" step: "<< "  item" << i << " " << " time: "<< time - main_time<<"  " << str  << std::endl;
        mtime += time - mtime;
    }
};
Logger log;

string myHash1(string s){
    string s1(s), s2(s);
    for (size_t i = 0; i < s.length(); i++)
    {
        s1[i] = (s[i] + i) %80 + 33;
        //log.print(10, s1, i);
        s2[i] = (s[i] + 2*i) % 80 + 33;
        //log.print(10, s2, i);
    }
    return s1+"~"+s2;
}

string myHash2(string s) {
    string s1(s), s2(s), s3(s);
    for (int i = 0; i < s.length(); i++)
    {
        s1[i] = (s[i] - i + 5)%80 + 33;
        s3[i] = (s[i] + i - 10) %80 + 33;
    }
    s2 = myHash1(s);
    return s1 + "_" + s2 + "_" +s3;
}

string myHash3(string s){
    string s1(s);
    for (int i = 0; i < s.length(); i++){
        s1[i] = (s[i] + 15) %80 + 33;
    }
    return "result" + s1 + "hash";
}


void SingleHash() {
    int num = 0;
    while (1) {
        if (num == n)
            break;
        m1.lock();
        if (queue1.empty()) {
            m1.unlock();
            continue;
        }
        input_t myObj = queue1.front();
        queue1.pop();
        m1.unlock();
        input_t newObj = myHash1(myObj);
        m2.lock();
        queue2.push(newObj);
        sleep(1);
        clock_t time = clock();
        log.print(1, newObj, num, time);
        m2.unlock();
        num++;
    }
}

void MultiHash() {
    int num = 0;
    while (1) {
        if (num == n)
            break;
        m2.lock();
        if (queue2.empty()) {
            m2.unlock();
            continue;
        }
        input_t myObj = queue2.front();
        queue2.pop();
        m2.unlock();
        input_t newObj = myHash2(myObj);
        m3.lock();
        queue3.push(newObj);
        sleep(3);
        clock_t time = clock();
        log.print(2, newObj, num, time);
        m3.unlock();

        num++;
    }
}

void Result() {
    int num = 0;
    while (1) {
        if (num == n)
            break;
        m3.lock();
        if (queue3.empty()) {
            m3.unlock();
            continue;
        }
        input_t myObj = queue3.front();
        queue3.pop();
        m3.unlock();
        input_t newObj = myHash3(myObj);
        resm.lock();
        res.push_back(newObj);
        sleep(1.5);
        clock_t time = clock();
        log.print(3, newObj, num, time);
        resm.unlock();

        num++;
    }
}


int main()
{
    cout << "Hello World!" << endl;

    f = fopen("res.txt", "w");
    n = 5;
    objvec.resize(n);

    thread t1(SingleHash);
    thread t2(MultiHash);
    thread t3(Result);
    main_time = clock();
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            objvec[i] = string("string") + to_string(i);
        }
        else { objvec[i] = to_string(i) + string("line"); }
    }

    for (int i = 0; i < n; i++) {
        clock_t time = clock();
        log.print(0, objvec[i], i, time);
        m1.lock();

        queue1.push(objvec[i]);
        m1.unlock();
        sleep(2);
    }

    t1.join();
    t2.join();
    t3.join();
    fclose(f);
    return 0;
}
