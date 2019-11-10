#include <iostream>
#define INF 1000000000
using namespace std;

int n, m;
int a, b, c;
int d[101][101];

void FloydWarshall() {
	for (int k = 1; k <= n; k++) { // 거쳐서 가는
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (d[i][j] == INF) { // 갈수없는 경우
				d[i][j] = 0;
			}
		}
	}
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				d[i][j] = 0;
			}
			else {
				d[i][j] = INF;
			}
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		if (c < d[a][b]) {
			d[a][b] = c;
		}
	}

	FloydWarshall();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}