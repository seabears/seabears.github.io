---
title: DFS, BFS
description: >-           #한 문장으로 나옴

date: 2024-12-27 17:39:46 +0900
lastmod : 2025-02-06 12:23:00 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - 백준 c언어 정리
tags: 
    - Untag1

sitemap :
  changefreq : daily
  priority : 1.0

#excerpt: "이 글의 요약"   # 요약
#image: "url_to_image.jpg"   # 대표 이미지 (옵션)
#permalink: /category1/first-post/
pin: false              # true | false
published: true        # true | false
---

## 📌 DFS, BFS

## 📌 DFS
깊이 우선 탐색, Depth-First Search
최대한 깊이 내려간 뒤, 더이상 깊게 갈 곳이 엎을 경우 옆으로 이동

해당 분기를 완벽하게 탐색(한 방향을 갈 수 있을 떄까지 쭉 가기)

구현 : Stack, 재귀함수
<br>


## 📌 BFS
너비 우선 탐색, Breadth-First Search
최대한 넓게 이동한 다음, 더 이상 갈 수 없을 때 깊게 이동

구현 : Queue

https://devuna.tistory.com/32

<br>

## 📌 사용 특징
1) 모든 정점 방문 -> 둘다  
2) 경로의 특징

<br>

| 항목  | 내용           | 유리할 때                                                                                                             |
| ----- | -------------- | --------------------------------------------------------------------------------------------------------------------- |
| `dfs` | 깊이 우선 탐색 | **1. 모든 경로 다 가볼 때** <br> 2. 목표 노드가 깊을 때<br> 3. 용량<br> 4. dx dy를 목표 노드 방향순으로 설정하면 유리 |
| `bfs` | 너비 우선 탐색 | **1. 최단 거리** <br> 2. 노드 수 적을 때<br> 3. 얕은 해일 때                                                          |

<br>

dfs 백트래킹 필요할 수도  
bfs 최단거리시 typedef struct에 step 변수 넣기


## 📌 1. 최단 거리 예시

백준 2178번  
https://www.acmicpc.net/problem/2178

```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 100
#define INF 1e9	//10억

#define CAN '1'

typedef struct {
	int x;
	int y;
	int step;
}Pos;

char map[MAX][MAX];
int N, M;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos end;

void input() {
	scanf("%d %d", &N, &M);

	(&end)->x = N - 1;
	(&end)->y = M - 1;


	for (int i = 0;i < N;i++) {
		scanf("%s", &map[i]);
	}

	//printf("end : %d %d\n", end.x, end.y);
}



bool dfs_visited[MAX][MAX] = { 0 };
int dfs_min_step = INF;

void dfs(Pos cur, int step) {
	
	// 현위치 종료조건 체크
	if (cur.x == end.x && cur.y == end.y) {
		if (step < dfs_min_step) {
			dfs_min_step = step;
		}
		return;
	}

	// 현위치 방문 체크
	dfs_visited[cur.x][cur.y] = 1;

	// 현위치 갈 수 있는 곳 체크
	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };
		if (map[new.x][new.y] == CAN && !dfs_visited[new.x][new.y] && new.x >=0 && new.x <N && new.y>=0 && new.y<M) {
			//printf("%d %d\n", new.x, new.y);
			dfs(new, step + 1);
		}
	}

	// 백트래킹 : 다시 돌려놓기
	dfs_visited[cur.x][cur.y] = 0;
}



bool bfs_visited[MAX][MAX];
Pos queue[MAX * MAX];
int front = 0, rear = 0;
void enqueue(Pos pos) {
	queue[rear++] = pos;
}
Pos dequeue() {
	return queue[front++];
}
int bfs() {
  // 첫 위치
	enqueue((Pos){ 0,0,1 });
	bfs_visited[0][0] = 1;

	// queue가 비어있지 않을 경우 == 더 이상 갈 곳 없지 않을 경우
	while (front < rear) {
		// 현위치
		Pos cur = dequeue();

		//printf("%d %d %d\n", cur.x, cur.y, cur.step);

		// 현위치 종료 조건 체크
		if (cur.x == end.x && cur.y == end.y) {
			return cur.step;
		}

		// 현위치에서 갈 수 있는 곳 체크
		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };

			if (new.x >= 0 && new.x < N && new.y>=0 && new.y < M && map[new.x][new.y] == CAN && !bfs_visited[new.x][new.y]) {
				bfs_visited[new.x][new.y] = 1;
				enqueue(new);
			}
		}
	}

	return -1;
}

int main() {
	input();

	Pos cur = { 0,0 };
	dfs(cur, 1);
	printf("dfs : %d\n", dfs_min_step);

	int res = bfs();
	printf("bfs : %d", res);

	return 0;
}
```


<br>

## 📌 2. 그냥 dfs, bfs

백준 2606번
https://www.acmicpc.net/problem/2606

```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 101

bool map[MAX][MAX];
bool visited[MAX];
int n, m;



int queue[MAX * MAX];
int front = 0, rear = 0;
void enqueue(int cur) {
	queue[rear++] = cur;
}
int dequeue() {
	return queue[front++];
}
void bfs(int start) {
	enqueue(start);
	visited[start] = 1;

	while (front < rear) {
		int cur = dequeue();
		//printf("%d\n", cur);
		for (int i = 1;i <= n;i++) {
			if (map[cur][i] && !visited[i]) {
				visited[i] = 1;
				enqueue(i);
			}
		}
	}

}

void dfs(int cur) {
	
	visited[cur] = 1;

	//printf("%d\n",cur);

	for (int i = 1;i <= n;i++) {
		if (map[cur][i] && !visited[i]) {
			dfs(i);
		}
	}


}

int main() {

	scanf("%d\n%d", &n, &m);

	
	for (int i = 0;i < m;i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = 1;
		map[b][a] = 1;
	}

	int start = 1;
	
	//dfs(start);
	bfs(start);

	int cnt = 0;
	for (int i = 2;i <= n;i++) {
		if (visited[i]) cnt++;
	}

	printf("%d\n", cnt);

	return 0;
}

```

<br>

## 📌 3. flood fill (dfs)

백준 2667번
https://www.acmicpc.net/problem/2667
```c
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX 26
#define CAN '1'

typedef struct {
	int x;
	int y;
}Pos;

int N;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int cnt = 0;
int home_cnt[MAX * MAX];

void dfs(Pos cur) {
	visited[cur.x][cur.y] = 1;
	home_cnt[cnt]++;

	//printf("%d %d\n", cur.x, cur.y);

	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };
		if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N && map[new.x][new.y] == CAN && !visited[new.x][new.y]) {
			//visited[new.x][new.y] = 1;
			
			dfs(new);
		}
	}
}
int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int main() {

	scanf("%d", &N);

	for (int i = 0;i < N;i++) {
		scanf("%s", &map[i]);
	}

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (map[i][j] == CAN && !visited[i][j]) {
				dfs((Pos) { i, j });
				cnt++;
			}
		}
	}

	qsort(home_cnt, cnt, sizeof(int), cmp);

	printf("%d\n", cnt);
	for (int i = 0;i < cnt;i++) {
		printf("%d\n", home_cnt[i]);
	}
	
	return 0;
}
```

<br>


## 📌 4. 촌수 구하기 (bfs)
백준 2644번
https://www.acmicpc.net/problem/2644

```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 101

typedef struct {
	int n;
	int step;
}Node;

int n;
bool map[MAX][MAX];
bool visited[MAX];

Node queue[MAX*MAX];
int front = 0, rear = 0;
void enqueue(Node n) {
	queue[rear++] = n;
}
Node dequeue() {
	return queue[front++];
}
int bfs(Node a, Node b) {
	enqueue(a);
	visited[a.n] = 1;

	int cnt = 0;
	while (front < rear) {
		Node cur = dequeue();

		//printf("%d\n", cur.n);

		if (cur.n == b.n) return cur.step;

		for (int i = 1;i <= n;i++) {
			if (map[cur.n][i] && !visited[i]) {
				visited[i] = 1;
				Node new = { i, cur.step + 1 };
				
				enqueue(new);
			}
		}
	}

	return -1;
}
int main() {

	scanf("%d", &n);

	int a, b;
	scanf("%d %d", &a, &b);

	int m;
	scanf("%d", &m);
	for (int i = 0;i < m;i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x][y] = 1;
		map[y][x] = 1;
	}

	int res = bfs((Node) { a, 0 }, (Node) { b, 0 });
	printf("%d\n", res);


	return 0;

}
```


<br>

## 📌 5. 3차원 (bfs)

백준 7569번
<https://www.acmicpc.net/problem/7569>

```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 101

enum Fruit {
	RIPEN = 1,
	NO_RIPEN = 0,
	NOT = -1
};

typedef struct {
	int x;
	int y;
	int z;
	int step;
}Pos;

// 오, 왼, 뒤, 앞
int dx[6] = { 0,0,1,-1,0,0 };
int dy[6] = { 1,-1,0,0,0,0 };
int dz[6] = { 0,0,0,0,1,-1 };

int M, N, H;
int map[MAX][MAX][MAX];
bool visited[MAX][MAX][MAX];
Pos queue[MAX * MAX * MAX];
int front = 0, rear = 0;

void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}

int max_step = 0;
void print(int submap[][MAX][MAX]) {
	printf("----\n");
	for (int z = 0;z < H;z++) {
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				printf("%d ", submap[z][i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	printf("----\n");
}
void bfs() {


	while (front < rear) {
		Pos cur = dequeue();	
		visited[cur.z][cur.x][cur.y] = 1;

		for (int i = 0;i < 6;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.z + dz[i], cur.step + 1 };

			if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && new.z >= 0 && new.z < H && map[new.z][new.x][new.y] == NO_RIPEN && !visited[new.z][new.x][new.y]) {
				enqueue(new);
				visited[new.z][new.x][new.y] = 1;
				map[new.z][new.x][new.y] = RIPEN;
				if (new.step > max_step) max_step = new.step;
			}

			//printf("**%d : dx dy dz : %d %d %d\n", cur.step, dx[i], dy[i], dz[i]);
			//print(map);
		}
	}
		
}
int check() {
	for (int z = 0;z < H;z++) {
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				if (map[z][i][j] == NO_RIPEN) return -1;
			}
		}
	}
	return max_step;
}
int main() {

	scanf("%d %d %d", &M, &N, &H);

	for (int z = 0;z < H;z++) {
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				scanf("%d", &map[z][i][j]);
				if (map[z][i][j] == RIPEN) {
					enqueue((Pos) { i, j, z, 0 });
				}
			}
		}
	}

	bfs();
	int res = check();
	printf("%d\n", res);

	return 0;
}
```


<br>


## 📌 6. dx 달라지는 (bfs)	나올만함

백준 1697번
https://www.acmicpc.net/problem/1697

```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 100001
#define INF (~(1<<31))

typedef struct {
	int x;
	int time;
}Subin;

int dx[3];

void sync(Subin subin) {
	dx[0] = subin.x + 1;
	dx[1] = subin.x - 1;
	dx[2] = subin.x * 2;
}

int min_time = INF;
bool visited[MAX];

Subin queue[MAX];
int front = 0, rear = 0;
void enqueue(Subin new) {
	queue[rear++] = new;
}
Subin dequeue() {
	return queue[front++];
}
int bfs(int start, int end) {
	Subin subin_start = { start, 0 };
	sync(subin_start);
	enqueue(subin_start);
	visited[subin_start.x] = 1;

	while (front < rear) {
		Subin cur = dequeue();
		//printf("%d\n", cur.x);
		if (cur.x == end) return cur.time;

		for (int i = 0;i < 3;i++) {
			sync(cur);
			Subin new = { dx[i], cur.time + 1 };

			if (new.x >= 0 && new.x < MAX && !visited[new.x]) {
				visited[new.x] = 1;
				enqueue(new);
			}
		}
	}


	return -1;
}


int main() {
	int N, K;
	scanf("%d %d", &N, &K);

	int res = bfs(N, K);
	printf("%d\n", res);

	return 0;
}
```


-> sync를 통해 dx 맞추기

<br>


## 📌 7. bfs 몸풀기

백준 5014번
https://www.acmicpc.net/problem/5014
```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 1000001

typedef struct {
	int y;
	int step;
}Pos;

bool visited[MAX];

int f;

Pos queue[MAX];
int front = 0, rear = 0;
void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}
int bfs(int start, int end, int* dy) {
	Pos s = { start, 0 };
	enqueue(s);
	visited[s.y] = 1;

	while (front < rear) {
		Pos cur = dequeue();
		if (cur.y == end) return cur.step;

		for (int i = 0;i < 2;i++) {
			Pos new = { cur.y + dy[i], cur.step + 1 };
			
			if (new.y >= 1 && new.y <= f && !visited[new.y]) {
				enqueue(new);
				visited[new.y] = 1;
			}
		}

	}
	return -1;

}

int main() {
	int s, g, u, d;
	scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);
	
	int dy[2] = { u,-1 * d };
	int res = bfs(s, g, dy);
	if (res == -1) printf("use the stairs");
	else printf("%d\n", res);

	return 0;
}
```



<br>

## 📌 8. dfs 영역 수 세기

백준 2468번
https://www.acmicpc.net/problem/2468
```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX 101

typedef struct {
	int x;
	int y;
}Pos;

int map[MAX][MAX];
int N;
bool visited[MAX][MAX];


int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void dfs(Pos cur, int h) {
	visited[cur.x][cur.y] = 1;
	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };

		//printf("%d %d\n", new.x, new.y);

		if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N && map[new.x][new.y] > h && !visited[new.x][new.y]) {
			//visited[new.x][new.y] = 1;	여기에할까 위에할까
			//시작위치 표시하려면 위에가 맞는듯
			dfs((Pos) { new.x, new.y}, h);
		}
	}


}

int main() {

	scanf("%d", &N);

	int max_h = 0;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] > max_h) max_h = map[i][j];
		}
	}

	int max_safe_cnt = 0;
	for (int h = 0;h <= max_h;h++) {
		memset(visited, 0, sizeof(visited));
		int safe_cnt = 0;

		for (int i = 0;i < N;i++) {
			for (int j = 0;j < N;j++) {
				if (map[i][j] > h && !visited[i][j]) {
					dfs((Pos) { i, j }, h);
					safe_cnt++;
				}
			}
		}
		if (safe_cnt > max_safe_cnt) max_safe_cnt = safe_cnt;
	}


	printf("%d\n", max_safe_cnt);


	return 0;
}
```



<br>

## 📌 9. dfs 맵이 계속 달라지는, 영역 수 세기

[백준 2573번](https://www.acmicpc.net/problem/2573)

```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX 301

enum MAP {
	SEA = 0,
	THRESHOLD = 2,
};

typedef struct {
	int x;
	int y;
}Pos;

int N, M;
int map[MAX][MAX];
int temp_map[MAX][MAX];
bool visited[MAX][MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void dfs(Pos cur) {
	visited[cur.x][cur.y] = 1;

	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };
		if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && map[new.x][new.y] != SEA && !visited[new.x][new.y]) {
			dfs(new);
		}
	}
}
int sea_check(Pos cur) {
	int res = 0;
	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };
		if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && temp_map[new.x][new.y] == SEA) {
			res++;
		}
	}
	return res;
}
void print() {
	printf("-----\n");
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	
	printf("-----\n");

}

int main() {

	scanf("%d %d", &N, &M);


	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			scanf("%d", &map[i][j]);
		}
	}

	int year = 0;
	while (++year) {

		//얼음 녹이기
		memcpy(temp_map, map, sizeof(map));

		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				if (map[i][j] != SEA) {
					int sea_cnt = sea_check((Pos) { i, j });
					map[i][j] -= sea_cnt;
					if (map[i][j] < 0) map[i][j] = 0;
				}
			}
		}


		//얼음 덩어리 수 세기
		memset(visited, 0, sizeof(visited));
		int ice_cnt = 0;

		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				if (map[i][j] != SEA && !visited[i][j]) {
					dfs((Pos) { i, j });
					ice_cnt++;
				}
			}
		}


		//종료 조건 체크
		if (ice_cnt >= THRESHOLD) {
			printf("%d\n", year);
			break;
		}
		else if (ice_cnt == 0) {
			printf("0\n");
			break;
		}


		//print();
	}
	return 0;
}
```


<br>


## 📌 10. bfs : dfs인줄 알았는데, 새로운 관점임 ( 맵 없이 ) | 틀렸던

백준 9205번
https://www.acmicpc.net/problem/9205
```c
#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include <string.h>

#define BEER 1000     // 한 번 이동할 수 있는 최대 거리 (50m * 20병)
#define DIST 50       // 한 번에 이동 가능한 거리 단위

typedef struct {
    int x;
    int y;
} Pos;

int n; // 편의점 개수
Pos home, festival, conv[101];
bool can_arrive = false;

Pos* queue;
int front = 0, rear = 0;
bool visited[102] = { false }; // 집 + 편의점 + 페스티벌

Pos* initqueue(int n) {
    queue = (Pos*)malloc(sizeof(Pos) * n);
    return queue;
}

void enqueue(Pos pos) {
    queue[rear++] = pos;
}
Pos dequeue() {
    return queue[front++];
}
// 거리 계산 함수
bool can_reach(Pos a, Pos b) {
    int distance = abs(a.x - b.x) + abs(a.y - b.y);
    return distance <= BEER;
}
void freequeue() {
    free(queue);
}
void bfs(Pos cur) {

    // 집을 큐에 넣고 탐색 시작
    enqueue(cur);
    visited[0] = true; // 집 방문 처리

    while (front < rear) {
        Pos current = dequeue();

        // 페스티벌 도착 가능 여부 확인
        if (can_reach(current, festival)) {
            can_arrive = true;
            break;
        }

        // 편의점 탐색
        for (int i = 0; i < n; i++) {
            if (!visited[i + 1] && can_reach(current, conv[i])) {
                visited[i + 1] = true;
                enqueue(conv[i]);
            }
        }
    }
}



int main() {
    int t;
    scanf("%d", &t);

    for (int i = 0;i < t;i++) {

        scanf("%d", &n);

        scanf("%d %d", &home.x, &home.y);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &conv[i].x, &conv[i].y);
        }
        scanf("%d %d", &festival.x, &festival.y);


        initqueue(n + 2);   // 집, 편의점, 페스티벌 포함, 큐 메모리 동적 할당

        bfs(home);

        // 결과 출력
        printf("%s\n", can_arrive ? "happy" : "sad");

        // 초기화
        front = 0;
        rear = 0;
        can_arrive = 0;
        memset(visited, 0, sizeof(visited));

        freequeue();
    }

    return 0;
}

```


<br>


## 📌 11. dfs + 시뮬레이션

[백준 14503번](https://www.acmicpc.net/problem/14503)

```c
#include<stdio.h>

#define MAX 51

enum Direction{
	NORTH = 0,
	WEST = 1,
	SOUTH = 2,
	EAST = 3,
};
enum Map {
	DIRTY = 0,
	WALL = 1,
	CLEAN = 2
};
typedef struct {
	int x;
	int y;
	int d;
}Robot;

int N, M;
int map[MAX][MAX];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };


int check_dirty(Robot cur) {
	int ret = 0;
	for (int i = 0;i < 4;i++) {
		Robot new = { cur.x + dx[i], cur.y + dy[i], 0 };
		if (map[new.x][new.y] == DIRTY) ret = 1;
	}
	return ret;
}
Robot rotate(Robot cur) {
	switch (cur.d) {
	case NORTH:
		cur.d = WEST;
		break;
	case WEST:
		cur.d = SOUTH;
		break;
	case SOUTH:
		cur.d = EAST;
		break;
	case EAST:
		cur.d = NORTH;
		break;
	}
	return cur;
}
int front_check(Robot cur) {
	Robot front = { cur.x + dx[cur.d], cur.y + dy[cur.d] , cur.d};
	
	if (map[front.x][front.y] == DIRTY)return 1;
	else return 0;
}

void print() {
	printf("----\n");
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}
int cnt = 0;
int stop = 0;
void dfs(Robot cur) {

	if (stop) return;
	if (map[cur.x][cur.y] == DIRTY) {
		map[cur.x][cur.y] = CLEAN;
		cnt++;
	}
	//printf("%d %d	  | %d\n", cur.x, cur.y, cur.d);
	//print();

	if (check_dirty(cur) == 0) {
		//방향 유지 후진, 처음으로
		Robot back = { cur.x - dx[cur.d], cur.y - dy[cur.d], cur.d };
		if (map[back.x][back.y] != WALL) {
			dfs(back);
		}
		//후진칸 벽 이면 작동 멈춤
		else {
			stop = 1;
			return;
		}
	}
	else {
		Robot rot = rotate(cur);
		Robot new = rot;
		if (front_check(rot)) {
			new = (Robot){ rot.x + dx[rot.d], rot.y + dy[rot.d] , rot.d };
		}
		dfs(new);
	}

}


int main() {

	scanf("%d %d", &N, &M);

	int r, c, d;
	scanf("%d %d %d", &r, &c, &d);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			scanf("%d", &map[i][j]);
		}
	}

	// 문제의 북동남서를 반시계 방향인 북서남동으로 변환
	if (d == 1) d = 3;
	else if (d == 3) d = 1;

	dfs((Robot) { r, c, d });

	printf("%d\n", cnt);

	return 0;
}
```


<br>


---
---

<br>


다른 문제집  


## 📌 12. 그림 영역 수와 최대 영역 찾기  
[백준 1926번](https://www.acmicpc.net/problem/1926)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">DFS 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 501

typedef struct {
	int x;
	int y;
}Pos;

int n, m;
bool picture[MAX][MAX];
bool visited[MAX][MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int max_area = 0;
int cur_area = 0;	//재귀이므로 따로 선언해야함

void dfs(Pos cur) {

	visited[cur.x][cur.y] = 1;
	cur_area++;
	if (cur_area > max_area) {
		max_area = cur_area;
	}
	//printf("area %d | %d %d\n", cur_area, cur.x, cur.y);

	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };
		if (new.x >= 0 && new.x < n && new.y >= 0 && new.y < m && picture[new.x][new.y] == 1 && !visited[new.x][new.y]) {
			dfs(new);
		}
	}
}
int main() {

	scanf("%d %d", &n, &m);

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			scanf("%d", &picture[i][j]);
		}
	}

	int cnt = 0;

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			if (picture[i][j] == 1 && !visited[i][j]) {
				cur_area = 0;
				dfs((Pos) { i, j });
				cnt++;
			}
		}
	}

	printf("%d\n", cnt);
	printf("%d\n", max_area);

	return 0;
}
```

</div>
</details>

<br>

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">BFS 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 501

typedef struct {
	int x;
	int y;
}Pos;

int n, m;
bool picture[MAX][MAX];
bool visited[MAX][MAX];

void enqueue(Pos cur, Pos* queue, int* rear) {
	queue[(*rear)++] = cur;
}
Pos dequeue(Pos* queue, int* front) {
	return queue[(*front)++];
}

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int max_area = 0;

int bfs(Pos start) {
	Pos queue[MAX * MAX];
	int front = 0, rear = 0;

	int area_cnt = 0;

	visited[start.x][start.y] = 1;
	enqueue(start, queue, &rear);

	while (front < rear) {

		Pos cur = dequeue(queue, &front);
		area_cnt++;
		if (area_cnt > max_area) max_area = area_cnt;

		//printf("%d %d %d\n", area_cnt, cur.x, cur.y);

		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i]};
			if (new.x >= 0 && new.x < n && new.y >= 0 && new.y < m && picture[new.x][new.y] == 1 && !visited[new.x][new.y]) {
				enqueue(new, queue, &rear);
				visited[new.x][new.y] = 1;
			}
		}
	}

	return area_cnt;
}
int main() {

	scanf("%d %d", &n, &m);

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			scanf("%d", &picture[i][j]);
		}
	}

	int cnt = 0;

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			if (picture[i][j] == 1 && !visited[i][j]) {
				bfs((Pos) { i, j });
				cnt++;
			}
		}
	}

	printf("%d\n", cnt);
	printf("%d\n", max_area);

	return 0;
}
```

</div>
</details>

<br>


## 📌 13. 토마토(2차원)
[백준 7576번](https://www.acmicpc.net/problem/7576)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">초기 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 1001

enum Tomato_status {
	RIPEN = 1,
	NO_RIPEN = 0,
	EMPTY = -1,
};
typedef struct {
	int x;
	int y;
	int step;
}Pos;

int M, N;
int box[MAX][MAX];
bool visited[MAX][MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos queue[MAX * MAX];
int front = 0, rear = 0;

void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}

int step = 0;
int check_all_ripen() {
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			if (box[i][j] == NO_RIPEN) return -1;
		}
	}
	return step;
}
void bfs() {

	while (front < rear) {
		Pos cur = dequeue();
		visited[cur.x][cur.y] = 1;

		//printf("%d %d | %d\n", cur.x, cur.y, cur.step);
		if (cur.step > step) step = cur.step;

		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };
			if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && box[new.x][new.y] == NO_RIPEN && !visited[new.x][new.y]) {
				enqueue(new);
				box[new.x][new.y] = RIPEN;
				visited[new.x][new.y] = 1;
			}
		}
	}
}


int main() {

	scanf("%d %d", &M, &N);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			scanf("%d", &box[i][j]);
			if (box[i][j] == RIPEN) enqueue((Pos) { i, j, 0 });
		}
	}
	
	bfs();
	int res = check_all_ripen();
		
	printf("%d\n", res);


	return 0;
}
```

</div>
</details>

<br>

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">visited 없앤 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 1001

enum Tomato_status {
	RIPEN = 1,
	NO_RIPEN = 0,
	EMPTY = -1,
};
typedef struct {
	int x;
	int y;
	int step;
}Pos;

int M, N;
int box[MAX][MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos queue[MAX * MAX];
int front = 0, rear = 0;

void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}

int step = 0;
int check_all_ripen() {
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			if (box[i][j] == NO_RIPEN) return -1;
		}
	}
	return step;
}
void bfs() {

	while (front < rear) {
		Pos cur = dequeue();

		//printf("%d %d | %d\n", cur.x, cur.y, cur.step);
		if (cur.step > step) step = cur.step;

		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };
			if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && box[new.x][new.y] == NO_RIPEN) {
				enqueue(new);
				box[new.x][new.y] = RIPEN;
			}
		}
	}
}


int main() {

	scanf("%d %d", &M, &N);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			scanf("%d", &box[i][j]);
			if (box[i][j] == RIPEN) enqueue((Pos) { i, j, 0 });
		}
	}
	
	bfs();
	int res = check_all_ripen();
		
	printf("%d\n", res);


	return 0;
}
```

</div>
</details>

<br>


<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">map에 step을 직접 삽입한 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 1001

enum Tomato_status {
	RIPEN = 1,
	NO_RIPEN = 0,
	EMPTY = -1,
};
typedef struct {
	int x;
	int y;
}Pos;

int M, N;
int box[MAX][MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos queue[MAX * MAX];
int front = 0, rear = 0;

void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}

int check_all_ripen() {
	int max = 0;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			if (box[i][j] == NO_RIPEN) return -1;
			else if (box[i][j] > max) max = box[i][j];
		}
	}
	return max - 1;//시작이 1이었으니까
}
void bfs() {

	while (front < rear) {
		Pos cur = dequeue();

		//printf("%d %d | %d\n", cur.x, cur.y, cur.step);

		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i] };
			if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && box[new.x][new.y] == NO_RIPEN) {
				enqueue(new);
				box[new.x][new.y] = box[cur.x][cur.y] + 1;	//box에 직접 이전거 + 1 삽입
			}
		}
	}
}

int main() {

	scanf("%d %d", &M, &N);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			scanf("%d", &box[i][j]);
			if (box[i][j] == RIPEN) enqueue((Pos) { i, j });
		}
	}
	
	bfs();
	int res = check_all_ripen();
		
	printf("%d\n", res);

	/*
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			printf("%d ", box[i][j]);
		}
		printf("\n");
	}
	*/
	return 0;
}
```

</div>
</details>

<br>

## 📌 14. BFS 매턴마다 확장하는 불을 피해 탈출하는 문제  
[백준 4179번](https://www.acmicpc.net/problem/4179)



<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 1001
enum Map {
	FIRE = 'F',
};
typedef struct {
	int x;
	int y;
	int step;
}Pos;

int R, C;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos fire[MAX * MAX];
int fire_front = 0;
int fire_rear = 0;

Pos queue[MAX * MAX];
int front = 0, rear = 0;
void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}
//디버깅용
void print(char map[MAX][MAX], Pos cur) {
	printf("\n");
	for (int i = 0;i < R;i++) {
		for (int j = 0;j < C;j++) {
			if (i == cur.x && j == cur.y) printf("J ");
			else printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//불 확장, 다음에 확장할 불 저장
void fire_update(Pos cur) {
	int end = fire_rear;
	for (int i = fire_front;i < fire_rear;i++) {
		for (int j = 0;j < 4;j++) {
			Pos new = { fire[i].x + dx[j], fire[i].y + dy[j], 0 };
			if (new.x >= 0 && new.x < R && new.y >= 0 && new.y < C && map[new.x][new.y] == '.') {
				map[new.x][new.y] = FIRE;
				fire[end++] = new;
			}
		}
	}
	fire_front = fire_rear;
	fire_rear = end;

	//print(map, cur);
}
//bfs 움직이기
int bfs(Pos start) {
	enqueue(start);
	visited[start.x][start.y] = 1;

	int temp_step = 0;
	while (front < rear) {
		Pos cur = dequeue();

		//printf("%d %d | %d\n", cur.x, cur.y, cur.step);

		if (cur.step > temp_step) {
			fire_update(cur);
			temp_step = cur.step;
		}
		if (map[cur.x][cur.y] == FIRE) { 
			continue;
		}

		if (cur.x == 0 || cur.x == R - 1 || cur.y == 0 || cur.y == C - 1) {
			return cur.step;

		}
		//print(map, cur);
		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };
			if (new.x >= 0 && new.x < R && new.y >= 0 && new.y < C && (map[new.x][new.y] == '.') && !visited[new.x][new.y]) {
				enqueue(new);
				visited[new.x][new.y] = 1;
			}
		}
	}
	return -1;
}
int main() {

	scanf("%d %d", &R, &C);

	Pos start;
	for (int i = 0;i < R;i++) {
		scanf("%s", map[i]);
		for (int j = 0;j < C;j++) {
			if (map[i][j] == 'J') {
				start = (Pos){ i,j, 0 };
				map[i][j] = '.';
			}
			else if (map[i][j] == FIRE) {
				fire[fire_rear++] = (Pos){ i,j,0 };
			}

		}
	}

	int res = bfs(start);
	if (res == -1) printf("IMPOSSIBLE\n");
	else printf("%d\n", res + 1);

	return 0;
}
```

</div>
</details>

## 📌 15. 배추 : 영역수 찾기 dfs
[백준 1012번](https://www.acmicpc.net/problem/1012)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define K_MAX (2500+1)
#define MAP_MAX (50 + 1)

typedef struct {
	int x;
	int y;
}Pos;

int M, N, K;
int map[MAP_MAX][MAP_MAX] = { 0 };
bool visited[MAP_MAX][MAP_MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void dfs(Pos cur) {
	visited[cur.x][cur.y] = 1;

	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };

		if (new.x >= 0 && new.x < M && new.y >= 0 && new.y < N && map[new.x][new.y] == 1 && !visited[new.x][new.y]) {
			dfs(new);
		}
	}
}
int main() {
	int T;
	scanf("%d", &T);
	for (;T > 0;T--) {
		scanf("%d %d %d", &M, &N, &K);

		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));

		for (int i = 0;i < K;i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			map[x][y] = 1;
		}

		int cnt = 0;
		for (int i = 0;i < M;i++) {
			for (int j = 0;j < N;j++) {
				if (map[i][j] == 1 && !visited[i][j]) {
					dfs((Pos) { i, j });
					cnt++;
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
```

</div>
</details>
<br>

## 📌 16. 적록색약 : 영역수 찾기 dfs, 특정 영역은 같이 처리
[백준 10026번](https://www.acmicpc.net/problem/10026)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX (100+1)

enum Color {
	RED = 'R',
	GREEN = 'G',
	BLUE = 'B',
};
typedef struct {
	int x;
	int y;
}Pos;

int N;
char map[MAX][MAX];
bool visited[MAX][MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void dfs(Pos cur, char color, bool sick) {
	visited[cur.x][cur.y] = 1;

	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };
		
		if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N && !visited[new.x][new.y]) {
			if (!sick && map[new.x][new.y] == color) {	//적록색약 아닌 경우
				dfs(new, color, sick);
			}
			else if (sick) {	//적록색약인 경우
				if (color == BLUE && map[new.x][new.y] == color) dfs(new, color, sick);	//파랑은 잘 구별
				else if ((color == RED || color == GREEN) && (map[new.x][new.y] == RED || map[new.x][new.y] == GREEN)) { //빨강, 초록은 같이 처리
					dfs(new, color, sick);
				}
			}
		}
	}
}

int main() {

	scanf("%d", &N);
	for (int i = 0;i < N;i++) {
		scanf("%s", map[i]);
	}

	int cnt = 0;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (!visited[i][j]) {
				dfs((Pos) { i, j }, map[i][j], 0);
				cnt++;
			}
		}
	}
	printf("%d ", cnt);

	cnt = 0;
	memset(visited, 0, sizeof(visited));
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (!visited[i][j]) {
				dfs((Pos) { i, j }, map[i][j], 1);
				cnt++;
			}
		}
	}
	printf("%d", cnt);

	return 0;
}
```

</div>
</details>
<br>

## 📌 17. 체스 나이트 원하는 곳까지 이동시키기 : BFS
[백준 7562번](https://www.acmicpc.net/problem/7562)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX (300+1)

typedef struct {
	int x;
	int y;
	int step;
}Pos;

int dx[8] = { -2,-1,1,2,2,1,-1,-2 };
int dy[8] = { 1,2,2,1,-1,-2,-2,-1 };

bool visited[MAX][MAX];
Pos queue[MAX * MAX];
int front = 0, rear = 0;
void enqueue(Pos cur) {
	queue[rear++] = cur;
}
Pos dequeue() {
	return queue[front++];
}

int bfs(int l, Pos start, Pos togo) {

	front = 0, rear = 0;
	memset(visited, 0, sizeof(visited));

	enqueue(start);
	visited[start.x][start.y] = 1;

	while (front < rear) {
		Pos cur = dequeue();
		//printf("cur: %d %d\n", cur.x, cur.y);
		if (cur.x == togo.x && cur.y == togo.y) return cur.step;

		for (int i = 0;i < 8;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };
			if (new.x >= 0 && new.x < l && new.y >= 0 && new.y < l && !visited[new.x][new.y]) {
				enqueue(new);
				visited[new.x][new.y] = 1;
			}
		}

	}
	return -1;
}

int main() {
	int T;
	scanf("%d", &T);

	for (;T > 0;T--) {
		int l;
		Pos cur;
		Pos togo;
		scanf("%d", &l);
		scanf("%d %d", &cur.x, &cur.y);
		scanf("%d %d", &togo.x, &togo.y);

		cur.step = 0, togo.step = 0;
		int res = bfs(l, cur, togo);
		printf("%d\n", res);
	}

	return 0;
}
```

</div>
</details>
<br>

## 📌 18. 빌딩 탈출 : 3차원 BFS, 최단거리
[백준 6593번](https://www.acmicpc.net/problem/6593)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX (30+1)

enum Map {
	START = 'S',
	END = 'E',
	WALL = '#',
};
typedef struct {
	int z;
	int x;
	int y;
	int step;
}Pos;

int L, R, C;

int dx[6] = { 0,0,1,-1,0,0 };
int dy[6] = { 1,-1,0,0,0,0 };
int dz[6] = { 0,0,0,0,1,-1 };
Pos queue[MAX * MAX * MAX];
int front = 0, rear = 0;
void enqueue(Pos cur) {
	queue[rear++] = cur;
}
Pos dequeue() {
	return queue[front++];
}

int bfs(char map[MAX][MAX][MAX], Pos start, Pos end) {
	bool visited[MAX][MAX][MAX] = { 0 };
	front = 0, rear = 0;	//큐 초기화

	enqueue(start);
	visited[start.z][start.x][start.y] = 1;

	while (front < rear) {
		Pos cur = dequeue();
		if (cur.x == end.x && cur.y == end.y && cur.z == end.z) {	//종료 조건
			return cur.step;
		}

		for (int i = 0;i < 6;i++) {
			Pos new = { cur.z + dz[i], cur.x + dx[i], cur.y + dy[i], cur.step + 1 };
			bool bound_check = new.z >= 0 && new.z < L && new.x >= 0 && new.x < R && new.y >= 0 && new.y < C;
			if (bound_check && map[new.z][new.x][new.y] != WALL && !visited[new.z][new.x][new.y]) {	//벽만 아니면 갈 수 있음
				enqueue(new);
				visited[new.z][new.x][new.y] = 1;
			}
		}
	}

	return -1;
}
int main() {

	while (1) {
		scanf("%d %d %d", &L, &R, &C);
		bool end_cond = !L && !R && !C;	//입력 종료 조건
		if (end_cond) break;

		Pos start, end;
		char map[MAX][MAX][MAX];
		for (int i = 0;i < L;i++) {
			for (int j = 0;j < R;j++) {
				scanf("%s", map[i][j]);
				for (int k = 0;k < C;k++) {
					if (map[i][j][k] == START) start = (Pos){ i, j, k, 0 };
					else if (map[i][j][k] == END) end = (Pos){ i,j,k,0 };
				}
			}
		}

		int res = bfs(map, start, end);
		if (res == -1) printf("Trapped!\n");
		else printf("Escaped in %d minute(s).\n", res);
	}

	return 0;
}
```

</div>
</details>
<br>

## 📌 19. 벽 부수고 이동 : BFS 벽 부쉈, 안 부쉈을 다른 visited로 관리, visited로 최단거리 저장
[백준 2206번](https://www.acmicpc.net/problem/2206)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX (1000+1)

enum Map {
	ROAD = '0',
	WALL = '1',
};
typedef struct {
	int x;
	int y;
	//int step;	//visited에 step 표시할 거라 필요 없음
	int br;
}Pos;

int N, M;
char map[MAX][MAX];
int visited[MAX][MAX][2];	//[i][j][0] : 벽 안부쉈, [i][j][1] : 벽 부쉈 | 별도 관리

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
Pos queue[MAX * MAX * 2];	//맵 크기의 2배 넣을 수 있음(벽 부쉈, 안부쉈)
int front = 0, rear = 0;
void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}

int bfs(Pos start, Pos end) {
	//memset(visited, 0, sizeof(visited));
	enqueue(start);
	visited[start.x][start.y][0] = 1;

	while (front < rear) {
		Pos cur = dequeue();
		//printf("cur %d %d\n", cur.x, cur.y);
		if (cur.x == end.x && cur.y == end.y) return visited[cur.x][cur.y][cur.br]; //cur.step + 1;
		
		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.br };
			bool beBound = new.x >= 0 && new.x < N && new.y >= 0 && new.y < M;
			if (beBound) {
				if (map[new.x][new.y] == ROAD && !visited[new.x][new.y][new.br]) {	//길
					visited[new.x][new.y][new.br] = visited[cur.x][cur.y][cur.br] + 1;
					enqueue(new);
				}

				if (map[new.x][new.y] == WALL && !new.br && !visited[new.x][new.y][new.br]) {	//벽
					new.br = 1;
					visited[new.x][new.y][1] = visited[cur.x][cur.y][0] + 1;	//벽 부수기 전에서 벽 부순후 방문배열로
					enqueue(new);
				}
			}
		}
	}

	return -1;
}
int main() {

	scanf("%d %d", &N, &M);

	Pos start = { 0,0,0 };
	Pos end = { N - 1, M - 1, 0 };
	for (int i = 0;i < N;i++) {
		scanf("%s", map[i]);
	}

	int res = bfs(start, end);
	printf("%d\n", res);

	return 0;
}
```

</div>
</details>
<br>


## 📌 20. 다른 섬까지 가는 최소 다리 길이 찾기 : DFS, BFS 둘다 사용
[백준 2146번](https://www.acmicpc.net/problem/2146)  

DFS는 섬 구별, BFS는 최소 다리 찾기에 사용  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX (100+1)
#define INF (~(1<<31))

enum Map {
	SEA = 0,
	LAND = 1,
};

typedef struct {
	int x;
	int y;
	int step;
}Pos;

int N;
int map[MAX][MAX];

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos queue[MAX * MAX];
int front = 0, rear = 0;
void initqueue() {
	front = 0, rear = 0;
	memset(queue, 0, sizeof(queue));
}
void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}
//디버깅용
void print(int map[MAX][MAX]) {
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//최소 다리 길이 찾기
int bfs(Pos start, int type) {
	bool visited[MAX][MAX] = { 0 };
	initqueue();	//bfs 여러번 호출하니까 초기화(front, rear, 큐)

	enqueue(start);
	visited[start.x][start.y] = 1;

	while (front < rear) {
		Pos cur = dequeue();

		//printf("cur %d %d | step %d | type %d\n", cur.x, cur.y, cur.step, type);
		if (map[cur.x][cur.y] != SEA && map[cur.x][cur.y] != type) {
			//printf("%d %d | step %d| %d\n", cur.x, cur.y, cur.step, map[cur.x][cur.y]);
			return cur.step;
		}
		for (int i = 0;i < 4;i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };
			if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N && !visited[new.x][new.y] && map[new.x][new.y] != type) {
				enqueue(new);
				visited[new.x][new.y] = 1;
			}
		}
	}

	return INF;
}

bool dfs_visited[MAX][MAX];
//섬 구별하기
void dfs(Pos cur, int cnt) {
	dfs_visited[cur.x][cur.y] = cnt;
	map[cur.x][cur.y] = cnt;

	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i], 0 };
		if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N && map[new.x][new.y] == LAND && !dfs_visited[new.x][new.y]) {
			dfs(new, cnt);
		}
	}
}

int main() {

	scanf("%d", &N);
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			scanf("%d", &map[i][j]);
		}
	}

	//섬 구별
	int cnt = 1;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			if (map[i][j] == LAND && !dfs_visited[i][j]) {
				dfs((Pos) { i, j, 0 }, cnt);
				cnt++;
			}
		}
	}

	//print(map);
	
	int min = INF;
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			bool beLand = (map[i][j] != SEA);
			bool beNearSea = 0;
			for (int k = 0;k < 4;k++) {
				Pos new = { i + dx[k], j + dy[k], 0 };
				bool beBound = (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N);
				beNearSea |= ((map[new.x][new.y] == SEA) && beBound);
				//printf("sea %d %d | %d\n", i, j, beNearSea);
			}
			if (beLand && beNearSea) {
				int res = bfs((Pos) { i, j, 0 }, map[i][j]);
				if (min > res) min = res;
			}
		}
	}

	printf("%d\n", min-1);
		
	return 0;
}
```

</div>
</details>
<br>

## 📌 21. 그래프, 연결 요소의 개수 찾기 : dfs
[백준 11724번](https://www.acmicpc.net/problem/11724)

서로 연결된 그룹의 개수를 찾는 문제  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAX (1000+1)

int map[MAX][MAX];	//map[i][0]에 연결된 정점의 개수 저장, map[i][1] ~ map[i][n] 정점 i에 연결된 정점 저장
bool visited[MAX];

void dfs(int cur) {

	visited[cur] = 1;

	//printf("cur : %d\n", cur);

	for (int i = 1;i <= map[cur][0];i++) {
		int new = map[cur][i];
		if(!visited[new])
			dfs(new);
	}

}
int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	                                                                           
	for (int i = 0;i < M;i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		map[u][++map[u][0]] = v;
		map[v][++map[v][0]] = u;
	}

	int cnt = 0;
	for (int i = 1;i <= N;i++) {
		if (!visited[i]) {
			if(map[i][0]!=0) dfs(i);
			cnt++;
		}
	}

	printf("%d\n", cnt);

	return 0;
}
```

</div>
</details>
<br>

## 📌 22. 그래프, 정점 1부터 연결된 두번 걸친곳 까지의 개수 찾기 : bfs, dfs 둘다 구현해봄
[백준 5567번](https://www.acmicpc.net/problem/5567)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">bfs 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define N_MAX (500+1)
//#define M_MAX (10000+1)

typedef struct {
	int x;
	int step;
}Pos;

int map[N_MAX][N_MAX];	//map[i][0] : 연결된 정점 개수 저장, map[i][j] : 연결된 정점
bool visited[N_MAX];

int cnt = 0;

Pos queue[N_MAX];
int front = 0, rear = 0;
void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}
void bfs(Pos start) {
	visited[start.x] = 1;
	enqueue(start);

	while (front < rear) {
		Pos cur = dequeue();

		if (cur.step >= 1) {
			//printf("cur %d\n", cur);
			cnt++;
			if (cur.step >= 2) continue;
		}

		for (int i = 1;i <= map[cur.x][0];i++) {
			Pos new = { map[cur.x][i], cur.step + 1 };
			if (!visited[new.x]) {
				enqueue(new);
				visited[new.x] = 1;
			}
		}
	}
	return;
}

int main() {
	int N;
	scanf("%d", &N);
	int M;
	scanf("%d", &M);
	
	for (int i = 0;i < M;i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		map[u][++map[u][0]] = v;
		map[v][++map[v][0]] = u;
	}

	bfs((Pos) { 1, 0 });
	printf("%d\n", cnt);

	return 0;
}
```

</div>
</details>
<br>

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">dfs 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define INF (~(1<<31))

#define N_MAX (500+1)
//#define M_MAX (10000+1)

typedef struct {
	int x;
	int step;
}Pos;

int map[N_MAX][N_MAX];	//map[i][0] : 연결된 정점 개수 저장, map[i][j] : 연결된 정점
int visited[N_MAX];		//각 정점까지 최소 거리 저장

void dfs(Pos cur) {

	//printf("cur %d | step %d\n", cur.x, cur.step);
	if (cur.step < visited[cur.x]) {	//최소 거리로 업데이트
		visited[cur.x] = cur.step;
	}

	if (cur.step > 2) return;	//2번 초과로 걸친 정점 필요 없음

	for (int i = 1;i <= map[cur.x][0];i++) {	//연결된 모든 정점 방문
		Pos new = { map[cur.x][i], cur.step + 1 };
		dfs(new);
	}

}

int main() {
	int N;
	scanf("%d", &N);
	int M;
	scanf("%d", &M);
	
	for (int i = 0;i < M;i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		map[u][++map[u][0]] = v;
		map[v][++map[v][0]] = u;
	}

	for (int i = 0;i < N_MAX;i++) visited[i] = INF;	//최소 거리 저장배열 초기화

	dfs((Pos) { 1, 0 });

	int cnt = 0;
	for (int i = 2;i <= N;i++) {
		//printf("%d ", visited[i]);
		if (visited[i] <= 2) cnt++;	//거리가 2 이하인 정점만 카운트
	}

	printf("%d\n", cnt);

	return 0;
}
```

</div>
</details>
<br>

## 📌 23. 특정 정점에서 갈 수 있는 모든 정점 표시하기 : dfs : 아직 정리 못함
[백준 11403번](https://www.acmicpc.net/problem/11403)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define N_MAX (100+1)

int N;
int map[N_MAX][N_MAX];

bool visited[N_MAX];
void dfs(int cur) {
	
	for (int i = 0;i < N;i++) {

		if (map[cur][i] && !visited[i]) {
			visited[i] = 1;
			dfs(i);
		}
	}
	
}

int main() {

	scanf("%d", &N);
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int i = 0;i < N;i++) {
		memset(visited, 0, sizeof(visited));

		dfs(i);

		for (int j = 0;j < N;j++) printf("%d ", visited[j]);
		printf("\n");
	}

	return 0;
}
```

</div>
</details>
<br>


플로이드-워셜 알고리즘을 변형하여 경로 유무만 판단  
k(중간노드) -> i -> j 순으로 반복  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">바꾼 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include <stdio.h>

#define MAX_N 100

int main() {
    int N;
    int graph[MAX_N][MAX_N];

    // 정점의 개수 입력
    scanf("%d", &N);

    // 인접 행렬 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // 플로이드-워셜 알고리즘	// k -> i -> j 순으로 반복
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (graph[i][k] && graph[k][j]) {
                    graph[i][j] = 1;
                }
            }
        }
    }

    // 결과 출력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

</div>
</details>
<br>

## 📌 24. 회장 뽑기 : 모든 사람을 방문하는데 최소인 사람 찾기
[백준 2660번](https://www.acmicpc.net/problem/2660)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<stdbool.h>

#define INF (~(1 << 31))
#define NMAX (50+1)

typedef struct {
    int val;
    int step;
}Pos;

int N;
int arr[NMAX][NMAX];

Pos queue[NMAX * NMAX];
int front = 0, rear = 0;
void enqueue(Pos new) {
    queue[rear++] = new;
}
Pos dequeue() {
    return queue[front++];
}

int bfs(Pos start) {
    bool visited[NMAX] = { 0 };
    front = 0, rear = 0;

    visited[start.val] = 1;
    enqueue(start);

    Pos cur = { 0,0 };
    while (front < rear) {
        cur = dequeue();

        //printf("cur %d %d\n", cur.val, cur.step);

        for (int i = 1;i <= N;i++) {
            if (arr[cur.val][i] && !visited[i]) {
                visited[i] = 1;
                enqueue((Pos) { i, cur.step + 1 });
            }
        }
    }

    return cur.step;	//마지막 탐색 단계를 return
}
int cmp(const void* a, const void* b) {
    return ((int*)a)[0] - ((int*)b)[0];
}
int main() {

    scanf("%d", &N);

    while(1){   //입력 제한 없을 때는 무한 루프로 하고 조건 break를 두자..
        int a1 = 0, a2 = 0;
        scanf("%d %d", &a1, &a2);
        if (a1 == -1 && a2 == -1) break;
        else {
            arr[a1][a2] = 1;
            arr[a2][a1] = 1;
        }
    }

    int pointArr[NMAX] = {0};   //점수를 저장할 배열
    int candidateArr[NMAX];     //후보 저장할 배열
    int candidate_index = 0;    //후보 저장 배열 index
    int min = INF;
    for (int i = 1;i <= N;i++) {
        int res = bfs((Pos) { i, 0 });
        pointArr[i] = res;

        if (res != -1 && res < min) min = res;
    }

    for (int i = 1;i <= N;i++) {
        if (pointArr[i] == min) {
            candidateArr[candidate_index++] = i;
        }
    }
    
    printf("%d %d\n", min, candidate_index);
    for (int i = 0;i < candidate_index;i++) {
        printf("%d ", candidateArr[i]);
    }
    return 0;
}
/*
다른 모든 회원과 친구 : 1점
다른 모든 회원이 친구 or 친구의 친구 : 2점
다른 모든 회원이 친구 or 친구의 친구 or 친구의 친구의 친구 : 3점
...

회장 : 점수가 가장 작은 사람
출력 :
회장의 점수, 후보의 수,
회장 후보를 오름차순으로
---

즉, 각 사람 입장에서 모든 사람을 포함하려면 몇다리까지 걸쳐야 하는가
다리 수가 최소인 사람이 회장 후보

*/
```
{% include code_close.html %}


## 📌 25. 숨바꼭질 3 : 이동시 소요 step이 달라서 목표에 도착시, 바로 종료하면 안됨, 큐 내부(또는 탐색하지 않은 곳)에 최소 step이 있을 수 있음
[백준 13549번](https://www.acmicpc.net/problem/13549)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

#define MAX 100000
#define INF (~(1<<31))

typedef struct {
    int x;
    int step;
}Pos;

int min_step = INF;

Pos queue[MAX];
int front = 0, rear = 0;
void enqueue(Pos new) {
    queue[rear++] = new;
}
Pos dequeue() {
    return queue[front++];
}
void bfs(int start, int end) {
    int visited[MAX + 1] = { INF };

    for (int i = 0; i <= MAX; i++) visited[i] = INF;

    visited[start] = 0;
    enqueue((Pos) { start, 0 });

    while (front < rear) {
        Pos cur = dequeue();

        //printf("cur %d %d\n", cur.x, cur.step);
        if (cur.step >= min_step) continue;
        if (cur.x == end && cur.step < min_step) {
            min_step = cur.step;
            continue;
        }

        for (int i = 0; i < 3; i++) {
            Pos new = { 0,0 };
            if (i == 0) {   //switch문으로 변환시 실행 시간 낮출 수 있음
                //new = (Pos){ cur.x * 2, cur.step };   //작은 step을 먼저 탐색해서 완성되지 않은 코드일 때, 맞을 확률이 올라감
                new = (Pos){ cur.x - 1, cur.step + 1 };
            }
            else if (i == 1) {
                new = (Pos){ cur.x + 1, cur.step + 1 };
            }
            else if (i == 2) {
                //new = (Pos){ cur.x - 1, cur.step + 1 };
                new = (Pos){ cur.x * 2, cur.step };
            }

            if (new.x >= 0 && new.x <= MAX && new.step < visited[new.x]) {
                enqueue(new);
                visited[new.x] = new.step;
            }
        }
    }
    return;
}
int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    bfs(N, K);

    printf("%d\n", min_step);

    return 0;
}
```
{% include code_close.html %}

## 📌 26. 팀 프로젝트 : 사이클이 아닌 것들 찾기 : DFS (정점 100,000 but 간선 1)
[백준 9466번](https://www.acmicpc.net/problem/9466)

최대 노드 수가 100,000이지만, 간선이 1개 이므로 dfs가 더 적합하다고 판단  
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>
#include <string.h>

#define MAX_N 100000

int n;
int students[MAX_N + 1];  // 학생 선택 정보
int visited[MAX_N + 1];   // 방문 여부 (0: 미방문, 1: 방문 중, 2: 방문 완료)
int finished[MAX_N + 1];  // 사이클 판별 여부 확인
int cnt;                  // 팀을 이루지 못한 학생 수

void dfs(int node) {
    visited[node] = 1;
    int next = students[node];

    if (!visited[next]) {
        dfs(next);
    }
    //visited[next] == 1 인 경우
    else if (!finished[next]) { // 사이클이 발생한 경우, 여부 확인이 되지 않은 노드라면
        //next부터 node직전까지 다시 회전
        for (int i = next; i != node; i = students[i]) {
            cnt--;
        }
        cnt--;  // 사이클의 시작 노드도 포함
    }

    finished[node] = 1; // 탐색 완료
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++) {
            scanf("%d", &students[i]);
            visited[i] = 0;
            finished[i] = 0;
        }

        cnt = n;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        printf("%d\n", cnt);
    }

    return 0;
}


/*
팀원수 제한 없
팀원 한명만 선택
자기 자신 선택도 가능
---
즉, 루프를 이룰 때만 팀 또는 자기 자신만 선택했을 때 -> 팀
---
출력 : 프로젝트 팀에 속하지 못한 학생들의 수

팀인 사람을 표시하고, 마지막 출력 때 표시 안된 사람 수 세기

#1)
1 2 3 4 5 6 7
3 1 3 7 3 4 6
-> 팀 : 3, 4 6 7 | 혼자 : 1 2 5

#2)
1 2 3 4 5
5 5 4 5 3
x x o o o

---
#3)
1
5
2 5 4 5 2

ans: 3

1 2 3 4 5
2 5 4 5 2
x o x x o

#4)
13
2 4 5 2 4 1 8 9 10 11 9 10 10

ans : 8

*/


```
{% include code_close.html %}

## 📌 27. 말이 되고픈 원숭이 : BFS (visited는 방문했던 곳을 다시 방문하지 않기 위한 것)
[백준 1600번](https://www.acmicpc.net/problem/1600)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

#define MAX 200
#define KMAX 31	// K: 0~30 -> 31개
#define INF (~(1<<31))
typedef struct {
	int x;
	int y;
	int k;	//남은 K
	int step;
}Pos;

enum Map {
	CAN = 0,
	CANT = 1,
};

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int dx2[8] = { -1,-2,-2,-1,1,2,2,1 };
int dy2[8] = { -2,-1,1,2,2,1,-1,-2 };

Pos queue[MAX * MAX * KMAX];	//MAX * MAX * 31
int front = 0, rear = 0;
void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}
int bfs(int map[MAX][MAX], int W, int H, Pos start, Pos end) {
	int visited[MAX][MAX][KMAX] = { 0 };

	visited[start.x][start.y][start.k] = 1;
	enqueue(start);

	while (front < rear) {
		Pos cur = dequeue();

		//printf("cur %d %d | %d %d\n", cur.x, cur.y, cur.k, cur.step);
		if (cur.x == end.x && cur.y == end.y) {
			return cur.step;
		}

		//1. dx,dy
		for (int i = 0; i < 4; i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.k, cur.step + 1 };
			if (new.x >= 0 && new.x < H && new.y >= 0 && new.y < W && map[new.x][new.y] == CAN && !visited[new.x][new.y][new.k]) {
				visited[new.x][new.y][new.k] = 1;
				enqueue(new);
			}
		}
		//2. dx2, dy2
		if (cur.k > 0) {
			for (int i = 0; i < 8; i++) {
				Pos new = { cur.x + dx2[i], cur.y + dy2[i], cur.k - 1, cur.step + 1 };
				if (new.x >= 0 && new.x < H && new.y >= 0 && new.y < W && map[new.x][new.y] == CAN && !visited[new.x][new.y][new.k]) {
					visited[new.x][new.y][new.k] = 1;
					enqueue(new);
				}
			}
		}
	}

	return -1;
}
int main() {
	int K;
	scanf("%d", &K);
	int W, H;
	scanf("%d %d", &W, &H);

	int map[MAX][MAX];
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	Pos start = { 0,0, K, 0 };
	Pos end = { H - 1, W - 1, 0, 0 };

	int res = bfs(map, W, H, start, end);
	printf("%d\n", res);

	return 0;
}
```
{% include code_close.html %}

## 📌 28. 열쇠 : 어려움 : 처음 푼 코드 비효율, 아직 개선 못함 TODO
[백준 9328번](https://www.acmicpc.net/problem/9328)
{% include code_open.html title="처음 내 코드 보기" %}
```c
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAP_MAX (100 * 10) //??????????? 10 왜 곱해야될까
#define DOOR_MAX (100 * 100)

enum MAP {
    EMPTY = '.',
    WALL = '*',
    GOAL = '$',
};

typedef struct {
    int x;
    int y;
}Pos;

int h, w;
char map[MAP_MAX][MAP_MAX];

bool key[26] = { 0 };   //가지고 있는 키

Pos entrance_stack[DOOR_MAX];   //가능한 입구 저장
int entrance_top = 0;

bool visited_goal[MAP_MAX][MAP_MAX];

int beDoor(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return 1;
    }
    else return 0;
}
int beKey(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return 1;
    }
    else return 0;
}
int beKeyforDoor(char door) {
    return key[door - 'A'];
}

Pos queue[MAP_MAX * MAP_MAX];
int front = 0, rear = 0;
void enqueue(Pos new) {
    queue[rear++] = new;
}
Pos dequeue() {
    return queue[front++];
}

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

bool flag_found_key = 0;

void bfs(Pos start) {
    //init
    front = 0, rear = 0;
    char visited[MAP_MAX][MAP_MAX] = { 0 };

    visited[start.x][start.y] = 1;
    enqueue(start);

    while (front < rear) {
        Pos cur = dequeue();

        //문서 발견
        if (map[cur.x][cur.y] == GOAL) {
            visited_goal[cur.x][cur.y] = 1;
        }
        //새로운 키 발견   //발견하지 않은
        else if (beKey(map[cur.x][cur.y]) && !key[map[cur.x][cur.y] - 'a']) {
            key[map[cur.x][cur.y] - 'a'] = 1;

            //처음부터 다시 탐색 : visited 초기화 및 큐 초기화
            memset(visited, 0, sizeof(visited));
            front = 0, rear = 0;

            flag_found_key = 1;
        }
        //문 발견
        else if (beDoor(map[cur.x][cur.y])) {
            //키 없으면 다음 턴
            if (!beKeyforDoor(map[cur.x][cur.y])) continue;
        }

        //printf("%d %d\n", cur.x, cur.y);

        for (int i = 0;i < 4;i++) {
            Pos new = { cur.x + dx[i], cur.y + dy[i] };

            if (new.x >= 0 && new.x < h && new.y >= 0 && new.y < w && map[new.x][new.y] != WALL) {
                if (!visited[new.x][new.y]) {
                    visited[new.x][new.y] = 1;
                    enqueue(new);
                }
            }
        }
    }

    return;
}
int main() {
    int T = 0;
    scanf("%d", &T);

    while (T--) {
        //init
        entrance_top = 0;
        memset(key, 0, sizeof(key));
        memset(visited_goal, 0, sizeof(visited_goal));
        flag_found_key = 0;
        //

        scanf("%d %d", &h, &w);

        for (int i = 0;i < h;i++) {
            scanf("%s", map[i]);

            for (int j = 0;j < w;j++) {
                bool beSide = (i == 0 || i == h - 1 || j == 0 || j == w - 1);
                if (beSide && map[i][j] != WALL) {
                    entrance_stack[entrance_top++] = (Pos){ i,j };
                }
            }
        }

        //key
        char key_input[26];
        scanf("%s", key_input);
        if (key_input[0] != '0') {
            for (int i = 0;key_input[i] != '\0';i++) {
                //if(beKey(key_input[i]))
                key[key_input[i] - 'a'] = 1;
            }
        }

        for (int i = 0;i < entrance_top;i++) {

            Pos start = entrance_stack[i];
            //printf("* start : %d %d\n", start.x, start.y);

            //입구가 빈곳
            if (map[start.x][start.y] == EMPTY) {
                bfs(start);
            }
            //입구가 문
            else if (beDoor(map[start.x][start.y])) {
                if (beKeyforDoor(map[start.x][start.y])) {
                    bfs(start);
                }
            }
            //입구가 달러
            else if (map[start.x][start.y] == GOAL) {
                visited_goal[start.x][start.y] = 1;
                bfs(start);
            }
            //입구가 키
            else if (beKey(map[start.x][start.y])) {
                //알고 있는 키
                if (!key[map[start.x][start.y] - 'a']) {
                    flag_found_key = 1;

                    key[map[start.x][start.y] - 'a'] = 1;
                }
                bfs(start);
            }


            if (flag_found_key) {
                //printf("key find!\n");
                i = -1;
                flag_found_key = 0;
            }
        }


        int res = 0;
        for (int i = 0;i < h;i++) {
            for (int j = 0;j < w;j++) {
                if (visited_goal[i][j]) res++;
                //if (visited_goal[i][j] && res) printf("%d %d\n", i, j);
            }
        }
        printf("%d\n", res);
    }

    return 0;
}

/*
키를 hash로


#1)
1
3 4
****
A.$*
****
a

ans : 1

#2)
1
10 10
JEMOTOFJOY
VMISTuVMsV
THVIQLMNXZ
RIEVJUQTUT
RN$UGDEXWE
VESTQEMFgU
RCSiYMTTLC
LLdXTNJGXG
YRKBKSqIoD
RRDFPXMNHJ
l

ans : 1

#3)
1
4 7
*A*B*C*
*C*$*a*
*$*c*$*
****a**
c

ans : 2

#4)
1
28 5
*A*a*
*b*B*
*C*c*
*d*D*
*E*e*
*f*F*
*G*g*
*h*H*
*I*i*
*j*J*
*K*k*
*l*L*
*M*m*
*n*N*
*O*o*
*p*P*
*Q*q*
*r*R*
*S*s*
*t*T*
*U*u*
*v*V*
*W*w*
*x*X*
*Y*y*
*z*Z*
*$*$*
*****
0

ans : 2


탐색하면서 문큐에 문다 때려넣고
열쇠 찾으면 문큐 다 꺼내서 이동
*/
```
{% include code_close.html %}


## 📌 29. A->B
[백준 16953번](https://www.acmicpc.net/problem/16953)
{% include code_open.html title="bfs 코드 보기" %}
```c
#include<stdio.h>
#include<stdbool.h>

#define MAX 10000

typedef struct {
	long long val;	//new.val = cur.val * 10 + 1;에서 overflow발생가능성 있기에 long long
	int step;
}Node;

Node queue[MAX];
int front = 0, rear = 0;

void enqueue(Node new) {
	queue[rear++] = new;
}
Node dequeue() {
	return queue[front++];
}
int bfs(int A, int B) {
	bool visited[10000000 + 1] = { 0 };
	visited[A] = 1;
	enqueue((Node) { A, 0 });

	while (front < rear) {
		Node cur = dequeue();
		if (cur.val == B) {
			return cur.step+1;
		}
		else if (cur.val > B) {
			continue;
		}

		//printf("%d\n", cur.val);
		for (int i = 0;i < 2;i++) {
			Node new = { 2 * cur.val, cur.step + 1 };
			if (i == 1) new.val = cur.val * 10 + 1;

			if (new.val <= B) {
				visited[new.val] = 1;
				enqueue(new);
			}
		}

	}

	return -1;
}


int main() {
	int A, B;
	scanf("%d %d", &A, &B);

	int res = bfs(A, B);
	printf("%d\n", res);

	return 0;
}
```
{% include code_close.html %}

{% include code_open.html title="bfs 필요 없는 간단한 코드 보기" %}
```c
#include <stdio.h>

int main() {
    long long A, B;
    scanf("%lld %lld", &A, &B);
    
    int count = 0;
    
    while (B > A) {
        // B가 짝수일 경우 2로 나누기
        if (B % 2 == 0) {
            B /= 2;
        }
        // B의 마지막 자리가 1일 경우 1을 제거하기
        else if (B % 10 == 1) {
            B /= 10;
        }
        // 그 외의 경우는 불가능하므로 종료
        else {
            break;
        }
        count++;
    }
    
    // B가 A로 변환되었으면 count를 출력, 아니라면 -1 출력
    if (B == A) {
        printf("%d\n", count + 1);  // 연산 횟수는 1을 더한 값 출력
    } else {
        printf("-1\n");
    }
    
    return 0;
}

```
{% include code_close.html %}

## 📌 30. 연구소 : 백트래킹으로 케이스를 만들고, dfs탐색
[백준 14502번](https://www.acmicpc.net/problem/14502)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<string.h>

#define MAX_N 8
#define MAX_M 8
#define MAX_VIRUS 10

enum Map {
	EMPTY = 0,
	WALL = 1,
	VIRUS = 2,
};

typedef struct {
	int x;
	int y;
}Pos;

int N, M;
int map[MAX_N][MAX_M];
Pos virus_stack[MAX_VIRUS];
int virus_stack_top = 0;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int temp_map[MAX_N][MAX_M];

int max = 0;
void debug() {
	printf("---------\n");
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			printf("%d ", temp_map[i][j]);
		}
		printf("\n");
	}
}
void dfs(Pos cur) {
	//visited[cur.x][cur.y] = 1;
	temp_map[cur.x][cur.y] = VIRUS;

	for (int i = 0;i < 4;i++) {
		Pos new = { cur.x + dx[i], cur.y + dy[i] };
		if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && temp_map[new.x][new.y] == EMPTY) {
			dfs(new);
		}
	}
}
void makeCase(int step) {
	if (step == 3) {

		memcpy(temp_map, map, sizeof(temp_map));

		for (int i = 0;i < virus_stack_top;i++) {
			dfs(virus_stack[i]);
		}

		int cnt = 0;
		for (int i = 0;i < N;i++) {
			for (int j = 0;j < M;j++) {
				if (temp_map[i][j] == EMPTY) {
					cnt++;
				}
			}
		}
		if (cnt > max) {
			max = cnt;
		}

		//debug();

		return;
	}

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			if (map[i][j] == EMPTY) {
				map[i][j] = WALL;
				makeCase(step + 1);
				map[i][j] = EMPTY;
			}
		}
	}
}
int main() {

	scanf("%d %d", &N, &M);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == VIRUS) {
				virus_stack[virus_stack_top++] = (Pos){ i,j };
			}
		}
	}

	makeCase(0);
	
	printf("%d\n", max);

	return 0;
}
/*
안전 영역의 최대 크기
2<= 바이러스 수 <= 10
벽 3개 세울 수 있음


*/
```
{% include code_close.html %}

## 📌 31. 조각 움직이기
[백준 1035번](https://www.acmicpc.net/problem/1035)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define INF (~(1<<31))
#define MAX_MAP 5
#define MAX_PIECE 5

enum Map {
    PIECE = '*',
    EMPTY = '.',
};

typedef struct {
    int x;
    int y;
    int step;
}Pos;

char map[MAX_MAP][MAX_MAP];
Pos piece[MAX_PIECE];
int piece_top = 0;

Pos selected[MAX_PIECE];

int min = INF;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos queue[5 * 5];
int front = 0, rear = 0;
void enqueue(Pos new) {
    queue[rear++] = new;
}
Pos dequeue() {
    return queue[front++];
}

int debug() {
    if (selected[0].x == 1 && selected[0].y == 2) {
        if (selected[1].x == 1 && selected[1].y == 3) {
            if (selected[2].x == 2 && selected[2].y == 3) {
                return 1;
            }
        }
    }
    return 0;
}
// start : [0]
int valid = 0;
int dfs_visited[5][5];
int dfs_cnt = 0;
void valid_dfs(Pos cur, char temp_map[5][5]) {
    dfs_cnt++;
    if(dfs_cnt == piece_top) {  // TODO already modified
        valid = 1;
        return;
    }

    dfs_visited[cur.x][cur.y] = 1;
    for (int i = 0;i < 4;i++) {
        Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };
        if (new.x >= 0 && new.x < 5 && new.y >= 0 && new.y < 5 && temp_map[new.x][new.y] == PIECE && !dfs_visited[new.x][new.y]) {
            valid_dfs(new, temp_map);
        }
    }
}
int beValid() {
    valid = 0;
    memset(dfs_visited, 0, sizeof(dfs_visited));
    dfs_cnt = 0;
    char temp_map[5][5] = { 0 };

    for (int i = 0;i < piece_top;i++) {
        temp_map[selected[i].x][selected[i].y] = PIECE;
    }

    valid_dfs(selected[0], temp_map);
    
    return valid;
}

int bfs(Pos start, int visited[5]) {
    int bfs_visited[5][5] = { 0 };
    front = 0, rear = 0;

    bfs_visited[start.x][start.y] = 1;
    enqueue(start);

    while (front < rear) {
        Pos cur = dequeue();

        for (int i = 0;i < piece_top;i++) {
            //if (cur.x == selected[i].x && cur.y == selected[i].y) {
            //if(map[cur.x][cur.y] == PIECE && !visited[i]) {
            if (cur.x == piece[i].x && cur.y == piece[i].y && !visited[i]) {
                visited[i] = 1;
                return cur.step;
            }
        }

        for (int i = 0;i < 4;i++) {
            Pos new = { cur.x + dx[i], cur.y + dy[i], cur.step + 1 };

            if (new.x >= 0 && new.x < 5 && new.y >= 0 && new.y < 5 && !bfs_visited[new.x][new.y]) {
                bfs_visited[new.x][new.y] = 1;
                enqueue(new);
            }
        }
    }

    return 0;
}
int calculate() {
    // 선택한 조각들로부터 처음 위치의 조각까지 거리합 계산
    int sum = 0;

    // 최소의 합은 최소
    int visited[5] = { 0 };
    for (int i = 0;i < piece_top;i++) {
        int distance = bfs(selected[i], visited);

        sum += distance;
    }
    return sum;
}
void makeCase(int step) {
    if (step == piece_top) {
        if (beValid()) {    // 하나의 연결인지
            int res = calculate(); // 각 조각까지 거리합 계산
            //printf("res : %d\n", res);
            if (res < min) {
                min = res;
            }
        }
        return;
    }

    // TODO can upgrade
    for (int i = 0; i < MAX_MAP; i++) {
        for (int j = 0; j < MAX_MAP; j++) {
            // 중복 확인
            bool isDuplicate = false;
            for (int k = 0; k < step; k++) {
                if (selected[k].x == i && selected[k].y == j) {
                    isDuplicate = true;
                    break;
                }
            }
            if (isDuplicate) continue;
            //
            selected[step] = (Pos){ i,j, 0 };
            makeCase(step + 1);
        }
    }
}
int main() {
    for (int i = 0; i < MAX_MAP; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < MAX_MAP; j++) {
            if (map[i][j] == PIECE) {
                piece[piece_top++] = (Pos){ i,j,0 };
            }
        }
    }

    makeCase(0);

    printf("%d\n", min);

    return 0;
}
/*
#1)
..*..
.....
.....
.....
*...*
ans : 6

#2)
..*..
.....
*...*
.....
..*..
ans : 5

    
*/
```
{% include code_close.html %}

기존 calculate 함수의 방식을 bfs -> 거리 합(abs() 이용)으로 바꿈 : 실행 시간 개선
{% include code_open.html title="수정 함수 코드 보기" %}
```c
int calculate() {
    // 선택한 조각들로부터 처음 위치의 조각까지 거리합 계산
    int sum = 0;

    // 최소의 합은 최소
    int visited[5] = { 0 };
    for (int i = 0;i < piece_top;i++) {
        //int distance = bfs(selected[i], visited); // 기존 코드
        
        int min = 1000000;  // 충분히 큰 값
        int prev_idx = -1;
        for (int j = 0;j < piece_top;j++) {
            if (visited[j]) continue;
            int dist = abs(selected[i].x - piece[j].x) + abs(selected[i].y - piece[j].y);
            if (dist < min) {
                min = dist;
                prev_idx = j;
                //visited[prev_idx] = 0;
                //visited[j] = 1;
            }
        }
        if (prev_idx != -1) {
            visited[prev_idx] = 1;
            sum += min;
        }

        //sum+= distance; // 기존 코드
    }
    return sum;
}
```
{% include code_close.html %}

## 