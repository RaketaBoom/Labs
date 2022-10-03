#include <iostream>
#include <string>

using namespace std;

string fail_in = "Input_fail"; //Ошибка ввода

int InCorK() { // Функция корректоного ввода
	int t;
	string s;
	bool Num = false;
	while (!Num) {
		cout << "Введите кол-во пифаогоровых троек" << endl;
		getline(cin, s);
		try {
			t = stoi(s);
			if (t <= 0) throw fail_in;
			for (int i = 0; i < s.length(); i++) {
				if (!isdigit(s[i])) throw fail_in;
			}
			
			Num = true;
		}
		catch (...) {
			cout << "Ошибка ввода" << endl;
		}
	}
	return t;
}



bool NOD1(int a, int b) { // Proverka nod
	int min = a > b ? b : a;

	for (int i = 2; i < min; i++) {
		if ((a % i == 0) && (b % i == 0))
			return false;
	}
	return true;
}




bool reset() {
	string s;
	
	bool cor = 0;

	while (!cor) {
		try {
			cout << "Запустить программу снова? (Да/Нет)" << endl;
			getline(cin, s);
			if (s != "Да" && s != "Нет") throw fail_in;
			cor = 1;
		}
		catch (...) {
			cout << "Ошибка ввода" << endl;
		}
	}

	if (s == "Да") return true;
	return false;
}




int main() {
	setlocale(0, "");
	system("chcp 1251");

	int k, count_tr = 0;
	long long a, b, c;
	

	bool Play = true;
	while (Play) {
	k = InCorK();
		for (int m = 2; count_tr < k; m++) {
			for (int n = 1; count_tr < k && n < m; n++) {
				if (NOD1(n, m) && ((m - n) & 1)) {
					count_tr++;
					a = m * m - n * n;
					b = 2 * m * n;
					c = m * m + n * n;
					cout << '(' << a << ", " << b << ", " << c << ')';
					if (count_tr < k) cout << ", ";
				}
			}
		}

		count_tr = 0;
		cout << endl;
		Play = reset();
		cout << endl;
		
	}
	int x = 1;
	x |= 1;
	x ^= 3;
}