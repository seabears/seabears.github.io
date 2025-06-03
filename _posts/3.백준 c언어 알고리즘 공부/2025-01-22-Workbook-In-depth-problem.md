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

## 📌 6. 감시
[백준 15683번](https://www.acmicpc.net/problem/15683)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<string.h>

#define INF (~(1<<31))
#define MAX_NM 8

enum Map {
    EMPTY = 0,
    WALL = 6,

    //CCTV1 = 1,    // 미사용
    //CCTV2 = 2,
    //CCTV3 = 3,
    //CCTV4 = 4,
    //CCTV5 = 5,

    EAST = 0,
    //SOUTH = 1,    // 미사용
    //WEST = 2,
    NORTH = 3,
};

typedef struct {
    int x;
    int y;
    int type;
}Pos;

int N, M;
int map[MAX_NM][MAX_NM];

// cctv
int cctv_cnt = 0;   // 맵 상의 CCTV 수
Pos cctv_Arr[8];    // 맵 상의 CCTV 좌표

int cctv_avb[6] = { 0,4,2,4,4,1 };  // cctv 타입별 가능한 방향의 수
int cctv[6][4][4] = {   // {E, S, W, N}
    {
        {0} // 0번 없음
    },
    {
        {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}   
    },
    {
        {1,0,1,0}, {0,1,0,1}  
    },
    {
        {1,0,0,1}, {1,1,0,0}, {0,1,1,0}, {0,0,1,1}  
    },
    {
        {1,0,1,1}, {1,1,0,1}, {1,1,1,0}, {0,1,1,1}
    },
    {
        {1,1,1,1}
    },
};

int selected_dir[8];    // 선택한 방향
int min_blind = INF;
int temp_map[MAX_NM][MAX_NM] = { 0 };

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
void mark(Pos cur, Pos dxdy) {

    Pos new = { cur.x + dxdy.x, cur.y + dxdy.y };
    while (new.x >= 0 && new.x < N && new.y >= 0 && new.y < M && temp_map[new.x][new.y] != WALL) {
        //if (temp_map[new.x][new.y] == EMPTY) {
        //   temp_map[new.x][new.y] = '#';
        //}
        temp_map[new.x][new.y] = '#';   // CCTV가 볼 수 있는 자리 마킹
        new.x += dxdy.x;
        new.y += dxdy.y;
    }
}
int calculate() {

    memcpy(temp_map, map, sizeof(temp_map));

    for (int i = 0; i < cctv_cnt; i++) {
        Pos cur_cctv = cctv_Arr[i];
        //int type = map[cur_cctv.x][cur_cctv.y]; // 1 ~ 5

        int* rm_dir = cctv[cur_cctv.type][selected_dir[i]]; // {1,0,0,0}와 같은 가장 작은 배열 하나의 시작주소

        //printf("%d : ", i);
        for (int j = EAST; j <= NORTH; j++) {

            //printf("%d ", rm_dir[i]);
            //printf("\n");

            if (rm_dir[j] == 1) {
                Pos dxdy = { dx[j], dy[j] };
                mark(cctv_Arr[i], dxdy);
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (temp_map[i][j] == EMPTY) {
                cnt++;
            }
        }
    }
    return cnt;
}
void makeCase(int cctv_idx) {
    if (cctv_idx == cctv_cnt) {
        // 거리 계산
        int cur_blind = calculate();
        //printf("cur : %d\n", cur_blind);
        if (cur_blind < min_blind) {
            min_blind = cur_blind;

            //for (int i = 0;i < cctv_cnt;i++) {
            //   printf("%d ", selected_dir[i]);
            //}
            //printf("\n");
        }

        return;
    }

    Pos cur_cctv = cctv_Arr[cctv_idx];
    //int type = map[cur_cctv.x][cur_cctv.y];

    for (int i = 0; i < cctv_avb[cur_cctv.type]; i++) {   // 방향
        selected_dir[cctv_idx] = i;
        makeCase(cctv_idx + 1);
    }

}
int main() {

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &map[i][j]);
            if (map[i][j] >= 1 && map[i][j] <= 5) {
                cctv_Arr[cctv_cnt++] = (Pos){ i,j,map[i][j] };
            }
        }
    }

    makeCase(0);
    printf("%d\n", min_blind);

    return 0;
}
```
{% include code_close.html %}

## 📌 7. 사다리 조작
[백준 15684번](https://www.acmicpc.net/problem/15684)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>

#define INF (~(1<<31))
#define MAX_N 10
#define MAX_H 30

int N, M, H;
int map[MAX_H][MAX_N]; // map[height][column]
int answer = INF;

int is_valid() {
    for (int start = 0; start < N; start++) {
        int pos = start;
        for (int h = 0; h < H; h++) {
            if (pos < N - 1 && map[h][pos] == 1) {
                pos++; // 오른쪽으로 이동
            }
            else if (pos > 0 && map[h][pos - 1] == 1) {
                pos--; // 왼쪽으로 이동
            }
        }
        if (pos != start) return 0;
    }
    return 1;
}

void dfs(int count, int x, int y) { 
    // x : 현재 놓은 가로선
    // y : 현재 놓은 세로선
    if (count >= answer) return;
    if (count > 3) return;
    if (is_valid()) {
        answer = count;
        return;
    }

    for (int i = x; i < H; i++) {   // 가로 선택
        for (int j = (i == x ? y : 0); j < N - 1; j++) {    // 세로 선택
            // j = (i == x ? y : 0)
            // 이전과 같은 가로선이면 이전 세로선부터
            // 아니면 첫 세로선부터 선택
            
            // 현재, 왼쪽, 오른쪽에 가로선이 없어야 함
            if (map[i][j] == 0 && map[i][j + 1] == 0 && (j == 0 || map[i][j - 1] == 0)) {
                map[i][j] = 1;
                dfs(count + 1, i, j);
                map[i][j] = 0;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &H);

    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        map[a - 1][b - 1] = 1; // 1-based to 0-based
    }

    dfs(0, 0, 0);

    printf("%d\n", answer == INF ? -1 : answer);

    return 0;
}
```
{% include code_close.html %}

## 📌 8. 스타트와 링크 : 간단
[백준 14889번](https://www.acmicpc.net/problem/14889)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

#define INF (~(1<<31))
#define MAX_N 20
#define MAX(a,b) ((a>b)?a:b)
#define MIN(a,b) ((a<b)?a:b)

int N;
int S[MAX_N][MAX_N];

int min_diff = INF;

int selected[MAX_N / 2];

int calculate_diff() {
	int sum1 = 0;
	int visited[MAX_N] = { 0 };

	for (int i = 0;i < N / 2;i++) {
		visited[selected[i]] = 1;
		for (int j = 0;j < N / 2;j++) {
			sum1 += S[selected[i]][selected[j]];
		}
	}

	int other_team[MAX_N / 2] = { 0 };
	int idx = 0;
	for (int i = 0;i < N;i++) {
		if (!visited[i]) {
			other_team[idx++] = i;
		}
		// 아래는 느림
		//int already_team = 0;
		//for (int j = 0;j < N / 2;j++) {
		//	if (selected[j] == i) {
		//		already_team = 1;
		//		break;
		//	}
		//}
		//if (already_team == 0) {
		//	other_team[idx++] = i;
		//}
	}

	int sum2 = 0;
	for (int i = 0;i < N / 2;i++) {
		for (int j = 0;j < N / 2;j++) {
			sum2 += S[other_team[i]][other_team[j]];
		}
	}

	return MAX(sum1, sum2) - MIN(sum1, sum2);
}
void makeTeam(int step, int start) {
	if (step == N / 2) {
		// cal
		int cur_diff = calculate_diff();
		if (cur_diff < min_diff) {
			min_diff = cur_diff;
		}
		return;
	}

	// step과 반복문의 start를 따로 받아서
	// 중복없이 항상 오름차순으로만 고름
	for (int i = start;i < N;i++) {
		selected[step] = i;
		makeTeam(step + 1, i + 1);	// 다음 사람부터 선택
		/*
		0 ~ N
		1 ~ N
		2 ~ N
		...
		*/
	}
}
int main() {

	scanf("%d", &N);
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			scanf("%d", &S[i][j]);
		}
	}

	makeTeam(0, 0);

	printf("%d\n", min_diff);

	return 0;
}
/*
축구 N, 짝수

Sij , Sji

*/
```
{% include code_close.html %}

## 📌 9. 주사위 굴리기 : 시뮬레이션
[백준 14499번](https://www.acmicpc.net/problem/14499)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<string.h>

#define MAX_MAP 20

typedef struct {
	int x;
	int y;
	int val[6];
}Dice;

enum Dir {
	EAST = 1,
	WEST = 2,
	NORTH = 3,
	SOUTH = 4,
};

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

int main() {
	int N, M, K;
	Dice dice = { 0 };
	scanf("%d %d %d %d %d", &N, &M, &dice.x, &dice.y, &K);
	//memcpy(dice.val, (int[]) { 2, 1, 5, 6, 4, 3 }, sizeof(dice.val));

	int map[MAX_MAP][MAX_MAP];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	int cmd = 1;
	for (int i = 0; i < K; i++) {
		scanf("%d", &cmd);
		
		dice.x += dx[cmd - 1];
		dice.y += dy[cmd - 1];

		if (!(dice.x >= 0 && dice.x < N && dice.y >= 0 && dice.y < M)) {
			dice.x -= dx[cmd - 1];
			dice.y -= dy[cmd - 1];
			continue;
		}

		int temp[6] = { 0 };
		memcpy(temp, dice.val, sizeof(temp));
		switch (cmd) {
		/*
		  0
		4 1 5
		  2
		  3

		*/
		case EAST:
			dice.val[4] = temp[3];
			dice.val[1] = temp[4];
			dice.val[5] = temp[1];
			dice.val[3] = temp[5];
			break;
		case WEST:
			dice.val[4] = temp[1];
			dice.val[1] = temp[5];
			dice.val[5] = temp[3];
			dice.val[3] = temp[4];
			break;
		case NORTH:
			dice.val[0] = temp[1];
			dice.val[1] = temp[2];
			dice.val[2] = temp[3];
			dice.val[3] = temp[0];
			break;
		case SOUTH:
			dice.val[0] = temp[3];
			dice.val[1] = temp[0];
			dice.val[2] = temp[1];
			dice.val[3] = temp[2];
			break;

		}

		if (map[dice.x][dice.y] == 0) {
			map[dice.x][dice.y] = dice.val[3];
		}
		else {
			dice.val[3] = map[dice.x][dice.y];
			map[dice.x][dice.y] = 0;
		}

		printf("%d\n", dice.val[1]);
	}

	return 0;
}

/*
이동칸에 쓰여있는 수가 0이면 주사위 바닥면이 칸에 복사
아니라면 칸이 주사위에 복사, 칸은 0

*/
```
{% include code_close.html %}

## 📌 10. 인구 이동 : BFS
[백준 16234번](https://www.acmicpc.net/problem/16234)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>
#include <string.h>

#define MAX_N 50
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))

typedef struct {
	int x;
	int y;
}Pos;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

Pos queue[MAX_N * MAX_N];
int front = 0, rear = 0;
void enqueue(Pos new) {
	queue[rear++] = new;
}
Pos dequeue() {
	return queue[front++];
}

Pos stack[MAX_N * MAX_N];
int stack_i = 0;

int main() {
	int N, L, R;
	scanf("%d %d %d", &N, &L, &R);

	int A[50][50];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &A[i][j]);
		}
	}

	int day = 0;
	int visited[MAX_N][MAX_N] = { 0 };
	int sum = 0;
	int beUnion = 1;	// 해당 날에 국경선을 열었는지

	while (++day && beUnion) {
		// 1. 국경선을 열 것인지 확인
		beUnion = 0;
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j]) continue;
				front = 0, rear = 0;
				Pos start = { i,j };
				enqueue(start);
				visited[start.x][start.y] = 1;
				stack_i = 0;
				sum = 0;

				while (front < rear) {
					Pos cur = dequeue();
					stack[stack_i++] = cur;
					sum += A[cur.x][cur.y];

					for (int d = 0; d < 4; d++) {
						Pos new = { cur.x + dx[d], cur.y + dy[d] };
						if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N && !visited[new.x][new.y]) {
							int diff = MAX(A[cur.x][cur.y], A[new.x][new.y]) - MIN(A[cur.x][cur.y], A[new.x][new.y]);
							if (diff >= L && diff <= R) {
								beUnion = 1;
								enqueue(new);
								visited[new.x][new.y] = 1;
							}
						}
					}
				}
			
				// 2. 국경선을 열어 인구 이동
				for (int idx = 0; idx < stack_i; idx++) {
					Pos cur = stack[idx];
					A[cur.x][cur.y] = sum / (stack_i);
					//printf("%d %d, A : %d\n", cur.x, cur.y, A[cur.x][cur.y]);
					//printf("%d %d\n", sum, stack_i);
				}

			}

		}
		//for (int i = 0; i < N; i++) {
		//	for (int j = 0; j < N; j++) {
		//		printf("%d ", A[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");

		//printf("day\n");

	}
	printf("%d\n", day - 2);

	return 0;
}
/*
NxN 땅, 정사각형 형태

*/
```
{% include code_close.html %}

문제를 잘 읽고, 사람의 관점에서 어떻게 동작시키고 있는지 확인하고,  
동작 하나하나를 구현  
특히, 연합이 끝나는 시점은 A[i][j]를 확인해봤을 때, `인구 이동이 없을 때` 이다.  

## 📌 11. 나무 재네크 : 시뮬레이션
[백준 16235번](https://www.acmicpc.net/problem/16235)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>
#include <string.h>

#define MAX_N 10
#define MAX_M 100

typedef struct {
    int x;
    int y;
}Pos;
typedef struct {
    int x;
    int y;
    int age;
}PreTree;

typedef struct {
    int ages[1000];
    int idx;
    int idxDie;
    int food;
}Map;

// 입력
int N, M, K;   // 땅 크기, 이미 심은 나무 수, 몇년후
int A[MAX_N][MAX_N];    // 겨울에 추가하는 양분
PreTree preTree[MAX_M];    // 사전에 심은 나무
//

Map map[MAX_N][MAX_N];  // 양분, 나무들의 나이

void debug() {
    printf("\n----DEBUG---------------\n");
    printf("---------idx------------\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", map[i][j].idx);
        }
        printf("\n");
    }
    printf("----------food----------\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", map[i][j].food);
        }
        printf("\n");
    }
    printf("----------age-----------\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", map[i][j].ages[0]);
        }
        printf("\n");
    }
    printf("------------------------\n");

    printf("%d %d\n", map[1][0].ages[0], map[2][1].ages[0]);

}
void spring() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            map[i][j].idxDie = 0;   // idxDie 초기화

            for (int k = 0; k < map[i][j].idx; k++) {
                map[i][j].food -= map[i][j].ages[k];

                // 양분 못 먹으면 뒷 나무들 다 죽음
                if (map[i][j].food < 0) {
                    map[i][j].food += map[i][j].ages[k];
                    map[i][j].idxDie = map[i][j].idx;
                    map[i][j].idx = k;  // k 전까지 살아있음
                    break;
                }
                else {
                    map[i][j].ages[k] += 1;
                }
            }
        }
    }
}
void summer() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = map[i][j].idx; k < map[i][j].idxDie; k++) {
                map[i][j].food += map[i][j].ages[k] / 2;
            }
        }
    }
}
void fall() {
    int dx[8] = { 0,-1,-1,-1,0,1,1,1 };
    int dy[8] = { 1,1,0,-1,-1,-1,0,1 };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 해당 칸에 나무가 있고
            if (map[i][j].idx <= 0) continue;

            for (int k = 0; k < map[i][j].idx; k++) {
                // 5의 배수인 나무만
                if (map[i][j].ages[k] % 5 != 0) continue;

                for (int m = 0; m < 8; m++) {
                    Pos newTree = { i + dx[m], j + dy[m] };
                    if (newTree.x < 0 || newTree.x >= N || newTree.y < 0 || newTree.y >= N) continue;

                    // 나무 뒤로 밀고
                    //map[newTree.x][newTree.y].idx += 1;
                    memmove(&map[newTree.x][newTree.y].ages[1], &map[newTree.x][newTree.y].ages[0], sizeof(int)*map[newTree.x][newTree.y].idx);
                    //for (int n = map[newTree.x][newTree.y].idx - 1; n >= 0; n--) {    // idx-2
                    //    map[newTree.x][newTree.y].ages[n + 1] = map[newTree.x][newTree.y].ages[n];
                    //}
                    // 맨 앞에 추가
                    map[newTree.x][newTree.y].idx += 1;
                    map[newTree.x][newTree.y].ages[0] = 1;
                }
            }
        }
    }
}
void winter() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j].food += A[i][j];
        }
    }
}

int main() {

    scanf("%d %d %d", &N, &M, &K);

    // 겨울에 추가하는 양분
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // 심은 나무 정보
    for (int i = 0; i < M; i++) {
        int x = 0, y = 0, z = 0;
        scanf("%d %d %d", &x, &y, &z);
        x -= 1, y -= 1;
        map[x][y].ages[map[x][y].idx++] = z;
    }


    // 기본 양분 5로 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j].food = 5;
        }
    }

    int year = 0;
    while (year++ != K) {
        //printf("\n===============year %d\n", year);
        //debug();
        spring();
        //debug();
        summer();
        fall();
        winter();
        //debug();
        //printf("f %d\n", map[0][0].food);
    }

    int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += map[i][j].idx;
        }
    }
    printf("%d\n", sum);

    return 0;
}

/*
땅 NxN
땅에 양분 기본 5

M개의 나무를 땅에
1x1에도 여러개 나무 가능
봄에 나무가 자기 나이만큼 양분 먹고 나이가 1 증가
하나의 칸에 나무가 여러개 -> 어린 나무 부터 양분 섭취
양분 부족하면 즉사

여름에
봄에 죽은 나무 -> 양분으로
죽은 나무의 나이 / 2 => 양분

가을
나이가 5의 배수인 나무가 번식
인접한 8개의 칸에 나이 1 나무 생김

겨울
땅에 양분 추가
A[r][c] -> 입력

구하고 싶은거
K년이 지난 후 땅에 살아있는 나무의 개수


*/
```
{% include code_close.html %}

년수가 1000년까지 가능하므로 1x1 칸에 나무가 최대 1000개까지 있을 수 있음.  
문제의 조건 범위를 잘 확인하기  

## 📌 12. 아기 상어 : BFS
[백준 16236번](https://www.acmicpc.net/problem/16236)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<stdbool.h>

#define INF (~(1<<31))
#define MAX_N 20

typedef struct {
	int x;
	int y;
	int size;
	int step;
}Pos;

int N;
int map[MAX_N][MAX_N];

Pos baby;

const int dx[4] = { -1,0,1,0 };
const int dy[4] = { 0,-1,0,1 };

void debug() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == baby.x && j == baby.y) {
				printf("$ ");
			}
			else {
				printf("%d ", map[i][j]);
			}
		}
		printf("\n");
	}
	printf("===============================\n\n");
}
Pos find() {
	Pos queue[10000];
	int front = 0, rear = 0;
	bool visited[MAX_N][MAX_N] = { 0 };

	queue[rear++] = baby;
	visited[baby.x][baby.y] = 1;

	Pos target = { 0,0,0,INF };
	while (front < rear) {
		Pos cur = queue[front++];

		if (cur.step > target.step) continue;
		if (map[cur.x][cur.y] != 0 && baby.size > map[cur.x][cur.y]) {
			if (cur.step < target.step) {
				target = cur;
			}
			if (cur.step == target.step) {
				if (cur.x < target.x) {
					target = cur;
				}
				else if (cur.x == target.x) {
					if (cur.y < target.y) {
						target = cur;
					}
				}
			}

			continue;
			//return target; // cur;
		}
		
		for (int i = 0; i < 4; i++) {
			Pos new = { cur.x + dx[i], cur.y + dy[i], cur.size, cur.step + 1 };

			if (new.x >= 0 && new.x < N && new.y >= 0 && new.y < N) {
				if (visited[new.x][new.y] == 1) continue;
				if (baby.size < map[new.x][new.y]) continue;

				visited[new.x][new.y] = 1;
				queue[rear++] = new;
			}
		}
	}
	return target;
}
int move() {
	int time = 0;
	int eat = 0;
	while (1) {
		// 1. 탐색
		Pos target = find();
		if (target.step == INF) return time;
		//printf("target : [%d] %d %d | 거리 %d\n", map[target.x][target.y], target.x, target.y, target.step);
		time += target.step;

		// 2. 이동
		baby.x = target.x;
		baby.y = target.y;
		eat += 1;
		if (eat == baby.size) {
			eat = 0;
			baby.size += 1;
		}
		map[baby.x][baby.y] = 0;
		
		//printf("size %d | eat %d\n", baby.size, eat);
		//debug();
	}
}
int main() {

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);

			if (map[i][j] == 9) {
				baby = (Pos){ i,j,2,0 };
				map[i][j] = 0;
			}
		}
	}

	int res = move();

	printf("%d\n", res);

	return 0;
}
/*
공간 NxN
물고기 M
아기 상어 1

칸당 물고기 최대 1

아기 상어 크기 2로 시작
1초에 상하좌우 한칸 이동
자기보다 큰 물고기칸 이동 못함

작은 물고기는 먹을 수 있음

같은 물고기는 이동만 가능


더이상 없으면 엄마상어에게 도움
거리가 가까운 물고기 먹으러 감
가장 위, 왼쪽이 우선

크기만큼 물고기 수 먹으면 크기 1 증가

요청 전 몇초동안??

*/
```
{% include code_close.html %}

## 