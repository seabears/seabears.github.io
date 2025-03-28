---
title: Solid 원칙
description: >-           #한 문장으로 나옴
  C++
date: 2025-01-10 09:02:21 +0900
lastmod : 2025-01-10 09:02:21 +0900  #마지막 수정 시간

author: "seabears"      # 작성자

categories: # 카테고리
    - C++
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

## Solid 원칙
객체 지향 프로그래밍의 5가지 설계 원칙  

### 1. 단일 책임 원칙 Single Responsibility Principle, SRP
클래스는 단 하나의 책임만 가져야 한다.

#### 예제

파일 읽기와 쓰기 기능을 동시에 가지는 클래스

<br>

<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">적용 전 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```c++
#include <iostream>
#include <string>
using namespace std;

class FileManager {
public:
    void writeToFile(const string& filename, const string& data) const {
        cout << "Writing data to file: " << filename << endl;
        cout << "Data: " << data << endl;
    }

    string readFromFile(const string& filename) const {
        cout << "Reading data from file: " << filename << endl;
        return "Dummy data"; // 실제 파일 읽기 대신 가상 데이터 반환
    }
};

int main() {
    FileManager fileManager;

    string filename = "example.txt";
    string data = "Hello, SRP Example!";

    // 파일 쓰기
    fileManager.writeToFile(filename, data);

    // 파일 읽기
    string readData = fileManager.readFromFile(filename);
    cout << "Read Data: " << readData << endl;

    return 0;
}
```

</div>
</details>

<br>

파일 읽기 클래스, 파일 쓰기 클래스로 분리


<details style="border: 1px solid #ccc; border-radius: 10px; padding: 10px;">
    <summary style="font-weight: bold; cursor: pointer;">적용 후 코드 보기</summary>
    <div markdown="1" style="margin-top: 10px;">

```cpp
#include <iostream>
#include <string>
using namespace std;

// 파일 쓰기 클래스
class FileWriter {
public:
    void writeToFile(const string& filename, const string& data) const {
        cout << "Writing data to file: " << filename << endl;
        cout << "Data: " << data << endl;
    }
};

// 파일 읽기 클래스
class FileReader {
public:
    string readFromFile(const string& filename) const {
        cout << "Reading data from file: " << filename << endl;
        return "Dummy data"; // 실제 파일 읽기 대신 가상 데이터 반환
    }
};

int main() {
    FileWriter writer;
    FileReader reader;

    string filename = "example.txt";
    string data = "Hello, SRP Example!";

    // 파일 쓰기
    writer.writeToFile(filename, data);

    // 파일 읽기
    string readData = reader.readFromFile(filename);
    cout << "Read Data: " << readData << endl;

    return 0;
}
```

</div>
</details>

<br>

### 2. 개방 폐쇄 원칙 Open/Closed Principle, OCP

### 3. 리스코프 치환 원칙 Liskov Substitution Principle, LSP

### 4. 인터페이스 분리 원칙 Interface Segregation Principle, ISP

### 5. 의존성 역전 원칙 Dependency Inversion Principle, DIP

