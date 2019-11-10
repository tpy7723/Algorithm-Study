#include <iostream>

using namespace std;

typedef long long ll;

// 최대 공약수
ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

int n;

ll res, a[300001], b[300001];
int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		res = gcd(res, b[i] - b[i - 1] - a[i]);
	}
	for (int i = 1; i <= n; i++) {
		if (b[i] - b[i - 1] == a[i]) continue; // 잔액이 더 많은 경우
		if (res != 0 && res <= b[i] || 0 < b[i - 1] + a[i]) {
			cout << -1 << endl;
			return 0;
		}
	}

	cout << (res ? res : 1) << endl;
	return 0;
}