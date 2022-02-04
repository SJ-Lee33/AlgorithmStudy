#include <algorithm>  // for sort deque
#include <deque>
#include <iostream>
using namespace std;
#define MAX 11

int N, M, K;
int A[MAX][MAX];
int MAP[MAX][MAX];
deque<int> alive_tree[MAX][MAX];
deque<int> dead_tree[MAX][MAX];
int ans;

// 위쪽부터 시계방향으로 인근 8칸 이동
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void Spring() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // 이 땅에 살아있는 나무 갯수 trees
            int trees = alive_tree[i][j].size();
            while (trees--) {
                int age = alive_tree[i][j].front();
                alive_tree[i][j].pop_front();
                if (age > MAP[i][j]) {
                    // 죽어
                    dead_tree[i][j].push_back(age);
                    continue;
                }
                MAP[i][j] -= age;
                alive_tree[i][j].push_back(age + 1);
            }
        }
    }
}

void Summer() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // 이 땅에 죽어있는 나무 갯수 dtrees
            int dtrees = dead_tree[i][j].size();
            while (dtrees--) {
                int age = dead_tree[i][j].front();
                dead_tree[i][j].pop_front();
                MAP[i][j] += (age / 2);
            }
        }
    }
}

void Breeding(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx <= N && ny <= N && nx >= 1 && ny >= 1) {
            alive_tree[nx][ny].push_front(1);
        }
    }
}

void Fall() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // 이 땅에 살아있는 나무 갯수 trees
            int trees = alive_tree[i][j].size();
            for (int k = 0; k < trees; k++) {
                int age = alive_tree[i][j][k];
                if (age % 5 == 0) {
                    Breeding(i, j);
                }
            }
        }
    }
}

void Winter() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            MAP[i][j] += A[i][j];
        }
    }
}

void Solution() {
    // 첫번째 봄이 오기 전에 alive_tree 나이순 정렬 해줘야됨
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            sort(alive_tree[i][j].begin(), alive_tree[i][j].end());
        }
    }

    // K년 나기
    while (K--) {
        Spring();
        Summer();
        Fall();
        Winter();
    }

    // 살아남은 나무 세기
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            ans += alive_tree[i][j].size();
        }
    }
}

void Input() {
    int x, y, z;
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
            MAP[i][j] = 5;
        }
    }
    for (int i = 0; i < M; i++) {
        cin >> x >> y >> z;
        alive_tree[x][y].push_back(z);
    }
}

int main() {
    // 입력
    Input();
    Solution();

    cout << ans << endl;
}