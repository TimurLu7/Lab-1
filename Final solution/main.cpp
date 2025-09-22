#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"
using namespace std;

void Print_binary_file(const char* filename) {
    try {
        ifstream in(filename, ios::binary);
        if (!in.is_open()) {
            throw runtime_error("Can't open binary file " + string(filename));
        }
        employee e;
        while (in.read((char*)&e, sizeof(employee))) {
            cout << e.num << " " << e.name << " " << e.hours << endl;
        }
        in.close();
    }
    catch (const exception& e) {
        throw runtime_error("Print_binary_file error: " + string(e.what()));
    }
}

void Print_text_file(const char* filename) {
    try {
        ifstream in(filename);
        if (!in.is_open()) {
            throw runtime_error("Can't open text file " + string(filename));
        }

        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
    catch (const exception& e) {
        throw runtime_error("Print_text_file error: " + string(e.what()));
    }
}

int main() {
    char bin[100], text[100];
    int count;
    double payment;

    cout << "Enter binary file name: ";
    cin >> bin;
    if (cin.fail()) {
        throw runtime_error("Error binary file name");
    }
    cout << "Enter number of records: ";
    cin >> count;
    if (cin.fail() || count <= 0) {
        throw runtime_error("Error number of records");
    }

    string creator = "Creator.exe " + string(bin) + " " + to_string(count);

    STARTUPINFO si;
    PROCESS_INFORMATION piApp;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcessA(NULL, (LPSTR)creator.c_str(), NULL, NULL, FALSE,
        NULL, NULL, NULL, &si, &piApp)) {
        cout << "Error opening Creator, " << GetLastError() << endl;
        return 1;
    }
    WaitForSingleObject(piApp.hProcess, INFINITE);
    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);

    cout << "\nBinary file content:\n";
    Print_binary_file(bin);

    cout << "\nEnter report file name: ";
    cin >> text;
    if (cin.fail()) {
        throw runtime_error("Error text file name");
    }
    cout << "Enter hour payment: ";
    cin >> payment;
    if (cin.fail() || payment < 0) {
        throw runtime_error("Wrong payment");
    }

    string reporter = "Reporter.exe " + string(bin) + " " + string(text) + " " + to_string(payment);

    if (!CreateProcessA(NULL, (LPSTR)reporter.c_str(), NULL, NULL, FALSE,
        NULL, NULL, NULL, &si, &piApp)) {
        cout << "Error starting Reporter, " << GetLastError() << endl;
        return 1;
    }

    WaitForSingleObject(piApp.hProcess, INFINITE);
    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);

    cout << "\nReport content:\n";
    Print_text_file(text);

    cout << "\nPress Enter to exit...";
    cin.ignore(); 
    cin.get();    
    return 0;
}