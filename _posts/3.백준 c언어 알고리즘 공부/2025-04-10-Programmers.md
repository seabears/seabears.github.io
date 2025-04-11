---
title: Programmers
description: >-           #한 문장으로 나옴
  
date: 2025-04-10 21:43:35 +0900
lastmod : 2025-04-10 21:43:35 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - Uncategorized  
tags: 
    - Untag1

#excerpt: "이 글의 요약"   # 요약
#image: "url_to_image.jpg"   # 대표 이미지 (옵션)
#permalink: /category1/first-post/
pin: false              # true | false
published: true        # true | false
---

## 📌 1. 아이템 줍기 : DFS
[프로그래머스 아이템 줍기](https://school.programmers.co.kr/learn/courses/30/lessons/87694?language=c)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INF_INT (~(1<<31))
#define MAX_MAP 50*2
#define MAX_H 4

typedef struct{
    int x;
    int y;
}Pos;


int map[MAX_MAP][MAX_MAP];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int dx2[8] = {0,0,1,-1, 1,1,-1,-1};
int dy2[8] = {1,-1,0,0, 1,-1,1,-1};


int min_dist = INF_INT;
bool visited[MAX_MAP][MAX_MAP];

void dfs(Pos cur, Pos end, int step){
    
    printf("cur %d %d\n", cur.x, cur.y);
    if(cur.x == end.x && cur.y == end.y){
        printf("도착\n");
        if(step < min_dist){
            min_dist = step;
        }
        return;
    }
    
    visited[cur.x][cur.y] = 1;
    
    for(int i=0;i < 4;i++){
        // 가려는 점
        Pos new = {cur.x + dx[i], cur.y + dy[i]};
        if(map[new.x][new.y] == 1 && !visited[new.x][new.y]){
            
            // 가려는 점의 주위에 빈칸 있어야함
            for(int j=0;j < 8;j++){
                Pos side = {new.x + dx2[j], new.y + dy2[j]};
                if(map[side.x][side.y] == 0){
                    dfs(new, end, step + 1);
                    break;  // 가려는 곳이면 빈칸 탐색 더 안해도 됨
                }
            }
        }
        
    }
}

// rectangle_row_len은 2차원 배열 rectangle의 행(세로) 길이입니다.
// rectangle_col_len은 2차원 배열 rectangle의 열(가로) 길이입니다.
// rectangle[i][j]는 rectangle의 i번째 행의 j번째 열에 저장된 값을 의미합니다.
int solution(int **rectangle, size_t rectangle_row_len, size_t rectangle_col_len, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    
    // 모든 좌표 2배로 뻥튀기 후 나중에 거리/2
    Pos start = (Pos){characterX*2, characterY*2};
    Pos end = (Pos){itemX*2, itemY*2};

    // marking
    for(int i=0;i<rectangle_row_len;i++){
        Pos left_low = {rectangle[i][0]*2,rectangle[i][1]*2};
        Pos right_high = {rectangle[i][2]*2,rectangle[i][3]*2};
        
        for(int j=left_low.x;j<=right_high.x;j++){
            for(int k=left_low.y;k<=right_high.y;k++){
                map[j][k]= 1;
            }
        }
    }
    
    // find dist
    dfs(start, end, 0);
    if(min_dist != INF_INT){
        answer = min_dist/2;
        
    }
    printf("%d\n", min_dist);
    
    return answer;
}
```
{% include code_close.html %}

경로의 좌표가 밀접하게 붙어있어 탐색이 어려울 때,  
모든 좌표를 x2 후, 최단 거리 등을 구하고,
나중에 /2 하기

## 📌 2. 퍼즐 조각 채우기 : DFS(퍼즐 조각 찾기), 퍼즐 조각의 좌표 비교..
[프로그래머스 퍼즐 조각 채우기](https://school.programmers.co.kr/learn/courses/30/lessons/84021?language=c)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAP 50

enum Map{
    EMPTY = 0,
    FILLED = 1,
};

typedef struct{
    int x;
    int y;
}Pos;
typedef struct{
    Pos pos[6];
    int len;
}Block;

int map_len;
int** game_board;
int** table;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int cmp_ascending(const void* a, const void* b){
    Pos pa = *(Pos*)a;
    Pos pb = *(Pos*)b;
    
    if(pa.x > pb.x){
        return 1;
    }
    else if(pa.x == pb.x){
        if(pa.y > pb.y){
            return 1;
        }
    }
    return -1;
}

bool table_visited[MAX_MAP][MAX_MAP] = {0};
Block block;
void table_dfs(Pos offset, Pos cur){
    
    table_visited[cur.x][cur.y] = 1;
    block.pos[block.len++] = (Pos){cur.x-offset.x, cur.y-offset.y}; // 블럭 추가, 0기준
    
    for(int i=0;i<4;i++){
        Pos new = {cur.x + dx[i], cur.y + dy[i]};
        if(new.x >= 0 && new.x < map_len && new.y >= 0 && new.y < map_len && table[new.x][new.y] == FILLED && !table_visited[new.x][new.y]) {
            table_dfs(offset, new);
        }
    }   
}

bool game_board_visited[MAX_MAP][MAX_MAP] = {0};
Block empty_block;
void game_board_dfs(Pos offset, Pos cur){
    
    game_board_visited[cur.x][cur.y] = 1;
    empty_block.pos[empty_block.len++] = (Pos){cur.x-offset.x, cur.y-offset.y}; // 블럭 추가, 0기준
    
    for(int i=0;i<4;i++){
        Pos new = {cur.x + dx[i], cur.y + dy[i]};
        if(new.x >= 0 && new.x < map_len && new.y >= 0 && new.y < map_len && game_board[new.x][new.y] == EMPTY && !game_board_visited[new.x][new.y]) {
            game_board_dfs(offset, new);
        }
    }   
}

Block rotate(int n){    // block을 n번 +90도 돌림
    Block new_block = {0};
    new_block.len = block.len;
    for(int i=0;i<block.len;i++){
        new_block.pos[i] = block.pos[i];
    }
    
    for(int i=0;i < n;i++){
        for(int len = 0; len < new_block.len; len++){
            int temp = new_block.pos[len].x;
            new_block.pos[len].x = new_block.pos[len].y;
            new_block.pos[len].y = temp * -1;
            
            /*
            0,0  0,1  0,2  0,3
            0,0  1,0  2,0  3,0
            0,0  0,-1  0,-2, 0,-3
            0,0 -1,0
            0,0 0,1
            
            */
        }
    }
    
    
        // block sync 가장 작은 좌표를 0으로 맞추자
    qsort(new_block.pos, new_block.len, sizeof(new_block.pos[0]), cmp_ascending);
    qsort(empty_block.pos, empty_block.len, sizeof(empty_block.pos[0]), cmp_ascending);
    
    Pos d1 = {-1 * new_block.pos[0].x, -1 * new_block.pos[0].y};
    Pos d2 = {-1 * empty_block.pos[0].x, -1 * empty_block.pos[0].y};
    
    for(int i=0;i<empty_block.len;i++){
        new_block.pos[i].x += d1.x;
        new_block.pos[i].y += d1.y;
        empty_block.pos[i].x += d2.x;
        empty_block.pos[i].y += d2.y;
    }
    return new_block;
}


bool check_valid(Block target){
//     // block sync 가장 작은 좌표를 0으로 맞추자
//     qsort(target.pos, target.len, sizeof(target.pos[0]), cmp_ascending);
//     qsort(empty_block.pos, empty_block.len, sizeof(empty_block.pos[0]), cmp_ascending);
    
//     Pos d1 = {-1 * target.pos[0].x, -1 * target.pos[0].y};
//     Pos d2 = {-1 * empty_block.pos[0].x, -1 * empty_block.pos[0].y};
    
//     for(int i=0;i<empty_block.len;i++){
//         target.pos[i].x += d1.x;
//         target.pos[i].y += d1.y;
//         empty_block.pos[i].x += d2.x;
//         empty_block.pos[i].y += d2.y;
//     }
    
    
    // 실제 체크
    for(int i=0;i<empty_block.len;i++){
        Pos empty_cur = empty_block.pos[i];
        Pos block_cur = target.pos[i];
        if(empty_cur.x != block_cur.x || empty_cur.y != block_cur.y){
            return 0;
        }
    }
    return 1;

}
// game_board_rows는 2차원 배열 game_board의 행 길이, game_board_cols는 2차원 배열 game_board의 열 길이입니다.
// table_rows는 2차원 배열 table의 행 길이, table_cols는 2차원 배열 table의 열 길이입니다.
int solution(int** game_board_temp, size_t game_board_rows, size_t game_board_cols, int** table_temp, size_t table_rows, size_t table_cols) {
    int answer = 0;
    
    game_board = game_board_temp;
    table =  table_temp;
    
    map_len = game_board_rows;

    
    // table에서 조각 찾기
    for(int i=0;i < map_len; i++){
        for(int j=0;j < map_len; j++){
            if(table[i][j] && !table_visited[i][j]){
                Pos offset = {i,j};
                Pos start = {i,j};
                block.len = 0;
                table_dfs(offset, start);
                
                printf("block.len %d\n", block.len);
                for(int d=0;d<block.len;d++){
                    printf("(%d %d)  ", block.pos[d].x, block.pos[d].y);
                }
                printf("\n");
                
                int valid = 0;
                // game_board에 넣을 공간 찾기
                memset(game_board_visited, 0, sizeof(game_board_visited));
                for(int m=0; m < map_len; m++){
                    for(int n=0; n < map_len; n++){
                        if(game_board[m][n] == EMPTY && !game_board_visited[m][n]){  // TODO 공간 비었을때
                        
                            // 겜보드에서 빈 블럭 찾기
                            Pos offset = {m,n};
                            Pos start = {m,n};
                            empty_block.len = 0;
                            game_board_dfs(offset, start);
                            
                            if(empty_block.len != block.len) continue;  // 길이 안맞는거 뛰어넘겨
                            
                            printf("empty.len %d\n", empty_block.len);
                            for(int d=0;d<empty_block.len;d++){
                                printf("(%d %d)  ", empty_block.pos[d].x, empty_block.pos[d].y);
                            }
                            printf("\n");
                            

                            for(int dir=0; dir<4; dir++){   // 회전
                                Block new_block = rotate(dir);
                                
                                printf("block rot %d\n", dir);
                                for(int d=0;d<new_block.len;d++){
                                    printf("(%d %d)  ", new_block.pos[d].x, new_block.pos[d].y);
                                }
                                printf("\n");
                                
                                int debug = check_valid(new_block);
                                printf("d %d\n", debug);
                                if(debug){ // 빈 블럭 안에 들어가는지
                                    
                                    // 겜보드에 삽입 // TODO
                                    for(int len=0;len < new_block.len;len++){
                                        printf("%d %d\n", new_block.pos[len].x + offset.x, new_block.pos[len].y + offset.y);
                                        game_board[new_block.pos[len].x + offset.x][new_block.pos[len].y + offset.y] = 1;
                                        
                                    }
                                    printf("find\n");
                                    answer += empty_block.len;
                                    valid = 1;
                                    break;
                                }
                            }
                            
                        }
                    if(valid) break;
                    }

                if(valid) break;
                }

                
            }
        }
    }
    return answer;
}
/*
조각 회전 가능
뒤집기 불가

딱 맞는경우만 넣기 가능
인접한칸 비면 안됨

1개에서 최대 6개가 연결된 형태의 조각
몇칸을 채울수 있는지 리턴

*/
```
{% include code_close.html %}

## 📌 3. 주식 가격 : 스택
[프로그래머스 주식 가격](https://school.programmers.co.kr/learn/courses/30/lessons/42584#)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100000

int stack[MAX];
int stack_top = 0;

// prices_len은 배열 prices의 길이입니다.
int* solution(int prices[], size_t prices_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int) * prices_len);
    
    for(int i=0;i < prices_len; i++){
        while (stack_top > 0 && prices[i] < prices[stack[stack_top - 1]]) {
            int top_idx = stack[--stack_top];
            answer[top_idx] = i - top_idx;
        }
        stack[stack_top++] = i;
    }
    
    // //Stack에 남은거
    // for(int i=0;i<stack_top;i++){
    //     int remain_idx = stack[i];
    //     answer[remain_idx] = prices_len-remain_idx - 1;
    // }
    
    while (stack_top > 0) {
        int top_idx = stack[--stack_top];
        answer[top_idx] = prices_len - top_idx - 1;
    }
    
    return answer;
}
```
{% include code_close.html %}

##