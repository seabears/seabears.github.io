---
title: Study-String
description: >-           #한 문장으로 나옴
  
date: 2025-04-09 11:28:51 +0900
lastmod : 2025-04-09 11:28:51 +0900  #마지막 수정 시간

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


## 📌 1. 문자열 폭발 : 주어진 문자열과 일치하는 문자열을 반복적으로 제거
[백준 9935번](https://www.acmicpc.net/problem/9935)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<string.h>

#define MAX_STR 1000000
#define MAX_BOOM 36

int main() {

	char str[MAX_STR + 1];
	char boom[MAX_BOOM + 1];
	int str_len = 0, boom_len = 0;

	scanf("%s", str);
	scanf("%s", boom);
	str_len = strlen(str);
	boom_len = strlen(boom);

	char result[MAX_STR + 1];
	int idx = 0;
	for (int i = 0;i < str_len;i++) {
		result[idx++] = str[i];	// 하나씩 추가

		if (idx >= boom_len) {	// 폭탄 문자열만큼 쌓였는지

			int flag_boom = 1;	// 폭발 flag

			// 이것도 가능
			//for (int j = 0;j < boom_len;j++) {
			//	if (result[idx - boom_len + j] != boom[j]) {
			//		flag_boom = 0;
			//		break;
			//	}
			//}

			flag_boom = strncmp(result + idx - boom_len, boom, boom_len);

			if (flag_boom == 0) {
				idx -= boom_len;
			}
		}
	}

	if (idx == 0) {
		printf("FRULA\n");
	}
	else {
		result[idx] = '\0';
		printf("%s\n", result);
	}

	return 0;
}
```
{% include code_close.html %}

## 📌 2. 가장 큰 수 : 수들을 문자열처럼 붙여서 만들 수 있는 최대수 찾기
[프로그래머스 가장 큰 수](https://school.programmers.co.kr/learn/courses/30/lessons/42746)
{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<string.h>

int cmp(const void* a, const void* b){
    char ab[10], ba[10];
    sprintf(ab, "%d%d", *(int*)a, *(int*)b);
    sprintf(ba, "%d%d", *(int*)b, *(int*)a);
    return strcmp(ba, ab); // 내림차순
}
// numbers_len은 배열 numbers의 길이입니다.
char* solution(int numbers[], size_t numbers_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* answer = (char*)malloc(sizeof(char) * (numbers_len * 4 + 1));
    
    qsort(numbers, numbers_len, sizeof(int), cmp);
    answer[0] = '\0';

    for (size_t i = 0; i < numbers_len; i++) {
        char buffer[5];
        sprintf(buffer, "%d", numbers[i]);
        strcat(answer, buffer);
    }

    // "0000..." 처리 (모든 수가 0인 경우)
    if (answer[0] == '0') {
        answer[1] = '\0';
    }
    
    return answer;
}
```
{% include code_close.html %}

## 📌 3. 생태학 : 문자열의 개수 세기
[백준 4358번](https://www.acmicpc.net/problem/4358)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_STR 30
#define MAX_KIND 10000

typedef struct {
	char name[MAX_STR + 1];
	int cnt;
}Tree;

Tree tree[MAX_KIND + 1];
int species_cnt = 0;
int tot_cnt = 0;

int binary_search(char* name) {
	int left = 0, right = species_cnt - 1;
	while (left <= right) {
		int mid = (left + right) / 2;

		int cmp_ret = strcmp(tree[mid].name, name);
		if (cmp_ret == 0) {
			return mid;
		}
		else if (cmp_ret > 0) {
			right = mid - 1;
		}
		else if (cmp_ret < 0) {
			left = mid + 1;
		}
	}
	return -1;
}
void insert_new(char* name) {
	// 뒤에서부터 하나씩 뒤로 밀면서 삽입할 자리 찾음
	int i = species_cnt - 1;
	while (i >= 0 && strcmp(tree[i].name, name) > 0) {
		tree[i + 1] = tree[i];
		i--;
	}
	i += 1;

	// 삽입
	strcpy(tree[i].name, name);
	tree[i].cnt = 1;
	species_cnt++;
}
int main() {
	char name[MAX_STR + 1];

	while (fgets(name, sizeof(name), stdin)) {
		name[strcspn(name, "\n")] = 0;
		tot_cnt++;

		int idx = binary_search(name);

		if (idx != -1) {	// 찾
			tree[idx].cnt++;
		}
		else {	//못 찾
			insert_new(name);
		}
	}

	for (int i = 0;i < species_cnt;i++) {
		double percent = (double)tree[i].cnt / tot_cnt * 100;
		printf("%s %.4f\n", tree[i].name, percent);
	}

	return 0;
}
```
{% include code_close.html %}

##