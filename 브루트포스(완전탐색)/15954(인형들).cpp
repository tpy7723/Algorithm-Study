#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
long double P[501];

long double calculate(int idx, int k_) {
	long double average = 0;
	long double dispersion = 0;
	long double deviation = 0;
	for (int i = 0; i < k_; i++) {
		average += P[idx + i] / k_; // 평균
	}
	for (int i = 0; i < k_; i++) {
		dispersion += pow(P[idx + i] - average, 2) / k_; // 분산
	}
	deviation = sqrt(dispersion); // 표준편차

	return deviation;
}

int main() {
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		cin >> P[i];
	}
	long double min_value = 100000000000;
	long double value;

	for (int i = 1; i <= N - K + 1; i++) {
		for (int k_ = K; k_ <= N - i + 1; k_++) {
			value = calculate(i, k_);
			if (min_value > value) {
				min_value = value;
			}
		}
	}

	cout.precision(11); // 소수 11번째자리
	cout << min_value << endl;

	return 0;
}
