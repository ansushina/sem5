#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "matrix.h"
#include <ctime>
using namespace std;

#define A_B_CONST 1

//рекурсивный алгоритм полного обхода

static int ss(0);
void absolute(Matrix &D, vector<int> &min_path, int &min_d, vector<int> &cur_path, vector<bool> &visited, int &cur_len);

pair<int, vector<int> > absolute_find(Matrix D)
{
    int n = D.rows();
    vector<bool> visited(n, 0);
    vector<int> cur_path;
    vector<int> min_path;
    int cur_len = 0;
    int min_path_len = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cur_path.clear();
        cur_path.push_back(i);
        fill(visited.begin(), visited.end(), 0);
        visited[i] = 1;
        cur_len = 0;
        absolute(D, min_path, min_path_len, cur_path, visited, cur_len);
    }
    return pair<int, vector<int>>(min_path_len, min_path);
}

void absolute(Matrix &D, vector<int> &min_path, int &min_d, vector<int> &cur_path, vector<bool> &visited, int &cur_len) {
    size_t M = D.cols();
    if (cur_path.size() == M) {
        ss++;
        int tmp = D[cur_path.back()][cur_path[0]];
        if (cur_len + tmp < min_d)
        {
            min_path = cur_path;
            min_d = cur_len + tmp;
        }
        return;
    }
    for (size_t i = 0; i < M; i++) {
        if (!visited[i])
        {
           int tmp = D[cur_path.back()][i];
           if (cur_len + tmp > min_d)
               continue;
           cur_len += tmp;
           cur_path.push_back(i);
           visited[i] = 1;
           absolute(D, min_path, min_d, cur_path, visited, cur_len);
           visited[i] = 0;
           cur_path.pop_back();
           cur_len -= tmp;
        }
    }
}

//заполнение матрицы привлекательности
void get_attractiveness(Matrix &attr, Matrix &D){
    for (size_t i = 0; i < D.rows(); i++){
        for (size_t j = 0; j < D.cols(); j++) {
            double tmp = 1/D[i][j];
            attr[i][j] = tmp;
            attr[j][i] = tmp;
        }
    }
}

// поиск всех еще не посещенных вершин
void find_not_visited(vector<int> &not_viseted, vector<int> cur_path, size_t M) {
    bool nv = true;
    for (size_t i = 0; i < M; i++) {
        nv = true;
        for (size_t j = 0; j < cur_path.size(); j++) {
            if ((int)i == cur_path[j]) nv = false;
        }
        if (nv) not_viseted.push_back(i);
    }
}

// Муравьиный алгоритм

pair<int, vector<int>> Ant(Matrix D, const int Tmax, const double alpha, const double ro){
    const int teta_start = 10;
    const int teta_min = 5;
    const size_t M = D.cols(); //количество вершин
    const double Q = D.avg()*M; //примерное значение длины пути
    const double betta = A_B_CONST - alpha;

    Matrix Attr(M, M); //привлекательность
    get_attractiveness(Attr, D);

    Matrix Teta(M, M, teta_start); //феромоны
    Matrix Delta_Teta(M, M); //феромоны на тек шаге

    int Lmin = -1; //длина кратчайшего маршрута
    vector<int> Lp; // кратчайший маршрут
    vector<double> P(M, 0.0); //вероятности

    double coin;
    // цикл по времени жизни колонии
    for (int t = 0; t < Tmax; t++) {
        Delta_Teta.zero();
        //цикл по всем муравьям
        for (size_t k = 0; k < M; k++) {
            vector<int> cur_path;
            cur_path.push_back(k);
            int cur_path_length = 0;
            int i = k;
            //строим маршрут
            while (cur_path.size() < M) {
                vector<int> not_visited;
                find_not_visited(not_visited,cur_path,M);
                for (size_t j = 0; j < M ; j++){
                    P[j] = 0.0;
                }
                // посчитаем вероятности
                for (size_t j = 0; j < not_visited.size(); j++) {
                    if (D[i][not_visited[j]]) {
                        double sum = 0;
                        for (auto n: not_visited) {
                            sum += pow(Teta[i][n], alpha) * pow(Attr[i][n], betta);
                        }
                        P[j] = pow(Teta[i][not_visited[j]], alpha)*pow(Attr[i][not_visited[j]], betta)/sum;
                    }
                    else {
                        P[j] = 0;
                    }
                }
                //подбросим монетку
                coin  = (rand() % 100) / 100.0;
                // подсчитаем куда мы попали
                int best_p = 0;
                double sum_p = 0;
                for (size_t s = 0; s < M; s++) {
                    sum_p += P[s];
                    if(coin < sum_p)
                    {
                        best_p = s;
                        break;
                    }
                }
                // добавим новый город в путь
                int new_town = not_visited[best_p];
                cur_path.push_back(new_town);
                cur_path_length += D[i][new_town];

                //обновим феромон на этом участке
                Delta_Teta[i][new_town] += Q/cur_path_length;

                i = new_town; // дальше продолжим путь из этого города
                not_visited.erase(not_visited.begin()+best_p);
            }
            // конец построения маршрута
            // осталось только добавить путь от последнего города к начальному
            // это завершит цикл
            cur_path_length += D[cur_path[cur_path.size()-1]][k];
            // проверим не каратчайший ли это путь
            if (Lmin == -1 || cur_path_length < Lmin){
                Lmin = cur_path_length;
                Lp = cur_path;
            }
        }
        // конец цикла по муравьям
        //теперь чатсь феромона должна испариться
        for (size_t ii = 0; ii < M; ii++) {
            for (size_t jj = 0; jj < M; jj++) {
                Teta[ii][jj] = Teta[ii][jj] * (1.0 - ro) + Delta_Teta[ii][jj];
                if (Teta[ii][jj] < teta_min)
                {
                    Teta[ii][jj] = teta_min;
                }
            }
        }
    }
    // конец цикла по времени
    return pair<int, vector<int>>(Lmin, Lp);
}

void print_res(pair<int, vector<int>> results){
    cout << "result:\n D = " << results.first << ";\n path: ";
    for (int i = 0; i < results.second.size(); i++) {
        cout << results.second[i] << " ";
    }
    cout <<";\n";
}

int main()
{
    //cout << "Hello World!" << endl;

    setbuf(stdout, NULL);
    Matrix M(12,12);
    M.make_rand();
    M.print();

    pair<int, vector<int>> results = absolute_find(M);
    int ideal_len = results.first;

    for (double ro = 0; ro <= 1; ro += 0.25)
    {
        for (double alpha = 0; alpha <= 1; alpha += 0.25)
        {
            for (int t = 50; t <= 400; t+=50)
            {
                double dif = 0;
                for (auto i = 0; i < 50; i++)
                {
                    pair<int, vector<int>> results = Ant(M, t, alpha, ro);
                    dif += abs(results.first - ideal_len);
                }
                dif /= 50.0;
                printf("%5lf, %5lf, %5d, %10lf\n",ro, alpha, t, dif);
            }

        }
    }


    /*
    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%10s,%10s,%10s\n", "N" , "1", "2", "-");
    printf("%5s,%10s,%10s,%10s\n", "N" , "1", "2", "-");
    std::clock_t time = 0;
    int repeat = 5;
    int start = 2;
    int end = 20;
    int step = 1;
    for (int i = start; i < end; i+=step) {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        Matrix M(i,i);
        M.make_rand();
        //M.print();

        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = std::clock();
            pair<int, vector<int>> results = absolute_find(M);
            std::clock_t end = std::clock();
            time += end-start;
            //printf("Absolute ");
            //print_res(results);
        }
        printf("%10d,", time/repeat);
        fprintf(f,"%10d,", time/repeat);
        time = 0;
        for (int j = 0; j < repeat ; j++)
        {
            std::clock_t start = std::clock();
            pair<int, vector<int>> results = Ant(M, 290, 0.5, 0.5);
            std::clock_t end = std::clock();
            time += end-start;
            //printf("Ant ");
            //print_res(results);
        }
        printf("%10d\n", time/repeat);
        fprintf(f,"%10d\n", time/repeat);
    }
    */

    return 0;
}
