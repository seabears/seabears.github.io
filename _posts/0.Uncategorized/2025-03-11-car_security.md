---
title: 🔒 car_security
description: >-           #한 문장으로 나옴
  
date: 2025-03-11 09:08:37 +0900
lastmod : 2025-03-11 09:08:37 +0900  #마지막 수정 시간

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


- 📌 **Key Security Concepts : CIA triad**  
  - 1. Confidentiality (기밀성)  
    - 허가된 사용자만 데이터 접근, 그외에 제한  
  - 2. Integrity (무결성)  
    - 부적절한 수정을 막음  
    - 해시 함수(SHA-256, SHA-512 등) 이용  
  - 3. Availability (가용성)  
    - 필요할 때 접근이 가능해야 함  
    - Dos 공격 등이 있음

<br>

- 📌 **Additional Security Concepts : AAA**
  - 1. Authentication (인증)  
    - 사용자를 확인  
  - 2. Authorization  (인가)  
    - 사용자가 특정 동작 수행을 허용하는지  
  - 3. Accounting (측정)  
    - 사용자의 행동을 추적하고 기록, 측정  

<br>

- 📌 **Security Concepts and Relationships**  
![security_img1](https://github.com/user-attachments/assets/e725bd49-0e40-418a-b2c2-4b4bb858b30c)

<br>

- 📌 **보안 위협별 대응 기술**  
  - 1. 차량
    - 펌웨어 변조 -> HSM
    - CAN 위변조 -> IDS

<br>

- 📌 **소프트웨어 개발 생명 주기**  
  - 정의 단계  
    - 1. 타당성 검토  
    - 2. 개발 계획  
    - 3. `요구사항 분석`  
  - 개발 단계  
    - 4. `설계`  
    - 5. `개발`  
    - 6. `테스트`  
  - 유지보수 단계  
    - 7. `유지보수`  
    - 8. 폐기  

<br>




birthday paradox
생일이 모두 다를 확률을 생각하면 됨
1-(365/365 * 364/365 * 363/365 ... ) < 0.5
23명이 모이면 생일이 겹칠 확률이 50%가 넘는다

