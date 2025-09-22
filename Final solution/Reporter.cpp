#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include "employee.h"
using namespace std;

int main(int argc, char* argv[]) {
    try {
        if (argc < 4) {
            throw runtime_error("Incorrect input.");
        }

        const char* binfile = argv[1];
        const char* textfile = argv[2];
        double payment = atof(argv[3]);
        if (payment < 0) {
            throw runtime_error("Payment can't be negative");
        }

        ifstream in(binfile, ios::binary);
        if (!in.is_open()) {
            throw runtime_error("Can't open input file: " + string(binfile));
        }
        ofstream out(textfile);

        if (!out.is_open()) {
            in.close();
            throw runtime_error("Can't open output file: " + string(textfile));
        }

        out << "File report: " << binfile << endl;
        out << "Number\tName\tHours\tSalary\n";

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
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
}
