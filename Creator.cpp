#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct employee {
    int num;        
    char name[10];  
    double hours;   
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Incorrect input" << endl;
        return 1;
    }

    const char* filename = argv[1];
    int count = std::stoi(argv[2]);

    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Can't open file" << endl;
        return 1;
    }
    employee e;
    for (int i = 0; i < count; i++) 
    {
        cout << "Введите данные сотрудника №" << (i + 1) << endl;
        cout << "Номер: "; 
        cin >> emp.num;
        cout << "Имя: ";
        cin >> emp.name;
        cout << "Часы: ";
        cin >> emp.hours;
        out.write((char*)&emp, sizeof(employee));
    }
    out.close();
    return 0;
}
