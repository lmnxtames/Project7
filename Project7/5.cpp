#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // Создаем снимок текущих процессов
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create snapshot" << std::endl;
        return 1;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32); // Устанавливаем размер структуры

    if (!Process32First(snapshot, &processEntry)) { // Получаем информацию о первом процессе
        std::cerr << "Failed to get process information" << std::endl;
        CloseHandle(snapshot);
        return 1;
    }

    std::cout << "Process List:" << std::endl;

    do {
        std::cout << "Process ID: " << processEntry.th32ProcessID << std::endl; // Выводим идентификатор процесса
        std::cout << "Process Name: " << processEntry.szExeFile << std::endl; // Выводим имя процесса

        // Если процесс помечен как скрытый
        if (processEntry.dwFlags == 0) {
            std::cout << "(Hidden Process)" << std::endl;
        }

        std::cout << std::endl;

    } while (Process32Next(snapshot, &processEntry)); // Получаем информацию о следующем процессе

    CloseHandle(snapshot); // Закрываем дескриптор снимка процессов

    return 0;
}
