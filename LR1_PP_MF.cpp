#include <iostream>
#include <string>

using namespace std;



int InCorN() { // Функция корректного ввода для n
	int t;
	cout << "Введите количество строк в матрице: " << endl;
	while (!(cin >> t) || cin.peek() != '\n' || t <= 0) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Данные некорректны" << endl;
		cout << "Введите количество строк в матрице: " << endl;
	}
	return t;
}

int InCorM() { // Функция корректного ввода для m
	int t;
	cout << "Введите количество столбцов в матрице: " << endl;
	while (!(cin >> t) || cin.peek() != '\n' || t <= 0) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Данные некорректны" << endl;
		cout << "Введите количество столбцов в матрице: " << endl;
	}
	return t;
}


bool RowIsCor(string s, int m) { // Функция, проверяющая корректный ввод строки
	int count_space = 0, count_p = 0, count_m = 0;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == false && (s[i] != ',' && s[i] != '-' && s[i] != ' ')) return false;
		else {
			if (s[i] == ',') {
				if (i > 0) {
					if (isdigit(s[i - 1]) == false) return false;
					else {
						count_p++;
						if (count_p > 1) return false;
					}
				}
				else return false;
			}


			if (s[i] == '-') {
				if (i < s.length() - 1) {
					if (isdigit(s[i + 1]) == false) return false;
					count_m++;
					if (count_m > 1) return false;
				}
				else {
					return false;
				}

			}
			if (s[i] == ' ') {
				if (i > 0 && i < s.length() - 1) {
					if (isdigit(s[i - 1]) == false) return false;
					if (s[i + 1] == ' ' || s[i + 1] == ',') return false;
					else {
						count_space++;
						count_p = 0;
						count_m = 0;
						if (count_space > (m - 1)) return false;
					}
				}
				else {
					return false;
				}
			}
		}
	}
	if (count_space != (m - 1)) return false;
	return true;
}

void InCorRow(double* arr, int m) { // Функция заполенения строки матрицы

	string s;
	bool F = 1;
	cout << "Введите строку матрицы" << endl;
	getline(cin, s);
	if (RowIsCor(s, m)) F = 0;
	while (F) {
		cout << "Данные некорректны" << endl;
		cout << "Введите строку матрицы" << endl;
		getline(cin, s);
		if (RowIsCor(s, m)) F = 0;
	}
	int b = 0;
	int ind = 0;
	for (int j = 0; j < s.length(); j++) {
		if (s[j] == ' ') {
			arr[ind] = stod(s.substr(b, j - b));
			b = j + 1;
			ind++;
		}
	}
	arr[m - 1] = stod(s.substr(b, s.length() - b));

	
}

double** create_arr(int n, int m) { // Функция создания матрицы заданного размера
	double** arr = new double* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new double[m];
	}
	return arr;
}

void MinMaxArr(double** arr, int n, int m) { // Функция нахождения минимального и максимального элементов
	double Min = arr[0][0], Max = arr[0][0];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] < Min) Min = arr[i][j];
			if (arr[i][j] > Max) Max = arr[i][j];
		}
	}
	cout << "Минимальный элемент матрицы: " << Min << endl;
	cout << "Максимальный элемент матрицы: " << Max << endl;
}

void show_arr(double** arr, int n, int m) {
	cout << "Исходная матрица: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
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
void del_arr(double** arr, int n) { // Функция для удаления динамического массива
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

int main() {
	setlocale(0, ""); // Нормальное отображение русского языка
	system("chcp 1251"); // Нормальный ввод русского языка
	int n, m; // Переменные размеров матрицы
	bool play = 1; // Флажок, контроллирующий работу цикла
	while (play) {
		n = InCorN();// Ввод размеров матрицы
		m = InCorM();
		while (n + m == 2) {
			cout << "Данные некорректны: массив из 1 элемента" << endl;
			n = InCorN();
			m = InCorM();
		}
		double** arr = create_arr(n, m); // Объявление массива
		cin.clear(); // Очищаем флажок cin
		while (cin.get() != '\n'); // Очищаем входной буфер
		for (int i = 0; i < n; i++) {
			InCorRow(arr[i], m); // Инициализация матрицы
		}

		show_arr(arr, n, m); // Вывод матрицы


		MinMaxArr(arr, n, m); // Нахождение Максимальное и Минимальное элементов

		del_arr(arr, n); // Удаление матрицы
		
		play = reset();
	}
}