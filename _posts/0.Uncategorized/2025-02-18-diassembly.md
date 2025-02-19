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


### 1. diassembly

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


### 2. Register 직접 접근 vs iLLD
iLLD : Infineon Low Level Driver  

```c
    while(1)
    {
        P10_OUT.U = 0x1 << 2;
        IfxPort_setPinHigh(IfxPort_P10_2.port, IfxPort_P10_2.pinIndex);

    }
```

```c
54            while(1)
80000094:   j  "Cpu0_Main.c"::54 (0x800000BC)
/*------------------Register----------------------*/
56                P10_OUT.U = 0x1 << 2;
80000096:   mov  d15,0x04
80000098:   movh.a  a15,0xF004
8000009c:   st.w  [a15]-0x5000,d15
/*------------------iLLD----------------------*/
57                IfxPort_setPinHigh(IfxPort_P10_2.port, IfxPort_P10_2.pinIndex);
800000a0:   movh.a  a15,0x6000
800000a4:   lea  a15,[a15]0x0004
800000a8:   ld.a  a15,[a15]
800000aa:   movh.a  a2,0x6000
800000ae:   lea  a2,[a2]0x0004
800000b2:   ld.bu  d15,[a2],0x04
568           IfxPort_setPinState(port, pinIndex, IfxPort_State_high);
800000b4:   mov  d0,0x01
592           port->OMR.U = action << pinIndex;
800000b6:   sha  d0,d0,d15
800000ba:   st.w  [a15],0x04,d0
54            while(1)
800000bc:   j  "Cpu0_Main.c"::56 (0x80000096)
```

```c
    while(1)
    {
        P10_OMR.U = 0x60006;

        P10_OUT.U = 0x1 << 2;

        P10_OUT.U = 0x1 << IfxPort_P10_2.pinIndex;
        IfxPort_P10_2.port->OMR.U = 1 << IfxPort_P10_2.pinIndex;
        IfxPort_setPinHigh(IfxPort_P10_2.port, IfxPort_P10_2.pinIndex);
    }
```

```c
 67               P10_OMR.U = 0x60006;
80000360:   mov  d15,0x06
80000362:   addih  d15,d15,0x0006
80000366:   movh.a  a15,0xF004
8000036a:   st.w  [a15]-0x4FFC,d15
 69               P10_OUT.U = 0x1 << 2;
8000036e:   mov  d15,0x04
80000370:   movh.a  a15,0xF004
80000374:   st.w  [a15]-0x5000,d15
 71               P10_OUT.U = 0x1 << IfxPort_P10_2.pinIndex;
80000378:   mov  d0,0x01
8000037a:   movh.a  a15,0x6000
8000037e:   lea  a15,[a15]0x0004
80000382:   ld.bu  d15,[a15],0x04
80000384:   sha  d0,d0,d15
80000388:   movh.a  a15,0xF004
8000038c:   st.w  [a15]-0x5000,d0
 72               IfxPort_P10_2.port->OMR.U = 1 << IfxPort_P10_2.pinIndex;
80000390:   movh.a  a15,0x6000
80000394:   lea  a15,[a15]0x0004
80000398:   ld.a  a15,[a15]
8000039a:   mov  d0,0x01
8000039c:   movh.a  a2,0x6000
800003a0:   lea  a2,[a2]0x0004
800003a4:   ld.bu  d15,[a2],0x04
800003a6:   sha  d0,d0,d15
800003aa:   st.w  [a15],0x04,d0
 73               IfxPort_setPinHigh(IfxPort_P10_2.port, IfxPort_P10_2.pinIndex);
800003ac:   movh.a  a15,0x6000
800003b0:   lea  a15,[a15]0x0004
800003b4:   ld.a  a15,[a15]
800003b6:   movh.a  a2,0x6000
800003ba:   lea  a2,[a2]0x0004
800003be:   ld.bu  d15,[a2],0x04
568           IfxPort_setPinState(port, pinIndex, IfxPort_State_high);
800003c0:   mov  d0,0x01
592           port->OMR.U = action << pinIndex;
800003c2:   sha  d0,d0,d15
800003c6:   st.w  [a15],0x04,d0
```

Register 직접 접근과 iLLD의 asm 코드는 같음  
보이기에 같은 동작이라도 어떤 Register을 제어하냐에 따라 세부적인 동작이 다르기에 asm 코드가 다름  



### 3. inline assembly
```c
    while(1)
    {
        __asm__(
                "movh.a      a15, #0xf004      \n\t"
                "ld.w        d15, [a15] - 0x5000 \n\t"
                "xor         d15, d15, #0x6  \n\t"
                "st.w        [a15] - 0x5000, d15 \n\t"
                :
                :
                : "a15", "d15"
            );
        __asm__(
                "mov         d0, #0x6  \n\t"
                "addih       d0, d0, #0x6      \n\t"
                "movh.a      a15, #0xf004      \n\t"
                "st.w        [a15] - 0x4ffc, d0 \n\t"
                :
                :
                : "a15", "d0"
            );
    }
```




