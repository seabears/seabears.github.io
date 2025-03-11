---
title: Study-Tree
description: >-           #한 문장으로 나옴
  
date: 2025-03-11 15:17:35 +0900
lastmod : 2025-03-11 15:17:35 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - Uncategorized  
tags: 
    - Untag1

sitemap :
  changefreq : daily
  priority : 1.0

#excerpt: "이 글의 요약"   # 요약
#image: "url_to_image.jpg"   # 대표 이미지 (옵션)
#permalink: /category1/first-post/
pin: false              # true | false
published: false        # true | false
---


## Study-Tree

## 📌 1. 유사 트리
[백준 11725번](https://www.acmicpc.net/problem/11725)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>

#define MAX_N 100000
#define MAX_EDGES ((MAX_N - 1) * 2) // 트리는 N-1개의 간선이지만 양방향 저장

int adj[MAX_EDGES], next[MAX_EDGES], head[MAX_N + 1], edgeCnt = 0;

void addEdge(int u, int v) {
    adj[edgeCnt] = v;           // n번째 간선이 어디로 가는지 저장
    //printf("adj[%d] = %d\n", edgeCnt, v);
    //printf("next[%d] = %d\n", edgeCnt, head[u]);
    next[edgeCnt] = head[u];    // 정점 u에서 출발하는 다른 간선
    //printf("head[%d] = %d\n", u, edgeCnt);
    //printf("-----------\n");
    head[u] = edgeCnt++;        // 정점 u가 몇번째 간선을 사용하는지
}

int parent[MAX_N + 1] = { 0 };
int visited[MAX_N + 1] = { 0 };

void dfs(int cur, int par) {
    visited[cur] = 1;
    parent[cur] = par;

    // 정점 cur의 간선 i가 존재하면
    for (int i = head[cur]; i != -1; i = next[i]) {  // next로 수정
        int nextNode = adj[i];
        if (!visited[nextNode]) {
            dfs(nextNode, cur);
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) head[i] = -1; // 연결 리스트 초기화

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }

    dfs(1, -1); // 루트 노드 1부터 시작

    for (int i = 2; i <= N; i++) {
        //printf("%d\n", next[i]);
        printf("%d\n", parent[i]);
    }

    return 0;
}
```
{% include code_close.html %}

