#!/bin/bash

# 현재 날짜와 시간을 변수에 저장
current_date=$(date +"%Y-%m-%d")
current_time=$(date +"%H:%M:%S")
timezone="+0900"

# 블로그 게시물 기본 디렉터리 설정
posts_dir="_posts"
default_dir="0.Uncategorized"

# 게시물 제목 입력받기
echo "Enter the post title:"
read post_title

# 제목에서 공백을 대시(-)로 변경하여 파일명 생성
file_title=$(echo "$post_title" | tr ' ' '-')

# 파일 경로 생성
post_file="$posts_dir/$default_dir/$current_date-$file_title.md"

# 게시물 템플릿 작성
cat << EOF > $post_file
---
title: $post_title
description: >-           #한 문장으로 나옴
  This is $post_title
  Write your description here.
date: $current_date $current_time $timezone
lastmod : $current_date $current_time $timezone  #마지막 수정 시간

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
published: true        # true | false
---

### $post_title

#### sub_title
Write your content here.

EOF
#여기까지

# 결과 출력
echo "New post created: $post_file"