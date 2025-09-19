#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Incorrect input" << endl;
        return 1;
    }

    const char* binfile = argv[1];
    const char* textfile = argv[2];
    double payment = atof(argv[3]);

    ifstream in(binfile, ios::binary);
    ofstream out(textfile);

    if (!in || !out) {
        cout << "Can't open files!" << endl;
        return 1;
    }

    out << "Отчет по файлу: " << binfile << endl;
    out << "Номер\tИмя\tЧасы\tЗарплата\n";

    employee e;
    while (in.read((char*)&e, sizeof(employee))) {
        double pay = e.hours * payment;
        out << e.num << "\t" << e.name << "\t"
            << e.hours << "\t" << fixed << setprecision(2) << pay << "\n";
    }

    in.close();
    out.close();
    return 0;
}
