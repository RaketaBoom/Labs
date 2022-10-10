#include <iostream> // Библиотека ввода-вывода
#include <cmath> // Библиотека математических функций
#include <iomanip> // Библиотека для форматированного вывода
#include <string> // Библиотека для использования переменных типа string
#include <vector>

using namespace std; // Использование стандартного пространства имён

double InCorX() { // Функция корректного ввода для параметра Х
	cout << "Введите значение x:" << endl;
	double t;
	while (!(cin >> t) || (cin.peek() != '\n') || (t >= 1 || t < -1)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Данные некорректны" << endl;
		cout << "Введите значение x:" << endl;
	}
	return t;
}

double InCorA() { // Функция корректного вывода для параметра Alpha
	cout << "Введите значение Alpha:" << endl;
	double t;
	while (!(cin >> t) || (cin.peek() != '\n') || ((t > 1) && (t - ((int)t) != 0)) || (t < 0)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Данные некорректны" << endl;
		cout << "Введите значение Alpha:" << endl;
	}
	return t;
}

bool reset() { // Функция для зацикливания программы
	string s;
	cout << "Запустить программу снова? (Да/Нет)" << endl;
	while (!(cin >> s) || (cin.peek() != '\n') || (s != "Да") && (s != "Нет")) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Данные некорректны" << endl;
		cout << "Запустить программу снова? (Да/Нет)" << endl;
	}
	if (s == "Да") return 1;
	return 0;
}

double seq_el(double x, int n) { // Функция для вычисления элемента последовательности
	double t = 0;
	for (int i = 1; i <= n; i++) {
		t += 1.0 / i;
	}
	return (t * pow(x, n + 1)) * 1.0 / (n + 1);
}

double err_rate(double sn, double an1) { // Функция для вычисления погрешности
	if (sn == 0 && an1 == 0) return 0;
	return abs(an1 / sn);
}

void show(int n, double an, double sn, double en) { // Функция форматированного вывода
	cout << "n = " << setw(6) << n << " | An = " << setw(12) << an << " | Sn = " << setw(12) << sn << " | En = " << setw(12) << en << endl;
}

vector<vector<double>> calculation(bool F, double x, double a) { // Функция для вычислений, возвращает результаты вычислений в виде двумерного вектора
	vector<vector<double>> memory; // Объявление вектора, в который записываются рызультаты вычислений
	double an, an1, en = 1; // Объявление переменных: an - текущий член последовательности, an1 - сдедующий член посл., en - погрешность
	double s = 0;
	if (F == 1) { // Если Alpha - целое число
		cout << "Alpha - это число слагаемых" << endl;
		for (int n = 1; n <= a; n++) { //  Alpha определяет число итераций, n - это номер элемента
			an = seq_el(x, n); // Вычисление текущего члена последовательности 
			s += an; // Вычисление суммы элементов последовательности 
			an1 = seq_el(x, n + 1); // Вычисление следующего члена последовательности 
			en = err_rate(s, an1); // Вычисление погрешности 
			show(n, an, s, en); // Форматированный вывод данных
			memory.push_back({ an, s, en });// Запись результатов
		}
	}
	else { //Если Alpha - нецелое
		cout << "Alpha - это погрешность" << endl;
		int n = 1;
		while (en > a) { // Вычисляем до тех пор, пока погрешность не станет меньше Alpha
			an = seq_el(x, n); // Вычисление текущего члена последовательности 
			s += an; // Вычисление суммы элементов последовательности
			an1 = seq_el(x, n + 1); // Вычисление следующего члена последовательности 
			en = err_rate(s, an1);// Вычисление погрешности 
			show(n, an, s, en);// Форматированный вывод данных
			memory.push_back({ an, s, en }); // Запись результатов
			n++; // Увеличиваем номер на 1
		}
	}
	cout << "Двойная сумма: " << 2 * s << endl;
	return memory;// возвращаем вектор с результатами
}

void partical_calculation(bool F, double x, double a, vector<vector<double>>& memory) { // Функция с частичными вычислениями (Взятие посчитанных результатов из memory)
	double an, an1, en = 1; // Объявление переменных: an - текущий член последовательности, an1 - сдедующий член посл., en - погрешность
	double s = 0;
	int calc_n = 1; // Счетчик выведенных элементов из вектора
	if (F == 1) { // Если Alpha - целое число
		cout << "Alpha - это число слагаемых" << endl;
		cout << "Раннее посчитанные результаты: " << endl;
		while (calc_n <= a && calc_n <= memory.size()) {
			show(calc_n, memory[calc_n - 1][0], memory[calc_n - 1][1], memory[calc_n - 1][2]);
			calc_n++;
		}
		if (calc_n <= a)
			cout << "Новые вычисления: " << endl;
		for (int n = calc_n; n <= a; n++) { //  Alpha определяет число итераций, n - это номер элемента
			an = seq_el(x, n); // Вычисление текущего члена последовательности 
			s += an; // Вычисление суммы элементов последовательности 
			an1 = seq_el(x, n + 1); // Вычисление следующего члена последовательности 
			en = err_rate(s, an1); // Вычисление погрешности 
			show(n, an, s, en); // Форматированный вывод данных
			memory.push_back({ an, s, en });
		}
	}
	else { //Если Alpha - нецелое
		cout << "Alpha - это погрешность" << endl;
		cout << "Раннее посчитанные результаты: " << endl;
		while (memory[(calc_n - 1)%memory.size()][2] > a && calc_n <= memory.size()) {
			show(calc_n, memory[calc_n - 1][0], memory[calc_n - 1][1], memory[calc_n - 1][2]);
			calc_n++;
		}
		en = memory[calc_n - 2][2];
		int n = calc_n;
		if (en > a)
			cout << "Новые вычисления: " << endl;
		while (en > a) { // Вычисляем до тех пор, пока погрешность не станет меньше Alpha
			an = seq_el(x, n); // Вычисление текущего члена последовательности 
			s += an; // Вычисление суммы элементов последовательности
			an1 = seq_el(x, n + 1); // Вычисление следующего члена последовательности 
			en = err_rate(s, an1);// Вычисление погрешности 
			show(n, an, s, en);// Форматированный вывод данных
			memory.push_back({ an, s, en });
			n++; // Увеличиваем номер на 1
		}
	}
	cout << "Двойная сумма: " << 2 * s << endl;
}

int main() { // Главная функция main
	setlocale(0, ""); // Нормальное отображение русского языка в консоли
	system("chcp 1251"); // Нормальное считывание русского языка с консоли
	double x, a; // Переменные параметров X, Alpha

	double x_old = 10;
	vector<vector <double>> memory;

	bool F, play = 1;
	while (play) { // play контроллирует работу программы (выход или перезапуск)
		x = InCorX(); // Инициализация параматра х
		a = InCorA(); // инициализация параметра Alpha
		F = a > 1 ? 1 : 0; //Флажок, фиксирующий тип параметра а (0 - погрешность, 1 - кол-во слагаемых)
		if (x != x_old) {
			memory = calculation(F, x, a); // Вызов функции, реализующей основную логику программы
		}
		else {
			partical_calculation(F, x, a, memory);
		}

		x_old = x;
		play = reset(); // Перезапуск или выход из программы
	}

}
