#include <iostream>
#include <ctime>


using namespace std;

void show_cubes(int res) { //@
	switch (res) {
	case 1:
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@ @@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		break;
	case 2:
		cout << "@@@@@@@" << endl;
		cout << "@@@@@ @" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@ @@@@@" << endl;
		cout << "@@@@@@@" << endl;
		break;
	case 3:
		cout << "@@@@@@@" << endl;
		cout << "@@@@@ @" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@ @@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@ @@@@@" << endl;
		cout << "@@@@@@@" << endl;
		break;
	case 4:
		cout << "@@@@@@@" << endl;
		cout << "@ @@@ @" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@ @@@ @" << endl;
		cout << "@@@@@@@" << endl;
		break;
	case 5:
		cout << "@@@@@@@" << endl;
		cout << "@ @@@ @" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@@@ @@@" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@ @@@ @" << endl;
		cout << "@@@@@@@" << endl;
		break;
	case 6:
		cout << "@@@@@@@" << endl;
		cout << "@ @@@ @" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@ @@@ @" << endl;
		cout << "@@@@@@@" << endl;
		cout << "@ @@@ @" << endl;
		cout << "@@@@@@@" << endl;
		break;
	}
}

void throw_cubes(int couple[]) {
	couple[0] = rand() % 6 + 1;
	couple[1] = rand() % 6 + 1;
}

void score(int& user_score, int& komp_score, bool motion) {
	//Задержка
	int couple[2];
	throw_cubes(couple);
	if (motion) {
		cout << "Ваш ход: " << endl;
		user_score += couple[0] + couple[1];
		cout << "Счёт: " << user_score << endl;
		show_cubes(couple[0]);
		cout << endl;
		show_cubes(couple[1]);
	}
	else {
		cout << "Ход компьютера: " << endl;
		komp_score += couple[0] + couple[1];
		cout << "Счёт: " << komp_score << endl;
		show_cubes(couple[0]);
		cout << endl;
		show_cubes(couple[1]);
	}
}

int InCorN() {
	int t;
	cout << "Введите число бросков: " << endl;
	cin >> t;
	while (!cin >> t || cin.peek() != '\n' || (t <= 0)) {
		cout << "Ошибка ввода" << endl;
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите число бросков: " << endl;
	}
	return t;
}

void win(int komp_score, int user_score) {
	if (user_score > komp_score) {
		cout << "Вы победили!" << endl;
		cout << "Счёт пользователя: " << user_score << endl;
		cout << "Счёт компьютера: " << komp_score << endl;
		
	}
	else {
		cout << "Победил компьютер!" << endl;
		cout << "Счёт пользователя: " << user_score << endl;
		cout << "Счёт компьютера: " << komp_score << endl;
		cout << "Вы проиграли 1000000 рублей" << endl;
	}
}

bool motion_user() {
	return rand() % 2;
}

bool reset() {
	string s;
	cout << "Играть снова? (Да/Нет)" << endl;
	while (!(cin >> s) || cin.peek() != '\n' || (s != "Да" && s != "Нет")) {
		cout << "Ошибка ввода" << endl;
		cin.clear();
		while (cin.get() != '\n');
		cout << "Играть снова? (Да/Нет)" << endl;
	}
	if (s == "Нет") return false;
	return true;

}

int main() {
	srand(time(NULL));
	setlocale(0, "");
	system("chcp 1251");
	int user_score, komp_score;
	bool motion;
	int n_motion;
	bool Play = 1;
	while (Play) {
		user_score = 0, komp_score = 0;
		motion = motion_user();
		n_motion = InCorN() * 2;
		for (int i = 0; i < n_motion; i++) {
			if (!(i & 1)) cin.get();
			score(user_score, komp_score, motion);
			cout << endl;

			motion = (!motion);
		}
		win(komp_score, user_score);
		Play = reset();
	}

}