#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

void Print_binary_file(const char* filename) {
    ifstream in(filename, ios::binary);
    if (!in.is_open()) {
        cout << "Can't open binary file " << filename << endl;
        return;
    }

    employee e;
    while (in.read((char*)&e, sizeof(employee))) {
        cout << e.num << " " << e.name << " " << e.hours << endl;
    }
    in.close();
}

void Print_text_file(const char* filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Can't open text file " << filename << endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
}

int main() {
    char bin[50], text[50];
    int count;
    double payment;

    cout << "Enter binary file name: ";
    cin >> bin;
    cout << "Enter number of records: ";
    cin >> count;

    char lpszAppName[]= "C:\\Users\\Timur\\proga\\ОС\\Solution\\Creator.exe";

    STARTUPINFO si;
    PROCESS_INFORMATION piApp;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcessA(NULL, lpszAppName, NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)) {
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
    cout << "Enter hour payment: ";
    cin >> payment;

    char lpszAppName2[]="C:\\Users\\Timur\\proga\\ОС\\Solution\\Reporter.exe";

    if (!CreateProcessA(NULL, lpszAppName2, NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)) {
        cout << "Error starting Reporter, " << GetLastError() << endl;
        return 1;
    }

    WaitForSingleObject(piApp.hProcess, INFINITE);
    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);

    cout << "\nReport content:\n";
    Print_text_file(text);

    return 0;
}