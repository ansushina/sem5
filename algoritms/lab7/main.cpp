#include <iostream>
#include <string>
#include <vector>
#include <map>

# define NO_OF_CHARS 256

using namespace std;


void getJump(string substr, vector<int> &jump) {
    int m = substr.length();

    jump.resize(m);
    vector<int> link(m);
    for (int i = 1; i < m+1; i++) {
        jump[i-1] = 2*m - i;
    }

    int test = m-1;
    int target = m;

    while (test>=0) {
        link[test] = target;
        while (target <= m-1 && substr[test] != substr[target]) {
            jump[target] = std::min(jump[target], m-test);
            target = link[target];
        }
        test--;
        target--;
    }
    for (int i = 0; i < target; i++)
    {
        jump[i] = std::min(jump[i], m+target-i);
    }

    int temp = link[target];
    while (target <= m) {
        while (target <= temp) {
            jump[target] = std::min(jump[target], temp-target+m);
            target++;
        }
        temp = link[temp];
    }
}

void badCharHeuristic(string str, int badchar[NO_OF_CHARS])
{
    int i;
    int size = str.length();
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = size;

    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = size-i;
}

void getSuffix(string substr, vector<int> &suffix) {
    auto m = substr.length();
    suffix.resize(m+1, m);
    vector<int> z(m,0);
    int maxZidx = 0;
    int maxZ = 0;
    for (int j = 1; j < m; j++) {
       if (j <= maxZ)
           z[j] = std::min(maxZ - j + 1, z[j - maxZidx]);
       while (j + z[j] < m && substr[m - 1 - z[j]] == substr[m - 1 - (j + z[j])])
           z[j]++;
       if (j + z[j] - 1 > maxZ) {
         maxZidx = j;
         maxZ = j + z[j] - 1;
       }
     }
     for (int j = m - 1; j > 0; j--) suffix[m - z[j]] = j; //цикл №1
     for (int j = 1, r = 0; j <= m - 1; j++) //цикл №2
       if (j + z[j] == m)
         for (; r <= j; r++)
           if (suffix[r] == m)
               suffix[r] = j;
}


int BM(string str, string substr) {
    if(str.length() == 0 || substr.length() == 0)
        return -1;
    int subLen = substr.length();
    int sLen = str.length();
    int badchar[NO_OF_CHARS];
    badCharHeuristic(substr, badchar);
    vector<int> jump;
    getSuffix(substr, jump);
    int textLoc = subLen-1;
    int patternLoc =  subLen-1;

    while (textLoc <= sLen && patternLoc > 0 ) {
        if (str[textLoc] == substr[patternLoc]) {
            textLoc--;
            patternLoc--;
        }
        else {
            textLoc = textLoc +max(badchar[str[textLoc]] ,jump[patternLoc+1]);
            patternLoc = subLen;
        }
    }

    if (patternLoc = 0) {
        return textLoc+1;
    }
    return 0;
}


int main()
{
    cout << BM(string("dtatadatadatata"), string("datadata")) << endl;
    return 0;
}
