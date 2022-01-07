#include <iostream>
#define MAX 1000000
#define endl "\n"
#define lld long long
using namespace std;

int A[MAX];
int N, B, C;
lld ans = 0;

void Input() {
	// 시험장의 갯수 N
	cin >> N;

	// 각 시험장의 응시자 수
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	// B와 C
	cin >> B >> C;
}

void How_Many_Supervisors(int candidates) {
	candidates -= B;
	ans++;

	if (candidates > 0)
		ans += ((candidates - 1) / C + 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Input();
	for (int i = 0; i < N; i++) {
		How_Many_Supervisors(A[i]);
	}

	cout << ans << endl;
	return 0;
}