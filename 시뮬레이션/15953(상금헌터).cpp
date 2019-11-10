#include <iostream>
#include <vector>

using namespace std;

int T;
vector<int> festival_1(1);
vector<int> festival_2(1);

int calculate(int a, int b) {
	return festival_1[a] + festival_2[b];
}
int main() {
	cin >> T;

	for (int i = 0; i < 1; i++) {
		festival_1.push_back(500);
	}
	for (int i = 0; i < 2; i++) {
		festival_1.push_back(300);
	}
	for (int i = 0; i < 3; i++) {
		festival_1.push_back(200);
	}
	for (int i = 0; i < 4; i++) {
		festival_1.push_back(50);
	}
	for (int i = 0; i < 5; i++) {
		festival_1.push_back(30);
	}
	for (int i = 0; i < 6; i++) {
		festival_1.push_back(10);
	}
	for (int i = 0; i < 79; i++) {
		festival_1.push_back(0);
	}

	for (int i = 0; i < 1; i++) {
		festival_2.push_back(512);
	}
	for (int i = 0; i < 2; i++) {
		festival_2.push_back(256);
	}
	for (int i = 0; i < 4; i++) {
		festival_2.push_back(128);
	}
	for (int i = 0; i < 8; i++) {
		festival_2.push_back(64);
	}
	for (int i = 0; i < 16; i++) {
		festival_2.push_back(32);
	}
	for (int i = 0; i < 33; i++) {
		festival_2.push_back(0);
	}
	
	int a, b;
	for (int i = 0; i < T; i++) {
		cin >> a >> b;

		cout << calculate(a,b) * 10000 << endl;

	}

	return 0;
}