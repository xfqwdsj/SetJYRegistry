#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 1 || argc > 3) {
        cerr << "Unexpected number of arguments." << endl;
        return 1;
    }
    bool pause = false;
    if ((string) argv[argc - 1] == "-p" || (string) argv[argc - 1] == "--pause") {
        pause = true;
        argc -= 1;
    }
    HKEY hKey;
    LONG openKey = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            R"(SOFTWARE\WOW6432Node\TopDomain\e-Learning Class\Student)",
            0,
            KEY_ALL_ACCESS,
            &hKey
    );
    if (openKey != ERROR_SUCCESS) {
        cerr << "Failed to open registry key. Code: " << openKey << "." << endl;
        return 1;
    }
    DWORD type = REG_BINARY;
    if (argc == 1) {
        DWORD maxValueLength;
        LONG queryInfo = RegQueryInfoKey(
                hKey,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                &maxValueLength,
                nullptr,
                nullptr
        );
        if (queryInfo != ERROR_SUCCESS) {
            cerr << "Failed to query registry info. Code: " << queryInfo << "." << endl;
            return 1;
        }
        BYTE *data = new BYTE[maxValueLength];
        LONG queryValue = RegQueryValueEx(
                hKey,
                "Knock1",
                nullptr,
                &type,
                data,
                &maxValueLength
        );
        if (queryValue != ERROR_SUCCESS) {
            cerr << "Failed to query registry value. Code: " << queryValue << "." << endl;
            return 1;
        }
        for (DWORD i = 0; i < maxValueLength; ++i) {
            cout << hex << setw(2) << setfill('0') << (int) data[i];
        }
        cout << endl;
    } else {
        string input = argv[1];
        unsigned long long size = input.length() / 2;
        BYTE bytes[size];
        for (unsigned long long i = 0; i < size; ++i) {
        	string byte;
        	byte.push_back(input[2 * i]);
        	byte.push_back(input[2 * i + 1]);
        	bytes[i] = strtoul(byte.c_str(), nullptr, 16);
		}
        LONG setValue = RegSetValueEx(
                hKey,
                "Knock1",
                0,
                type,
                bytes,
                size
        );
        if (setValue != ERROR_SUCCESS) {
            cerr << "Failed to set registry value. Code: " << setValue << "." << endl;
            return 1;
        }
        cout << "Success." << endl;
    }
    if (pause) system("pause");
    return 0;
}
