#include <iostream>
#include <string>
#include <vector>
using namespace std;

int linearSearch(const string& str, const string& substr) {
    int n = str.length();
    int m = substr.length();

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (str[i + j] != substr[j]) {
                break;
            }
        }
        if (j == m) {
            return i; // возвращаем индекс первого вхождения подстроки
        }
    }

    return -1; // если подстрока не найдена
}
vector<int> buildBadCharTable(const string& substr) {
    int m = substr.length();
    vector<int> badCharTable(256, -1);

    for (int i = 0; i < m; i++) {
        badCharTable[substr[i]] = i;
    }

    return badCharTable;
}

int boyerMooreHorspool(const string& str, const string& substr) {
    int n = str.length();
    int m = substr.length();

    vector<int> badCharTable = buildBadCharTable(substr);

    int i = m - 1; // индекс текущего символа в строке
    int j = m - 1; // индекс текущего символа в подстроке

    while (i < n) {
        if (str[i] == substr[j]) {
            if (j == 0) {
                return i; // возвращаем индекс последнего вхождения подстроки
            }
            i--;
            j--;
        }
        else {
            i += m - min(j, 1 + badCharTable[str[i]]);
            j = m - 1;
        }
    }

    return -1; // если подстрока не найдена
}


int main() {
    string str;
    string substr;
    int cmd;
    cout << "Enter command, 1 for linear search, 2 for moore search";
    cin >> cmd;
    cout << "Enter string: ";
    cin >> str;
    cout << "Enter substring: ";
    cin >> substr;
    int index, index2;
    switch(cmd) {
        case 1:
            index = linearSearch(str, substr);
            if (index != -1) {
                cout << "String is found on position: " << index << endl;
            }
            else {
                cout << "String wasn't found" << endl;
            }
            break;
        case 2:
            index2 = boyerMooreHorspool(str, substr);
            if (index2 != -1) {
                cout << "Substring was found on position: " << index2 << endl;
            }
            else {
                cout << "Substring wasn't found" << endl;
            }

    }


    return 0;
}
