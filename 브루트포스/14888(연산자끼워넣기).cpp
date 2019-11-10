#include <iostream>
#include <vector>
#include <algorithm>

#define endl "\n"

using namespace std;

int N;
int map[11];
int result;
int op;
int max_value = -987654321;
int min_value = (-1) * max_value;
vector<int> v;

void calculate(int x, int oper) {
	switch (oper)
	{
	case 0: // ÇÃ
		result += x;
		break;
	case 1: // ¸¶
		result -= x;
		break;
	case 2: // °ö
		result *= x;
		break;
	case 3: // ³ª
		if (result < 0) {
			result *= -1;
			result /= x;
			result *= -1;
		}
		else {
			result /= x;
		}
		break;
	default:
		break;
	}
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> map[i];
	}

	for (int i = 0; i < 4; i++) {
		cin >> op;
		while (op--) {
			v.push_back(i);
		}
	}

	do {
		result = map[0];
		for (int i = 0; i < v.size(); i++) {
			calculate(map[i + 1], v[i]);
		}
		max_value = max(max_value, result);
		min_value = min(min_value, result);
	} while (next_permutation(v.begin(), v.end()));

	cout << max_value << "\n" << min_value << endl;
	return 0;
}