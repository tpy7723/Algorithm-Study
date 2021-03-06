#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

struct state {
	int rx, ry, bx, by, d; // ���� �Ķ� ��ǥ , Ƚ��
};

int n, m;
char a[10][10];
bool visit[10][10][10][10];
queue<state> q;
const int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 }; // �����¿� ��� ����

//call by reference
void move(int &x, int &y, int &c, int dx, int dy) { // c�� �̵��Ÿ� dx dy �����¿� ����
	while (a[x + dx][y + dy] != '#' && a[x][y] != 'O') { // ���� ��ġ�� ���� �ƴϰ� ���� ��ġ�� ������ �ƴϸ� ��� �̵�
		x += dx; // x����
		y += dy; // y����
		c += 1; // �̵� �Ÿ�
	}
}

void bfs() {
	while (!q.empty()) {
		// ���� ��ǥ
		int rx = q.front().rx;
		int ry = q.front().ry;
		// �Ķ� ��ǥ
		int bx = q.front().bx;
		int by = q.front().by;
		// Ƚ��
		int d = q.front().d;

		q.pop();

		for (int i = 0; i < 4; i++) { // �����¿� �׹��� üũ
			int next_rx = rx;
			int next_ry = ry;
			int next_bx = bx;
			int next_by = by;
			int next_d = d + 1; // Ƚ�� 1 ����

			int rc = 0; // ���� �̵� �Ÿ� 
			int bc = 0; // �Ķ� �̵� �Ÿ�

			move(next_rx, next_ry, rc, dx[i], dy[i]); // ���� �̵� -> ��ǥ���ٲ�
			move(next_bx, next_by, bc, dx[i], dy[i]); // �Ķ� �̵� -> ��ǥ���ٲ�

			if (a[next_bx][next_by] == 'O') continue; // �Ķ��� ���ۿ� ���� ����

			if (a[next_rx][next_ry] == 'O') { // ������ ���ۿ� ���� ��
				cout << next_d << endl; // Ƚ�� ���
				return;
			}

			if (next_rx == next_bx && next_ry == next_by) { // �̵��� ���� ��ġ�� ��� 
				// �̵��Ÿ��� �� ū ���� �� ĭ �������� ��
				if (rc > bc) next_rx -= dx[i], next_ry -= dy[i];
				else next_bx -= dx[i], next_by -= dy[i];
			}

			if (!visit[next_rx][next_ry][next_bx][next_by]) {
				visit[next_rx][next_ry][next_bx][next_by] = true; // �̹� ������ �ʾҴ� ��Ȳ�̸� �湮ó��
				q.push({ next_rx, next_ry, next_bx, next_by, next_d }); // ���� ���¸� ť�� �Է��� ��
			}
		}
	}
	cout << -1 << endl;
}

int main() {
	cin >> n >> m; // ���� ����

	int rx, ry, bx, by; // ���� �Ķ� xy ��ǥ

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];

			if (a[i][j] == 'R') {
				rx = i;
				ry = j;
			} // ���� ��ǥ ����
			else if (a[i][j] == 'B') {
				bx = i;
				by = j;
			} // �Ķ� ��ǥ ����
		}
	}

	q.push({ rx, ry, bx, by, 0 }); // �ʱ� ���� queue ����

	visit[rx][ry][bx][by] = true; // �湮 �迭

	bfs();

	return 0;
}
