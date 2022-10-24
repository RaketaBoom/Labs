#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


long InCorInt(std::string text) { // Функция корректого ввода
	std::string s;
	long t;
	while (true) {
		try {
			std::cout << text << std::endl;
			std::getline(std::cin, s); // вводим значение в s
			t = std::stol(s); // Преобразовываем строку в число
			if (t < 2)
				throw std::exception("The length of the sequence cannot be less than 2"); // Если число меньше 2, выбросить исключение
			for (int i = 0; i < s.length(); i++)
				if (!isdigit(s[i]))
					throw std::exception("The input contains more than just number"); // Если ввод некорректный, выбросить исключение

			return t;
		}
		catch (std::exception& ex) {
			std::cout << "Input error: " << ex.what() << std::endl; // Сообщаем об ошибке
		}
	}

}

std::string type_gen() { // Функция, определяющая тип генерации вектора

	std::string s;
	while (true) {
		try {
			std::cout << "Manual input of vector - M" << std::endl;
			std::cout << "Filling of vector with random numbers - R" << std::endl;
			std::cout << "Filling of vector with random numbers with small value - S" << std::endl;
			std::cout << "Please, enter your method of filling vector (M/R/S)" << std::endl;
			std::getline(std::cin, s);

			if ((s != "M") && (s != "R") && (s != "S"))
				throw std::exception("Invalid value");
			
			return s;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
}

void fill_seq_manual_inp(std::vector<long long>& seq, long n) { // Функция заполнения вектора с клавиатуры
	for (int i = 1; i <= n; i++)
		seq.push_back(InCorInt("Please, enter " + std::to_string(i) + " element"));
}

void fill_seq_rand(std::vector<long long>& seq, long n) { // Функция заполнения вектора случайными числами
	for (int i = 0; i < n; i++)
		seq.push_back(rand());
}

void fill_seq_small_val(std::vector<long long>& seq, long n) { // Функция заполнения вектора случайными числами из [0, 9]
	for (int i = 0; i < n; i++)
		seq.push_back(rand() % 10);
}

      

void show_seq(std::vector<long long>& seq, long n, std::string text) { // Функция корректного вывода вектора в консоль
	std::cout << text << std::endl;
	int limit_out = 20;
	if (n <= limit_out) {  // выводится не более 20 элементов вектора в консоль
		for (int i = 0; i < n; i++)
			std::cout << seq[i] << " ";
	}
	else {
		for (int i = 0; i < limit_out; i++)
			std::cout << seq[i] << " ";
	}
	std::cout << std::endl;
}



void Sort_Seq(std::vector<long long>& seq, long len) { // Функция сортировки вектора методом Шелла


	long step = len / 2; // Формула Шелла для нахождения шага
	while (step > 0) {
		for (int i = step; i < len; i++) {
			for (int j = i; j >= step && seq[j] < seq[j - step]; j -= step) { // Сортировка последовательности элементов, стоящих на расстоянии шага(step)
				seq[j] = seq[j] ^ seq[j - step];
				seq[j - step] = seq[j] ^ seq[j - step];
				seq[j] = seq[j] ^ seq[j - step]; // Обмен значениями при помощи побитового сложения по модулю 2
			}
		}
		step /= 2; // Формула Шелла для нахождения шага
	}

}

void show_time(long double time_Shell, long double time_bibl_sort) {
	if (time_Shell == 0)
		std::cout << "Shell sorting sorted the vector in less than 0.0001 seconds" << std::endl;
	else
		std::cout << "Shell sorting time: " << time_Shell << std::endl;
	if (time_bibl_sort == 0)
		std::cout << "Integrated sorting sorted the vector in less than 0.0001 seconds" << std::endl;
	else
		std::cout << "Integreted sorting time: " << time_bibl_sort << std::endl;
	if (time_Shell > 0 && time_bibl_sort > 0)
		std::cout << "Integrated sorting is " << time_Shell / time_bibl_sort << " times faster" << std::endl;

}

bool reset() { // Функция для зацикливания программы
	std::string s;

	bool correct = false;
	while (!correct) {
		try {
			std::cout << "Run again? (Yes/No)" << std::endl;
			std::getline(std::cin, s);
			if (s != "Yes" && s != "No")
				throw std::exception("Invalid value");
			if (s == "Yes")
				return true;
			return false;

		}
		catch (std::exception& ex) {
			std::cout << "Input error: " << ex.what() << std::endl;
		}
	}
}

int main() {
	bool play = true; // Флажок,контроллирующий выход из программы
	while (play) {
		srand(time(NULL)); // Инициализируем генератор случайных чисел rand при помощи даннных о времени
		long seq_len = InCorInt("Please, Enter sequence length:"); // корректный ввод длины последовательности
		std::vector<long long> seq_orig, seq_sort; // Создание векторов: seq_orig для исходной последовательности, seq_sort - для отсортированнной
		clock_t st_time, fin_time;
		long double time_Shell, time_bibl_sort;

		switch(type_gen()[0]) { //
		case 'M':
			fill_seq_manual_inp(seq_orig, seq_len);
			break;
		case 'R':
			fill_seq_rand(seq_orig, seq_len);
			break;
		case 'S':
			fill_seq_small_val(seq_orig, seq_len);
			break;
		}
		

		show_seq(seq_orig, seq_len, "The original sequence"); // Вывод исходного вектора в консоль

		seq_sort = seq_orig; // Присвоение значений одного вектора другому


		st_time = clock();
		Sort_Seq(seq_sort, seq_len); // Сортировка вектора по методу Шелла
		fin_time = clock();
		time_Shell = (long double)(fin_time - st_time)/ (long double)CLOCKS_PER_SEC;


		show_seq(seq_sort, seq_len, "Sorted sequence: ");// Вывод отсортированного вектора в консоль

		st_time = clock();
		std::sort(seq_orig.begin(), seq_orig.end());
		fin_time = clock();
		time_bibl_sort = (long double)(fin_time - st_time) / (long double)CLOCKS_PER_SEC;

		show_time(time_Shell, time_bibl_sort);

		play = reset();// Выход или перезапуск программы
	}
}