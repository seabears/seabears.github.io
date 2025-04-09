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


## 📌 1. 문자열 폭발
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

## 📌 2. 가장 큰 수
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

##