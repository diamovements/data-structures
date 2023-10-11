#include <iostream>
#include <bitset>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <vector>
using namespace std;
void task1a() {
	unsigned char num = 255;
	unsigned char maska = 1;
	num = num & (~(maska << 4));
	cout << num;
}

void task1b(int num) {
	unsigned char maska = 1;
	num = num | (maska << 6);
	cout << num;
}

void task1v() {
	unsigned int x = 25;
	const int n = sizeof(int) * 8;
	unsigned maska = (1 << n - 1);
	cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
	cout << "Результат: ";
	for (int i = 1; i <= n; i++) {
		cout << ((x & maska) >> (n - i));
		maska = maska >> 1;
	}
	cout << endl;
	system("pause");
}

void task2a(vector<int> array, int n) {
	unsigned int list = 0;
	const int x = sizeof(int) * 2;
	unsigned mask = (1 << (x-1)); //маска с двигающейся единицей в зависимости от числа в массиве
	for (int i = 0; i < n; i++) {
		//передвигаем единицу вправо на столько разрядов, какое у нас итое число в массиве
		//если 5 то будет например 00100000 и тд
		list = list | (mask >> ((x - 1)- array[i]));
	}

	cout << "Битовый массив: " << bitset<x>(list) << endl;
	vector<int> result;
	for (int i = 0; i < x; i++) {
		//значение битового массива и маски совпадают
		//(например, маска 10000000 при i=0 совпадает с
		//значением 10110111 первого индекса -> первое число
		// (маска) семерка. затем идет 5 и тд.
		if ((list & (mask >> i)) != 0) {
			result.push_back(x - i - 1);
		}
	}
	reverse(result.begin(), result.end());
	cout << "Результат: ";
	for (int i = 0; i < n; i++) {
		cout << result[i] << " ";
	}

}
void task2b(vector<int> array, int n) {
	int j = 0;
	unsigned long long list = 0;
	int x = sizeof(long long) * 8;
	unsigned long long mask = (1ULL << (x - 1));
	for (int i = 0; i < n; i++) {
		list = list | (mask >> ((x - 1) - array[i]));
	}

	vector<int> result;
	for (int i = 0; i < x; i++) {
		if ((list & (mask >> i)) != 0) {
			result.push_back(x - i - 1);
			if ((x - i - 1) <= n){
				j++;
			}

		}
	}
	reverse(result.begin(), result.end());
	cout << "Результат: ";
	for (int i = 0; i < j; i++) {
		cout << result[i] << " ";
	}
}
void task2v(vector<int> array, int n) {
	int j = 0;
	bitset<256> list = 0;
	int x = sizeof(long long) * 32;
	bitset<256> mask;
	//первый индекс единица, остальные нули
	mask[255] = 1ULL;
	for (int i = 0; i < n; i++) {
		list = list | (mask >> ((x - 1) - array[i]));
	}

	vector<int> result;
	for (int i = 0; i < x; i++) {
		if ((list & (mask >> i)) != 0) {
			result.push_back(x - i - 1);
			//счетчик против повторов
			if ((x - i - 1) <= n) {
				j++;
			}

		}
	}
	reverse(result.begin(), result.end());
	cout << "Результат: ";
	for (int i = 0; i < j; i++) {
		cout << result[i] << " ";
	}
}
void task3() {
	int start = clock();
	ifstream file;
	ofstream out;
	file.open("file.txt");
	out.open("out.txt");
	vector <unsigned char> numbers;
	unsigned long long mask = 1ULL;
	//размер вектора 1 250 000 - в него поместятся все значения из диапазона
	for (int i = 0; i < 10000000 / 8; i++) {
		numbers.push_back(0);
	}

	int a;
	while (file >> a) {
		//получение индекса очередного числа в векторе
		//сдвиг маски влево на остаток от деления (записываем значение)
		numbers[a / 8] = numbers[a / 8] | (mask << (a % 8));
	}
	//запись в отсортированный файл
	for (int i = 0; i < 10000000 / 8; i++) {
		//кол-во бит в числе, i равна биту с единицей
		for (int j = 0; j < 8; j++) {
			//запись 0 и сдвиг вправо на 1 бит
			a = (numbers[i] & mask) >> j;
			//если есть 1, то восстанавливаем исходное значение числа
			if (a == 1)
				out << 8 * i + j << " ";
			//сдвигаем маску влево
			mask = mask << 1;
		}
		//обновляем маску
		mask = 1;
	}
	file.close();
	out.close();
	int stop = clock();
	int result = stop - start;
	numbers.shrink_to_fit();
	cout << numbers.capacity() << " байт" << endl;
	cout << numbers.capacity() / (1024 * 1024) << " мб" << endl;
	cout << "Время: " << result << " мс" << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	int choice;
	int number;
	int array_nums;
	int size;
	vector<int> array;
	cout << "Введите одно число: " << endl;
	cout << "1 - задание 1а, 2 - задание 1б, 3 - задание 1в" << endl;
	cout << "10 - задание 2а, 20 - задание 2б, 30 - задание 2в" << endl;
	cout << "100 - задание 3" << endl;
	cin >> choice;



	switch (choice) {
	case 1:
		cout << "Результат:  ";
		task1a();
		break;
	case 2:
		cout << "Введите одно число: ";
		cin >> number;
		cout << "Результат:  ";
		task1b(number);
		break;
	case 3:
		task1v();
		break;
	case 10:
		cout << "Введите размер массива (не более 8): ";
		cin >> size;
		cout << "Введите числа (от 0 до 7): ";
		for (int i = 0; i < size; i++) {
			cin >> array_nums;
			array.push_back(array_nums);
		}
		task2a(array, size);
		break;
	case 20:
		cout << "Введите размер массива (не более 64): ";
		cin >> size;
		for (int i = 0; i < size; i++) {
			array.push_back(rand() % size);
		}
		cout << "Сгенерированный массив: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
		task2b(array, size);
		break;
	case 30:
		cout << "Введите размер массива (не более 256): ";
		cin >> size;
		for (int i = 0; i < size; i++) {
			array.push_back(rand() % size);
		}
		cout << "Сгенерированный массив: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
		task2v(array, size);
		break;
	case 100:
		task3();

		break;
	default:
		break;
	}

	return 0;
}








