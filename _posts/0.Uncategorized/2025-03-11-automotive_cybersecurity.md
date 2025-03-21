---
title: 🔒 Automotive Cybersecurity 정리중
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
published: true        # true | false
---

## 자동차 사이버 보안 개요  

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
  - 정의 단계 : What  
    - 1. 타당성 검토  
    - 2. 개발 계획  
    - 3. `요구사항 분석`  
  - 개발 단계 : How  
    - 4. `설계`  
    - 5. `개발`  
    - 6. `테스트`  
  - 유지보수 단계 : Change  
    - 7. `유지보수`  
    - 8. 폐기  

<br>

[소프트웨어 보안약점 진단가이드](https://www.kisa.or.kr/2060204/form?postSeq=9&page=1)  

[소프트웨어 개발 보안 가이드](https://www.kisa.or.kr/2060204/form?postSeq=5&page=1)  

<br>

- 🔓 **보안 취약 사례**  
  - [Log4j](https://namu.wiki/w/Log4j%20%EB%B3%B4%EC%95%88%20%EC%B7%A8%EC%95%BD%EC%A0%90%20%EC%82%AC%ED%83%9C#s-2.1)  
  - 이니세이프 공급망 공격  

<br>

- SBOM : SW Bill of Materials  
  - SW 공급망위협관리를 위한 투명한 SW 구성요소 정보 제공  

<br>

birthday paradox
생일이 모두 다를 확률을 생각하면 됨
1-(365/365 * 364/365 * 363/365 ... ) < 0.5
23명이 모이면 생일이 겹칠 확률이 50%가 넘는다


## 

- **String**



##

- Dynamic allocation  
  - safety-critical systems에서는 사용하지 않는다  

##

- 펌웨어 이미지 획득
  - JTAG (Joint Test Action Group)
    - 임베디드 기기 대상 디버깅에 사용되는 표준 장비
    - 비휘발성 메모리의 데이터(펌웨어) 추출 기능 제공
  - UART (범용 비동기화 수신기)
    - JTAG에 비해 간단하고 저렴
    - 디버깅용도로 이용
  
- 펌웨어 분석
  - 특징
    - 바이너리 실행 파일 분석 과정과 매우 유사
    - 하드웨어와 연동되어 동작, 분석 환경 조성이 필요
  - 정적 분석
    - 바이너리 및 소스 코드 파일 대상
  - 동적 분석
    - 펌웨어의 실제 동작(HW 입력 등)을 에뮬레이터를 이용하며 확인, 분석 수행
    - 사용자 입력/네트워크 입력에 대한 펌웨어의 처리 과정과 결과 확인
  

---

## Cybersecurity  

### 1. Cybersecurity Overview  
iso21434

시중 차량 중 다수가 무선 기술 적용  
주행 기록 및 차량 성능에 대한 많은 양의 데이터 수집 중  

2015년 8월, Jeep와 Fiat Chrysler 자동차를 원격 해킹하여 와이퍼 이상 동작 및 엔진 정지하는 모습을 시연  
-> 차량 140만대 리콜(Fiat Chrysler), 자동차 사이버보안 법 제정 준비 시작(미국)


SAE J3061


ISO 21434 : 사이버 보안 엔지니어링  
ISO/PAS 5112 : 사이버 보안 심사 가이드라인  




cl은 프로젝트 단위로만, 회사 전체 단위가 아님
cl3 받았다는 건, 그 프로젝트가 cl3를 받았다는 것, 다른프로젝트는 모름

a-spice pm 개발단계에서의 활동만 고려
pm이 프로세스 매니지먼트인듯

아키텍터 (sw를 총괄)가 별로 없음
보통 해당 작업만 계속하는 경향(캔 통신만 계속 만들거나)
전체를 아우르는 사람이 거의 없음


오토에버는 모빌진(소프트웨어 플랫폼) 파는 회사
다른 협력업체가 가져다 씀

다른 사람들이 무슨일을하는지 알아야 pm 잘할수있

pm을 잘 알아봐야겠네


TARA :Threat Analysis and Risk Assessment 사이버보안 위협 분석


- SW 요구사항 : 
  - 1. 기능 :  
    - 소프트웨어가 수행해야 하는 기능적인 동작  
    - ➡️ **무엇을  해야 하는가**  
  - 2. 비기능 :   
    - 수행 방식, 응답속도, 성능, 보안 등  
    - ➡️ **어떻게 해야 하는가**  


OTA
ISO/CD 24089 이거 말고 새로나온 게 있음

tara  

- Risk Treatment Decision  
  - 1. avoiding the risk (위험 요소 제거)  
  - 2. rdeucing the risk  
  - 3. sharing the risk  
  - 4. retaining the risk   


ISO : 국제 표준화 기구
SAE : 자동차 공학회

- ISO/SAE 21434 (Cybersecurity Engineering)
  - 자동차 산업에서 사이버 보안을 보장하기 위한 국제 표준  
  - 사이버 보안 엔지니어링을 위한 표준
  - ex)
    - 사이버 보안 관리(조직, 프로젝트)(CSMS, Cybersecurity Management System)
    - 지속적인 사이버 보안 활동
    - 분산개발 사이버 보안 활동
    - 위험 평가 방법론(TARA, Threat Analysis and Risk Assessment)
    - 엔지니어링 프로세스(개념, 개발, 생산, 운영 및 유지보수, 폐기)


asset : 가치 있는 자원, 보호가 필요한 대상
item : 특정한 시스템 또는 요소, 넓은 개념

---

참고문헌
[ISO 21434 통한 실질적 사이버 보안 대응](https://www.autoelectronics.co.kr/article/articleView.asp?idx=4655)  


