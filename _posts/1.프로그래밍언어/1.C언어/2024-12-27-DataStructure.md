---
title: 자료구조
description: >-           #한 문장으로 나옴

date: 2024-12-27 09:20:55 +0900
lastmod : 2024-12-27 09:20:55 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - c언어  
tags: 
    - c언어
    - 자료구조

#excerpt: "이 글의 요약"   # 요약
#image: "url_to_image.jpg"   # 대표 이미지 (옵션)
#permalink: /category1/first-post/
pin: false              # true | false
published: true        # true | false
---

## 📌 1. 스택
LIFO (last input first out)  
```c
#define MAX 100
int stack[MAX] = { 0 };
int stack_index = 0;

void push(int new){
  stack[stack_index++] = new;
}
int pop(){
  return stack[--stack_index];
}
```

## 📌 2. 큐
FIFO (first input first out)  
```c
#define MAX 100
int queue[MAX] = { 0 };
int front = 0, rear = 0;

void enqueue(int new){
  queue[rear++] = new;
}
int dequeue(){
  return queue[front++];
}
```

## 📌 3. 트리

1) 배열 기반 트리  
**노드의 위치 규칙**  
- 부모 노드가 `i`일 떄,
  - 왼쪽 자식   : `2i + 1`  
  - 오른쪽 자식 : `2i + 2`  
