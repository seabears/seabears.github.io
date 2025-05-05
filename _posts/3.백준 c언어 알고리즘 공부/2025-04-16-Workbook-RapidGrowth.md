---
title: 백준 단기간 성장 문제집
description: >-           #한 문장으로 나옴
  
date: 2025-04-16 08:43:34 +0900
lastmod : 2025-04-16 08:43:34 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - 백준
    - c언어  
tags: 
    - 백준
    - c언어

#excerpt: "이 글의 요약"   # 요약
#image: "url_to_image.jpg"   # 대표 이미지 (옵션)
#permalink: /category1/first-post/
pin: false              # true | false
published: true        # true | false
---


## 백준 단기간 성장 문제집
[백준 단기간 성장 문제집 링크](https://www.acmicpc.net/workbook/view/4349)

### 📌 1. 레이저 통신
[백준 6087번](https://www.acmicpc.net/problem/6087)
{% include code_open.html title="처음 코드 보기(bfs)" %}
```c
#include<stdio.h>

#define INF (~(1<<31))
#define MAX_MAP 100

enum {
	EMPTY = '.',
	WALL = '*',
	TARGET = 'C',
};
typedef struct {
	int x;
	int y;
}Pos;
typedef struct {
	int x;
	int y;
	int dir;
	int turn; // 꺾인 수 = 거울 수
}Razer;

int W, H;
char map[MAX_MAP][MAX_MAP + 1];

Pos target[2];
int target_idx = 0;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int min_turn = INF;

Razer queue[MAX_MAP * MAX_MAP * 10];	// 큐 크기를 얼마나 해야할까?
int front = 0, rear = 0;
void enqueue(Razer new) {
	queue[rear++] = new;
}
Razer dequeue() {
	return queue[front++];
}

void debug(Razer cur) {
	for (int i = 0;i < H;i++) {
		for (int j = 0;j < W;j++) {
			if (i == cur.x && j == cur.y) {
				printf("C");
			}
			else printf("%c", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int bfs_visited[MAX_MAP][MAX_MAP][4] = { 0 };
void bfs() {

	while (front < rear) {
		Razer cur = dequeue();

		//printf("\ncur %d %d | %d %d | %d\n", cur.x, cur.y, cur.dx, cur.dy, cur.turn);
		//debug(cur);

		if (cur.turn >= min_turn) continue; // 가지치기
		if (cur.x == target[1].x && cur.y == target[1].y) {
			//printf("도착\n");
			if (cur.turn < min_turn) {
				min_turn = cur.turn;
			}
			continue;
		}

		for (int i = 0;i < 4;i++) {
			Razer new = { cur.x + dx[i], cur.y + dy[i], i, cur.turn };

			//printf("%d %d |%d %d : ", cur.dx, cur.dy, new.dx, new.dy);
			if (cur.dir != new.dir) {
				new.turn += 1;
			}
			if (new.turn >= min_turn) continue;

			if (new.x >= 0 && new.x < H && new.y >= 0 && new.y < W && map[new.x][new.y] != WALL && new.turn < bfs_visited[new.x][new.y][new.dir]) {
				bfs_visited[new.x][new.y][new.dir] = new.turn;
				enqueue(new);
			}
		}
	}
}

int main() {
	scanf("%d %d", &W, &H);
	for (int i = 0;i < H;i++) {
		scanf("%s", map[i]);
		for (int j = 0;j < W;j++) {
			if (map[i][j] == TARGET) {
				target[target_idx++] = (Pos){ i,j };
			}
		}
	}
	// bfs_visited 초기화
	for (int i = 0;i < H;i++) {
		for (int j = 0;j < W;j++) {
			for (int k = 0;k < 4;k++)
				bfs_visited[i][j][k] = INF;
		}
	}

	// 시작 좌표 큐에 삽입
	for (int i = 0;i < 4;i++) {
		Razer start = { target[0].x, target[0].y, i, 0 };
		if (start.x >= 0 && start.x < H && start.y >= 0 && start.y < W && map[start.x][start.y] != WALL) {
			front = 0, rear = 0;
			enqueue(start);
			bfs_visited[start.x][start.y][start.dir] = 0;
			bfs();
		}
	}

	printf("%d\n", min_turn);

	return 0;
}
/*
C를 연결하기 위해 설치할 거울 개수의 최소값

#1)
3 3
...
*.C
C..
ans : 1

#2)
15 10
...*...***.C..*
.*.*.*........*
.*...*...*....*
.*.*....****.**
.*..**........*
.**..********.*
.*...*...*..*.*
.**..***.*.**.*
C........*.....
..***..........
ans : 6

#3)
100 7
...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*
C*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*.*
...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*
**************************************************************************************************.*
...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*
C*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*.*
...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*...*
ans : 196

*/
```
{% include code_close.html %}

### 📌 2. 파일 합치기 : 어떻게 풀지 생각하는 게 어려움
[백준 11066번](https://www.acmicpc.net/problem/11066)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

#define INF (~(1<<31))
#define MAX_NUM (500+1)
#define MIN(a,b) ((a<b)?a:b)

int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		int K = 0;
		scanf("%d", &K);

		int sum[MAX_NUM] = { 0 };
		int file[MAX_NUM] = { 0 };
		for (int i = 1;i <= K;i++) {
			scanf("%d", &file[i]);
			sum[i] = sum[i - 1] + file[i];
		}

		int dp[MAX_NUM][MAX_NUM] = { 0 };
		for (int len = 2;len <= K;len++) {	// 파일 len개를 합침
			for (int i = 1;i <= K - (len - 1);i++) {	// 가능한 i
				int j = i + (len - 1);	// i부터 len개의 idx : j
				dp[i][j] = INF;
				for (int k = i;k < j;k++) {	// i~j사이 중 어디서 나눠야 최소인지
					dp[i][j] = MIN(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]);
					// i ~ k 와 k+1 ~ j 합침
				}
			}
		}

		printf("%d\n", dp[1][K]);
	}

	return 0;
}
/*
소설을 여러장에
각 장을 다른 파일로
파일을 합쳐서 소설 완성본 한 파일로

합칠때는 두개씩
합칠때 필요 비용 = 두파일 크기 합

최종 한 파일 제작 비용의 총합 계산(최소)

c1 c2 c3 c4
40 30 30 50

c2+c3 = 60

c1 + (c2,c3) = 100

c4 + (c1,c2,c3) = 150

60 + 100 + 150 = 310

*/
```
{% include code_close.html %}

### 📌 3. 팰린드롬?
[백준 10942번](https://www.acmicpc.net/problem/10942)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>

#define MAX_N 2000

int main() {
    int N, M;
    scanf("%d", &N);
    int num[MAX_N];
    for (int i = 0;i < N;i++) {
        scanf("%d", &num[i]);
    }
    scanf("%d", &M);

    int dp[MAX_N][MAX_N] = { 0 };   // i부터 j까지 팰린드롬?

    // 길이 1 : 항상 팰린드롬
    for (int i = 0;i < N;i++) {
        dp[i][i] = 1;
    }

    // 길이 2
    for (int i = 0;i < N - 1;i++) {
        if (num[i] == num[i + 1]) {
            dp[i][i + 1] = 1;
        }
    }

    // 길이 3 이상 : 12321, 121 등
    for (int len = 3; len <= N;len++) {
        for (int i = 0;i <= N - len;i++) {
            int j = i + len - 1;
            if (num[i] == num[j] && dp[i + 1][j - 1]) {
                dp[i][j] = 1;
            }
        }
    }

    while (M--) {
        int S = 1, E = 1;
        scanf("%d %d", &S, &E);
        printf("%d\n", dp[S - 1][E - 1]);
    }

    return 0;
}
/*
DP
1. 문제를 작은 문제로 나눠
2. 중복되는 부분 문제(같은 계산 저장)
3. 중복 계산 방지


1 2 3 2 1 이 펠린드롬이려면
1 == 1이고, 2 3 2 가 펠린드롬이어야 함

2 3 2 가 펠린드롬이려면
2 == 2이고, 3이 펠린드롬이어야 함

->
1 2 3 4 4 3 2 1
1 == 1이고, 2 3 4 4 3 2 가 펠린드롬이어야 함

*/
```
{% include code_close.html %}

### 📌 4. 가스관
[백준 2931번](https://www.acmicpc.net/problem/2931)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<string.h>

#define MAX_MAP 25

enum Map_Info {
    EMPTY = '.',
    MOSK = 'M',
    ZAGR = 'Z',
};
enum Dir_Info {
    DISABLE = -1,
};

typedef struct {
    int x;
    int y;
}Pos;

int R, C;
char map[MAX_MAP][MAX_MAP + 1];
Pos start, end;

// 동남서북
// 3
//2  0
// 1
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

// 7종류, 4개의 입구, 출구의 방향 저장
int pipe_outdir[7][4] = {   // 출구 없는 경우 DISABLE(-1)
   { DISABLE, 3, DISABLE, 1 },
   { 2, DISABLE, 0, DISABLE },
   { 2, 3, 0, 1 },
   { 1, 0, DISABLE, DISABLE },
   { 3, DISABLE, DISABLE, 0 },
   { DISABLE, DISABLE, 3, 2 },
   { DISABLE, 2, 1, DISABLE }
};

Pos temp[10];   // 탐색 중 발견한 EMPTY 좌표 저장
int temp_idx = 0;

int dfs_visited[MAX_MAP][MAX_MAP];
void dfs(Pos cur, int type) {   
    // type0 : start->end
    // type1 : end->start

   //printf("cur %d %d , dir %d\n", cur.x, cur.y, cur.prev_dir);
    if (map[cur.x][cur.y] == EMPTY) {
        //printf("empty %d %d , dir %d\n", cur.x, cur.y, cur.prev_dir);
        temp[temp_idx++] = cur;
        return;
    }
    else if (type == 0 && cur.x == end.x && cur.y == end.y) {
        return;
    }
    else if (type == 1 && cur.x == start.x && cur.y == start.y) {
        return;
    }
    dfs_visited[cur.x][cur.y] = 1;

    for (int i = 0; i < 4; i++) {
        int new_dir = pipe_outdir[map[cur.x][cur.y]][i];
        if (new_dir != DISABLE) {
            Pos new = { cur.x + dx[new_dir], cur.y + dy[new_dir] };
            if (new.x >= 0 && new.x < R && new.y >= 0 && new.y < C && !dfs_visited[new.x][new.y]) {
                dfs(new, type);
            }
        }
    }
}
int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < C; j++) {
            switch (map[i][j]) {
            case 'M': start = (Pos){ i,j }; map[i][j] = 2; break;
            case 'Z': end = (Pos){ i,j }; map[i][j] = 2; break;
            case '|': map[i][j] = 0; break;
            case '-': map[i][j] = 1; break;
            case '+': map[i][j] = 2; break;
            case '1': map[i][j] = 3; break;
            case '2': map[i][j] = 4; break;
            case '3': map[i][j] = 5; break;
            case '4': map[i][j] = 6; break;
            }
        }
    }

    // start -> end 끊어지는곳 찾기
    dfs(start, 0);

    // end -> start 끊어지는 곳 찾기
    memset(dfs_visited, 0, sizeof(dfs_visited));
    dfs(end, 1);

    // 끊어지는 좌표 특정하기
    Pos ans;
    for (int i = 0; i < temp_idx; i++) {
        int be = 0;
        for (int j = 0; j < temp_idx; j++) {
            if (j == i) continue;
            if (temp[i].x == temp[j].x && temp[i].y == temp[j].y) {
                be = 1;
                break;
            }
        }
        if (be == 1) {
            ans = temp[i];
            //printf("same %d %d , dir %d\n", temp[i].x, temp[i].y, temp[i].prev_dir);
            break;
        }
    }

    // 끊어지는 좌표 주변 파이프의 방향 확인
    int dir[4] = { 0 };   // 동서남북
    for (int i = 0; i < 4; i++) {
        Pos side = { ans.x + dx[i], ans.y + dy[i] };
        int ch = map[side.x][side.y];
        if (ch == '.') continue;
        if (ch == 2) {  // 시작지점이나 끝지점은 패스
            if (side.x == start.x && side.y == start.y) continue;
            else if (side.x == end.x && side.y == end.y) continue;
        }

        if (side.x >= 0 && side.x < R && side.y >= 0 && side.y < C) {
            //printf("%d\n", ch);
            switch (i) {
            case 0:
                if (ch == 1 || ch == 2 || ch == 5 || ch == 6) {
                    dir[i] = 1;
                }
                break;
            case 1:
                if (ch == 0 || ch == 2 || ch == 4 || ch == 5) {
                    dir[i] = 1;
                }
                break;
            case 2:
                if (ch == 1 || ch == 2 || ch == 3 || ch == 4) {
                    dir[i] = 1;
                }
                break;
            case 3:
                if (ch == 0 || ch == 2 || ch == 3 || ch == 6) {
                    dir[i] = 1;
                }
                break;
            }
        }
    }

    // 방향 환산
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += dir[i] << i;   // 1 2 4 8
    }
    /*
       동서남북
       1 2 4 8

        8
       4 1
        2
    */
    //printf("%d\n", sum);

    printf("%d %d ", ans.x + 1, ans.y + 1);
    switch (sum) {
    case 10: printf("|\n"); break;
    case 5: printf("-\n"); break;
    case 15: printf("+\n"); break;
    case 3: printf("1\n"); break;
    case 9: printf("2\n"); break;
    case 12: printf("3\n"); break;
    case 6: printf("4\n"); break;
    default: break;
    }

    return 0;
}
/*
#1)
3 5
..1-M
1-.4.
Z.23.
ans : 2 3 +

#2)
6 9
.........
.M--41Z..
....2+4..
.....2+4.
......2+4
.......2.
ans : 6 9 3

#3)
3 7
.14....
.M.Z...
..23...
answer: 2 3 |


*/
```
{% include code_close.html %}

### 📌 5. 행렬 곱셈 순서 : DP, 작은 길이부터 안쪽에서 최소비용 찾기, (2.파일합치기)와 거의 같은 문제
[백준 11049번](https://www.acmicpc.net/problem/11049)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

#define INF (~(1<<31))
#define MAX_N 500

typedef struct {
	int r;
	int c;
}Matrix;

int main() {
	int N;
	scanf("%d", &N);
	Matrix matrix[MAX_N];
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &matrix[i].r, &matrix[i].c);
	}
	
	int dp[MAX_N][MAX_N] = { 0 }; // i부터 j까지 더하는 최소

	for (int len = 2; len <= N; len++) {	// i부터 j까지의 길이
		for (int i = 0; i <= N - len; i++) {	// 가능한 i의 경우의 수
			int j = i + len - 1;			// 길이와 i를 선택했기에 j는 고정
			dp[i][j] = INF;
			for (int k = i; k < j; k++) {	// i~j 사이 중 어디에서 나누는 것이 가장 최소인지 찾음
				int cost = dp[i][k] + dp[k + 1][j] + matrix[i].r * matrix[k].c * matrix[j].c;
				if (cost < dp[i][j]) {
					dp[i][j] = cost;
				}
			}
		}
	}
	
	printf("%d\n", dp[0][N - 1]);

	return 0;
}
/*
#1)
3
5 3
3 2
2 6
ans : 90


4
5 3
3 2
2 6
6 5

*/
```
{% include code_close.html %}

###

