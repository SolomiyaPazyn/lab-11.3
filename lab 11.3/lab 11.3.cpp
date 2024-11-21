#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

struct TrainInfo {
    string destination;  // Пункт призначення
    string type;         // Тип потяга
    int departureTime;   // Час відправлення
};

const int MAX_TRAINS = 1000; // Максимальна кількість потягів

// Функція створення нового файлу або відкриття для додавання записів
void createOrAppendFile(string filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Помилка при створенні/відкритті файлу" << endl;
    }
    file.close();
}

// Функція додавання інформації про потяг до файлу
void addTrainInfo(string filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Помилка при відкритті файлу" << endl;
        return;
    }

    TrainInfo train;
    cout << "Введіть назву пункту призначення: ";
    getline(cin, train.destination);

    cout << "Введіть тип потяга (звичайний/підвищеного комфорту/швидкісний-експрес): ";
    cin >> train.type;
    while (train.type != "звичайний" && train.type != "підвищеного комфорту" && train.type != "швидкісний-експрес") {
        cout << "Некоректний тип потяга. Спробуйте ще раз: ";
        cin >> train.type;
    }
    cin.ignore(); // Ігноруємо \n після вводу типу

    cout << "Введіть час відправлення (24-годинний формат, наприклад, 1530 для 15:30): ";
    cin >> train.departureTime;
    cin.ignore(); // Ігноруємо \n після вводу часу

    file << train.destination << ", " << train.type << ", " << train.departureTime << endl;
    file.close();
    cout << "Інформація про потяг додана до файлу." << endl;
}

// Функція виводу інформації про потяги, що відправляються після заданого часу
void displayTrainsAfterTime(string filename, int time) {
    ifstream file(filename);
    if (!file) {
        cerr << "Помилка при відкритті файлу" << endl;
        return;
    }

    TrainInfo trains[MAX_TRAINS]; // Масив для збереження інформації про потяги
    int count = 0;               // Лічильник кількості потягів

    string line;
    while (getline(file, line) && count < MAX_TRAINS) {
        size_t comma1 = line.find(',');                // Знаходимо першу кому
        size_t comma2 = line.find(',', comma1 + 1);    // Знаходимо другу кому
        trains[count].destination = line.substr(0, comma1);
        trains[count].type = line.substr(comma1 + 2, comma2 - comma1 - 2);
        trains[count].departureTime = stoi(line.substr(comma2 + 2));
        ++count;
    }
    file.close();

    bool found = false; // Флаг для перевірки, чи знайдено результати
    cout << "Потяги, що відправляються після " << time << ":" << endl;
    cout << left << setw(20) << "Пункт призначення"
        << setw(30) << "Тип"
        << right << setw(10) << "Час" << endl;
    cout << string(60, '-') << endl;

    // Виводимо потяги, які відправляються після заданого часу
    for (int i = 0; i < count; ++i) {
        if (trains[i].departureTime >= time) {
            found = true;
            cout << left << setw(20) << trains[i].destination
                << setw(30) << trains[i].type
                << right << setw(10) << trains[i].departureTime << endl;
        }
    }

    if (!found) {
        cout << "Немає потягів, що відправляються після заданого часу." << endl;
    }
}

// Функція для відображення меню і виконання вибраних дій
void menu(string filename) {
    int option, departureTime;
    while (true) {
        cout << "Меню:\n"
            << "[1] Створити/додати інформацію до файлу\n"
            << "[2] Вивести інформацію про потяги, що відправляються після вказаного часу\n"
            << "[3] Вихід\n: ";
        cin >> option;
        cin.ignore(); // Ігноруємо \n після вводу опції

        switch (option) {
        case 1:
            addTrainInfo(filename); // Додати інформацію про потяг
            break;
        case 2:
            cout << "Введіть час у 24-годинному форматі (наприклад, 1530 для 15:30): ";
            cin >> departureTime;
            cin.ignore(); // Ігноруємо \n після вводу часу
            displayTrainsAfterTime(filename, departureTime); // Вивести потяги після заданого часу
            break;
        case 3:
            return; // Завершити програму
        default:
            cout << "Неправильний ввід!" << endl;
            break;
        }
    }
}

// Головна функція
int main() {
    SetConsoleCP(1251);        // Налаштування кодування для вводу
    SetConsoleOutputCP(1251); // Налаштування кодування для виводу

    string filename;
    cout << "Введіть ім'я файлу: ";
    getline(cin, filename);

    createOrAppendFile(filename); // Створення/відкриття файлу
    menu(filename);              // Відображення меню

    return 0;
}
