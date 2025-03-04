---
title: 투포인터
description: >-           #한 문장으로 나옴
  
date: 2025-02-14 21:50:39 +0900
lastmod : 2025-02-14 21:50:39 +0900  #마지막 수정 시간

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
published: true        # true | false
---

## 🔍 투포인터
정렬된 배열에서 두 개의 포인터(인덱스)를 사용하여 특정 조건을 만족하는 값을 빠르게 탐색하는 기법  

ex) 한 반복문 안에서 조건에 따라 left와 right를 적절히 조절하며 원하는 값을 찾음

---
### 📌 1. 두 수의 차가 M이상이면서 최소인 차이 값 구하기
[백준 2230번](https://www.acmicpc.net/problem/2230)  

왼쪽 0, 1에서 시작  
차가 M보다 작으면 오른쪽 index를 증가 : 차이를 벌리기  
차가 M보다 크면 왼쪽 index를 증가 : 차이를 좁히기  
이 과정에서 최소 차이 갱신  
<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int A[MAX_N];

// 비교 함수 (오름차순 정렬용)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    int M, min_diff = 2000000000; // 문제 조건의 최대값
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    // 배열 정렬 (O(N log N))
    qsort(A, N, sizeof(int), compare);

    int left = 0, right = 1;

    // 투 포인터 탐색 (O(N))
    while (right < N) {
        //printf("%d %d\n", A[left], A[right]);
        int diff = A[right] - A[left];

        if (diff >= M) { // 조건을 만족하면 최소 차이 갱신
            if (diff < min_diff) {
                min_diff = diff;
            }
            left++; // 더 작은 차이를 찾기 위해 left 증가
        }
        else {
            right++; // M 이상이 아니면 right 증가
        }
    }

    printf("%d\n", min_diff);
    return 0;
}
/*
N개의 정수로 이루어진 수열에서 두 수(중복가능)고를 때,
차이가 M이상이면서 제일 작은 값을 구하라

N 100,000이니까 N^2은 2초 이상임

1. 정렬
2. 왼쪽 오른쪽 계속 좁혀오면서 차이 확인
3. 처음 M 미만 될때에서 멈춰
4.

6 2
1 5 6 9 13 15

8 11
1 5 6 9 13 15 36 39


for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
        int diff = A[j] - A[i];
        if (diff < min_diff && diff >= M) {
            min_diff = diff;
        }
    }
}
*/
```

</div>
</details>
<br>

---
### 📌 2. 합이 S 이상이 되는 부분합 중, 가장 짧은 것의 길이 구하기
[백준 1806번](https://www.acmicpc.net/problem/1806)
<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>

#define MAX 100000
#define INF (~(1<<31))

int N, S;
int arr[MAX];

void solve() {
	int left = 0, right = 0;
	int minlen = INF;
	int len = 0;
	int sum = arr[left];	//초기값
	while (right < N) {
		len = right - left + 1;

		//최수 개수 갱신
		if (sum >= S) {
			if (len < minlen) {
				minlen = len;
			}

		//index옮기기
			sum -= arr[left];
			left++;
		}
		else if (sum < S) {
			right++;
			if(right < N) sum += arr[right];
		}
	}
	if (minlen == INF) printf("0\n");	//합 만드는 거 불가할 때
	else printf("%d\n", minlen);
}
int main() {
	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	solve();

	return 0;
}
/*
N개의 수열에서 연속된 부분합 중 S이상, 가장 적게 선택

*/
```

</div>
</details>
<br>

---
### 📌 3. 소수의 연속합
[백준 1644번](https://www.acmicpc.net/problem/1644)
<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>

#define MAX 4000000

int isPrime(int n) {	//O(sqrt(n))
	if (n < 2) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;

	for (int i = 3;i * i <= n;i += 2) {
		if (n % i == 0) return 0;
	}
	return 1;
}
int main() {
	int N;
	scanf("%d", &N);
	
	//1. N이하 소수 모두 저장
	int primes[283145] = { 0 };	//4,000,000까지 283145개 존재
	int primeCnt = 0;
	for (int i = 2;i <= N;i++) {
		if (isPrime(i)) {
			primes[primeCnt++] = i;
			//printf("%d ", i);
		}
	}
	//printf("%d\n", primeCnt);

	//2. 연속된 소수 합이 N인 경우 찾기
	int left = 0, right = 0, sum = 0, cnt = 0;
	while (right <= primeCnt) {
		printf("%d %d %d\n", left, right, sum);
		if (sum < N) {	//소수 하나 제외
			sum += primes[right++];
		}
		else if (sum > N) {	//소수 하나 포함
			sum -= primes[left++];
		}
		else {
			cnt++;
			sum += primes[right++];	//다음 경우를 탐색
			//기존 찾은 범위보다 더 긴 범위를 탐색하기 위해 right++
		}
	}

	printf("%d\n", cnt);

	return 0;
}
/*
정렬된 배열 만들기
배열 최대 인덱스 내부에서 찾기
*/
```

</div>
</details>
<br>

---
### 📌 4. 수의 연속합
[백준 2003번](https://www.acmicpc.net/problem/2003)
<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>

#define NMAX (10000+1)

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	int A[NMAX];
	for (int i = 1;i <= N;i++) {
		scanf("%d", &A[i]);
	}

	int left = 1, right = 1, sum = 0, cnt = 0;
	while (right <= N + 1) {
		//printf("%d %d %d\n", left, right, sum);
		if (sum < M) {
			sum += A[right++];
		}
		else if (sum > M) {
			sum -= A[left++];
		}
		else if (sum == M) {
			cnt++;
			sum += A[right++];
		}
	}

	printf("%d\n", cnt);

	return 0;
}
/*
i부터 j까지 합이 M이 되는 경우의 수

*/
```

</div>
</details>
<br>

---
### 📌 5. 특정 개수이상 겹치지 않는 부분 수열
[백준 20922번](https://www.acmicpc.net/problem/20922)  
{% include code_open.html title="코드 보기" %}

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 100000
#define NMAX 200000

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int arr[NMAX];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    int count[MAX_VAL + 1] = { 0 };  // 현재 윈도우에서 수의 빈도수를 기록하는 배열
    int left = 0, right = 0;
    int max_length = 0;

    while (right < N) {
        count[arr[right]]++;    //윈도우에 오른쪽 숫자 추가

        // 같은 숫자가 K개 이상인 경우, 왼쪽 포인터를 이동시킴
        while (count[arr[right]] > K) {
            count[arr[left]]--; //윈도우에서 제거
            left++;
        }

        // 최장 길이 갱신
        max_length = (right - left + 1 > max_length) ? (right - left + 1) : max_length;

        right++;
    }

    printf("%d\n", max_length);
    return 0;
}
```

{% include code_close.html %}

---
### 📌 6. 가장 긴 짝수 부분 수열, K개 홀수 제외 가능
[백준 22862번](https://www.acmicpc.net/problem/22862)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

#define NMAX (1000000+1)

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int S[NMAX];
    for (int i = 0; i < N; i++) scanf("%d", &S[i]);

    int left = 0, right = 0, len = 0, maxlen = 0;
    int cntOdd = 0;
    while (right < N) {
        //printf("%d %d | %d : %d\n", left, right, cntOdd, len);

        if (S[right] % 2) {   //홀수
            cntOdd += 1;

            if (cntOdd > K) {
                //left옮기기   : 홀수 하나 빠질 때까지
                while (1) {
                    if (S[left++] % 2) {
                        cntOdd -= 1;
                        break;
                    }
                    else {  //짝수 빠질 때마다
                        len -= 1;
                    }
                }
            }
        }
        else {  //짝수 추가
            len++;
        }
        right++;    //다음 수

        //maxlen갱신
        if (len > maxlen) {
            maxlen = len;
            //len = 0;
        }
        //printf("%d %d | %d : %d\n", left, right, cntOdd, len);
    }

    //maxlen갱신
    if (len > maxlen) {
        maxlen = len;
        len = 0;
    }
    printf("%d\n", maxlen);
    return 0;
}
/*
길이가 N인 수열 S에서
최대 K번 삭제 후,
짝수로 이루어진 연속 부분 수열 중 가장 긴 길이

1 2 3 4 5 6 7 8
    k   k

*/
```
{% include code_close.html %}


---
### 📌 7. 