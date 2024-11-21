#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

struct TrainInfo {
    string destination;  // ����� �����������
    string type;         // ��� ������
    int departureTime;   // ��� �����������
};

const int MAX_TRAINS = 1000; // ����������� ������� ������

// ������� ��������� ������ ����� ��� �������� ��� ��������� ������
void createOrAppendFile(string filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "������� ��� ��������/������� �����" << endl;
    }
    file.close();
}

// ������� ��������� ���������� ��� ����� �� �����
void addTrainInfo(string filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "������� ��� ������� �����" << endl;
        return;
    }

    TrainInfo train;
    cout << "������ ����� ������ �����������: ";
    getline(cin, train.destination);

    cout << "������ ��� ������ (���������/���������� ��������/���������-�������): ";
    cin >> train.type;
    while (train.type != "���������" && train.type != "���������� ��������" && train.type != "���������-�������") {
        cout << "����������� ��� ������. ��������� �� ���: ";
        cin >> train.type;
    }
    cin.ignore(); // �������� \n ���� ����� ����

    cout << "������ ��� ����������� (24-�������� ������, ���������, 1530 ��� 15:30): ";
    cin >> train.departureTime;
    cin.ignore(); // �������� \n ���� ����� ����

    file << train.destination << ", " << train.type << ", " << train.departureTime << endl;
    file.close();
    cout << "���������� ��� ����� ������ �� �����." << endl;
}

// ������� ������ ���������� ��� ������, �� ������������� ���� �������� ����
void displayTrainsAfterTime(string filename, int time) {
    ifstream file(filename);
    if (!file) {
        cerr << "������� ��� ������� �����" << endl;
        return;
    }

    TrainInfo trains[MAX_TRAINS]; // ����� ��� ���������� ���������� ��� ������
    int count = 0;               // ˳������� ������� ������

    string line;
    while (getline(file, line) && count < MAX_TRAINS) {
        size_t comma1 = line.find(',');                // ��������� ����� ����
        size_t comma2 = line.find(',', comma1 + 1);    // ��������� ����� ����
        trains[count].destination = line.substr(0, comma1);
        trains[count].type = line.substr(comma1 + 2, comma2 - comma1 - 2);
        trains[count].departureTime = stoi(line.substr(comma2 + 2));
        ++count;
    }
    file.close();

    bool found = false; // ���� ��� ��������, �� �������� ����������
    cout << "������, �� ������������� ���� " << time << ":" << endl;
    cout << left << setw(20) << "����� �����������"
        << setw(30) << "���"
        << right << setw(10) << "���" << endl;
    cout << string(60, '-') << endl;

    // �������� ������, �� ������������� ���� �������� ����
    for (int i = 0; i < count; ++i) {
        if (trains[i].departureTime >= time) {
            found = true;
            cout << left << setw(20) << trains[i].destination
                << setw(30) << trains[i].type
                << right << setw(10) << trains[i].departureTime << endl;
        }
    }

    if (!found) {
        cout << "���� ������, �� ������������� ���� �������� ����." << endl;
    }
}

// ������� ��� ����������� ���� � ��������� �������� ��
void menu(string filename) {
    int option, departureTime;
    while (true) {
        cout << "����:\n"
            << "[1] ��������/������ ���������� �� �����\n"
            << "[2] ������� ���������� ��� ������, �� ������������� ���� ��������� ����\n"
            << "[3] �����\n: ";
        cin >> option;
        cin.ignore(); // �������� \n ���� ����� �����

        switch (option) {
        case 1:
            addTrainInfo(filename); // ������ ���������� ��� �����
            break;
        case 2:
            cout << "������ ��� � 24-��������� ������ (���������, 1530 ��� 15:30): ";
            cin >> departureTime;
            cin.ignore(); // �������� \n ���� ����� ����
            displayTrainsAfterTime(filename, departureTime); // ������� ������ ���� �������� ����
            break;
        case 3:
            return; // ��������� ��������
        default:
            cout << "������������ ���!" << endl;
            break;
        }
    }
}

// ������� �������
int main() {
    SetConsoleCP(1251);        // ������������ ��������� ��� �����
    SetConsoleOutputCP(1251); // ������������ ��������� ��� ������

    string filename;
    cout << "������ ��'� �����: ";
    getline(cin, filename);

    createOrAppendFile(filename); // ���������/�������� �����
    menu(filename);              // ³���������� ����

    return 0;
}
