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
    int count = atoi(argv[2]);

    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Can't open file" << endl;
        return 1;
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

