#!/bin/bash

# _posts 디렉토리 경로
posts_dir="_posts"

# _posts 디렉토리 내의 모든 하위 디렉토리 순회 (카테고리 폴더)
for category_dir in "$posts_dir"/*/; do
    # 폴더인지 확인
    if [ -d "$category_dir" ]; then
        # 카테고리 폴더 이름 추출
        category_name=$(basename "$category_dir")
        
        # 카테고리 폴더 내의 모든 .md 파일 순회
        for md_file in "$category_dir"*.md; do
            # md 파일 내 categories 항목을 폴더 이름으로 변경 후, 그 다음 줄에 카테고리 이름 추가
            if [ -f "$md_file" ]; then
                # sed를 사용하여 'categories: # 카테고리' 항목을 해당 카테고리로 변경
                sed -i "/^categories:[[:space:]]*#[[:space:]]*카테고리/ {
                    s/^categories:[[:space:]]*#[[:space:]]*카테고리/categories: # 카테고리/
                    a\
    - $category_name
                }" "$md_file"
                echo "Updated categories in $md_file to $category_name"
            fi
        done
    fi
done
