#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // ������� ������ ������� ���������
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create snapshot" << std::endl;
        return 1;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32); // ������������� ������ ���������

    if (!Process32First(snapshot, &processEntry)) { // �������� ���������� � ������ ��������
        std::cerr << "Failed to get process information" << std::endl;
        CloseHandle(snapshot);
        return 1;
    }

    std::cout << "Process List:" << std::endl;

    do {
        std::cout << "Process ID: " << processEntry.th32ProcessID << std::endl; // ������� ������������� ��������
        std::cout << "Process Name: " << processEntry.szExeFile << std::endl; // ������� ��� ��������

        // ���� ������� ������� ��� �������
        if (processEntry.dwFlags == 0) {
            std::cout << "(Hidden Process)" << std::endl;
        }

        std::cout << std::endl;

    } while (Process32Next(snapshot, &processEntry)); // �������� ���������� � ��������� ��������

    CloseHandle(snapshot); // ��������� ���������� ������ ���������

    return 0;
}
