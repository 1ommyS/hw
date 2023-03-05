#include "/usr/local/include/bits/stdc++.h"
#include <map>
#include "StudentInfo.h"
#include "functions.h"

using namespace std;

int main() {
    int faculty, group, course;
    string name;

    int N;
    cout << "Введите количество студентов: ";
    cin >> N;

    vector<StudentInfo> students;
    for (int i = 0; i < N; i++) {

        cout << "Введите факультет: ";
        cin >> faculty;
        cout << "Введите курс: ";
        cin >> course;

        cout << "Введите группу: ";
        cin >> group;

        cout << "Введите ФИО (Вместо пробелов _): ";
        cin >> name;

        StudentInfo studentInfo = StudentInfo(faculty, group, course, name);
        students.push_back(studentInfo);
    }
    int amount_of_bits = (3 + 3 + 7 + 8) * N;

    for (const auto &student: students) {
        for (int _ = 0; _ < student.getName().length(); _++) amount_of_bits += 5;
    }
    const int bytes = amount_of_bits / 8 + (amount_of_bits % 8 == 0 ? 0 : 1);

    cout << "Вы ввели информацию о " << N << " студентах.\n";
    cout << "На ее кодирование потребуется " << amount_of_bits << " бит или же \n";
    cout << bytes << " целых байт." << endl;

    map<char, int> rel;
    for (int i = 0; i < 26; ++i)
        rel[(char) (65 + i)] = i;
    rel['_'] = 26;

    char *pointer;
    pointer = new char[bytes];

    int byte = 0, // current bytes
    byte_size = 0, // 0..8
    index = 0; // current index, index + pointer - new el

    for (int i = 0; i < N; ++i) {
        auto _faculty = students[i].getFaculty();
        auto _group = students[i].getGroup();
        auto _course = students[i].getCourse();
        auto _name = students[i].getName();

        write(pointer, byte, byte_size, index, _faculty, 3);
        write(pointer, byte, byte_size, index, _course, 3);
        write(pointer, byte, byte_size, index, _group, 7);
        write(pointer, byte, byte_size, index, _name.length(), 8);

        for (char s: students[i].getName())
            write(pointer, byte, byte_size, index, rel[s], 5);
    }
    if (byte_size != 0)
        write(pointer, byte, byte_size, index, 0, 8 - byte_size);
    cout << "Запись в память завершена\nБайты в двоичном представлении выглядят так:" << endl;

    unsigned char result[bytes];
    for (int i = 0; i < bytes; ++i) {
        int value = *(pointer + i);
        value = value < 0 ? -1 * value - 1 : value;

        vector<char> res;
        while (value != 0) {
            res.push_back(value % 2);
            value = value / 2;
        }
        while (res.size() < 7)
            res.push_back(0);

        if (value < 0)
            for (int i = 0; i < 7; ++i)
                res[i] = !res[i];

        res.push_back(value < 0);

        reverse(res.begin(), res.end());

        for (int j = 0; j < 8; ++j)
            cout << (int) res[j];
        cout << " ";

        unsigned char b = 0;
        for (int j = 0; j < 8; ++j)
            b += pow(2, 7 - j) * res[j];
        *(result + i) = b;
    }
    cout << "Восстанавливаю данные о студентах:" << endl;
    byte_size = 8;
    index = 0;
    for (int i = 0; i < N; ++i) {
        unsigned char _faq = read(result, index, byte_size, 3),
                _course = read(result, index, byte_size, 3),
                _group = read(result, index, byte_size, 7),
                len = read(result, index, byte_size, 8);

        char _name[len];
        for (int j = 0; j < len; ++j)
            _name[j] = rel[(int) read(result, index, byte_size, 5)];

        cout << (int) _faq + 1 << "-" << (int) _course << (_group < 10 ? "0" : "") << (int) _group << " ";
        for (int j = 0; j < len; ++j)
            cout << _name[j];
        cout << endl;
    }
}