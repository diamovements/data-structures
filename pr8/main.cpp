#include <iostream>
using namespace std;

long long countSequences(const string& sequence) {
    int n = sequence.length();

    // Базовые случаи
    long long endsWithZero = 1, endsWithOne = 1;

    // Заполняем значения для последовательностей заданной длины
    for (int i = 1; i < n; i++) {
        long long newEndsWithZero = endsWithZero + endsWithOne;
        long long newEndsWithOne = endsWithZero;
        endsWithZero = newEndsWithZero;
        endsWithOne = newEndsWithOne;
        if (sequence[i] == '1' && sequence[i - 1] == '1') {
            endsWithZero = 0;  // Если два идущих подряд единицы, обнуляем endsWithZero
        }
    }

    return endsWithZero + endsWithOne;
}

int main() {
    system("chcp 65001");
    string sequence;
    cout << "Введите последовательность нулей и единиц (например, 101010): ";
    cin >> sequence;
    long long result = countSequences(sequence);
    cout << "Число последовательностей без двух идущих подряд единиц: " << result << endl;

    return 0;
}