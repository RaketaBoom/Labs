#include <iostream>// Подключаем стандартные библиотеки 
#include <vector>
#include <string>

using namespace std; //Вводим пространство имён

bool IsNum(string s) { // функция проверки на число
    int count = 0;
    for (int i = 0; i < s.length(); i++) { // Проверяем кол-во запятых
        if (s[i] == ',') count++;
        if (count > 1) return false; // Если кол-во запятых более одного, то это не число
    }
    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i]) == false && s[i] != ',') {
            return false; // Если символ - это не цифра и не запятая, то это не число
        }
    }
    return true;// Если строка дошла до конца, значит это число
}

int main()
{
    setlocale(0, "");
    
    vector<float> seq;//Объявляем вектор для хранения последовательности
    bool F = true; // Флажок, контролирующий выход из цикла
    float num; // Переменная для записи в вектор
    string s; // переменная для проверки на число
    string Quit = "No"; // Переменная выхода из программы

    while (Quit == "No") {
        F = true;
        while (F) {
            cout << "Please, enter your number" << endl;

            cin >> s; //Ввод числа
            if (IsNum(s)) { // Проверка на число
                num = stof(s);
                if (num != 0) { // Если число не равно 0
                    if (num > 0) seq.push_back(num); // если число больше 0, то записываем его в вектор
                    else cout << "Incorrect data" << endl; // если число отрицательное,то уведомляем пользователя о некорректных данных 
                }
                else F = false; // Иначе выходим из цикла
            }
            else cout << "Incorrect data" << endl; // если в строке s есть символ-Не цифра, то уведомляем пользователя о некорректных данных
        }
        float Min = seq[0], Max = seq[0], arnum = 0, Sum = 0; //Переменные Минимума,Максимума, Среднего арифметического и Суммы последовательности

        for (int i = 0; i < seq.size(); i++) {
            if (Min > seq[i]) Min = seq[i];// Подбираем Минимум
            if (Max < seq[i]) Max = seq[i];// Подбираем Максимум
            Sum += seq[i]; // Считаем сумму
        }
        arnum = Sum / seq.size(); // Считаем среднее арифметическое

        cout << "Minimum number is " << Min << endl;//выводим ответ
        cout << "Maximum number is " << Max << endl;
        cout << "Arithmetic mean is " << arnum << endl;
        cout << "Quit Yes/No?" << endl; 
        cin >> Quit;
        while ((Quit != "Yes") && (Quit != "No")) { 
            cout << "Incorrect data" << endl;
            cout << "Quit Yes/No?" << endl;
            cin >> Quit;
        }
        // запрашиваем переменную Quit, от которой зависит выход из программы

    }
    return 0;
}