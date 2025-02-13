---
title: CAN통신
description: >-           #한 문장으로 나옴

date: 2025-01-15 00:13:15 +0900
lastmod : 2025-01-15 00:13:15 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - 임베디드
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


## CAN통신

송신
```ino
#include <SPI.h>
#include <mcp_can.h>

// MCP2515 CS 핀 설정
MCP_CAN CAN0(10);

void setup() {
  Serial.begin(115200);

  // MCP2515 초기화 (500 kbps, 8 MHz 클럭)
  if (CAN0.begin(MCP_ANY, 500000, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 초기화 성공 (송신기)");
  } else {
    Serial.println("MCP2515 초기화 실패");
    while (1);
  }

  CAN0.setMode(MCP_NORMAL); // CAN 일반 모드 설정
  Serial.println("CAN 모듈 준비 완료");
}

void loop() {
  // 송신 데이터 (8바이트)
  byte data[8] = {0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70};

  // 메시지 송신 (ID: 0x100)
  if (CAN0.sendMsgBuf(0x100, 0, 8, data) == CAN_OK) {
    Serial.println("메시지 전송 성공");
  } else {
    Serial.println("메시지 전송 실패");
  }

  delay(5000); // 1초 대기
}
```

수신
```ino
#include <SPI.h>
#include <mcp_can.h>

// MCP2515 CS 핀 설정
MCP_CAN CAN0(10);

void setup() {
  Serial.begin(115200);

  // MCP2515 초기화 (500 kbps, 8 MHz 클럭)
  if (CAN0.begin(MCP_ANY, 500000, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 초기화 성공 (수신기)");
  } else {
    Serial.println("MCP2515 초기화 실패");
    while (1);
  }

  CAN0.setMode(MCP_NORMAL); // CAN 일반 모드 설정
  Serial.println("CAN 모듈 준비 완료");
}

void loop() {
  // 수신 데이터 저장용 변수
  long unsigned int rxId;
  unsigned char len = 0;
  unsigned char rxBuf[8];

  // 메시지 수신
  if (CAN0.checkReceive() == CAN_MSGAVAIL) {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    Serial.print("수신된 ID: 0x");
    Serial.println(rxId, HEX);

    Serial.print("데이터 길이: ");
    Serial.println(len);

    Serial.print("데이터: ");
    for (int i = 0; i < len; i++) {
      //Serial.print(rxBuf[i], HEX);
      Serial.print((char)rxBuf[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
```

