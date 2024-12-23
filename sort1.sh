#!/bin/bash

# _posts 디렉토리 경로
posts_dir="_posts"

# 수정하지 않을 폴더 지정
exclude_folders=("start(no_use)" "z_No_post" "z_template")

# _posts 디렉토리 내의 모든 하위 디렉토리 순회 (카테고리 폴더)
for category_dir in "$posts_dir"/*/; do
    # 폴더인지 확인
    if [ -d "$category_dir" ]; then
        # 카테고리 폴더 이름 추출
        category_name=$(basename "$category_dir")
        
        # 제외할 폴더인지 확인
        if [[ " ${exclude_folders[@]} " =~ " ${category_name} " ]]; then
            echo "Skipping folder: $category_name"
            continue
        fi
        
        # 카테고리 폴더 내의 모든 .md 파일 순회
        for md_file in "$category_dir"*.md; do
            # md 파일 내 categories 항목을 찾고, 현재 카테고리 목록과 비교
            if [ -f "$md_file" ]; then
                # 기존 categories 항목을 가져오기 (categories 항목이 두 번째 줄 이후에 있을 때)
                current_categories=$(sed -n '/^categories:/,/^$/p' "$md_file" | tail -n +2)
                
                # 카테고리 목록에 해당 카테고리 이름이 없는 경우
                if [[ "$current_categories" != *"$category_name"* ]]; then
                    # sed를 사용하여 'categories: # 카테고리' 항목을 해당 카테고리로 변경하고, 그 다음 줄에 카테고리 이름 추가
                    sed -i "/^categories:/ {
                        n
                        s/^/    - $category_name\n/
                    }" "$md_file"
                    echo "Updated categories in $md_file to $category_name"
                else
                    : #echo "No update needed in $md_file, categories are already correct"
                fi
            fi
        done
    fi
done
