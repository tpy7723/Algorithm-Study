#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map;
vector<vector<int>> swim;
pair<vector<vector<int>>, vector<vector<int>>> p;

int answer = 0;

int dir[9][2] = { {0,0}, {0,-1}, {-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} }; // ��j, ��i

bool indoor(int i, int j) {
	return (0 <= i && i < 4) && (0 <= j && j < 4);
}

pair<vector<vector<int>>, vector<vector<int>>> Swim(pair<vector<vector<int>>, vector<vector<int>>> p) {
	vector<vector<int>> m = p.first;
	vector<vector<int>> s = p.second;

	// 2. ������ ��ȣ�� ���� �������� ������� �̵��Ѵ�.
	for (int n = 1; n <= 16; n++) {
		int stop = 0;

		for (int i = 0; i < 4; i++) {
			if (stop == 1) break;
			for (int j = 0; j < 4; j++) {
				if (stop == 1) break;
				if (m[i][j] == n) {
					int next = s[i][j];

					for (int k = 0; k < 7; k++) { // 7�� ���� ��ȯ
						int dx = j + dir[next][0];
						int dy = i + dir[next][1];

						if (indoor(dy, dx) && m[dy][dx] >= 0) {
							int temp = m[i][j];
							m[i][j] = m[dy][dx];
							m[dy][dx] = temp;

							s[i][j] = next;
							temp = s[i][j];
							s[i][j] = s[dy][dx];
							s[dy][dx] = temp;

							stop = 1;
							break;
						}

						if (next == 8) {
							next = 1;
						}
						else {
							next++;
						}
					}
				}
			}
		}
	}

	p = make_pair(m, s);

	return p;
}

void Shark(int m, int n, int ans, pair<vector<vector<int>>, vector<vector<int>>> p) {
	// 2. ����� �̵�
	p = Swim(p);

	vector<vector<int>> map = p.first;
	vector<vector<int>> swim = p.second;

	if (answer < ans) { // �ִ밪 ����
		answer = ans;
	}

	int next = swim[m][n]; // �̵�����
	
	for (int i = 1; i <= 3; i++) { // �̵��� �� �ִ� ĭ ��
		int dx = n + (dir[next][0] * i);
		int dy = m + (dir[next][1] * i);
		
		if (indoor(dy, dx)) {
			if (map[dy][dx] > 0) {
				int temp1 = map[dy][dx];
				int temp2 = map[m][n];
				map[dy][dx] = -1;
				map[m][n] = 0;

				int temp3 = swim[m][n];
				swim[m][n] = 0;

				Shark(dy, dx, ans + temp1, make_pair(map, swim));

				// ����
				map[dy][dx] = temp1;
				map[m][n] = temp2;

				swim[m][n] = temp3;
			}
		}
		else break;
	}
	return;
}

int main() {
	map.assign(4, vector<int>(4, 0));  // ����� ��ȣ 4X4
	swim.assign(4, vector<int>(4, 0)); // ���� 4X4

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> map[i][j] >> swim[i][j];
		}
	}

	// 1. û�ҳ� ���� (0, 0)�� �ִ� ����⸦ �԰�, (0, 0)�� ���� �ȴ�. ����� ������ (0, 0)�� �ִ� ������� ����� ����
	answer += map[0][0];
	map[0][0] = -1; // ��� ǥ�� 

	Shark(0, 0, answer, make_pair(map,swim)); // ��� ��, ��� ��, ���� ����� ������, ������ȣ/����
	
	cout << answer << endl;

	return 0;
}

