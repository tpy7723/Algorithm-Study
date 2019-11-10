//// https://www.acmicpc.net/blog/view/12
//#include <cstdio>
//#include <stack>
//
//using namespace std;
//long long a[1000001];
//
//int main() {
//	long long n;
//
//	while (1) {
//		scanf("%lld", &n);
//		if (n == 0) break;
//
//		for (int i = 0; i < n; i++) {
//			scanf("%d", &a[i]);
//		}
//
//		stack<int> s;
//		long long ans = 0;
//
//		for (int i = 0; i < n; i++) {
//			long long left = i;
//			while (!s.empty() && a[s.top()] > a[i]) {
//				long long right = i - 1;
//				long long height = a[s.top()];
//				s.pop();
//				long long width = i;
//				if (!s.empty()) {
//					long long left = s.top();
//					width = (right - left);
//				}
//				if (ans < width*height) {
//					ans = width * height;
//				}
//			}
//			s.push(i);
//		}
//		while (!s.empty()) {
//			long long right = n - 1;
//			long long height = a[s.top()];
//			s.pop();
//			long long width = n;
//			if (!s.empty()) {
//				long long left = s.top();
//				width = (right - left);
//			}
//			if (ans < width*height) {
//				ans = width * height;
//			}
//		}
//
//		printf("%lld\n", ans);
//	}
//
//
//	return 0;
//}