#include <iostream>
#include <cstring>
using namespace std;

int N, L;
int map[100][100];
int visit[100];
int result;

void findrow() {
	for (int i = 0; i < N; i++) {
		int cnt = 1; // ������ �� ����
		bool success = true;
		memset(visit, 0, sizeof(visit));

		for (int j = 0; j < N - 1; j++) {
			if (abs(map[i][j] - map[i][j + 1]) > 1) {
				success = false;
				break; // ���̰� 1 �ʰ�
			}

			if (abs(map[i][j] - map[i][j + 1]) == 0) { // ���� ������ ���
				cnt++;
				continue;
			}
			if (map[i][j] - map[i][j + 1] == -1) { // �ڿ� ���� ���� ���
				if (cnt >= L) {
					bool check = true;
					for (int k = 0; k < L; k++) {
						if (visit[j - k] != 0) { // �̹� �ٸ��� �ִ� ���
							check = false;
							success = false;
							break;
						}
						visit[j - k] = 1; // �ٸ��� ����
					}
					if (!check) break; // �̹� �ٸ��� �ִ� ���
					cnt = 1;
				}
				else {
					success = false;
					break; // �ٸ��� ���� ������ ���� ���
				}
			}
			if (map[i][j] - map[i][j + 1] == 1) { // �տ� ���� ���� ���
				bool check = true;
				for (int k = 0; k < L; k++) {
					if (map[i][j + 1 + k] != map[i][j + 1]) {
						check = false;
						success = false;
						break;
					}
					visit[j + 1 + k] = 1;
				}
				if (!check) break; // �ٸ� ���� ������ ���� ���
				j += L - 1;
				cnt = 0;
			}
		}

		if (success) result++;
	}
}
void findcol() {
	for (int j = 0; j < N; j++) {
		int cnt = 1; // ������ �� ����
		bool success = true;
		memset(visit, 0, sizeof(visit));

		for (int i = 0; i < N - 1; i++) {
			if (abs(map[i][j] - map[i + 1][j]) > 1) {
				success = false;
				break; // ���̰� 1 �ʰ�
			}

			if (abs(map[i][j] - map[i + 1][j]) == 0) { // ���� ������ ���
				cnt++;
				continue;
			}
			if (map[i][j] - map[i + 1][j] == -1) { // �ڿ� ���� ���� ���
				if (cnt >= L) {
					bool check = true;
					for (int k = 0; k < L; k++) {
						if (visit[i - k] != 0) { // �̹� �ٸ��� �ִ� ���
							check = false;
							success = false;
							break;
						}
						visit[i - k] = 1; // �ٸ��� ����
					}
					if (!check) break; // �̹� �ٸ��� �ִ� ���
					cnt = 1;
				}
				else {
					success = false;
					break; // �ٸ��� ���� ������ ���� ���
				}
			}
			if (map[i][j] - map[i + 1][j] == 1) { // �տ� ���� ���� ���
				bool check = true;
				for (int k = 0; k < L; k++) {
					if (map[i + 1 + k][j] != map[i + 1][j]) {
						check = false;
						success = false;
						break;
					}
					visit[i + 1 + k] = 1;
				}
				if (!check) break; // �ٸ� ���� ������ ���� ���
				i += L - 1;
				cnt = 0;
			}
		}
		if (success) result++;
	}
}
int main() {
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	// �� Ž��
	findrow();

	// �� Ž��
	findcol();

	cout << result << endl;
	return 0;
}