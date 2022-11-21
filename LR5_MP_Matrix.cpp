#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>

void InCorIntSize(std::string text, std::istream& in, int& n, int& m) {
	std::string s;

	
	while (true) {
		try {
			std::string n_str, m_str;
			std::cout << text << std::endl;
			std::getline(in, s);
			bool F = false;
			for (char i : s) {
				if (i == ' ' && F)
					throw std::exception("The input contains more than just number");
				if (i == ' ') {
					F = true;
				}
				if (!isdigit((unsigned)i) && i != ' ')
					throw std::exception("The input contains more than just number");
				
				if (F && i != ' ')
					m_str.push_back(i);
				else
					n_str.push_back(i);
			}
			if (!F) {
				std::exception("Incorrect input");
			}


			n = std::stoi(n_str);
			m = std::stoi(m_str);
			if (n < 2 || m < 2)
				throw std::exception("The number less or equal 1: No sense");

			return;
			
		}
		catch (std::exception& ex) {
			std::cout << "Input error: " << ex.what() << std::endl;
		}
	}
}

std::string type_input() { 

	std::string s;
	while (true) {
		try {
			
			std::cout << "Console Input - C" << std::endl;
			std::cout << "Input from a file - F" << std::endl;
			std::cout << "Please, enter your method of input data (C/F))" << std::endl;
			std::getline(std::cin, s);

			if ((s != "C") && (s != "F"))
				throw std::exception("Invalid value");

			return s;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
}

std::string type_output() {

	std::string s;
	while (true) {
		try {

			std::cout << "Answer in console - C" << std::endl;
			std::cout << "Answer in file - F" << std::endl;
			std::cout << "Please, enter your method of output (C/F))" << std::endl;
			std::getline(std::cin, s);

			if ((s != "C") && (s != "F"))
				throw std::exception("Invalid value");

			return s;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
}

long InCorIntLen(std::string text) { // Функция корректого ввода
	std::string s;
	long t;
	while (true) {
		try {
			std::cout << text << std::endl;
			std::getline(std::cin, s); // вводим значение в s
			t = std::stol(s); // Преобразовываем строку в число
			if (t < 1)
				throw std::exception("The length of the sequence cannot be less than 1"); // Если число меньше 2, выбросить исключение
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

class Fraction {
private:
	int numerator;
	int denumerator;
	int lcm(int a, int b)
	{
		int temp = gcd(a, b);

		return temp ? (a / temp * b) : 0;
	}
	int gcd(int a, int b) {
		a = abs(a);
		b = abs(b);
		while (a && b)
			if (a > b) a %= b;
			else b %= a;
		return a + b > 0 ? a + b: 1;
	}
	void reduse(int& num, int& denum) {
		int value_gcd = gcd(num, denum);
		num /= value_gcd;
		denum /= value_gcd;
	}
public:
	Fraction() {
		numerator = 0;
		denumerator = 1;
	}
	Fraction(int n) {
		numerator = n;
		denumerator = 1;
	}
	Fraction(int n, int d) {
		numerator = n;
		denumerator = d;
		reduse(numerator, denumerator);
	}

	Fraction(const Fraction& frac) {
		numerator = frac.numerator;
		denumerator = frac.denumerator;
	}
	Fraction& operator= (const Fraction& frac) {
		numerator = frac.numerator;
		denumerator = frac.denumerator;
		return (*this);
	}
	Fraction& operator+= (const Fraction& frac) {
		int value_lcm = lcm(denumerator, frac.denumerator);
		numerator = numerator * value_lcm / denumerator + frac.numerator * value_lcm / frac.denumerator;
		denumerator = value_lcm;
		reduse(numerator, denumerator);
		return (*this);
	}
	Fraction operator+ (const Fraction& frac) {
		int value_lcm = lcm(denumerator, frac.denumerator);
		int num = numerator * value_lcm / denumerator + frac.numerator * value_lcm / frac.denumerator;
		int denum = value_lcm;
		reduse(num, denum);
		return Fraction(num, denum);
	}
	Fraction& operator*= (const Fraction& frac) {
		int wrong_num = numerator * frac.numerator;
		int wrong_denum = denumerator * frac.denumerator;
		int value_gcd = gcd(wrong_num, wrong_denum);
		numerator = wrong_denum > 0 ? wrong_num / value_gcd : (-1) * wrong_num / value_gcd;
		denumerator = abs(wrong_denum / value_gcd);
		return (*this);
	}
	Fraction operator* (const Fraction& frac) {
		int wrong_num = numerator * frac.numerator;
		int wrong_denum = denumerator * frac.denumerator;
		int value_gcd = gcd(wrong_num, wrong_denum);
		wrong_num = wrong_denum > 0 ? wrong_num : (-1) * wrong_num;
		wrong_denum = abs(wrong_denum);
		return Fraction(wrong_num / value_gcd, wrong_denum / value_gcd);
	}
	Fraction& operator-= (const Fraction& frac) {
		int value_lcm = lcm(denumerator, frac.denumerator);
		numerator = numerator * value_lcm / denumerator - frac.numerator * value_lcm / frac.denumerator;
		denumerator = value_lcm;
		reduse(numerator, denumerator);
		return (*this);
	}
	Fraction operator- (const Fraction& frac) {
		int value_lcm = lcm(denumerator, frac.denumerator);
		int num = numerator * value_lcm / denumerator - frac.numerator * value_lcm / frac.denumerator;
		int denum = value_lcm;
		reduse(num, denum);
		return Fraction(num, denum);
	}
	Fraction& operator/= (const Fraction& frac) {
		int wrong_num = numerator * frac.denumerator;
		int wrong_denum = denumerator * frac.numerator;
		int value_gcd = gcd(wrong_num, wrong_denum);
		numerator = wrong_denum > 0 ? wrong_num / value_gcd: (-1)*wrong_num/value_gcd;
		denumerator = wrong_denum > 0 ? abs(wrong_denum / value_gcd): 1;

		return (*this);
	}
	Fraction operator/ (const Fraction& frac) {
		int wrong_num = numerator * frac.denumerator;
		int wrong_denum = denumerator * frac.numerator;
		int value_gcd = gcd(wrong_num, wrong_denum);
		wrong_num = wrong_denum > 0 ? wrong_num : (-1) * wrong_num;
		wrong_denum = abs(wrong_denum);
		return Fraction(wrong_num / value_gcd, wrong_denum / value_gcd);
	}
	Fraction& operator= (const int n) {
		Fraction frac(n);
		numerator = frac.numerator;
		denumerator = frac.denumerator;
		reduse(numerator, denumerator);
		return (*this);
	}
	Fraction& operator+= (const int n) {
		Fraction frac(n);
		int value_lcm = lcm(denumerator, frac.denumerator);
		numerator = numerator * value_lcm / denumerator + frac.numerator * value_lcm / frac.denumerator;
		denumerator = value_lcm;
		reduse(numerator, denumerator);
		return (*this);
	}
	Fraction operator+ (const int n) {
		Fraction frac(n);
		int value_lcm = lcm(denumerator, frac.denumerator);
		int num = numerator * value_lcm / denumerator + frac.numerator * value_lcm / frac.denumerator;
		int denum = value_lcm;
		reduse(num, denum);
		return Fraction(num, denum);
	}
	Fraction& operator*= (const int n) {
		Fraction frac(n);
		int wrong_num = numerator * frac.numerator;
		int wrong_denum = denumerator * frac.denumerator;
		int value_gcd = gcd(wrong_num, wrong_denum);
		return (*this);
	}
	Fraction operator* (const int n) {
		Fraction frac(n);
		int wrong_num = numerator * frac.numerator;
		int wrong_denum = denumerator * frac.denumerator;
		int value_gcd = gcd(wrong_num, wrong_denum);
		return Fraction(wrong_num / value_gcd, wrong_denum / value_gcd);
	}
	friend std::ostream& operator<< (std::ostream& out, const Fraction& frac) {
		if (frac.denumerator == 1)
			out << frac.numerator;
		else
			out << frac.numerator << '/' << frac.denumerator;
		return out;
	}

	friend std::istream& operator>> (std::istream& in, Fraction& frac) {
		if (in.peek() == ' ' || isalpha(in.peek()) && in.peek() != '/') {
			while (in.get() != '\n');
			throw std::exception("Incorrect fraction");
		}
		in >> frac.numerator;
		if (in.peek() == '\n')
			frac.denumerator = 1;
		else if (in.get() == '/' && in.peek() != '\n')
			in >> frac.denumerator;
		else {
			while (in.get() != '\n');
			throw std::exception("Incorrect fraction");
		}
		return in;
	}

	operator bool() const { return numerator != 0; }

	int GetNum() {
		return numerator;
	}

};

class Matrix {
private:
	int n, m;
	std::vector<std::vector <Fraction>> A;
	int Min(int a, int b) {
		return a > b ? b : a;
	}
	void division_row(std::vector<std::vector <Fraction>>& B, Fraction a, int k) {
		for (int i = k; i < m; i++) {
			B[k][i] /= a;
		}
	}
	
public:
	Matrix() {};
	Matrix(int n, int m, std::vector<std::vector <Fraction>> B) {
		this->n = n;
		this->m = m;
		this->A = B;
	}
	void Replace_rows(std::vector<std::vector <Fraction>>& B, int i1, int i2) {
		std::swap(B[i1], B[i2]);
	}
	void Replace_cols(std::vector<std::vector <Fraction>>& B, int j1, int j2) {
		for (int i = 0; i < n; i++) {
			std::swap(B[i][j1], B[i][j2]);
		}
	}

	void create_zero_in_row(std::vector<std::vector <Fraction>>& B, int k) {
		for (int j = k+1; j < m; j++) {
			Fraction a = B[k][j];
			for (int i = k; i < n; i++) {
				B[i][j] -= (B[i][k] * a);
			}
		}
		for (int i = k + 1; i < n; i++) {
			Fraction a(0);
			B[k][i] = a;
		}
	}
	 int rankA() {
		int d = Min(n, m);
		bool Find_nozero = true;
		bool ok = false;
		std::vector<std::vector <Fraction>> B = A;
		for (int i = 0; i < d && Find_nozero; i++) {
			
			if (!B[i][i]) {
				Find_nozero = false;
				for (int j = i; j < n && !Find_nozero && !ok; j++) {
					for (int k = i; k < m && !Find_nozero && !ok; k++) {
						if (B[j][k] && k != i) {
							Find_nozero = true;
							Replace_cols(B, k, i);
							ok = true;
						}
					}
				}
			}
			division_row(B, B[i][i], i);
			create_zero_in_row(B, i);
		}
		int rank = 0;
		for (int i = 0; i < d; i++) {
			rank += B[i][i].GetNum();
		}
		return rank;
	}

	int const GetNRows () const {
		return n;
	}
	friend std::ostream& operator<< (std::ostream& out, Matrix& Matr) {
		
		for (int i = 0; i < Matr.n; i++) {
			int j;
			for (j = 0; j < Matr.m - 1; j++) {

				out << Matr.A[i][j] << std::setw(7);
			}
			out << Matr.A[i][j];
			out << std::endl;
		}
		out << "rank of matrix: " << Matr.rankA() << std::endl;
		return out;
	}

	friend std::istream& operator>> (std::istream& in, Matrix& Matr) {
		InCorIntSize("Please, enter matrix size: ", in, Matr.n, Matr.m);
		for (int i = 0; i < Matr.n; i++) {
			Matr.A.push_back({});
			for (int j = 0; j < Matr.m; j++) {
				
				Matr.A[i].push_back(Fraction());
				bool Ok_fr = false;
				while (!Ok_fr) {
					try {
						std::cout << "Please, Enter row=" << i + 1 << " col=" << j + 1 << ": ";
						in >> Matr.A[i][j];
						Ok_fr = true;
					}
					catch (std::exception& ex) {
						std::cout << ex.what() << std::endl;
					}
				}
			}
		}
		return in;
	}       
	
	friend std::ifstream& operator>> (std::ifstream& in, Matrix& Matr) {
		std::string s;
		std::getline(in, s);
		int n, m;
		std::string n_str, m_str;
		
		bool F = false;
		for (char i : s) {
			if (i == ' ' && F)
				throw std::exception("The input contains more than just number");
			if (i == ' ') {
				F = true;
			}
			if (!isdigit((unsigned)i) && i != ' ')
				throw std::exception("The input contains more than just number");

			if (F && i != ' ')
				m_str.push_back(i);
			else if (i != ' ')
				n_str.push_back(i);
		}
		if (!F) {
			std::exception("Incorrect input");
		}


		n = std::stoi(n_str);
		m = std::stoi(m_str);
		if (n < 2 || m < 2)
			throw std::exception("The number less or equal 1: No sense");
		Matr.n = n;
		Matr.m = m;

		
		std::string el;
		for (int i = 0; i < n; i++) {
			int number_el = 0;
			std::getline(in, s);
			Matr.A.push_back({});

			for (int j = 0; j < s.length(); j++) {
				if (s[j] != ' ') {
					el.push_back(s[j]);
				}
				if (s[j] == ' ' || j == s.length() - 1) {
					Matr.A[i].push_back(Fraction());
					std::string a, b;
					bool F = false;
					for (char k : el) {
						if (k == '/' && F)
							throw std::exception("Incorrect data");
						if (k == '/') {
							F = true;
						} 
						if (!isdigit((unsigned)k) && k != '/')
							throw std::exception("The input contains more than just number");

						if (F && k != '/')
							b.push_back(k);
						else if (k != '/')
							a.push_back(k);
					}
					if (F)
						Matr.A[i][number_el] = Fraction(stoi(a), stoi(b));
					else
						Matr.A[i][number_el] = Fraction(stoi(a));
					number_el++;
					el = "";
				}
			}
		}


	}

};
int main() {
	bool Play = true;
	while (Play) {
		std::cout << "Enter data in the format: Matrix dimensions, matrix elements" << std::endl;
		int n;
		std::vector<Matrix> A;
		try {
			switch (type_input()[0]) {
			case 'C':
				std::cout << "Console input is selected" << std::endl;
				n = InCorIntLen("Enter the number of objects of the class");
				for (int i = 0; i < n; i++) {
					A.push_back(Matrix());
					std::cin >> A[i];
				}
				break;
			case 'F':
				std::cout << "File input is selected" << std::endl;
				std::ifstream input("input.txt");
				if (input.eof())
					throw std::exception("Incorrect data");
				for (int i = 0; input.peek() != EOF; i++) {
					A.push_back(Matrix());
					input >> A[i];
				}
				break;
			}
		}
		catch (std::exception& ex) {
			std::cout << "Error: " << ex.what() << std::endl;
		}
		switch (type_output()[0]) {
		case 'C':
			std::cout << "Console output is selected" << std::endl;
			for (int i = 0; i < A.size(); i++) {
				std::cout << A[i] << std::endl;
			}
			break;
		case 'F':
			std::cout << "File output is selected" << std::endl;
			std::ofstream out("output.txt");
			for (int i = 0; i < A.size(); i++) {
				out << A[i] << std::endl;
			}
			break;
		}

	}
	}