#include <iostream>
#define endl "\n"
#define MAX 20
using namespace std;

int N, M, x, y, K;
int map[MAX][MAX];
int move_order[1000];
int dice[6];

int Judgement(int d) {
    if (d == 1) {
        if (y == M - 1) return 0;
    } else if (d == 2) {
        if (y == 0) return 0;
    } else if (d == 3) {
        if (x == 0) return 0;
    } else if (d == 4) {
        if (x == N - 1) return 0;
    }
    return 1;
}

void Movement(int d) {
    int temp = dice[0];
    if (d == 1) {
        y++;
        dice[0] = dice[3];
        dice[3] = dice[1];
        dice[1] = dice[2];
        dice[2] = temp;
    } else if (d == 2) {
        y--;
        dice[0] = dice[2];
        dice[2] = dice[1];
        dice[1] = dice[3];
        dice[3] = temp;
    } else if (d == 3) {
        x--;
        dice[0] = dice[4];
        dice[4] = dice[1];
        dice[1] = dice[5];
        dice[5] = temp;
    } else if (d == 4) {
        x++;
        dice[0] = dice[5];
        dice[5] = dice[1];
        dice[1] = dice[4];
        dice[4] = temp;
    }
}

void Play() {
    for (int i = 0; i < K; i++) {
        if (!Judgement(move_order[i])) {
            continue;
        }

        Movement(move_order[i]);
        if (map[x][y] == 0) {
            map[x][y] = dice[1];
        } else {
            dice[1] = map[x][y];
            map[x][y] = 0;
        }
        cout << dice[0] << endl;
    }
}

int main() {
    // input
    cin >> N >> M >> x >> y >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < K; i++) cin >> move_order[i];

    Play();
}