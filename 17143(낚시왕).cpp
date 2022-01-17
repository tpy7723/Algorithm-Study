#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct shark {
	int s, d, z; // ���ǵ� ���� ũ��
};

int r, c, m, ans; // �� �� ���� ��
shark a[101][101]; // �� ��ġ�� ��

const int dx[4] = {-1, 1, 0, 0 }, dy[4] = {0, 0, 1, -1 }; // �¿����

void solve() {
	for (int t = 1; t <= c; t++) { // �� ��ĭ�� �̵�
		shark b[101][101] = { 0 }; // ����� �̵� �� �ʱ�ȭ
		// Fishing a shark
		for (int i = 1; i <= r; i++) {
			if (a[i][t].z) { // �ش� �� �� ��
				ans += a[i][t].z; // ��� ����
				a[i][t] = { 0, 0, 0 }; // ��� ����
				break;
			}
		}
		// Sharks move
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if (a[i][j].z) { // �� �����ϰ�
					if (a[i][j].d < 3) { // Up, Down
						int s = a[i][j].s % ((r - 1) * 2); // ������
						int d = a[i][j].d; // ����
						int ni = i; // ��
						while (s--) { // �������� �̵�
							if (ni == 1 && d == 1) d = 2; // 1 �ε����� �ε�ĥ�� ������ȯ
							if (ni == r && d == 2) d = 1; // r �ε����� �ε�ĥ�� ������ȯ
							ni += dx[d-1]; // �� �� ��ȭ
						}
						if (a[i][j].z > b[ni][j].z) b[ni][j] = { a[i][j].s, d, a[i][j].z }; // ��ƸԱ�
					}
					else { // Right, Left
						int s = a[i][j].s % ((c - 1) * 2);
						int d = a[i][j].d;
						int nj = j; //��
						while (s--) {
							if (nj == 1 && d == 4) d = 3; // ���� ��迡 �ε�ĥ��
							if (nj == c && d == 3) d = 4; // ������ ��迡 �ε�ĥ ��
							nj += dy[d-1]; // �� �� ��ȭ
						}
						if (a[i][j].z > b[i][nj].z) b[i][nj] = { a[i][j].s, d, a[i][j].z }; // ��ƸԱ�
					}
					a[i][j] = { 0, 0, 0 }; // �̵������� ����
				}
			}
		}
		memcpy(a, b, sizeof(b)); // a�� b�� ������
	}
}

int main() {
	cin >> r >> c >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, s, d, z;
		cin >> x >> y >> s >> d >> z;
		a[x][y] = { s, d, z }; // ��� ���� ����
	}
	solve();
	cout << ans << endl;
	return 0;
}