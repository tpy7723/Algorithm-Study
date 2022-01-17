#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
int minN, maxN;
int answer = 0;
int dir[4][2] = { {0,-1},{0,1} ,{-1,0} ,{1,0} };
vector<vector<int>> v;
vector<vector<int>> dist;

bool indoor(int i, int j) {
	return (1 <= i && i <= N) && (1 <= j && j <= N);
}

void OneLine() {
	//4. �Ϸķ� ���� 
	int a = 1;
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			if (v[i][j] != 10001) {
				v[1][a++] = v[i][j];
			}
		}
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			v[i][j] = 10001;
		}
	}
}

void Rotation() {
	// 5. ���� �ξ� �۾��� �ؾ� �Ѵ�. �̹����� ����� �߽����� ���� N/2���� ���� �ξ���� ��ü�� �ð� �������� 180�� ȸ�� ��Ų ����
		//, ������ N/2���� ���� ���ƾ� �Ѵ�. �� �۾��� �� �� �ݺ��ؾ��Ѵ�. 
	int count = N / 2;
	for (int i = 0; i < N / 2; i++) {
		v[2][count + 1] = v[1][N - count];
		v[1][N - count] = 10001;
		count++;
	}

	count = N - (N / 4);
	for (int i = 0; i < N / 4; i++) {
		v[3][count + 1] = v[2][N - count + (N / 2)];
		v[2][N - count + (N / 2)] = 10001;

		v[4][count + 1] = v[1][N - count + (N / 2)];
		v[1][N - count + (N / 2)] = 10001;
		count++;
	}
}

bool Check() {
	// 8. ����Ⱑ ���� ���� ����ִ� ���װ� ���� ���� ����ִ� ������ ����� �� ���̰� K �������� üũ
	minN = 10001;
	maxN = -1;
	for (int i = 1; i <= N; i++) {
		if (maxN < v[1][i]) {
			maxN = v[1][i];
		}
		if (minN > v[1][i]) {
			minN = v[1][i];
		}
	}

	return abs(maxN - minN) <= K;
}
void Arrange() {
	// 3. ����� �� ����.  ��� ������ �� ���׿� ���ؼ�, ����� ���� ���̸� ���Ѵ�. ���̸� 5�� ���� ���� d. d�� 0���� ũ��, 
	// �� ���� �� ������� ���� ���� ���� �ִ� ����� d ������ ���� ���� �ִ� ������ ������.
	dist.assign(101, vector<int>(101, 0));   // 0���� �ʱ�ȭ�� 101X101
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (v[i][j] != 10001) {

				for (int k = 0; k < 4; k++) {
					int dx = i + dir[k][0];
					int dy = j + dir[k][1];

					if (v[dx][dy] != 10001 && indoor(dx, dy)) {
						dist[i][j] += ((v[dx][dy] - v[i][j]) / 5);
					}
				}

			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			v[i][j] += dist[i][j];
		}
	}
}

void Add() {
	// 1. ������� ���� ���� ���� ���׿� ����⸦ �� ���� �ִ´�.  ����, �׷��� ������ ��������� ������� ���� �ּ��� ���� ��ο� �� ������ �ִ´�.
	minN = *min_element(v[1].begin(), v[1].end());

	for (int i = 1; i <= N; i++) {
		if (v[1][i] == minN) {
			v[1][i]++;
		}
	}
}

void FishRotation() {
	// 2-1. �� ���� ������ ���� �ι�° ���׿� �ױ�
	v[2][2] = v[1][1];
	v[1][1] = 10001;

	// 2-2. 2�� �̻� �׿��ִ� ������ ��� ���� �ξ��Ų ����, ��ü�� �ݽð�������� 90�� ȸ����Ų��. (�ݺ�)

	int stop_flag = 0;
	while (1) {
		for (int i = N; i >= 1; i--) { // 2ĭ�̻��� ���� ã��
			if (v[2][i] != 10001) {
				int col = i;
				int row = 1;
				int temp = 2;
				for (int j = 1; j <= N; j++) {
					if (v[j][i] == 10001) {
						row = j - 1; // �ִ� ����
						break;
					}
				}

				//���� �ξ��Ų ���� �� ���� �����ʿ� �ִ� ������ �Ʒ��� �ٴڿ� �ִ� ������ ���������� �ݺ�
				if (N - i < row) {
					stop_flag = 1;
					break;
				}

				for (int k = col; k >= 1; k--) {
					if (v[1][k] == 10001) break;
					int temp2 = col + 1;
					for (int m = 1; m <= row; m++) {
						v[temp][temp2++] = v[m][k];
						v[m][k] = 10001;
					}
					temp++;
				}
				break;
			}
		}
		if (stop_flag) break;
	}
}

int main() {
	v.assign(101, vector<int>(101, 10001));   // 10001���� �ʱ�ȭ�� 101X101

	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		cin >> v[1][i];
	}
	
	while (1) {
		answer++;
			
		// 1. ����� �߰�
		Add();

		// 2. ����� ȸ��
		FishRotation();

		// 3. ����� �� ����
		Arrange();

		// 4. �Ϸķ� ���� 
		OneLine();

		// 5. ���� �ξ� �۾�
		Rotation();
		
		// 6. ����� �� ����
		Arrange();			

		// 7. �Ϸķ� ����
		OneLine();

		// 8. ����� �� üũ
		if (Check()) break;

	}

	cout << answer << endl;
}
