---
title: 심화문제
description: >-           #한 문장으로 나옴
  백준 문제풀이
date: 2025-01-22 23:14:43 +0900
lastmod : 2025-01-22 23:14:43 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - 백준 c언어 정리
tags: 
    - Untag1

#excerpt: "이 글의 요약"   # 요약
#image: "url_to_image.jpg"   # 대표 이미지 (옵션)
#permalink: /category1/first-post/
pin: false              # true | false
published: true        # true | false
---


## 📌 1. BFS 고려할 게 많음

백준 13460번  
[https://www.acmicpc.net/problem/13460]

<br>

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>

#define MAP_MAX 11

enum Map_Information {
    WALL = '#',
    BLUE = 'B',
    RED = 'R',
    HOLE = 'O',
};
typedef struct {
    int x;
    int y;
}Ball;
typedef struct {
    Ball red;
    Ball blue;
    int step;
}Pos;

int N, M;
char map[MAP_MAX][MAP_MAX];
//처음 생각 red와 blue의 visited를 나누어서
//bool red_visited[MAP_MAX][MAP_MAX];
//bool blue_visited[MAP_MAX][MAP_MAX];
bool visited[MAP_MAX][MAP_MAX][MAP_MAX][MAP_MAX];   //redx redy bluex bluey
Pos start;
Ball blue, red;

Pos queue[MAP_MAX * MAP_MAX];
int front, rear;
void enqueue(Pos new) {
    queue[rear++] = new;
}
Pos dequeue() {
    return queue[front++];
}
//우 좌 하 상
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

bool ret_flag = 0;
bool blueInhole = 0;
Pos gogo(Pos cur, int dx, int dy) {
    Pos new = cur;
    int red_go = 0, blue_go = 0;

    while (map[new.red.x][new.red.y] != WALL) {
        if (map[new.red.x][new.red.y] == HOLE) {
            //printf("hole : red %d %d\n", new.red.x, new.red.y);
            ret_flag = 1;
        }
        new.red.x += dx;
        new.red.y += dy;
        red_go++;
    }
    new.red.x -= dx;
    new.red.y -= dy;

    while (map[new.blue.x][new.blue.y] != WALL) {
        if (map[new.blue.x][new.blue.y] == HOLE) blueInhole = 1;
        new.blue.x += dx;
        new.blue.y += dy;
        blue_go++;
    }
    new.blue.x -= dx;
    new.blue.y -= dy;

    //printf("r : %d | b : %d\n", red_go, blue_go);
    if (new.red.x == new.blue.x && new.red.y == new.blue.y) {
        if (red_go > blue_go) {
            new.red.x -= dx;
            new.red.y -= dy;
        }
        else if (blue_go > red_go) {
            new.blue.x -= dx;
            new.blue.y -= dy;
        }
    }



    return new;
}
int bfs() {
    enqueue(start);
    //red_visited[start.red.x][start.red.y] = 1;
    //blue_visited[start.blue.x][start.blue.y] = 1;
    visited[start.red.x][start.red.y][start.blue.x][start.blue.y] = 1;

    while (front < rear) {
        Pos cur = dequeue();

        if (cur.step >= 10) continue;
        //printf("%d %d\n", cur.red.x, cur.red.y); //디버깅용

        for (int i = 0; i < 4; i++) {
            blueInhole = 0;
            Ball new_red = { cur.red.x + dx[i], cur.red.y + dy[i] };
            Ball new_blue = { cur.blue.x + dx[i], cur.blue.y + dy[i] };
            Pos new = { new_red, new_blue, cur.step + 1 };

            //if (new.step > 10) continue;

            bool red_cond = new_red.x >= 0 && new_red.x < N && new_red.y >= 0 && new_red.y < M;
            bool blue_cond = new_blue.x >= 0 && new_blue.x < N && new_blue.y >= 0 && new_blue.y < M;
            bool not_wall = map[new.red.x][new.red.y] != WALL || map[new.blue.x][new.blue.y] != WALL;
            //bool rb_visited = red_visited[new.red.x][new.red.y] && blue_visited[new.blue.x][new.blue.y];

            if (red_cond && blue_cond && not_wall) { //&& !rb_visited) {
                //한번 동작에 끝까지

                new = gogo((Pos) { cur.red, cur.blue, cur.step + 1 }, dx[i], dy[i]);
                //bool rb_visited = red_visited[new.red.x][new.red.y] && blue_visited[new.blue.x][new.blue.y];
                bool rb_visited = visited[new.red.x][new.red.y][new.blue.x][new.blue.y];
                //printf("new red : %d %d | new blue : %d %d | new.step : %d\n\n", new.red.x, new.red.y, new.blue.x, new.blue.y, new.step);
                /*
                if (rb_visited || blueInhole) {
                    if (ret_flag) printf("? : %d %d\n", rb_visited, blueInhole);
                    ret_flag = 0;
                    continue;
                }
                */
                //if (rb_visited) continue;
                
                if (blueInhole) {
                    ret_flag = 0;
                    continue;
                }
                if (ret_flag) {
                    return new.step;
                }
                if (!rb_visited) {
                    enqueue(new);
                    //red_visited[new.red.x][new.red.y] = 1;
                    //blue_visited[new.blue.x][new.blue.y] = 1;
                    visited[new.red.x][new.red.y][new.blue.x][new.blue.y] = 1;

                    //printf("enq : dx : %d | dy : %d | ", dx[i], dy[i]);
                    //printf("new red : %d %d | new blue : %d %d | new.step : %d\n\n", new.red.x, new.red.y, new.blue.x, new.blue.y, new.step);
                }
            }
        }
    }
    return -1;
}

int main() {

    scanf("%d %d", &N, &M);


    for (int i = 0; i < N; i++) {
        scanf("%s", &map[i]);
        for (int j = 0; j < M; j++) {
            switch (map[i][j]) {
            case BLUE:
                blue = (Ball){ i,j };
                break;
            case RED:
                red = (Ball){ i,j };
                break;
            case HOLE:
                //hole = (Pos){ i,j,0 };
                break;
            default:
                break;
            }
        }
    }
    start = (Pos){ red, blue, 0 };

    int res = bfs();
    if (res > 10) printf("-1\n");
    else {
        printf("%d\n", res);
    }

    return 0;
}
```

</div>
</details>
<br>


## 📌 2. 재귀 : dfs인줄 알았음 유사함
백준 12100번  
[https://www.acmicpc.net/problem/12100]

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAP_MAX 21
#define NUM_MAX 5

//#define ARR_MAX (MAP_MAX * MAP_MAX*MAP_MAX)
enum {
    EMPTY = 0,
};
enum Direction {
    EAST = 0,
    WEST = 1,
    SOUTH = 2,
    NORTH = 3,
};
typedef struct {
    int map[MAP_MAX][MAP_MAX];
    int dx;
    int dy;
}Visited;

int N;
int map[MAP_MAX][MAP_MAX];

//e, w, s, n
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

//int max_arr[ARR_MAX];
//int iindex = 0;

int tot_max_val = 0;

void print(int arr[MAP_MAX][MAP_MAX]) {
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
int find_max_in_arr(int arr[MAP_MAX][MAP_MAX]) {
    int max = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j] > max) max = arr[i][j];
        }
    }
    return max;
}
//시계방향 : dir값만큼 회전
void rotate_map(int new_map[MAP_MAX][MAP_MAX], int dir) {

    for (int k = 0; k < dir; k++) {
        int temp[MAP_MAX][MAP_MAX];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                temp[j][N - 1 - i] = new_map[i][j];
            }
        }
        memcpy(new_map, temp, sizeof(int) * MAP_MAX * MAP_MAX);
    }
    //print(new_map);
}
//EAST방향으로 블럭 밀고 합치기
void move_block(int new_map[MAP_MAX][MAP_MAX]) {

    for (int i = 0; i < N; i++) {
        //1.밀기
        for (int j = N - 1; j >= 0; j--) {
            if (new_map[i][j] == EMPTY) {
                for (int k = j; k >= 0; k--) {
                    if (new_map[i][k] != EMPTY) {
                        new_map[i][j] = new_map[i][k];
                        new_map[i][k] = EMPTY;
                        break;
                    }
                }
            }
        }

        //print(new_map);
        //2.합치기
        for (int j = N - 1; j >= 1; j--) {
            if (new_map[i][j] == new_map[i][j - 1]) {
                new_map[i][j] *= 2;
                new_map[i][j - 1] = EMPTY;
                //change_flag = 1;
            }
        }

        //print(new_map);
        //3.밀기
        for (int j = N - 1; j >= 0; j--) {
            if (new_map[i][j] == EMPTY) {
                for (int k = j; k >= 0; k--) {
                    if (new_map[i][k] != EMPTY) {
                        new_map[i][j] = new_map[i][k];
                        new_map[i][k] = EMPTY;
                        break;
                    }
                }
            }
        }
        //print(new_map);
    }
}
//모든 방향을 EAST 방향으로 바꿔 처리
void proc_dir(int new_map[MAP_MAX][MAP_MAX], int dir) {
    switch (dir) {
    case EAST:
        move_block(new_map);
        break;
    case WEST:
        rotate_map(new_map, 2);
        move_block(new_map);
        rotate_map(new_map, 2);
        break;
    case SOUTH:
        rotate_map(new_map, 3);
        move_block(new_map);
        rotate_map(new_map, 1);
        break;
    case NORTH:
        rotate_map(new_map, 1);
        move_block(new_map);
        rotate_map(new_map, 3);
        break;
    }
}
void solve(int cur_map[][MAP_MAX], int num) {

    if (num > 5) {
        return;
    }
    else {
        //max_arr[iindex++] = find_max_in_arr(cur_map);
        int max = find_max_in_arr(cur_map);
        if (max > tot_max_val) tot_max_val = max;
    }

    for (int i = 0; i < 4; i++) {
        int new_map[MAP_MAX][MAP_MAX];
        //memcpy(new_map, make_new_map(new_map, cur_map, i), sizeof(new_map));

        memcpy(new_map, cur_map, sizeof(new_map));
        proc_dir(new_map, i);

        //print(new_map);
        //맵이랑 dx, dy : visit확인

        solve(new_map, num + 1);

        //else return;
    }
}


int main() {

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    solve(map, 0);

    /*
    int max = 0;
    for (int i = 0; i < ARR_MAX; i++) {
        if (max_arr[i] > max) max = max_arr[i];
    }
    if (max == 0) {
        printf("%d\n", find_max_in_arr(map));

    }
    else printf("%d\n", max);
    */

    printf("%d\n", tot_max_val);

    return 0;
}
```

</div>
</details>

<br>

## 📌 3. 뱀
백준 3190번  
[https://www.acmicpc.net/problem/3190]

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">내 코드 보기(재귀 : 76ms)</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define N_MAX 101
#define K_MAX 101
#define L_MAX 101

enum Map {
    APPLE = 1,
    EMPTY = 0,
};
enum Dir_info {
    LEFT = 'L',
    RIGHT = 'D',
    EAST = 0,
    SOUTH = 1,
    WEST = 2,
    NORTH = 3,
};
typedef struct {
    int x;
    int y;
}Pos;
typedef struct {
    Pos head;

    Pos body[N_MAX * N_MAX];
    int len;

    int dir;   //initial 0
}Snake;

int N, K;
int L;
int dir_info[L_MAX][2];
int dir_index = 0;

//e s w n
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int ans = -1;
bool ret_flag = 0;

//디버깅용
void print(int map[N_MAX][N_MAX], Snake snake) {
    printf("\n");
    int c = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int m = 0; m < snake.len; m++) {
                if (i == snake.body[m].x && j == snake.body[m].y) {
                    printf("b ");
                    c = 1;
                    break;
                }
                else c = 0;
            }
            if (c) continue;
            else printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void add_rear_body(Snake* snake, Pos new) {
    snake->body[snake->len++] = new;
}
void sub_rear_body(Snake* snake) {
    snake->len--;
}
void add_front_body(Snake* snake, Pos new) {
    for (int i = snake->len - 1; i >= 0; i--) {
        snake->body[i + 1] = snake->body[i];
    }
    snake->body[0] = new;
    snake->len++;
}

int snake_rotate(Snake cur, char dir) {
    if (dir == LEFT) {
        if (cur.dir == 0) cur.dir = 3;
        else cur.dir -= 1;
    }
    else if (dir == RIGHT) {

        if (cur.dir == 3) cur.dir = 0;
        else cur.dir += 1;
    }
    return cur.dir;
}
bool check_head_in_body(Snake cur) {
    for (int i = 1; i < cur.len; i++) {
        if (cur.head.x == cur.body[i].x && cur.head.y == cur.body[i].y) {
            return 1;
        }
    }
    return 0;
}

Snake move_snake(Snake cur, int cur_map[N_MAX][N_MAX]) {

    //뱀 이동
    cur.head.x += dx[cur.dir];
    cur.head.y += dy[cur.dir];

    //종료조건 만들기 : 1 머리가 벽에, 2.머리가 몸에
    bool head_in_wall = cur.head.x < 0 || cur.head.x >= N || cur.head.y < 0 || cur.head.y >= N;
    bool head_in_body = check_head_in_body(cur);
    ret_flag = head_in_wall || head_in_body;

    //사과없으면 꼬리움직임
    if (cur_map[cur.head.x][cur.head.y] != APPLE) {

        add_front_body(&cur, cur.head);
        sub_rear_body(&cur);
        
    }
    //사과면
    else {
        cur_map[cur.head.x][cur.head.y] = EMPTY;    //사과 냠냠
        add_front_body(&cur, cur.head);
    }
    
    return cur;
}

void proc_snake(Snake cur, int cur_map[N_MAX][N_MAX], int cur_time) {

    //뱀 : 방향으로 한칸 이동
    cur = move_snake(cur, cur_map);

    //회전 조건 확인
    if (cur_time == dir_info[dir_index][0]) {
        cur.dir = snake_rotate(cur, dir_info[dir_index][1]); //회전
        dir_index++;
    }

    //디버깅
    //printf("head: %d %d |dx: %d | t: %d", cur.head.x, cur.head.y, cur.dir, cur_time);
    //print(cur_map, cur);

    if (ret_flag) {
        if (ans == -1) ans = cur_time;
        return;
    }

    //다음 시간 처리 호출
    proc_snake(cur, cur_map, cur_time + 1);

}
int main() {

    scanf("%d", &N);
    scanf("%d", &K);

    int map[N_MAX][N_MAX];
    memset(map, 0, sizeof(map));
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        map[x-1][y-1] = APPLE;
    }

    scanf("%d", &L);
    for (int i = 0; i < L; i++) {
        scanf("%d %c", &dir_info[i][0], &dir_info[i][1]);
    }

    Pos stt = { 0,0 };
    Snake start;

    start.head = stt;
    start.len = 0;
    add_front_body(&start, stt);
    start.dir = EAST;

    proc_snake(start, map, 1);

    printf("%d\n", ans);

    return 0;
}
```

</div>
</details>

<br>

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">내 코드 보기(반복 : 76ms)</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define N_MAX 101
#define K_MAX 101
#define L_MAX 101

enum Map {
    APPLE = 1,
    EMPTY = 0,
};
enum Dir_info {
    LEFT = 'L',
    RIGHT = 'D',
    EAST = 0,
    SOUTH = 1,
    WEST = 2,
    NORTH = 3,
};
typedef struct {
    int x;
    int y;
}Pos;
typedef struct {
    Pos head;

    Pos body[N_MAX * N_MAX];
    int len;

    int dir;   //initial 0
}Snake;

int N, K;
int L;
int dir_info[L_MAX][2];
int dir_index = 0;

//e s w n
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int ans = -1;
bool ret_flag = 0;

//디버깅용
void print(int map[N_MAX][N_MAX], Snake snake) {
    printf("\n");
    int c = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int m = 0; m < snake.len; m++) {
                if (i == snake.body[m].x && j == snake.body[m].y) {
                    printf("b ");
                    c = 1;
                    break;
                }
                else c = 0;
            }
            if (c) continue;
            else printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void add_rear_body(Snake* snake, Pos new) {
    snake->body[snake->len++] = new;
}
void sub_rear_body(Snake* snake) {
    snake->len--;
}
void add_front_body(Snake* snake, Pos new) {
    for (int i = snake->len - 1; i >= 0; i--) {
        snake->body[i + 1] = snake->body[i];
    }
    snake->body[0] = new;
    snake->len++;
}

int snake_rotate(Snake cur, char dir) {
    if (dir == LEFT) {
        if (cur.dir == 0) cur.dir = 3;
        else cur.dir -= 1;
    }
    else if (dir == RIGHT) {

        if (cur.dir == 3) cur.dir = 0;
        else cur.dir += 1;
    }
    return cur.dir;
}
bool check_head_in_body(Snake cur) {
    for (int i = 1; i < cur.len; i++) {
        if (cur.head.x == cur.body[i].x && cur.head.y == cur.body[i].y) {
            return 1;
        }
    }
    return 0;
}

Snake move_snake(Snake cur, int cur_map[N_MAX][N_MAX]) {

    //뱀 이동
    cur.head.x += dx[cur.dir];
    cur.head.y += dy[cur.dir];

    //종료조건 만들기 : 1 머리가 벽에, 2.머리가 몸에
    bool head_in_wall = cur.head.x < 0 || cur.head.x >= N || cur.head.y < 0 || cur.head.y >= N;
    bool head_in_body = check_head_in_body(cur);
    ret_flag = head_in_wall || head_in_body;

    //사과없으면 꼬리움직임
    if (cur_map[cur.head.x][cur.head.y] != APPLE) {

        add_front_body(&cur, cur.head);
        sub_rear_body(&cur);
        
    }
    //사과면
    else {
        cur_map[cur.head.x][cur.head.y] = EMPTY;    //사과 냠냠
        add_front_body(&cur, cur.head);
    }
    
    return cur;
}


void proc_snake(Snake cur, int cur_map[N_MAX][N_MAX], int cur_time) {

    while (!ret_flag) {
        cur_time++;

        //뱀 : 방향으로 한칸 이동
        cur = move_snake(cur, cur_map);

        //회전 조건 확인
        if (cur_time == dir_info[dir_index][0]) {
            cur.dir = snake_rotate(cur, dir_info[dir_index][1]); //회전
            dir_index++;
        }
    }
    //디버깅
    //printf("head: %d %d |dx: %d | t: %d", cur.head.x, cur.head.y, cur.dir, cur_time);
    //print(cur_map, cur);

    if (ret_flag) {
        if (ans == -1) ans = cur_time;
        return;
    }
}
int main() {

    scanf("%d", &N);
    scanf("%d", &K);

    int map[N_MAX][N_MAX];
    memset(map, 0, sizeof(map));
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        map[x-1][y-1] = APPLE;
    }

    scanf("%d", &L);
    for (int i = 0; i < L; i++) {
        scanf("%d %c", &dir_info[i][0], &dir_info[i][1]);
    }

    Pos stt = { 0,0 };
    Snake start;

    start.head = stt;
    start.len = 0;
    add_front_body(&start, stt);
    start.dir = EAST;

    proc_snake(start, map, 0);

    printf("%d\n", ans);

    return 0;
}
```

</div>
</details>

<br>

하지만 더 빠른 코드들이 보이므로 개선 필요  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">더 빠른 코드 보기(0ms)</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 101

typedef struct {
    int x, y;
} Position;

typedef struct {
    int time;
    char direction;
} DirectionChange;

int N, K, L;
int board[MAX][MAX];
DirectionChange directions[100];
Position snake[MAX * MAX];
int snakeLength = 1;
int dx[4] = { 0, 1, 0, -1 }; // 우, 하, 좌, 상
int dy[4] = { 1, 0, -1, 0 };

int is_valid(int x, int y) {
    return x > 0 && x <= N && y > 0 && y <= N;
}

int simulate() {
    int time = 0, dir = 0, d_idx = 0;
    int head_x = 1, head_y = 1;

    while (1) {
        time++;
        head_x += dx[dir];
        head_y += dy[dir];

        // 충돌 확인 (벽 또는 자기 자신)
        if (!is_valid(head_x, head_y) || board[head_x][head_y] == 2) {
            break;
        }

        // 이동한 칸이 사과인 경우
        if (board[head_x][head_y] == 1) {
            board[head_x][head_y] = 2;
            snake[snakeLength++] = (Position){ head_x, head_y };
        }
        else { // 이동한 칸이 빈 칸인 경우
            board[head_x][head_y] = 2;
            snake[snakeLength++] = (Position){ head_x, head_y };

            // 꼬리 이동
            int tail_x = snake[0].x, tail_y = snake[0].y;
            board[tail_x][tail_y] = 0;
            for (int i = 1; i < snakeLength; i++) {
                snake[i - 1] = snake[i];
            }
            snakeLength--;
        }

        // 방향 전환
        if (d_idx < L && directions[d_idx].time == time) {
            if (directions[d_idx].direction == 'L') {
                dir = (dir + 3) % 4;
            }
            else if (directions[d_idx].direction == 'D') {
                dir = (dir + 1) % 4;
            }
            d_idx++;
        }
    }

    return time;
}

int main() {
    scanf("%d", &N);
    scanf("%d", &K);

    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        board[x][y] = 1; // 사과 위치
    }

    scanf("%d", &L);
    for (int i = 0; i < L; i++) {
        scanf("%d %c", &directions[i].time, &directions[i].direction);
    }

    board[1][1] = 2; // 뱀 초기 위치
    snake[0] = (Position){ 1, 1 };

    printf("%d\n", simulate());
    return 0;
}
```

</div>
</details>

<br>

맵의 재사용이 없으므로, 맵에 뱀을 직접 표시해가며 답을 도출해가는 과정이 더 빠름  
-> 뱀이 뱀의 몸과 부딪혔는지 판단하는 코드의 오버헤드가 크게 감소  


## 📌 4. 테트로미노
[백준 14500번](https://www.acmicpc.net/problem/14500)  
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<stdbool.h>

#define MAX_NM 500
#define MAX_TETROMINO 7

typedef struct {
	int x;
	int y;
}Pos;

typedef struct {
	Pos block[4];
}Tetromino;

int N, M;
int map[MAX_NM][MAX_NM];

int max;
Tetromino tetromino[MAX_TETROMINO] = {
	{ { {0,0}, {0,1}, {0,2}, {0,3} } },
	{ { {0,0}, {0,1}, {1,0}, {1,1} } },
	{ { {0,0}, {1,0}, {2,0}, {2,1} } },
	{ { {0,0}, {1,0}, {1,1}, {2,1} } },
	{ { {0,0}, {0,1}, {0,2}, {1,1} } },

	// 대칭 고려
	{ { {0,0}, {1,0}, {2,0}, {2,-1} } },
	{ { {0,0}, {1,0}, {1,-1}, {2,-1} } },
};

void rotate(Tetromino *cur, int n) {

	for (int i = 0;i < n;i++) {	// 회전 수
		for (int j = 1;j < 4;j++) {
			Pos temp = cur->block[j];
			cur->block[j] = (Pos){ temp.y, temp.x * -1 };
		}
	}

	/*
	0,1
	1,0
	0,-1
	-1,0

	2,1
	1,-2
	-2,-1
	-1,2
	
	*/
}
bool checkValid(int x, int y, Tetromino object) {
	bool ret = 1;

	for (int i = 0;i < 4;i++) {
		Pos temp = { object.block[i].x + x, object.block[i].y + y };

		if (temp.x < 0 || temp.y < 0 || temp.x >= N || temp.y >= M) {
			ret = 0;
			return ret;
		}
	}

	return ret;
}
int calPoint(int x, int y, Tetromino object) {
	int ret = 0;

	Tetromino cur = { 0 };
	for (int i = 0;i < 4;i++) {
		cur.block[i] = (Pos){ object.block[i].x + x, object.block[i].y + y };
	
		ret += map[cur.block[i].x][cur.block[i].y];
	}

	return ret;
}
void makeCase() {

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			
			for (int k = 0;k < MAX_TETROMINO;k++) {
				for (int l = 0;l < 4;l++) {

					// 시간 줄이는 용
					if (k <= 0) { // 1자 길쭉이
						if (l >= 2) continue;
					}
					else if (k <= 1) { // 사각형
						if (l >= 1) continue;
					}

					Tetromino new = tetromino[k];

					rotate(&new, l);
					
					/*
					if (i == 0 & j == 0) {
						//printf("%d = %d %d\n", point, k, l);

						for (int m = 0;m < 4;m++) {
							printf("i:%d = %d %d\n", m, new.block[m].x, new.block[m].y);
						}
					}
					*/

					bool valid = checkValid(i, j, new);
					if (valid) {
						int point = calPoint(i, j, new);

						//printf("%d\n", point);
						if (point > max) max = point;
					}
				}
			}
		}
	}
}
int main() {

	scanf("%d %d", &N, &M);

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < M;j++) {
			scanf("%d", &map[i][j]);
		}
	}

	makeCase();

	printf("%d", max);

	return 0;
}
```
{% include code_close.html %}

{% include code_open.html title="코드 보기" %}
{% include code_close.html %}


## 📌 5. 톱니바퀴
[백준 14891번](https://www.acmicpc.net/problem/14891)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

enum Direction {
	CW = 1,	// clockwise 시계 방향
	ACW = -1, // anticlockwise 시계 반대 방향

	// 톱니 index
	RIGHT = 2,
	LEFT = 6,
};

void debug(char wheel[9]) {
	wheel[8] = '\0';
	printf("-- %s\n", wheel);
}
void rotate(char arr[9], int direction) {
	char temp = 0;
	if (direction == CW) {
		temp = arr[7];
		for (int i = 7;i >= 1;i--) {
			arr[i] = arr[i - 1];
		}
		arr[0] = temp;
	}
	else if (direction == ACW) {
		temp = arr[0];
		for (int i = 0;i <= 7;i++) {
			arr[i] = arr[i + 1];
		}
		arr[7] = temp;
	}
}
void move(char wheel[4][9], int num, int direction) {

	int rightVal = wheel[num][RIGHT];
	int leftVal = wheel[num][LEFT];
	rotate(wheel[num], direction);

	int subDirection = direction;
	for (int i = num + 1;i < 4;i++) {
		//printf("%d | %c %c\n", i, rightVal, wheel[i][LEFT]);
		if (rightVal != wheel[i][LEFT]) {
			subDirection *= -1;
			rightVal = wheel[i][RIGHT];	// 돌리기 전에 미리 저장
			rotate(wheel[i], subDirection);
		}
		else break;
		//printf("%d : %s\n", i, wheel[i]);
		//debug(wheel[i]);
	}
	subDirection = direction;
	for (int i = num - 1;i >= 0;i--) {
		if (leftVal != wheel[i][RIGHT]) {
			subDirection *= -1;
			leftVal = wheel[i][LEFT];
			rotate(wheel[i], subDirection);
		}
		else break;
		//printf("%d : %s\n", i, wheel[i]);
	}
}
int main() {
	char wheel[4][9];
	for (int i = 0;i < 4;i++) {
		scanf("%s", wheel[i]);
	}
	int K;
	scanf("%d", &K);
	int num = 0, direction = 0;
	for (int i = 0;i < K;i++) {
		scanf("%d %d", &num, &direction);
		num -= 1;

		move(wheel, num, direction);
	}

	// 점수 계산
	int sum = 0;
	for (int i = 0;i < 4;i++) {
		if (wheel[i][0] == '1') {
			sum += 1 << i;	// 1 2 4 8
		}
		//sum += wheel[i][0];
	}
	printf("%d\n", sum);

	return 0;
}
/*
N S 같이 반대방향
S S 회전x

0 1 2 3 4 5 6 7
v   v       v

#1)
11011111
11011111
00000111
00000000
1
1 1

ans : 7
---

11011111
  v   v
11011111
  v   v
00000111
  v   v
00000000

*/
```
{% include code_close.html %}

##