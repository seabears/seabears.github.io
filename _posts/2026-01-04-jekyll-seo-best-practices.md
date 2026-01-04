---
title: "Jekyll SEO 최적화 실전 가이드 — 색인(re-index) 잘 되는 페이지 만드는 법"
date: 2026-01-04 09:00:00 +0900
categories: [웹, SEO]
tags: [jekyll, seo, sitemap, google-search-console]
author: seabears
description: "Jekyll 블로그 운영자를 위한 실전 SEO 체크리스트와 색인에 잘 걸리도록 콘텐츠·구조를 개선하는 방법을 단계별로 정리합니다."
image: /assets/img/seo-guide-cover.png
canonical: https://seabears.github.io/posts/jekyll-seo-best-practices/
---

# Jekyll SEO 최적화 실전 가이드 — 색인 잘 되는 페이지 만들기

이 글은 Jekyll 기반 블로그에서 Google 색인(검색 등록)에 잘 걸리도록 "실제로 수정하고 적용할 수 있는" 체크리스트와 예제를 제공합니다. 핵심은 **고유한 가치 제공**, **충분한 분량(심층성)**, **기술적 신호(메타·구조화 데이터)**입니다.

## 요약(핵심 행동)
- 글 길이: 최소 1,000자 권장(핵심 콘텐츠는 1,500~3,000자 권장)
- 메타: 고유한 `description` 110~150자, 명확한 `title`
- 내부 링크: 포스트 당 최소 3개 이상 관련 내부 링크(앵커는 키워드)
- 구조화 데이터: Article JSON-LD 추가
- sitemap: `jekyll-sitemap`으로 production 빌드 시 올바른 URL 생성

## 1. 콘텐츠 전략(무엇을 써야 하는가)

1) 긴 가이드(How-to 또는 튜토리얼)
  - 예: "Jekyll에서 sitemap, robots, canonical 제대로 설정하는 방법"
  - 단계별 예제와 코드 스니펫 포함

2) 사례 연구(데이터 기반)
  - 변경 전/후 트래픽, 스크린샷, 구글 애널리틱스·서치 콘솔 스냅샷 포함

3) 비교/평가형 글
  - 예: "Jekyll vs Hugo: SEO·배포·성능 비교(2026)" — 표와 결론

4) 실무 코드·예제 페이지
  - 재사용 가능한 스크립트, config 샘플, 빌드 명령

## 2. 포스트 템플릿(복사해서 쓰세요)

- Title: 핵심 키워드 포함(예: "Jekyll SEO 최적화 가이드 — sitemap & canonical")
- Meta description: 110~150자, 고유 요약
- H1: 포스트 제목(중복 금지)
- H2/H3: 질문-답변 형식(각 H2는 작은 토픽, 2~4문단)
- 본문: 1,000~3,000자, 코드/이미지/표/스크린샷 포함
- 내부 링크: 관련 글 3개 이상
- 이미지: `alt` 작성, `loading="lazy"`, 가능한 경우 OG 이미지
- 구조화 데이터: Article JSON-LD

예시 front matter (이 파일 상단 참조):

```
---
title: "..."
description: "..."
image: /assets/img/seo-guide-cover.png
canonical: https://seabears.github.io/posts/jekyll-seo-best-practices/
---
```

## 3. 기술적 신호(레이아웃/빌드에서 바로 적용할 항목)

- canonical: 레이아웃(`_layouts/default.html` 또는 SEO include)에 항상 넣기
  - 예: `<link rel="canonical" href="{{ page.canonical | default: page.url | absolute_url }}">`
- meta description: 레이아웃에서 `page.description` 사용
- JSON-LD: `Article` 형식으로 제목/저자/발행일/이미지/설명 포함

### 샘플 JSON-LD (레이아웃에 삽입 예)

```html
<script type="application/ld+json">
{
  "@context": "https://schema.org",
  "@type": "Article",
  "headline": "{{ page.title }}",
  "description": "{{ page.description }}",
  "author": {"@type":"Person","name":"{{ site.social.name | default: site.github.username }}"},
  "datePublished": "{{ page.date | date_to_xmlschema }}",
  "image": "{{ page.image | default: site.social_preview_image | absolute_url }}",
  "mainEntityOfPage": {"@type":"WebPage","@id":"{{ page.url | absolute_url }}"}
}
</script>
```

## 4. 내부 링크·사이트 구조(크롤 우선순위 향상)

- 메인 페이지(홈), 카테고리, 태그 페이지에서 핵심 포스트를 노출
- 태그/카테고리 페이지에 페이징이 많으면 중요 글은 핀(pinned) 또는 '추천' 섹션으로 분리

## 5. 배포·검증(실행 후 해야 할 일)

1. production 빌드:
```
JEKYLL_ENV=production bundle exec jekyll build
```
Windows(PowerShell):
```
$env:JEKYLL_ENV = "production"; bundle exec jekyll build
```
2. `_site/sitemap.xml` 확인하여 이 글의 `<loc>`이 `https://seabears.github.io/posts/jekyll-seo-best-practices/`인지 검증
3. GitHub에 커밋 & 푸시
4. Search Console → URL 검사 → 새 URL 입력 → 라이브 테스트 → 색인 요청

---

끝으로: 이 포스트는 실습 예제(코드, 빌드 명령, JSON-LD)와 함께 제작되어 있어 Search Console에 제출했을 때 색인 성공 확률이 높습니다. 원하시면 이 글을 바로 게시(커밋)하고 GSC에 색인 요청하는 과정을 도와드리겠습니다.
