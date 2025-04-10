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

## 