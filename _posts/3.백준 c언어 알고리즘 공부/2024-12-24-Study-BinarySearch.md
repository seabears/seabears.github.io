---
title: 이진 탐색(Binary Search)
description: >-           #한 문장으로 나옴
  백준 문제풀이
date: 2024-12-24 14:05:57 +0900
#lastmod : 2024-12-24 14:05:57 +0900  #마지막 수정 시간

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

## 이진 탐색  

## 📌 1.   
[백준 14425번](https://www.acmicpc.net/problem/14425)  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">수정 전 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>
#include<string.h>

#define MAX 10000
#define LEN_MAX 501

int strcheck(char* str, int s[LEN_MAX], int n) {

	int a = 0;
	for (int i = 0;str[i] != '\0';i++) {
		a += str[i] * str[i] * (i + 1) * (i + 1);
	}
	for (int i = 0;i < n;i++) {
		if (s[i] == a) return 0;
	}
	return 1;

}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	int s[MAX];
	for (int i = 0;i < n;i++) {
		char temp[LEN_MAX];
		scanf("%s", temp);

		s[i] = 0;
		for (int j = 0;temp[j] != '\0';j++) {
			s[i] += temp[j] * temp[j] * (j + 1) * (j + 1);
		}
	}
	
	int check = 0;
	for (int i = 0;i < m;i++) {
		char temp[LEN_MAX];
		scanf("%s", temp);
		if (strcheck(temp, s, n) == 0)check++;
	}
	printf("%d", check);
	
	return 0;
}
```

</div>
</details>

<br>

이진 탐색으로 변환  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">수정 후 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, m, i, num = 0, cmp, start, mid, end;
char list[10000][501], temp[501];

int main(void) {
	scanf("%d %d ", &n, &m);
	for (i = 0; i < n; i++) {
		gets(list[i]);
	}

	qsort(list, n, sizeof(char) * 501, strcmp); //사전순 정렬

	for (i = 0; i < m; i++) {
		gets(temp);

		start = 0;
		end = n - 1;

		while (start <= end) {
			mid = (start + end) / 2;
			cmp = strcmp(temp, list[mid]);  //중간 확인인

			if (!cmp) {
				num++;
				break;
			}
			else if (cmp < 0) end = mid - 1;  //사전순 앞
			else start = mid + 1;             //사전순 뒤
		}
	}

	printf("%d", num);
}
```

</div>
</details>


-> 
qsort(list, n, sizeof(char) * 501, strcmp);  
qsort에 strcmp를 이용하면 바로 사전순 정렬 가능  


<br>


## 📌 2. 이진 탐색을 잘 설명하는 문제  
[백준 1920번](https://www.acmicpc.net/problem/1920)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdlib.h>

#define MAX 100001

int cmp(const void* a, const void* b) {
	int numa = *(int*)a;
	int numb = *(int*)b;
	//return numa-numb;은 overflow 발생(자료형 long long으로 변환도 가능) 
	if (numa > numb) return 1;
	else if (numa == numb)return 0;
	else if (numa < numb) return -1;
}
int find(int arr[MAX], int endIndex, int num) {
	int start = 0;
	int end = endIndex - 1;
	int middle = 0;
	while (start <= end) {
		middle = (start + end) / 2;

		//printf("start: %d, end: %d, mid : %d\n", arr[start], arr[end], arr[middle]);

		if (arr[middle] == num) break;
		else if (arr[middle] > num) end = middle - 1;
		else if (arr[middle] < num) start = middle + 1;
	}

	if (arr[middle] == num) return 1;
	else return 0;
}
int main() {
	int N;
	scanf("%d", &N);
	int numArr[MAX];
	for (int i = 0;i < N;i++) {
		scanf("%lld", &numArr[i]);
	}
	qsort(numArr, N, sizeof(int), cmp);

	int M;
	scanf("%d", &M);
	int num;
	for (int i = 0;i < M;i++) {
		scanf("%d", &num);

		int res = find(numArr, N, num);
		printf("%d\n", res);

	}
	return 0;
}
```

</div>
</details>

<br>


## 📌 3. 숫자 카드 나열해주고 몇개인지 찾기  
[백준 10816번](https://www.acmicpc.net/problem/10816)

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">방법 1 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 500001

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}
int getHowManyHave(int card[MAX][2], int n, int num) {
	int start = 0;
	int end = n - 1;
	int middle = 0;

	while (start <= end) {
		middle = (start + end) / 2;

		if (card[middle][0] == num) break;
		else if (card[middle][0] > num) end = middle - 1;
		else if (card[middle][0] < num) start = middle + 1;
	}

	if (card[middle][0] == num) return card[middle][1];
	else return 0;
}
int main() {
	int N;
	scanf("%d", &N);
	int card[MAX];
	memset(card, 0, sizeof(card));
	for (int i = 0;i < N;i++) {
		scanf("%d", &card[i]);
	}

	qsort(card, N, sizeof(int), cmp);

	int organized_card[MAX][2];
	int index = 0;
	int cnt = 1;
	for (int i = 1;i < N;i++) {
		if (card[i - 1] == card[i]) cnt++;
		else {
			organized_card[index][0] = card[i - 1];
			organized_card[index++][1] = cnt;
			cnt = 1;
		}
	}
	organized_card[index][0] = card[N - 1];
	organized_card[index++][1] = cnt;
	
	int M;
	scanf("%d", &M);
	int num;
	for (int i = 0;i < M;i++) {
		scanf("%d", &num);

		int res = getHowManyHave(organized_card, index, num);
		printf("%d ", res);
	}

	return 0;
}
```

</div>
</details>

<br>

**`lower_bound`, `upper_bound` 찾기로 수정**  
각 bound 찾는 방법 알아두기  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">방법 2 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 500001

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}
//lower_bound: key 시작값 찾기 //오른쪽 끝 수는 key 이전 값
int lower_bound(int card[MAX], int N, int key) {
	int start = 0, end = N - 1;
	while (start <= end) {
		int mid = (start + end) / 2;

		printf("lower_mid : %d | %d %d\n", mid, start, end);

		if (card[mid] >= key) end = mid - 1;
		else start = mid + 1;
	}
	return start;
}
// upper_bound: 처음으로 key 초과 나오는 위치 찾기 //오른쪽 끝 수는 key 끝값
int upper_bound(int* arr, int N, int key) {
	int start = 0, end = N - 1;
	while (start <= end) {
		int mid = (start + end) / 2;

		printf("upperr_mid : %d | %d %d\n", mid, start, end);

		if (arr[mid] > key) end = mid - 1;
		else start = mid + 1;
	}
	return start;
}
int main() {
	int N;
	scanf("%d", &N);
	int card[MAX];
	memset(card, 0, sizeof(card));
	for (int i = 0;i < N;i++) {
		scanf("%d", &card[i]);
	}

	qsort(card, N, sizeof(int), cmp);

	printf("\n");
	for (int i = 0;i < N;i++) printf("%d ", card[i]);
	printf("\n");
	
	int M;
	scanf("%d", &M);
	int num;
	for (int i = 0;i < M;i++) {
		scanf("%d", &num);

		int res = upper_bound(card, N, num) - lower_bound(card, N, num);
		printf("%d ", res);
	}
	return 0;
}
```

</div>
</details>

<br>

## 📌 4. 차집합 : 그냥 이진 탐색 중 하나  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<stdlib.h>

#define MAX 500001

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}
int BinarySearch(int arr[MAX], int size, int key) {
	int start = 0, end = size - 1;
	int mid = 0;
	while (start <= end) {
		mid = (start + end) / 2;

		if (arr[mid] == key) break;
		else if (arr[mid] > key) end = mid - 1;
		else if (arr[mid] < key) start = mid + 1;
	}
	//printf("mid : %d\n", arr[mid]);
	if (arr[mid] == key) return 1;
	else return -1;
}
int main() {
	int nA, nB;
	scanf("%d %d", &nA, &nB);

	int A[MAX], B[MAX];
	for (int i = 0;i < nA;i++) {
		scanf("%d", &A[i]);
	}
	for (int i = 0;i < nB;i++) {
		scanf("%d", &B[i]);
	}
	qsort(A, nA, sizeof(int), cmp);
	qsort(B, nB, sizeof(int), cmp);

	int cnt = 0;
	int arr[MAX];
	for (int i = 0;i < nA;i++) {
		int res = BinarySearch(B, nB, A[i]);
		if (res == -1) {
			arr[cnt] = A[i];
			cnt++;
		}
		else continue;
	}

	printf("%d\n", cnt);
	for (int i = 0;i < cnt;i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}
```

</div>
</details>

<br>

## 📌 5. 여러 랜선 잘라서 N개 이상 최대 길이 랜선 찾기
[백준 1654번](https://www.acmicpc.net/problem/1654)  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include <stdio.h>

int K, N;
long long lan[10000];

int count_lan(long long length) {
    int count = 0;
    for (int i = 0; i < K; i++) {
        count += lan[i] / length;
    }
    return count;
}

long long binary_search(long long left, long long right) {
    long long mid, max_length = 0;

    while (left <= right) {
        mid = (left + right) / 2;	//이 과정에서 int형은 overflow 발생  가능 -> long long으로
        if (count_lan(mid) >= N) {  // N개 이상 만들 수 있으면 길이를 늘려보기
            max_length = mid;
            left = mid + 1;
        }
        else {  // N개 미만이면 길이를 줄이기
            right = mid - 1;
        }
    }
    return max_length;
}

int main() {
    scanf("%d %d", &K, &N);

    long long max_lan = 0;
    for (int i = 0; i < K; i++) {
        scanf("%lld", &lan[i]);
        if (lan[i] > max_lan) max_lan = lan[i];  // 가장 긴 랜선 길이 찾기
    }

    printf("%lld\n", binary_search(1, max_lan));  // 1cm ~ 가장 긴 랜선 길이 사이 탐색
    return 0;
}
```

</div>
</details>
<br>

## 📌 6. 과자 나눠주기 : 많이 배움
[백준 16401번](https://www.acmicpc.net/problem/16401)
1. `mid = start + (end - start) / 2;` 오버플로우를 방지하는 안전한 방식  
2. `if (cnt >= M)` 를 통해 최대 길이를 찾음  

{% include code_open.html title="코드 보기" %}
```c
#include <stdio.h>

#define NMAX 1000000

int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    int L[NMAX];
    int sum = 0, max_length = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &L[i]);
        sum += L[i];
        if (L[i] > max_length) {
            max_length = L[i];  // 가장 긴 과자 길이 저장
        }
    }

    int start = 1;  // 0으로 나누는 문제 방지
    int end = max_length;  // 가장 긴 과자 길이까지 가능
    int answer = 0;  // 최대 과자 길이 저장

    while (start <= end) {
        //int mid = ((long long)start + (long long)end) / 2;  //(start + end)시 int 오버플로우 발생 가능 (long long)으로 형변환
        int mid = start + (end - start) / 2;  //안전한 방식 (start+end)/2와 수학적으로 동일
        
        //printf("%d %d %d\n", start, end, mid);
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            cnt += L[i] / mid;
        }

        if (cnt >= M) { //등호가 핵심
            answer = mid;  // 가능한 경우 저장
            start = mid + 1;  // 더 큰 길이를 찾기 위해 오른쪽 탐색
        }
        else if (cnt < M) {
            end = mid - 1;  // 부족하면 왼쪽 탐색
        }
    }

    printf("%d\n", answer);
    return 0;
}

/*
조카들에게 최대한 긴 과자, 모두 동일
1명에게 줄 수 있는 최대 과자 길이

과자는 나누기만 가능, 합치기 불가

과자 수 <= 100만
과자 길이 <= 10억
---
3명에게 10
1 2 3 4 5 6 7 8 9 10

*/
```
{% include code_close.html %}


## 📌 7. 나무자르기 : 위랑 거의 비슷한 문제, 등호로 최댓값 찾기
[백준 2805번](https://www.acmicpc.net/problem/2805)  
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>

#define MAX 1000000

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int tree[MAX];
	int maxHeight = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &tree[i]);
		if (tree[i] > maxHeight) maxHeight = tree[i];
	}

	int start = 0;
	int end = maxHeight;
	int mid = 0;
	int ans = 0;
	while (start <= end) {
		mid = start + (end - start) / 2;
		//mid = (long long)(start + end) / 2;  // 중간값 설정

		//printf("%d %d %d\n", start, end, mid);
		
		long long len = 0;	//지속해서 +연산을 하기에 오버플로우 발생가능 -> long long 사용
		for (int i = 0; i < N; i++) {
			if (tree[i] > mid) {
				len += tree[i] - mid;
			}
		}

		if (len >= M) {	//등호로 높이 최댓값 찾기
			ans = mid;
			start = mid + 1;
		}
		else if (len < M) {
			end = mid - 1;
		}
	}

	printf("%d\n", ans);
	return 0;
}
/*
적어도 M미터의 나무를 집에 가져가기 위한 절단기 설정 높이 최댓값
나무는 필요한 만큼만
H 이상만 잘림
---

#1)
4 7
20 15 10 17
ans : 15

(20-15) + (17-15) = 7

#2
5 20
4 42 40 26 46
ans : 36

*/
```
{% include code_close.html %}

## 📌 8. 세 수의 합 : bsearch, stdlib.h 내장 함수 사용해봄
[백준 2295번](https://www.acmicpc.net/problem/2295)
{% include code_open.html title="개선 코드 보기" %}
```c
#include<stdio.h>
#include<stdlib.h>

#define MAX_N 1000

int check(int* arr, int size, int key) {
	//printf("%d\n", key);
	int start = 0, end = size - 1;
	while (start <= end) {
		int middle = start + (end - start) / 2;

		if (arr[middle] == key) {
			//printf("find %d\n", key);
			return 1;
		}
		else if (arr[middle] < key) {
			start = middle + 1;
		}
		else if (arr[middle] > key) {
			end = middle - 1;
		}
	}
	return 0;
}
int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}
int main() {

	int N;
	scanf("%d", &N);
	int num[MAX_N];
	for (int i = 0;i < N;i++) {
		scanf("%d", &num[i]);
	}

	qsort(num, N, sizeof(int), cmp);

	int sum[MAX_N * MAX_N] = { 0 };
	int sum_idx = 0;
	for (int i = 0;i < N;i++) {
		for (int j = i;j < N;j++) {
			sum[sum_idx++] = num[i] + num[j];
		}
	}

	qsort(sum, sum_idx, sizeof(int), cmp);

	for (int i = N - 1;i >= 0;i--) {
		for (int j = 0;j < N;j++) {
			int key = num[i] - num[j];
			if (check(sum, sum_idx, key)) {
				printf("%d\n", num[i]);
				return 0;
			}
		}
	}

	return 0;
}
/*
U[x] + U[y] + U[z] = U[k]
U[k] - U[z] = U[x] + U[y]

U[x] + U[y]은 sum[]에 미리 다 저장

*/
```
{% include code_close.html %}

{% include code_open.html title="처음 만든 코드 보기(시간 초과)" %}
```c
#include<stdio.h>
#include<stdlib.h>

#define MAX_N 1000

int N;
int num[MAX_N];
int max = 0;

int selected[3];
int check() {
	int key = selected[0] + selected[1] + selected[2];
	//printf("%d\n", key);
	int start = selected[2], end = N - 1;
	while (start <= end) {
		int middle = start + (end - start) / 2;

		if (num[middle] == key) {
			//printf("find %d\n", key);
			return key;
		}
		else if (num[middle] < key) {
			start = middle + 1;
		}
		else if (num[middle] > key) {
			end = middle - 1;
		}
	}

	return 0;
}
void makeCase(int step) {
	if (step == 3) {
		int cur = check();
		
		//printf("max : %d\n", max);
		if (cur > max) {
			max = cur;
			//printf("max : %d\n", max);
		}
		return;
	}

	for (int i = 0;i < N;i++) {
		//printf("? %d\n", num[i]);
		selected[step] = num[i];
		
		makeCase(step + 1);
	}

}
int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}
int main() {

	scanf("%d", &N);
	for (int i = 0;i < N;i++) {
		scanf("%d", &num[i]);
	}

	qsort(num, N, sizeof(int), cmp);
	makeCase(0);

	printf("%d\n", max);

	return 0;
}
```
{% include code_close.html %}

{% include code_open.html title="bsearch 내장 함수 사용 코드 보기" %}
```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N, U[MAX_N];
    int sum_table[MAX_N * MAX_N], sum_count = 0;
    
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &U[i]);
    }
    
    qsort(U, N, sizeof(int), compare);
    
    // 두 수의 합을 미리 계산하여 저장
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            sum_table[sum_count++] = U[i] + U[j];
        }
    }
    
    qsort(sum_table, sum_count, sizeof(int), compare);
    
    // 가장 큰 수부터 시작하여 찾기
    for (int k = N - 1; k >= 0; k--) {
        for (int i = 0; i < N; i++) {
            int target = U[k] - U[i];
            if (bsearch(&target, sum_table, sum_count, sizeof(int), compare) != NULL) {
                printf("%d\n", U[k]);
                return 0;
            }
        }
    }
    
    return 0;
}
```
{% include code_close.html %}

## 