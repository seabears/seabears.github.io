#include<stdio.h>

#define MAX(a,b) ((a>b)?a:b)
#define TMAX 1000
#define WMAX 30

int main() {
    int T, W;
    scanf("%d %d", &T, &W);
    int drop[TMAX + 1] = { 0 };
    for (int i = 1; i <= T; i++) {
        scanf("%d", &drop[i]);
    }

    //dp[t][w][p] : t(초) w(남은 이동 횟수) p(위치) 
    int dp[TMAX + 1][WMAX + 1][2 + 1] = { 0 };

    // 초기값
    dp[1][W][1] = (drop[1] == 1) ? 1 : 0;
    dp[1][W - 1][2] = (drop[1] == 2) ? 1 : 0;

    for (int i = 2; i <= T; i++) {
        for (int j = 0; j <= W; j++) {
            for (int k = 1; k <= 2; k++) {
                //1. 이번 초에 얻는 사과
                int get = (k == drop[i]) ? 1 : 0;

                //2. 이번 초 계산 : 이동 안한거
                dp[i][j][k] = dp[i - 1][j][k] + get;

                //2. 이동 한거
                if (j > 0) {
                    dp[i][j][k] = MAX(dp[i][j][k], dp[i - 1][j - 1][3 - k] + !get);
                }

            }
        }
    }

    //3. T초에서의 최대값 찾기
    int ans = 0;
    for (int w = 0; w <= W; w++) {
        for (int p = 1; p <= 2; p++) {
            ans = MAX(ans, dp[T][w][p]);
        }
    }

    printf("%d\n", ans);


    return 0;
}
/*
매초마다 두개의 나무중 하나에서 열매 떨어짐
움직이는 시간 0초
자두는 T초동안 떨어짐, 최대 W번 움직이고 싶
---
#1)
7 2
2 1 1 2 2 1 1

*/