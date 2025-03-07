---
title: 백트래킹
description: >-           #한 문장으로 나옴
  
date: 2025-02-11 11:44:48 +0900
lastmod : 2025-02-11 11:44:48 +0900  #마지막 수정 시간

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

백트래킹은 "가능한 모든 해"를 탐색하는 과정에서, 불필요한 경로를 미리 차단하고, 유효하지 않은 경로는 되돌려서 다른 경로를 탐색하는 알고리즘  

### 📌 1. 1부터 N까지에서 골라  길이가 M인 모든 수를 출력
[백준 15649](https://www.acmicpc.net/problem/15649)  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX (8+1)

int N, M;
int seq[9];
bool visited[9];

void backtrack(int index) {
	if (index == M) {	//M개 수 다 선택하면 출력
		for (int i = 0;i < M;i++) {
			printf("%d ", seq[i]);
		}
		printf("\n");
		return;
	}

	for (int i = 1;i <= N;i++) {	//1부터 N까지
		if (!visited[i]) {
			visited[i] = 1;	//방문 표시
			seq[index] = i;	//배열에 추가
			backtrack(index + 1);
			visited[i] = 0;	//방문 되돌리기
		}	
	}
}

int main() {

	scanf("%d %d", &N, &M);

	backtrack(0);	//index는 0부터

	return 0;
}

/*
1~N 자연수 중에서 중복 없이 길이가 M인 수열을 모두 구하라

*/
```

</div>
</details>
<br>

--- 
### 📌 2. 스도쿠
[백준 2580번](https://www.acmicpc.net/problem/2580)  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>

#define MAX (9+1)

int board[MAX][MAX];

int issafe(int row, int col, int val) {

    for (int i = 0; i < 9; i++) {   //가로 세로 유효여부 확인
        if (board[row][i] == val || board[i][col] == val) {
            return 0;
        }
    }

    int start_row = row - row % 3;
    int start_col = col - col % 3;
    /*
    if (row % 3 == 0) start_row = row;
    else if (row % 3 == 1) start_row = row - 1;
    else if (row % 3 == 2) start_row = row - 2;

    if (col % 3 == 0) start_row = col;
    else if (col % 3 == 1) start_col = col - 1;
    else if (col % 3 == 2) start_col = col - 2;
    */
    for (int i = start_row; i < start_row + 3; i++) {   //3x3 유효여부 확인
        for (int j = start_col; j < start_col + 3; j++) {
            if (board[i][j] == val) {
                return 0;
            }
        }
    }

    return 1;
}
void print() {
    for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 9; k++) {
            printf("%d ", board[j][k]);
        }
        printf("\n");
    }
}
int beReturn() {    //모든 칸 다 채웠는지 확인
    int ret = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) ret = 0;
        }
    }
    return ret;
}
int ret_flag = 0;
void solve() {

    if (ret_flag) return;

    if (beReturn()) {   //원하는 목표 도달시 return flag = 1;
        ret_flag = 1;
        return;
    }

    //빈곳 찾기
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {   //col
            if (board[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {

                    if (issafe(i, j, k)) {
                        board[i][j] = k;
                        solve();
                        if(!ret_flag) board[i][j] = 0;   //원하는 목표 도달 못하면 다시 되돌리기
                    }
                    //
                }
                return;
            }
        }
    }
}

int main() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    solve();

    if (ret_flag) {
        print();
    }


    return 0;
}
```

</div>
</details>
<br>

---
### 📌 3. 수열의 합 특정 값인 부분 수열의 개수
[백준 1182번](https://www.acmicpc.net/problem/1182)  

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">


```c
#include<stdio.h>

#define MAX (20+1)

int N, S;
int num[MAX];

int cnt = 0;
void solve(int index, int sum, int num_cnt) {
   /*
   index   : num배열에서 선택/미선택할 원소 인덱스
   sum      : 현재 분기까지의 합
   num_cnt : 선택한 원소의 개수(문제 조건 : 양수여야 함)
   */

   if (index == N) {
      if (sum == S && num_cnt > 0) cnt++;
      return;
   }

   //1. 포함
   solve(index + 1, sum + num[index], num_cnt + 1);

   //2. 미포함
   solve(index + 1, sum, num_cnt);

}
int main() {

   scanf("%d %d", &N, &S);
   for (int i = 0;i < N;i++) {
      scanf("%d", &num[i]);
   }
   
   solve(0, 0, 0);

   printf("%d\n", cnt);

   return 0;
}

/*
요구사항 : 부분수열의 합이 S인 경우의 수

-> 부분 수열을 선택

1. 현재 원소를 포함하는 경우
2.            포함 안하는 경우

*/
```

</div>
</details>
<br>

---
### 📌 4. N과 M(2)
[백준 16560번](https://www.acmicpc.net/problem/15650)  
<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>

#define MAX (8+1)

int N, M;

int ans[MAX];
int issafe(int num) {
	
	for (int i = 0;i < M;i++) {
		if (ans[i] == num) return 0;
	}
	return 1;
}
void solve(int selectNum, int selectCnt) {
	if (selectCnt == M) {
		for (int i = 0;i < M;i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
		return;
	}
	
	for (int i = selectNum;i <= N;i++) {
		if (issafe(i)) {
			ans[selectCnt] = i;
			solve(i, selectCnt + 1);
			ans[selectCnt] = 0;	//다른 곳에서 탐색할 때 유효하지 않은 index에서 걸리지 않도록
		}
	}
}

int main() {

	scanf("%d %d", &N, &M);

	solve(1, 0);

	return 0;
}
/*
1~N에서 중복 없이 M개를 골라라

1. 일단 차례대로 골라서 저장, 출력
2. 하나 빠꾸 저장 수정, 출력
...

*/
```

</div>
</details>
<br>

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">조금 변형 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>

#define MAX (8+1)

int N, M;

int ans[MAX];
int issafe(int num, int selectCnt) {
	
	for (int i = 0;i < selectCnt;i++) {
		if (ans[i] == num) return 0;
	}
	return 1;
}
void solve(int selectNum, int selectCnt) {
	if (selectCnt == M) {
		for (int i = 0;i < M;i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
		return;
	}
	
	for (int i = selectNum;i <= N;i++) {
		if (issafe(i, selectCnt)) {
			ans[selectCnt] = i;
			solve(i, selectCnt + 1);
			//ans[selectCnt] = 0;	//다른 곳에서 탐색할 때 유효하지 않은 index에서 걸리지 않도록
		}
	}
}

int main() {

	scanf("%d %d", &N, &M);

	solve(1, 0);

	return 0;
}
/*
1~N에서 중복 없이 M개를 골라라

1. 일단 차례대로 골라서 저장, 출력
2. 하나 빠꾸 저장 수정, 출력
...

*/
```

</div>
</details>
<br>

---

### 📌 5. N과 M(3)
[백준  15651번](https://www.acmicpc.net/problem/15651)
<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c
#include<stdio.h>

#define MAX (7+1)

int N, M;

int ans[MAX];
void solve(int numCnt, int num) {	//numCnt : 개수
	if (numCnt == M) {
		//ans배열 출력
		for (int i = 0; i < M; i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
		return;
	}

	for (int i = 1; i <= N; i++) {
		ans[numCnt] = i;
		solve(numCnt + 1, i);
		//ans[numCnt] = 0;
	}
}
int main() {
	scanf("%d %d", &N, &M);

	solve(0, 0);

	return 0;
}
/*
1부터 N까지 자연수 중에 M개를 고른 부분 수열, 중복 가능

1. 선택, 분기
2. 다뽑으면 출력, 리턴
3. 되돌리기

*/
```

</div>
</details>
<br>

---
### 📌 6. N과 M(4)
[백준 15652번](https://www.acmicpc.net/problem/15652)
{% include code_open.html title="첫 코드 보기" %}
```c
#include<stdio.h>

#define MAX_ANS 8

int ans[MAX_ANS + 1] = { 0 };	//index 1부터 8 사용

void solve(int N, int M, int step) {
	if (step == M + 1) {
		for (int i = 1;i <= M;i++) printf("%d ", ans[i]);
		printf("\n");
		return;
	}
	
	for (int i = 1;i <= N;i++) {
		if (i >= ans[step - 1]) {
			ans[step] = i;
			solve(N, M, step + 1);
		}
	}
}
int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	solve(N, M, 1);

	return 0;
}
/*
문제의 조건에 만족하는 수열 출력
중복 수열 여러번 출력 금지
공백으로 구분 수열
사전순 증가하는 순서로 출력

조건
1. 1~N 자연수 중 M개 고른 수열
2. 수 중복 가능
3. 비내림차순

#1)
3 1

1 2 3 중 1개를 고른 수열
1
2
3

*/
```
{% include code_close.html %}

{% include code_open.html title="조금 개선 코드 보기" %}
```c
#include<stdio.h>

#define MAX_ANS 8

int ans[MAX_ANS + 1] = { 0 };	//index 1부터 8 사용

void solve(int N, int M, int step, int cur_val) {
	if (step == M + 1) {
		for (int i = 1;i <= M;i++) printf("%d ", ans[i]);
		printf("\n");
		return;
	}
	
	for (int i = cur_val;i <= N;i++) {  //현재 추가값 이상만 추가
		ans[step] = i;
		solve(N, M, step + 1, i);
	}
}
int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	solve(N, M, 1, 1);  //step 1, cur_val 1부터 시작

	return 0;
}
```
{% include code_close.html %}

### 📌 7. N과 M(5)
[백준 15654번](https://www.acmicpc.net/problem/15654)
{% include code_open.html title="코드 보기" %}
```c
#include<stdio.h>
#include<stdlib.h>

#define MAX_ANS 8

int N, M;
int inputArr[MAX_ANS] = {0};	//입력 배열
int visited[MAX_ANS] = { 0 };	//입력의 방문 확인 배열
int ans[MAX_ANS + 1] = { 0 };	//답 출력할 배열

void solve(int step) {
	if (step == M + 1) {
		for (int i = 0;i < M;i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
		return;
	}

	for (int i = 0;i < N;i++) {
		if (!visited[i]) {
			visited[i] = 1;
			ans[step - 1] = inputArr[i];
			solve(step + 1, i);
			visited[i] = 0;	//사용한건 다시 0으로 돌려놔야 다음번에 반영 안됨
		}
	}
}
int cmp(const void* a, const void* b) {
	return *((int*)a) - *((int*)b);
}

int main() {

	scanf("%d %d", &N, &M);

	for (int i = 0;i < N;i++) {
		scanf("%d", &inputArr[i]);
	}
	qsort(inputArr, N, sizeof(int), cmp);

	solve(1);	//step 1 부터 시작
	return 0;
}
/*
N개의 자연수 중에서 M개를 고른 수열
*/
```
{% include code_close.html %}

###