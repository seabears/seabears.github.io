---
title: Union Find
description: >-           #한 문장으로 나옴
  
date: 2025-03-24 13:57:48 +0900
lastmod : 2025-03-24 13:57:48 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - Uncategorized  
tags: 
    - Untag1

#excerpt: "이 글의 요약"   # 요약
#image: "url_to_image.jpg"   # 대표 이미지 (옵션)
#permalink: /category1/first-post/
pin: false              # true | false
published: false        # true | false
---

## 📌 1. 여행 가자
[백준 1976번](https://www.acmicpc.net/problem/1976)
{% include code_open.html title="DFS 코드 보기" %}
```c
#include<stdio.h>
#include<string.h>

#define MAX_N 200

int N;
int map[MAX_N][MAX_N] = { 0 };

int valid = 1;
int visited[MAX_N];
void beValid(int cur, int end) {

	//printf("%d\n", cur);

	if (cur == end) {
		valid = 1;
		//printf("valid\n");
		return;
	}

	visited[cur] = 1;

	for (int i = 0;i < N;i++) {
		/*
		printf("cur %d | i : %d\n", cur, i);
		if (i == 3 && cur == 4) {
			printf("DEBUG %d %d\n", !visited[i], map[cur][i]);
		}
		if (visited[3]) printf("?\n");
		*/
		if (!visited[i] && map[cur][i]) {
			beValid(i, end);
			//visited[i] = 0;
		}
	}
}
int main() {

	scanf("%d", &N);
	int M;
	scanf("%d", &M);


	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			scanf("%d", &map[i][j]);
		}
	}

	// 이전 도시로부터 다음 도시로 가는 경로가 있는지 확인
	int prev_city = 0;
	scanf("%d", &prev_city);
	prev_city--;
	for (int i = 1;i < M;i++) {
		int city = 0;
		scanf("%d", &city);
		city--;
			
		if (valid) {
			//printf("---city : %d\n", city);
			valid = 0;
			memset(visited, 0, sizeof(visited));
			beValid(prev_city, city);
			prev_city = city;
		}
	}
	printf("%s\n", (valid) ? "YES" : "NO");

	return 0;
}
```
{% include code_close.html %}

{% include code_open.html title="Union-Find 코드 보기" %}
```c

```
{% include code_close.html %}

##

