#include <iostream> // Библиотека для ввода-вывода
#include <fstream> // Библиотека для работы с файлами
#include <vector> // Библиотека для работы с вектором

bool reset() { // Функция для зацикливания программы
	char t;
	std::cout << "Run again? (Y/N)" << std::endl;
	while (!(std::cin >> t) || (std::cin.peek() != '\n') || (t != 'Y' && t != 'N')) {
		std::cout << "Input error" << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Run again? (Y/N)" << std::endl;
	}
	return t == 'Y';
}

char read_file(std::vector <char>& str) { // Функция чтения файла и записи данных в вектор
	
	std::ifstream input("input.txt"); // Создание входного файлового потока input
	if (!input.is_open())
		throw std::exception("This file not found"); // Если файл не найден, выбросить исключение
	if (input.peek() == EOF)
		throw std::exception("This file is empty");  // Если файл пуст, выбросить исключение
	char sym;
	while (input.get(sym) && sym != '\n') {
		if (sym != ' ') 
			str.push_back(sym); //считываение элементов первой строки в вектор
	}
	input.get(sym); // считываение элемента следующей строки
	if (input.peek() != EOF)
		throw std::exception("Data entered incorrectly"); // Если в файле присутствуют лишние символы, выбросить исключение
	input.close(); // Закрываем входящий поток
	return sym; // Возвращаем Символ, частоту каторого нужно определить
}

int freq_of_sym(char sym, std::vector <char> str) { // Функция для подсчета частоты символа в векторе
	int count = 0;
	for (int i : str) { // Проходимся циклом по вектору
		if (i == sym)
			count++; // Если элемент вектора совпадает с sym, то увеличиваем счетчик
	}
	return count; // Возвращаем счётчик
}

void write_file(char symbol, int answer) { // Функция для записи ответа в файл
	std::ofstream output("output.txt"); // Создание выходного файлового потока

	
	output << "Number of symbol \"" << symbol << "\": " << answer; // Запись ответа в файл

}

void delay() { // Функция задержки, спрашиваем пользователя о готовности файла input.txt
	std::cout << "Create the file \"input.txt\" and put input data there" << std::endl;
	std::cout << "Note: if you use Cyrillic, then save the file in ANSI encoding" << std::endl;
	std::cout << "If the file is ready, enter Y: " << std::endl;
	char t;
	while (!(std::cin >> t) || (std::cin.peek() != '\n') || (t != 'Y')) {
		std::cout << "Input error" << std::endl;
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "If the file is ready, enter Y: " << std::endl;
	}
}


int main() {
	bool play = true; // Флажок, от которого зависит будет ли выполняться основное тело программы
	while (play) {
		delay(); // Спрашивваем пользователя, готов ли файл input.txt
		std::vector<char> str;
		try { // Блок кода, в котором могут возникнуть ошибки
			char frequent_symbol = read_file(str); // Считываем данные с файла

			std::cout << "Data successfully read!" << std::endl; // уведомляем об успешном чтении с файла
			
			int answer = freq_of_sym(frequent_symbol, str); // Подсчитываем ответ

			write_file(frequent_symbol, answer); // Записываем ответ в output.txt
			std::cout << "The response has been successfully written to the file!" << std::endl; // Уведомляем об успешной записи в файл
		}
		catch (std::exception& ex) { // Обработка исключение: сообщаем пользователю об ошибке
			std::cout << "Error: " << ex.what() << std::endl;
		} 



		play = reset(); // Перезапуск или выход из программы
	}
}