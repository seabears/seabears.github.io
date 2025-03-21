---
title: 함수포인터
description: >-           #한 문장으로 나옴
  C언어
date: 2025-01-02 12:20:25 +0900
lastmod : 2025-01-02 12:20:25 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - c언어
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

### 함수포인터

장점 : 콜백 함수 (callback function) 구현
콜백함수 : 특정 작업 완료 후, 실행될 함수를 동적으로 지정
            , 개발간 권한 위임 (분리된 독립적 개발)


<br>

#### Struct 안에 함수 포인터 -> 마치 객체처럼

```c
#include <stdio.h>

int add(int x, int y) {
	return (x + y);
}

typedef struct _calculator_t {
	int (*op)(int a, int b);
} calculator_t;
typedef int (*fp_calc)(int, int);


int main() {
	calculator_t calculator;
	calculator.op = &add;

	int a = 7;
	int b = 3;
	float r = 0;

	r = calculator.op(a, b);

	printf("%d%c%d=%3.1f\n", a, '+', b, (float)r);

	return 0;
}
```


<br>

```c
#include<stdio.h>

int hot(int a, int b) {
	printf("%s ", __func__);	// __func__ : 매크로, 함수 이름을 문자열로
	printf("(a,b) = (%d, %d)\n", a, b);
	return (a + b);
}
void set_hot(int a, int b, int(*func)(int, int)) {
	int res = func(a, b);
	printf("res : %d\n", res);
}
int main() {

	set_hot(1, 2, hot);

	return 0;
}
```

<br>

#### 2차원 함수 포인터

```c
#include <stdio.h>

#define COL (2)
#define ROW (2)

void f00() { printf("This function is %s()", __FUNCTION__); }
void f01() { printf("This function is %s()", __FUNCTION__); }
void f10() { printf("This function is %s()", __FUNCTION__); }
void f11() { printf("This function is %s()", __FUNCTION__); }

int main() {
	// 2차원 함수 포인터 배열을 선언하시오.
	void (*fp[COL][ROW])() = { NULL, };

	// 2차원 함수 포인터 배열에 위 함수를 모두 대입하시오
	fp[0][0] = &f00;
	fp[0][1] = &f01;
	fp[1][0] = &f10;
	fp[1][1] = &f11;

	int col = 0;
	int row = 0;
	printf("input col : ");
	int d1 = scanf("%d", &col);
	printf("input row : ");
	int d2 = scanf("%d", &row);

	// 2차원 함수 포인터배열의 주소 출력 및 함수를 호출하시오
	printf("Address of fp[%d][%d]: 0x%p \r\n", col, row, fp[col][row]);
	fp[col][row]();
	printf("\r\n");

	return 0;
}
```

<br>

#### 함수 포인터 이럴 때 쓰면 좋다

```c
#include<stdio.h>

#define print_func_name (printf("%s\n", __func__))

void zero() { print_func_name; }
void one() { print_func_name; }
void two() { print_func_name; }
void three() { print_func_name; }
void four() { print_func_name; }
void five() { print_func_name; }
void six() { print_func_name; }
void seven() { print_func_name; }
void eight() { print_func_name; }
void nine() { print_func_name; }

int main() {
	int num = 0;
	printf("Enter a num between 0 to 9 : ");
	scanf("%d", &num);


#define MAX_FUNC_CNT (10)
	
	void (*fp_arr[MAX_FUNC_CNT])() = {
		zero, one, two, three, four, five, six, seven, eight, nine
	};


	(*fp_arr[num])();


	return 0;
}
```


<br>

### 더 많은 예시

```c
#include <stdio.h>

// 콜백 함수의 형태로 사용할 함수
void print_result(int result) {
    printf("Result: %d\n", result);
}

// 함수를 포인터로 받아서 호출하는 함수
void perform_calculation(int a, int b, void (*callback)(int)) {
    int result = a + b;  // 계산 작업
    callback(result);     // 계산 완료 후 콜백 함수 호출
}

int main() {
    // perform_calculation 함수에 콜백 함수 print_result를 전달
    perform_calculation(5, 3, print_result);
    
    return 0;
}

```



#### 예시

#### void (*pfunc)(int, int) = &bts;

```c
#include <stdio.h>

void bts(int a, int b) {
    printf("hi");
}
int main(){
    int a = 123;
    void (*pfunc)(int, int) = &bts;   // ==  void (*pfunc)(int, int) = (void*)bts;
    pfunc(1,3);

   
    return 0;
}

```

#### int (*operation)(int, int);

```c
#include <stdio.h>

// 함수 선언
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0) {
        return a / b;
    }
    else {
        printf("Error: Division by zero\n");
        return 0;
    }
}

int main() {
    // 함수 포인터 선언
    int (*operation)(int, int); //괄호 중요

    int num1 = 10, num2 = 5;
    char operator = '+';

    // operator에 따라 다른 함수를 호출하도록 설정
    if (operator == '+') {
        operation = add;
    }
    else if (operator == '-') {
        operation = subtract;
    }
    else if (operator == '*') {
        operation = multiply;
    }
    else if (operator == '/') {
        operation = divide;
    }
    else {
        printf("Invalid operator\n");
        return -1;
    }

    // 함수 포인터를 통해 함수 호출
    int result = operation(num1, num2);
    printf("Result: %d\n", result);

    return 0;
}

```

<br>

#### void* op = (void*)add;

```c
#include <stdio.h>

// int형 값을 반환하는 함수
int add(int a, int b) {
    return a + b;
}

// void형 함수: int형 함수를 받는 함수
void callOperation(void* op, int a, int b) {
    // void* 포인터를 (int (*)(int, int)) 형식으로 캐스팅
    int (*operation)(int, int) = (int (*)(int, int))op;
    printf("Result: %d\n", operation(a, b));
}

int main() {
    // add 함수의 주소를 void* 포인터로 넘기기
    void* op = (void*)add;
    
    // callOperation 함수에서 void* 포인터를 사용하여 add 함수 호출
    callOperation(op, 5, 3);  // Result: 8 출력

    return 0;
}

```




<br>

```c
#include <stdio.h>
#include<conio.h>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    EVENT_CNT   //EventType의 총 개수 및 유효성 확인 위해
} EventType;

// 콜백 함수 타입 정의
typedef void (*EventHandler)(void); //반환 void, 인자 void, 함수 포인터 타입 정의

typedef struct {
    EventHandler handlers[EVENT_CNT];
}EventSystem;

void register_event_handler(EventSystem* system, EventType type, EventHandler handler) {
    if (type < EVENT_CNT) {
        system->handlers[type] = handler;
    }
}
void trigger_event(EventSystem* system, EventType type) {
    if (type < EVENT_CNT && system->handlers[type]) {
        system->handlers[type]();
    }
}

// 콜백 함수의 등록
//void button_click(ButtonCallback callback) {
void up_button_press(void (*callback)(void)) {
    //printf("up 버튼이 클릭되었습니다.\n");
    callback(); // 콜백 함수 호출
}

void down_button_press(void (*callback)(void)) {
    //printf("down 버튼이 클릭되었습니다.\n");
    callback(); // 콜백 함수 호출
}
void left_button_press(void (*callback)(void)) {
    //printf("down 버튼이 클릭되었습니다.\n");
    callback(); // 콜백 함수 호출
}void right_button_press(void (*callback)(void)) {
    //printf("down 버튼이 클릭되었습니다.\n");
    callback(); // 콜백 함수 호출
}
// 버튼이 눌렸을때 실제 동작 함수
void up_button_pressed() {
    printf("이벤트: up 버튼 클릭 처리가 완료되었습니다.\n");
}

void down_button_pressed() {
    printf("이벤트: down 버튼 클릭 처리가 완료되었습니다.\n");
}
void left_button_pressed() {
    printf("이벤트: left 버튼 클릭 처리가 완료되었습니다.\n");
}
void right_button_pressed() {
    printf("이벤트: right 버튼 클릭 처리가 완료되었습니다.\n");
}

void num_handler(int n) {

}
int main() {
    
    EventSystem system = { 0 };
    register_event_handler(&system, UP, up_button_pressed);
    register_event_handler(&system, DOWN, down_button_pressed);
    register_event_handler(&system, LEFT, left_button_pressed);
    register_event_handler(&system, RIGHT, right_button_pressed);

    trigger_event(&system, UP);
    trigger_event(&system, DOWN);
    trigger_event(&system, LEFT);
    trigger_event(&system, RIGHT);

    /*
    up_button_press(&up_button_pressed); // up 버튼 클릭 이벤트 등록
    down_button_press(&down_button_pressed);
    left_button_press(&left_button_pressed);
    right_button_press(&right_button_pressed);
    */

    char n = getch();
    printf("%c", n);
    //scanf("%d", &n);



    return 0;
}
```


<br>



#### 함수 포인터의 무수한 활용
: 코드를 나눠서 짤 수 있음 -> 독립적 개발


```c, main.c
//#include<stdio.h>
#include"tetris.h"


int main() {
    // 이벤트 시스템 초기화
    EventSystem system = { 0 };

    // 이벤트 핸들러 등록
    register_event_handler(&system, GAME_INIT, tetris_game_init);
    register_event_handler(&system, GAME_START, tetris_game_start);
    register_event_handler(&system, GAME_OVER, tetris_game_over);

    register_event_handler(&system, KEY_UP, tetris_key_up);
    register_event_handler(&system, KEY_DOWN, tetris_key_down);
    register_event_handler(&system, KEY_LEFT, tetris_key_left);
    register_event_handler(&system, KEY_RIGHT, tetris_key_right);
    register_event_handler(&system, KEY_FIRE, tetris_key_fire);
    register_event_handler(&system, KEY_BOMB, tetris_key_bomb);

    // 게임 시작
    trigger_event(&system, GAME_INIT);
    trigger_event(&system, GAME_START);

    // 키 입력 시뮬레이션
    trigger_event(&system, KEY_UP);
    trigger_event(&system, KEY_DOWN);
    trigger_event(&system, KEY_LEFT);
    trigger_event(&system, KEY_RIGHT);
    trigger_event(&system, KEY_FIRE);
    trigger_event(&system, KEY_BOMB);

    // 게임 종료
    trigger_event(&system, GAME_OVER);

    return 0;
}

```

<br>

```c, tetris.h
#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <stdio.h>

// 이벤트 타입 정의
typedef enum {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_FIRE,
    KEY_BOMB,
    GAME_INIT,
    GAME_START,
    GAME_OVER,
    EVENT_COUNT  // 총 이벤트 개수
} EventType;

// 콜백 함수 타입 정의
typedef void (*EventHandler)(void);

// 이벤트 시스템 구조체
typedef struct {
    EventHandler handlers[EVENT_COUNT];
} EventSystem;

void tetris_game_init(void);
void tetris_game_start(void);
void tetris_game_over(void);

void tetris_key_up(void);
void tetris_key_down(void);
void tetris_key_left(void);
void tetris_key_right(void);
void tetris_key_fire(void);
void tetris_key_bomb(void);

#endif


```

<br>

```c, tetris.c
#include "tetris.h"


// 이벤트 등록 함수
void register_event_handler(EventSystem* system, EventType type, EventHandler handler) {
	if (type < EVENT_COUNT) {
		system->handlers[type] = handler;
	}
}

// 이벤트 트리거 함수
void trigger_event(EventSystem* system, EventType type) {
	if (type < EVENT_COUNT && system->handlers[type]) {
		system->handlers[type]();
	}
}

void tetris_game_init(void) {
	printf("tetris initialized.\n");
}

void tetris_game_start(void) {
	printf("tetris started.\n");
}

void tetris_game_over(void) {
	printf("tetris game over...\n");
}

void tetris_key_up(void)		{ 
	printf("tetris up\n");	
}

void tetris_key_down(void)	{ 
	printf("tetris down\n"); 
}

void tetris_key_left(void)	{ 
	printf("tetris left\n");	
}

void tetris_key_right(void)	{ 
	printf("tetris right\n"); 
}

void tetris_key_fire(void)	{ 
	printf("tetris fire\n");	
}

void tetris_key_bomb(void)	{ 
	printf("tetris booom !!!\n"); 
}

```




