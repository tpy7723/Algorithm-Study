#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct info {
	int y, x, d, n; 
};

int tc, N;
int dx[] = { 0,0,-1,1 }, dy[] = { 1,-1,0,0 }; // �����¿�
int map[4001][4001];

vector<info> v;

int solve() {
	int ans = 0;
	while (!v.empty()) { // ���Ұ� �� ������
		// �̵�
		for (int i = 0; i < v.size(); i++) { // ��� ���ҿ� ����
			map[v[i].x][v[i].y] = 0; // �̵� �� ��ġ�� 0���� �ʱ�ȭ
			int x = v[i].x += dx[v[i].d]; // �̵� �� x
			int y = v[i].y += dy[v[i].d]; // �̵� �� y
			if (x < 0 || x > 4000 || y < 0 || y > 4000) { // ������ �����
				v[i].n = 0;  // ȹ���Ҽ��ִ� ������ 0
				continue;  // ����
			}
			map[x][y] += v[i].n; // �̵��� ĭ�� ������ �ű� or ����
		}
		// �ľ�
		for (int i = 0; i < v.size(); i++) { // ��� ���ҿ� ����
			if (!v[i].n) continue; // ������ ��� �� or 
			int x = v[i].x;
			int y = v[i].y; 
			if (map[x][y] != v[i].n) { // ���� �ٸ��� �浹��
				ans += map[x][y];
				map[x][y] = 0; // �ʱ�ȭ
				v[i].n = 0; // �浹 �� ȹ���Ҽ��ִ� ������ 0
			}
		}

		// ���� ���� �����ִ� �͸� �ɷ���
		vector<info> tmp;
		tmp = v;
		v.clear();

		for (int i = 0; i < tmp.size(); i++) {
			if (tmp[i].n != 0) {
				v.push_back(tmp[i]);
			}				
		}
	}
	return ans;
}

int main() {
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		cin >> N;

		int y, x, d, n;
		for (int i = 0; i < N; i++)
		{
			cin >> x >> y >> d >> n;
			// ���� ����
			v.push_back({ 2 * (y + 1000), 2 * (x + 1000), d, n }); // ����� �����, 0.5�� ������
		}
		cout << "#" << t << " " << solve() << endl;
	}
	return 0;
}
