#include <iostream>
#include <cstring>
using namespace std;

int N;
int cnt[3];
int cnt2[3];
char c;
int map[101][101];
bool visited[101][101];
int dir[4][2] = { {1,0},{-1,0}, {0,-1}, {0,1} }; // �����¿�

bool isindoor(int y, int x) {
	return (0 <= y && y < N) && (0 <= x && x < N);
}

void dfs(int y, int x, int key) {
	if (visited[y][x]) return;
	visited[y][x] = true;
	map[y][x] = key + 10;
	for (int i = 0; i < 4; i++) {
		int next_x = x + dir[i][1];
		int next_y = y + dir[i][0];

		if (isindoor(next_y, next_x) && map[next_y][next_x] == key) {
			dfs(next_y, next_x, key);
		}
	}
}

int main() {
	cin >> N;

	// ���� 0 �ʷ� 1 �Ķ� 2
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> c;
			if (c == 'G') {
				map[i][j] = 1;
			}
			else if (c == 'B') {
				map[i][j] = 2;
			}
		}
	}

	//�������� ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) { // ����
				dfs(i, j, 0);
				cnt[0]++; // �׷� ����
			}
			else if (map[i][j] == 1) { // �ʷ�
				dfs(i, j, 1);
				cnt[1]++;
			}
			else if (map[i][j] == 2) { // �Ķ�
				dfs(i, j, 2);
				cnt[2]++;
			}
		}
	}

	int original_sum = 0;
	for (int i = 0; i < 3; i++) {
		original_sum += cnt[i];
	}

	// �ʷ��� �������� �ٲ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 11) {
				map[i][j] = 10;
			}
		}
	}

	memset(visited, 0, sizeof(visited));

	// ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 10) {
				dfs(i, j, 10);
				cnt2[0]++; // ������ �ʷ� �׷�
			}
			else if (map[i][j] == 12) {
				dfs(i, j, 12);
				cnt2[2]++; // �Ķ� �׷�
			}
		}
	}

	int rgb_sum = 0;
	for (int i = 0; i < 3; i++) {
		rgb_sum += cnt2[i];
	}

	cout << original_sum << " " << rgb_sum << endl;

	return 0;

}
