#include <iostream>

using namespace std;

int main() {
	int time_begin[2]; // 0 - час, 1 - минута
	int time_end[2];
	cin >> time_begin[0] >> time_begin[1];
	cin >> time_end[0] >> time_end[1];
	int strike_time[2];
	if (time_begin[1] > 30) {
		strike_time[0] = (time_begin[0] + 1) % 12;
		strike_time[1] = 0;
	}
	else {
		strike_time[0] = time_begin[0];
		strike_time[1] = 30;
	}
	int count_BOOM = 0;
	if (time_begin[0] > time_end[0])
		count_BOOM = 90;
	if (time_begin[0] == time_end[0] && time_begin[1] > time_end[1])
		count_BOOM = 90;
	time_end[0] = time_end[0] % 12;
	bool strike_h_end = false; // придумать для случая, когда часы будут больше положенного
	while ((strike_time[0] != time_end[0] || strike_time[1] <= time_end[1]) && (!strike_h_end || strike_time[1] != 0)) {
		if (strike_time[1] == 30) {
			count_BOOM += 1;
			strike_time[1] = 0;
			strike_time[0] = (strike_time[0] + 1) % 12;
			strike_h_end = (strike_time[0] == time_end[0]);
		}
		else {
			count_BOOM += strike_time[0] > 0 ?strike_time[0]%12 : 12;
			strike_time[1] = 30;
		}
	}
	cout << count_BOOM;
}
