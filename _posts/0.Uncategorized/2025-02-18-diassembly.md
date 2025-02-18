---
title: diassembly
description: >-           #한 문장으로 나옴
  
date: 2025-02-18 17:07:29 +0900
lastmod : 2025-02-18 17:07:29 +0900  #마지막 수정 시간

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
published: false        # true | false
---


## diassembly

```c
    P10_IOCR0.U &= ~(0x1F<<19);
    P10_IOCR0.U |= (0x10<<19);

    while(1)
    {
        P10_OUT.U = 0x1 << 2;

    }
```


### diassembly

```c
47            P10_IOCR0.U &= ~(0x1F<<19);
8000006c:   movh.a  a15,0xF004        // a15 = 0xF0040000
80000070:   ld.w  d15,[a15]-0x4FF0    // d15 = *(0xF0040000 - 0x4FF0) → P10_IOCR0 값 읽기
80000074:   insert  d15,d15,0x00,0x13,0x05  // d15의 19번 비트부터 5비트를 0으로 변경
80000078:   movh.a  a15,0xF004        // a15 = 0xF0040000 (재설정)
8000007c:   st.w  [a15]-0x4FF0,d15    // *(0xF0040000 - 0x4FF0) = d15 → P10_IOCR0 값 저장

48            P10_IOCR0.U |= (0x10<<19);
80000080:   movh.a  a15,0xF004        // a15 = 0xF0040000
80000084:   ld.w  d15,[a15]-0x4FF0    // d15 = *(0xF0040000 - 0x4FF0) → P10_IOCR0 값 읽기
80000088:   insert  d15,d15,0x01,0x17,0x01  // d15의 23번 비트부터 1비트를 1로 변경 (0x10 << 19 적용)
8000008c:   movh.a  a15,0xF004        // a15 = 0xF0040000 (재설정)
80000090:   st.w  [a15]-0x4FF0,d15    // *(0xF0040000 - 0x4FF0) = d15 → P10_IOCR0 값 저장

51            while(1)
80000094:   j  "Cpu0_Main.c"::51 (0x800000A0)  // 무한 루프 (Jump to 0x800000A0)

53                P10_OUT.U = 0x1 << 2;
80000096:   mov  d15,0x04             // d15 = 0x04 (0x1 << 2)
80000098:   movh.a  a15,0xF004        // a15 = 0xF0040000
8000009c:   st.w  [a15]-0x5000,d15    // *(0xF0040000 - 0x5000) = d15 → P10_OUT 설정

51            while(1)
800000a0:   j  "Cpu0_Main.c"::53 (0x80000096)  // 무한 루프 (Jump to 0x80000096)

56        }
800000a2:   ret                        // 함수 종료 (return)
```

a15 : address register  
d15 : data register  


PORT 10 주소 : Port 10 F003 B000H -F003 B0FFH  

모든 PORT(~40) 끝나고 다음 SEGMENT 시작 주소 : F004 0000H  


