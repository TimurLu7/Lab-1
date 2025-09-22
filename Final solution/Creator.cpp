#include <iostream>
#include <fstream>
#include <windows.h>
#include "employee.h"
using namespace std;

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            throw runtime_error("Incorrect input.");
        }

        const char* filename = argv[1];
        int count = atoi(argv[2]);
        if (count <= 0) {
            throw runtime_error("Count must be positive");
        }

        ofstream out(filename, ios::binary);
        if (!out.is_open()) {
            throw runtime_error("Can't open file: " + string(filename));
        }
        employee e;
        for (int i = 0; i < count; i++)
        {
            cout << "Enter details employee" << (i + 1) << endl;
            cout << "Number: ";
            cin >> e.num;
            cout << "Name: ";
            cin >> e.name;
            cout << "Hours: ";
            cin >> e.hours;
            out.write((char*)&e, sizeof(employee));
        }
        out.close();
        return 0;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
}
