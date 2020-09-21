#include <iostream>
#include <fstream>

using namespace std;

//Структура дата-время
struct datetime {
    //Поля
    int year,
        month,
        day,
        hour,
        minute,
        second;

    //Метод вывода на экран
    void Show() {
        cout << endl << "NOW: " << day << "." << month << "." << year << "  TIME: " << hour << ":" << minute << ":" << second << endl;
    }


    //Метод, переводящий дату объекта, имеющего структуру дату-время, на следующий день
    void Next_date() {
        day++;  //Добавляем день
        //А дальше проверяем случаи с високосными годами, концами месяцев и конца года
        if (day > 28) {
            if ((day == 29) && (month == 2) && (year % 4 != 0)) {
                day = 1;
                month++;
            }
            else if ((day == 30) && (month == 2)) {
                day = 1;
                month++;
            }
            else if (day == 31) {
                if ((month != 3) && (month != 5) && (month != 7) && (month != 8) && (month != 10) && (month != 12)) {
                    day = 1;
                    month++;
                    if (month > 12) {
                        month = 1;
                        year++;
                    }
                }
            }
            else if (day > 31) {
                day = 1;
                month++;
                if (month > 12) {
                    month = 1;
                    year++;
                }
            }
        }
    }

    //Метод, возвращающий дату объекта на день назад
    void Prev_date() {
        day--; //Отнимаем один день
        //Проверяем случаи високосных годов и т.д.
        if (day == 0) {
            if ((month == 3) && (year % 4 != 0)) {
                day = 28;
                month--;
            }
            else if ((month == 3) && (year % 4 == 0)) {
                day = 29;
                month--;
            }
            else if ((month - 1 == 3) || (month - 1 == 5) || (month - 1 == 7) || (month - 1 == 8) || (month - 1 == 10) || (month - 1 == 0)) {
                day = 31;
                month--;
                if (month == 0) {
                    month = 12;
                    year--;
                }
            }
            else {
                day = 30;
                month--;
            }
        }
    }

};

//--------------------------------------------------------------

int main() {
    //Открываем файл
    ifstream fin("input.txt");
    setlocale (LC_ALL, "");
    //Если файл не открылся
    if (!fin.is_open())
        cout << "Файл не был открыт!" << endl;

    //-----Подсчёт записей в файле-------

    datetime temp;  //Вспомогательнй объект дата-время
    int n = 0;      //Количество записей в файле

    //Пока файл не кончится
    while (!fin.eof()) {
        //Считываем строки и подсчитываем их количество (одна строка = одна дата)
        fin >> temp.day >> temp.month >> temp.year >> temp.hour >> temp.minute >> temp.second;
        n++;
    }

    fin.close(); //Закрываем файл

    //-----Считываем записи из файла в массив------

    //Создаём днамически массив по найденному количеству записей в файле
    datetime* DT;
    DT = new datetime[n];

    fin.open("input.txt"); //Снова открываем файл

    int i = 0;
    while (!fin.eof()) {  //Пока файл не закончится
        //Считываем каждую дату в отдельный элемент массива, где каждый элемент является объектов дата-время
        fin >> DT[i].day >> DT[i].month >> DT[i].year >> DT[i].hour >> DT[i].minute >> DT[i].second;
        i++;
    }

    //--------Выводим на экран записи----------------
    cout << "Данные из файла: " << endl;
    for (int i = 0; i < n; i++) {
        cout << endl << i + 1 << "  NOW DATE: " << DT[i].day << "." << DT[i].month << "." << DT[i].year;
        DT[i].Next_date();
        cout << "  Next date: " << DT[i].day << "." << DT[i].month << "." << DT[i].year;
        DT[i].Prev_date();
        DT[i].Prev_date();
        cout << "  Previous date: " << DT[i].day << "." << DT[i].month << "." << DT[i].year;
        DT[i].Next_date();
        cout << endl;
    }

    //--------Выполняем задание варианта 10---------------------
    cout << endl << endl << "Задание варианта: " << endl;

    for (int i = 0; i < n; i++)

        if (DT[i].day % 2 == 1) {
            DT[i].Next_date();
            if (DT[i].day % 2 == 0) {
                DT[i].Prev_date();
                cout << i + 1 << " : " << DT[i].day << "." << DT[i].month << "." << DT[i].year << " - ";
                DT[i].Next_date();
                cout << DT[i].day << "." << DT[i].month << "." << DT[i].year << " - ";
                DT[i].Prev_date();
                DT[i].Prev_date();
                cout << DT[i].day << "." << DT[i].month << "." << DT[i].year << endl;
                DT[i].Next_date();
            }
            DT[i].Prev_date();
        }
    return 0;
}