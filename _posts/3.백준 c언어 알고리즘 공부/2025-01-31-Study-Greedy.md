---
title: 그리디
description: >-           #한 문장으로 나옴

date: 2025-01-31 12:24:17 +0900
lastmod : 2025-01-31 12:24:17 +0900  #마지막 수정 시간

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


## 그리디
탐욕 알고리즘  

### 회의실 잘 배정하기 (그리디, 정렬)  : 꽤 생각함
[백준 1931번](https://www.acmicpc.net/problem/1931)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 100001

typedef struct {
    int start, end;
} Meeting;
int N;

void print(Meeting arr[MAX]) {
    printf("\n");
    for (int i = 0;i < N;i++) {
        printf("%d %d\n", arr[i].start, arr[i].end);
    }
    printf("\n");
}
// 끝나는 시간을 기준으로 정렬하는 비교 함수
int compare(const void* a, const void* b) {
    Meeting* m1 = (Meeting*)a;
    Meeting* m2 = (Meeting*)b;

    if (m1->end == m2->end) {
        return m1->start - m2->start;  // 끝나는 시간이 같으면 시작 시간 기준 정렬
    }
    return m1->end - m2->end;  // 기본적으로 끝나는 시간 기준 정렬
}

int main() {

    scanf("%d", &N);

    Meeting meetings[MAX];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &meetings[i].start, &meetings[i].end);
    }

    // 끝나는 시간을 기준으로 정렬
    qsort(meetings, N, sizeof(Meeting), compare);

    //print(meetings);

    int count = 0;
    int lastEndTime = 0;

    for (int i = 0; i < N; i++) {
        if (meetings[i].start >= lastEndTime) {
            count++;  // 회의 배정
            lastEndTime = meetings[i].end;  // 마지막으로 배정된 회의의 끝나는 시간 갱신
        }
    }

    printf("%d\n", count);  // 최대 배정할 수 있는 회의 개수 출력

    return 0;
}
```

</div>
</details>

<br>
끝나는 시간 기준으로 정렬 후, 최소 끝나는 시간을 우선으로 배정  

<br>


### 로프로 최대 하중 찾기 (그리디, 정렬)  : 그냥 간단한 문제
[백준 2217번](https://www.acmicpc.net/problem/2217)
<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>
#include<stdlib.h>

#define MAX 100001

int cmp(const void* a, const void* b) {
	return *(int*)b - *(int*)a;	//내림차순
}

int main() {
	int N;
	scanf("%d", &N);

	int rope[MAX];
	for (int i = 0; i < N; i++) {
		scanf("%d", &rope[i]);
	}

	qsort(rope, N, sizeof(int), cmp);

	int max = 0;
	int arr[MAX] = { 0 };
	for (int i = 0; i < N; i++) {
		int cnt = 0;
		arr[i] = (i + 1) * rope[i];
		if (arr[i] > max) max = arr[i];
	}
	printf("%d\n", max);

	return 0;
}
```

</div>
</details>

<br>