---
title: 라즈베리파이
description: >-           #한 문장으로 나옴

date: 2024-12-27 20:20:22 +0900
lastmod : 2024-12-27 20:20:22 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - 라즈베리파이
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

### 라즈베리파이


#### 정기적 업데이트
```bash
sudo apt update && sudo apt upgrade
```


#### 고정ip 설정

sudo vi /etc/dhcpcd.conf  : 네트워크 설정
```bash
hostname -I
sudo vi /etc/dhcpcd.conf
```

```bash
interface eth0
static ip_address=192.168.0.100/24
static routers=192.168.0.1
static domain_name_servers=192.168.0.1

interface wlan0
static ip_address=192.168.0.101/24
static routers=192.168.0.1
static domain_name_servers=192.168.0.1
```

| 항목                  | 설명                             |
| --------------------- | -------------------------------- |
| `ip_address`          | 설정할 고정 IP 주소              |
| `/24`                 | 서브넷 마스크 (255.255.255.0)    |
| `routers`             | 기본 게이트웨이 (라우터 IP 주소) |
| `domain_name_servers` | 도메인 이름을 IP 주소로 변환     |



DNS  
Domain Name System  
도메인 이름(예 : google.com) -> ip 주소로 변환
ex) 8.8.8.8

DDNS  
Dynamic Domain Name System  
동적으로 변하는 공인 IP 주소를 특정 도메인 이름에 매핑
ex) myhome.iptime.org



#### 기본 언어 한글로 설정

locale설정  
```bash
sudo vi /etc/locale.gen
# ko_KR.UTF-8 찾아서 주석 해제
```

```bash
sudo vi /etc/default/locale

# 아래 입력
LANG="ko_KR.UTF-8"
LC_CTYPE="ko_KR.UTF-8"

# 시스템 재부팅
sudo reboot

# locale 확인
locale
```


sudo update-alternatives --config editor

<br>

#### 기본 에디터 변경
```bash
~/.bashrc

# 추가
export EDITOR=vi
```

<br>

#### crontab 설정
```bash
crontab -e

# 추가
*/5 * * * * /bin/bash /home/woong/maint/temp/log_temp.sh
```


#### vi 설정
```bash
vi ~/.vimrc

# 내용 추가

" 기본 설정
set number      "줄번호
highlight LineNr ctermfg=darkgreen ctermbg=NONE

set mouse=a     "마우스로 커서 이동

set tabstop=4   "탭을 4칸으로
set expandtab   "탭을 공백으로

syntax on       "구문 강조


" 검색 설정
set hlsearch    " 검색어 하이라이트

```