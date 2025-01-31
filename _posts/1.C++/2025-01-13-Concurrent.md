---
title: Concurrent
description: >-           #한 문장으로 나옴
  This is Concurrent
  Write your description here.
date: 2025-01-13 12:38:54 +0900
lastmod : 2025-01-13 12:38:54 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - C++
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


### Concurrent
Write your content here.

## Concurrent API

`#include<thread>` : 스레드 생성 및 조작
`#include<mutex>` : 멀티 스레드 환경 동기화
`#include<condition_variable>` : 조건 변수


std::thread 클래스는 스레드를 생성하고 관리하는 데 사용됩니다.
주요 함수 및 메서드:
std::thread(ThreadFunc&& func, Args&&... args) : 스레드 생성
join() : 스레드가 종료될 때까지 기다림
detach() : 스레드가 종료되더라도 종료 대기 없이 관리에서 해제됨


std::mutex 클래스는 멀티 스레드 환경에서 동기화를 위한 객체입니다.
주요 함수 및 메서드:
lock() : 뮤텍스를 획득
unlock() : 뮤텍스를 해제
std::lock_guard<std::mutex> : 자동으로 뮤텍스를 잠금 해제하는 스마트 포인터


std::condition_variable 클래스는 스레드 간의 동기화를 위한 객체로, 특정 조건이 만족될 때까지 스레드를 잠시 멈출 수 있게 해줍니다.
주요 함수 및 메서드:
wait(std::unique_lock<std::mutex>& lock) : 특정 조건이 충족될 때까지 스레드를 잠금
notify_one() : 하나의 스레드에게 조건이 충족되었음을 알림
notify_all() : 모든 스레드에게 조건이 충족되었음을 알림




```cpp
#include <iostream>
#include <thread>

void task1(const std::string& name) {
    for (int i = 0; i < 5; ++i) {
        std::cout << name << " 가 작업을 수행중입니다." << i << "\n";
        std::this_thread::yield(); // 다른 스레드에게 CPU 양보
    }
}

void task2(const std::string& name) {
    for (int i = 0; i < 5; ++i) {
        std::cout << name << " 가 작업을 수행중입니다." << i << "\n";
        std::this_thread::yield(); // 다른 스레드에게 CPU 양보 (1)
    }
}

int main() {
    std::thread t1(task1, "Thread 1");
    std::thread t2(task2, "Thread 2");

    t1.join();
    t2.join();

    return 0;
}
```

![cmd 출력](/_posts/1.C++/Concurrent1.png)

```cmd
Thread 1 가 작업을 수행중입니다.0
Thread 2 가 작업을 수행중입니다.0
Thread 1 가 작업을 수행중입니다.1
Thread 2Thread 1 가 작업을 수행중입니다.2
 가 작업을 수행중입니다.1
Thread 1 가 작업을 수행중입니다.3
Thread 1 가 작업을 수행중입니다.4
Thread 2 가 작업을 수행중입니다.2
Thread 2 가 작업을 수행중입니다.3
Thread 2 가 작업을 수행중입니다.4
```




