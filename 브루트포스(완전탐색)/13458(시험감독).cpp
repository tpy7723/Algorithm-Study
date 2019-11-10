#include <iostream>

using namespace std;

int n;
int a[1000003];
int b, c;
long long int ans;

int main() {
	cin >> n;
	
	for (int i = 1; i <=n; i++) {
		cin >> a[i];
	}

	cin >> b >> c;

	for (int i = 1; i <= n; i++) {
		a[i] -= b; // 총감독관 뺴기
		ans++; // 총감독관 인원 세기

		if (a[i] > 0) { // 최소인원 따져야 맞네여
			if (a[i] % c == 0) {
				ans += a[i] / c;
			}
			else {
				ans += a[i] / c + 1;
			}
		}

	}

	cout << ans << endl;

	return 0;
}