#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//генератор номера билета
long long int generator() {
    int n;
    long long int r = 0;
    for (int i = 0; i < 5; i++) {
        n = rand() % 10;
        //возводим 10 в степень i и умножаем на рандомную цифру
        //затем вычисляем r
        r = r + n * pow(10, i);
        //cout << r << "\t\t";
    }
    //рекурсия до тех пор, пока число не будет содержать 5 цифр
    if (r > 100000) r = generator();
    return r;
}

void linear_search(long long key) {
    //открытие файла в бинарном режиме (нет учета форматирования)
    ifstream file_p("f.txt", ios::binary);
    long long int a_;
    string name_;
    string address_;
    //метка, отвечающая за наличие или отсутствие билета
    bool label = false;

    //чтение двоичных файлов в переменные, read возвращает ссылку на поток ввода, sizeof - размнер байтов, занятых на диске
    while (file_p.read((char*)&a_, sizeof(long long int)) && file_p.read((char*)&name_, sizeof(name_))
        && file_p.read((char*)&address_, sizeof(address_))) {
        if (a_ == key) {
            cout << "Читательский билет был найден: " << endl;
            cout << name_ << ' ' << address_ << endl;
            label = true;
            break;
        }
    }
    if (!label) {
        cout << "Читательский билет не был найден" << endl;
    }
    file_p.close();
}

struct Ticket {
    int number;
    string name;
    string address;
};



int binarysearch(const vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1; // Возвращаем -1, если элемент не найден
}

// Функция для создания таблицы в оперативной памяти
void createTable(Ticket* table, int size, ifstream& file) {
    for (int i = 0; i < size; i++) {
        file.read(reinterpret_cast<char*>(&table[i]), sizeof(Ticket));
    }
}

// Функция для чтения записи из файла по ссылке
Ticket readRecord(ifstream& file, int index) {
    //смещение
    int offset = sizeof(Ticket) * index;
    //ищет позицию в файле по смещению
    file.seekg(offset);

    Ticket record;
    file.read(reinterpret_cast<char*>(&record), sizeof(Ticket));

    return record;
}

bool compareRecords(const Ticket& record1, const Ticket& record2) {
    return record1.number < record2.number;
}
int main()
{
    long long a;
    int size;
    string name;
    string address;

    setlocale(LC_ALL, "rus");
    //открываем файл для бинарной записи
    ofstream file_out("f.txt", ios::binary);
    cout << "Введите количество строк: ";
    cin >> size;

    /*for (int i = 0; i < size; i++) {
        //генерируем номер чит билета
        a = generator();
        //запись в двоичный файл номера билета, имени и адреса
        file_out.write((char*)&a, sizeof(long long int));
        file_out.write((char*)&name, sizeof(name));
        file_out.write((char*)&address, sizeof(address));
    }
    file_out.close();*/

    vector<Ticket> records;

    for (int i = 0; i < size; i++) {
        a = generator();
        name = "Name" + to_string(i);
        address = "Address" + to_string(i);

        Ticket record;
        record.number = a;
        record.name = name;
        record.address = address;

        records.push_back(record);
    }

    sort(records.begin(), records.end(), compareRecords);

    for (const Ticket& record : records) {
        file_out.write(reinterpret_cast<const char*>(&record), sizeof(Ticket));
    }

    file_out.close();

    //открытие для чтения
    ifstream file_in("f.txt", ios::binary);

    vector<int> numbers;
    Ticket t;
    while (file_in.read(reinterpret_cast<char*>(&t), sizeof(Ticket))) {
        numbers.push_back(t.number);
        cout << "Читательский билет: ";
        cout << t.number << ' ' << t.name << ' ' << t.address << endl;
    }

    const int tableSize = 200;
    Ticket table[tableSize];
    createTable(table, size, file_in);

    int key;
    cout << "Введите номер читательского билета: ";
    cin >> key;

    //bool found = binary_search(numbers.begin(), numbers.end(), key);

    int index = binarysearch(numbers, key);
    //if (found) {
        if (index != -1) {

            cout << "Запись найдена" << endl;

        }
        else {
            cout << "Запись не найдена" << endl;
        }
    //}
    //else cout << "Запись не найдена";

    file_in.close();
    return 0;
}

