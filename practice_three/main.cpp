#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


const int EMPTY = -1; // метка для пустой ячейки таблицы
const int LOADING = 2; // пороговое значение коэффициента нагрузки
const int TABLESIZE = 10; // размер таблицы


class Ticket {

private:
    int number;
    string name;
    string address;

public:
    Ticket() : number(0), name(""), address("") {}
    Ticket(int num, string n, string addr) : number(num), name(n), address(addr) {}
    void setNumber(int num) { number = num; }
    void setName(string n) { name = n; }
    void setAddress(string addr) { address = addr; }

    int getNumber() const { return number; }
    string getName() const { return name; }
    string getAddress() const { return address; }

};
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

class TicketReader {
private:
    int capacity; //вместимость в таблице
    int* table; //хэш таблица
    Ticket* data; //массив объектов билета
    int size; //кол-во объектов

    int hash(int num) const { //создание хэша
        return num % capacity;
    }
    int findIndex(int num) const { //поиск по индексу через хэш
        int index = hash(num);
        while (table[index] != EMPTY) {
            if (data[table[index]].getNumber() == num) {
                return index;
            }
            index = (index + 1) % capacity;
        }
        return -1;
    }
    void resize() { //обновление размера таблицы
        int old_capacity = capacity;
        capacity *= 2;
        Ticket* old_data = data;
        int* old_table = table;
        data = new Ticket[capacity];
        table = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = EMPTY;
        }
        size = 0;
        for (int i = 0; i < old_capacity; i++) {
            if (old_table[i] != EMPTY) {
                insert(old_data[old_table[i]].getNumber(), old_data[old_table[i]].getName(), old_data[old_table[i]].getAddress());
            }
        }
        delete[] old_data;
        delete[] old_table;
    }
public:
    TicketReader() : size(0), capacity(TABLESIZE) {
        data = new Ticket[capacity];
        table = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = EMPTY;
        }
    }
    ~TicketReader() {
        delete[] data;
        delete[] table;
    }
    void insert(int num, string name, string address) {//метод вставки нового объекта
        if (size >= capacity / LOADING) {
            resize();
        }
        int index = hash(num);
        while (table[index] != EMPTY) {
            if (data[table[index]].getNumber() == num) {
                return; //билет существует
            }
            index = (index + 1) % capacity;
        }
        data[size] = Ticket(num, name, address);
        table[index] = size++;
    }
    bool remove(int num) { //удаление билета
        int index = findIndex(num);
        if (index == -1) {
            return false;
        }
        table[index] = EMPTY;
        int i = (index + 1) % capacity;
        while (table[i] != EMPTY) {
            int j = hash(data[table[i]].getNumber());
            if ((i > index && (j <= index || j > i)) || (i < index && (j <= index && j > i))) {
                table[index] = table[i];
                table[i] = EMPTY;
                index = i;
            }
            i = (i + 1) % capacity;
        }
        size--;
        return true;
    }
    Ticket* find(int num) { //поиск билета
        int index = findIndex(num);
        if (index == -1) {
            return nullptr;
        }
        return &data[table[index]];
    }
    void print() const { //вывод всех билетов
        for (int i = 0; i < capacity; i++) {
            if (table[i] != EMPTY) {
                cout << data[table[i]].getNumber() << ": " << data[table[i]].getName() << ", " << data[table[i]].getAddress() << endl;
            }
        }
    }

};

int main() {
    TicketReader tr;
    //int a;
    //string name, address;
    tr.insert(12345, "Name1", "Address1");
    tr.insert(23456, "Name2", "Address2");
    tr.insert(36789, "Name3", "Address3");
    tr.insert(47890, "Name4", "Address4");
    tr.insert(56781, "Name5", "Address5");
    /*for (int i = 0; i < 7; i++) {
        a = generator();
        name = "Name" + to_string(i);
        address = "Address" + to_string(i);

        Ticket t;
        t.setNumber(a);
        t.setName(name);
        t.setName(address);

    }*/
    int cmd;
    do {
        cout << "0 - Exit\n1 - Add new ticket\n2 - Delete ticket\n3 - Find ticket\n4 - Show all tickets\nChoose action: ";
        cin >> cmd;
        switch (cmd) {
        case 1: {
            int num;
            string name, address;
            cout << "Enter number of ticket: ";
            cin >> num;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter address: ";
            getline(cin, address);
            tr.insert(num, name, address);
            cout << "Ticket has been added" << endl;
            break;
        }
        case 2: {
            int num;
            cout << "Enter number of ticket: ";
            cin >> num;
            if (tr.remove(num)) {
                cout << "Ticket has been deleted" << endl;
            }
            else {
                cout << "Ticket is absent" << endl;
            }
            break;
        }
        case 3: {
            int num;
            cout << "Enter number of ticket: ";
            cin >> num;
            Ticket* ticket = tr.find(num);
            if (ticket != nullptr) {
                cout << "Name: " << ticket->getName() << endl;
                cout << "Address: " << ticket->getAddress() << endl;
            }
            else {
                cout << "Ticket is absent" << endl;
            }
            break;
        }
        case 4: {
            tr.print();
            break;
        }
        case 0: {
            cout << "Exit" << endl;
            break;
        }
        default: {
            cout << "No such command. Try again" << endl;
            break;
        }
        }
    } while (cmd != 0);
    return 0;
}
