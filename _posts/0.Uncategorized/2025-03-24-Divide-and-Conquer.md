---
title: Divide and Conquer
description: >-           #한 문장으로 나옴
  
date: 2025-03-24 11:52:36 +0900
lastmod : 2025-03-24 11:52:36 +0900  #마지막 수정 시간

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


## Divide and Conquer



### 분할정복 제곱
[백준 1629번](https://www.acmicpc.net/problem/1629)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

long long mult(A, B, C) {

	if (B == 1) return A % C;
	long long res = mult(A, B / 2, C);

	if (B % 2) {
		res = res * res % C;
		res = res * A % C;
	}
	else {
		res = res * res % C;
	}

	return res;
	/*
	2^6 = 2^3 * 2^3
	2^3 = 2^1 * 2^1 * 2
	2^1 = 2

	*/
}
int main() {

	long long A, B, C;
	scanf("%d %d %d", &A, &B, &C);

	printf("%d", mult(A, B, C));

	return 0;
}
```
{% include code_close.html %}



