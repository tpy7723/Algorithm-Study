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
		a[i] -= b; // �Ѱ����� ����
		ans++; // �Ѱ����� �ο� ����

		if (a[i] > 0) { // �ּ��ο� ������ �³׿�
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