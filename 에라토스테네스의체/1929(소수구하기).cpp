#include <iostream>

using namespace std;

int M, N;
int arr[1000001];

void findPrimeNumber() {
	for (int i = 2; i <= N; i++) { // 2부터 100000까지 나눠 봄
		if (arr[i] == 0) continue;

		for (int j = i+i; j <= N; j+= i) {
			if (arr[j] % i == 0) 
				arr[j] = 0; // 나눠지는 것은 소수가 아님
		}
	}

	for (int i = M; i <= N; i++) {
		if (arr[i] != 0) 
			cout << arr[i] << "\n"; // endl 시간초과 ;;
	}
}

int main() {
	cin >> M >> N;

	for (int i = 2; i <= N; i++) {
		arr[i] = i;
	}

	findPrimeNumber();

	return 0;
}