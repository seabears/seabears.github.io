---
title: 이더넷 통신 시스템
description: >-           #한 문장으로 나옴
  
date: 2025-03-24 09:14:54 +0900
lastmod : 2025-03-24 09:14:54 +0900  #마지막 수정 시간

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


##

한가닥 선
PWM, on/off

analog input은 한가닥에 노이즈

- **1대1 선**
  - 선 너무 많아짐 aCb
  - 복잡함

- FlexRay
  - 2006년 BMW X5
  - air 서스펜션에 사용
  - 비쌈

기존 유압에서
steer by wire
brake by wire

CAN은 스케줄링 안해서 단점임
직접 연겷해서 해결
local can

flex ram 쓸걸 local can으로 해결


메시지 ID 기반 우선순위 경쟁

can fd

Overclocking  of controlller area controllers 논문

standard can frame을 overclocked can frame
data length, data, crc : S zone : 빨리 보낼 수 있을 거 같음 -> 일방적으로 트랜시버가 쓰는 시간
나머지 M-zone : 속도 못바꿈 -> 트랜시버/리시버가 데이터를 주고 받아야함
나머지 500k 넘기면 안됨

혼자쓸 때는 500kbps아까움, 빠르게 해도 된다
-> can fd 2,4,8mbps
can 8바이트
can fd 64바이트


a : 0 0 0 0 0 1 0000  1보낼때 우선순위짐(bus상태 확인하고 나랑 다르니 receiver로)
b   : 0 0 0 0 0 0 0 1 0
bus : 0 0 0 0 0 0 0 1 0
0이 1을 이김
0은 3.5 1.5, 1은 2.5 2.5

crc
ack : transmitter에서 1쓰고 리시버가 0 쓰면 버스 0 돼서
트랜스미터가 버스를 확인하고 아 0이 됐구나 하고 잘 보내졌네 라고 인식


다른 리시버가 오류가 나서 1쓰려다가 버스에 0이라서 못쓰면
에러 프레임 발생 다시해!


트랜시버 두개의 시간 100ns
100미터 전선 500ns

1미터 5ns

min(T_prop_seg) = 2(500ns + 100ns) = 1.2us



Bosch 별별별

MOST
인포테인먼트용
이더넷으로 대체중

LVDS
카메라
2.5 Gbps

Ethernet
BMW
멀티미디어용



E/E 아키텍처
Central Gateway

Powertrain
동력 발생 장치에서 실제로 일을 하는 부품(바퀴), 동력을 전달하는 장치를 포함하여 지칭

동력 발생 장치 : 엔진, 모터 등
동력 전달 장치 : 변속기, 추진 축, 차동 기어 등

엔진 연료 분사 타이밍 제어 등 차량을 제어하기 위해 마이크로초 수준의 정확하고 빠른 센서 값을 읽을 수 있어야 함 (Complex Driver)

엔진 제어기 및 변속기 제어기 간의 효율적인 제어를 위해 ms초 수준(2~10ms)의 정확하고 빠른 정보 교환이 필요함 (CAN 통신 등)

CAN 8 byte : 130bit? -> 260us
ecu(엔진) <---can---> tcu(변속기)
10ms




샤시
차량 하중을 지탱하는 프레임워크
차체, 조향, 서스펜션, 브레이크 등

iso26262 asil
엔진 b
변속기 c

안전 관점에서 파워트레인보다 중요 -> Flex Ray
abs, steeringwheel


ADAS
Advanced Driver Assistance System
실시간, 대용량 데이터 전송 필요

HMI
Human Machine Interface



차량 요구사항의 변화
단순한 이동수단이 아닌 소유의 이유
빌려타는 것보다 이점이 있어야함
핸드폰을 빌려쓰는 게 아닌 본인 소유의 핸드폰을 더 선호하는 것처럼
차량이 핸드폰처럼 세팅을 갖고, 운전자가 만족감을 느낄 수 있게




제어기를 도메인별로 접접 합쳐감

도메인별로 제어기가 생김


도메인간 데이터 공유는 Central Gateway를 통하기에 정보 공유 시간이 오래걸림

전통적으로 도메인이 나눠져있음
자율주행 등장으로 모든 도메인을 나누는 게 아니라 다 같이 써야하고 필요함
도메인을 합치고자 함


CAN DB


기존
Domain 아키텍처
제어별 별도의 컨트롤러

Zonal 아키텍처
처량 내 고성능 연산 기능을 가진 vehicle computer와 고속/대용량 통신이 가능한 백본망 구축
하나의 컨트롤러(Zonal컨트롤러, ZCU)가 다양한 제어
물리적으로 거리가 가까운 ECU들끼리 클러스터링 구성
-> 도메인 아키텍처 대비  배선 무게 15~20% 감소, 구리선 가격도


다수의 제어기로 나누어진 기능을 하나의 고성능 컴퓨터로 통합

Linux가 유리 -> 무거워서 us단위 기능은 어려움
말단의 센서는 Autosar로
Linux가 여러가지 소프트웨어를 효율적으로 실행시키기 좋음




Flex Ray
TDMA(Time Division Multiple Access) 기반 시결정적 통신 지원
-> 기존 CAN이 가지고 있던 우선순위 경쟁으로 인해 우선순위가 낮은 메시지가 통신 지연이 발생하는 문제를 해결

제어기 CLK의 완벽 일치가 불가(크리스탈에 오차가 있음(제조편차))
->Flex Ray는 이걸 해결

CLK동기화로 모든 CLk를 맞추고 시작
시간을 완벽히 예약 (가격이 비쌈)
해당 시간에 해당 통신을 무조건 하게끔


Time Triggered System
- Flex Ray
- 정해진 시간에 ECU가 데이터 전송
-> 완벽한 시간이란 게 불가능한 단점
  -> Safety Margin으로 동기 오차 매꿈
    -> 낭비임
-> 비싼 가격

Event Triggered system
- CAN
- 모든 ECU는 원하는 시간에 데이터 전송


현대자동차는 Flex Ray 안씀
외국계는 씀
모비스나 만도는 외국계에도 납풉하니 씀


- LIN
  - Local Interconnect Network
  - 1999년 Motolora(현 NXP)에서 개발
  - CAN으로 연결된 제어기의 센서, 엑추에이터 제어 Local 통신으로 구성

  - 1가닥 통신 배선
  - 제어기별 풀업저항
  - 12V
  - 자동차 내에서 버튼 누르면 움직이는 것들
  - 싱글 마스터 기반 통신


can 500k
flexray 10mb
이더넷 100mb


시리얼 통신
한가닥
컴퓨터 - 컴퓨터 통신
통신 속도 필요


병렬 통신
8가닥
MCU내에서 cpu와 Peripheral 연결할 때


동기 전송
송/수신측 공통 클럭
SPI, JTAG 등
CLK이 전자파 발생함
SPI는 MCU 내부에 사용해서 괜찮
JTAG는 개발용이라 괜찮

비동기 전송
송/수신측 공통 클럭 없이


차량 대부분 비동기 통신


physical layer
0,1을 어떻게 물리적으로 표현할지 정의
명확한 기준
광통신 : 빛의 세기로 0,1
CAN 통신 : CAN_H, CAN_L의 전압차로 1,0 표현
이것보다 더 구체적으로 정의
통신 연결을 위한 커넥터 등도 정의
Ethernet RJ45 등

LIN 통신 물리 계층
배터리 12V
버스 전압(12V)의 60% 이상(7.2V) -> 1 Recessive
버스 전압의 40% 이하(4.8V) -> 0 Dominant
중간 값은 이전에 값(히스테리시스)


EMI, Electromagnetic Interface
전자파

EMC, Electromagnetic Compatibility
피해자, 가해자
Source : 전자기파를 방출하는 소스, 적게 방출하는 능력
Victim : 외부 전자기파에 대한 내성을 가지는 것









Bosch!!!


신기술에 대한 첫 적용 회사를 자부심





media access control

- 차 비싼 순
  - 엔진 
  - 샤시 
  - 케이블(자동화 안되고 사람이 직접 해야 함)

