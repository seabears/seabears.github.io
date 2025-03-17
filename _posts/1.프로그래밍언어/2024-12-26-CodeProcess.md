---
title: 코드 실행 과정
description: >-           #한 문장으로 나옴

date: 2024-12-26 17:14:12 +0900
lastmod : 2024-12-26 17:14:12 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - 0.Uncategorized  
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


### 코드 실행과정
소스코드(.c) -> 전처리(.i) -> 컴파일(.s) -> 어셈블(.o) -> 링크 -> 빌드

전처리 : 전처리 과정
컴파일 : 
링크 : 라이브러리 함수, 외부 파일 연결



#### 전처리

헤더파일, 매크로 중복 선언 방지(한번만 include)
헤더파일 전체 내용 긁어옴(컴파일 단계에서 필요 없는 내용 제거)

```c
#pragma once  //이것보다 아래 ifndef define ~ endif 사용하기
```

헤더파일(.h) 이렇게 쓰는 게 좋음
```c 표준(권장)
//example.h
#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "hello.h"
void some_function();

#endif
```

<br>

매크로
전처리 과정에서 그자리로 들어감(텍스트 치환)
```c
#define A 100

int a = A;
```


매크로 함수 컴파일 단계 최적화 x

inline 함수 


```c
#define mypow(n) (n*n)

int ans1 = mypow(2+2)  //(2+2*2+2)

int ans2 = mypow((2+2)) //(2+2)*(2+2)   //원하는 결과

#define mypow2(n) n*n

int ans3 = mypow(2+2) //(2+2*2+2)
```

short circuit evaluation




#### 컴파일

헤더 파일은 직접적(독립적)으로 컴파일 x

소스 파일을 통해 간접적으로 컴파일 o


---
소스코드

📌 Relocatable(재배치 가능 코드)  
: 코드가 특정 주소에 고정되지 않고, 원하는 메모리 주소에 배치될 수 있는 형태  
🚀 여러 개의 오브젝트 파일을 합쳐서 원하는 메모리 영역에 배치할 수 있도록 하기 위해 사용  

📌 Locator(주소 할당)  
: Relocatable 코드가 특정 메모리 주소에 배치  
링커(Linker)가 오브젝트 파일(.o)를 결합하여 최종 실행 가능한 주소를 할당(.elf)  
링커 스크립트(.ld)를 사용하여 ROM, RAM, Flash 등의 메모리 영역을 설정 가능  
🚀 Relocatable 파일을 실제 하드웨어 환경에 맞게 적절한 주소로 변환하는 과정  

📌 Executable(실행 파일)  
: Relocatable 코드가 Locator를 거쳐 실제 메모리 주소를 할당받고 실행 가능한 상태(.hex, .bin, .elf)  
🚀 실제 하드웨어에 배포되어 실행됨  

---
📌 임베디드 SW 개발 흐름
1️⃣ 소스 코드 작성 → 2️⃣ 컴파일 (Relocatable 오브젝트 생성) → 3️⃣ 링킹 & 주소 배치 (Locator) → 4️⃣ 실행 파일 생성 (Executable) → 5️⃣ Flash에 업로드 후 실행 🚀