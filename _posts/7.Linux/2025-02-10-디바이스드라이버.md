---
title: 디바이스드라이버
description: >-           #한 문장으로 나옴
  
date: 2025-02-10 10:47:37 +0900
lastmod : 2025-02-10 10:47:37 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - Linux  
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


## 디바이스 드라이버

디바이스 드라이버(Device Driver)는 운영 체제와 하드웨어 간의 인터페이스 역할을 하는 소프트웨어  
리눅스에서 커널 모듈(kernel module, `.ko`(kernel object) ) 형태로 동작  

---

### 1. 문자(Char) 디바이스 드라이버  

#### 특징
- 데이터를 바이트 단위로 입출력  
- 키보드 입력, 마우스 이벤트, 시리얼 포트 등의 장치 제어  
- 버퍼링 사용 x, 즉시 데이터 처리  

---

### 2. 블록(Block) 디바이스 드라이버  

#### 특징  
- 데이터를 블록(512B, 4KB 등) 단위로 입출력  
- 주로 디스크 장치(HDD, SSD, USB, SD 카드) 등에서 사용  
- 버퍼링 및 캐싱을 지원, 성능 최적화 가능  

---

### 3. 네트워크(Network) 디바이스 드라이버  

#### 특징
- 네트워크 패킷 송수신을 처리  
- TCP/IP 스택과 직접 통신  
- `eth0`, `wlan0` 같은 네트워크 인터페이스 제공  

---



### 예제

hello.c  
```c
#include <linux/module.h> // 모듈 관련 헤더
#include <linux/kernel.h> // printk 함수 사용

MODULE_LICENSE("GPL"); // 라이센스 지정, 필수

// 모듈이 로드될때 실행되는 함수
static int __init hello_init(void) {
	printk(KERN_INFO "Hello, Device Driver Loaded.\n");
	return 0;
}

// 모듈이 언로드 될때 실행되는 함수
static void __exit hello_exit(void) {
	printk(KERN_INFO "Goodbye, Device Driver Unloaded.\n");	
}

module_init(hello_init); // 초기화 함수 등록
module_exit(hello_exit); // 종료 함수 등록
```

Makefile  
```Makefile
obj-m += hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

```

$  
```bash
sudo apt install linux-headers-$(uname -r)
```

커널에 로드  
```bash
sudo insmod hello.ko
```

언로드  
```bash
sudo rmmod hello
```

로그 확인  
```bash
dmesg | tail
```

