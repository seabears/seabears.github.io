---
title: C++연습
description: >-           #한 문장으로 나옴
  C++
date: 2025-01-07 17:01:31 +0900
lastmod : 2025-01-07 17:01:31 +0900  #마지막 수정 시간

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

### C++연습 : 첫 객체 프로그램

<br>

#### main.cpp

```cpp
#include<iostream>
#include"Database.hpp"

void select();
int be_process(Database&, int);

int main() {
	
	Database database;
	
	int run = 1;
	while (run) {
		select();
		int user_input;
		cin >> user_input;

		run = be_process(database, user_input);

		cout << endl;
	}
}
int be_process(Database& database, int input) {

	string first_name = "", last_name = "";
	int id, salary;
	cout << endl;
	switch (input) {
	case 1:
		cout << "First name : ";
		cin >> first_name;
		cout << "Last name : ";
		cin >> last_name;
		database.hire(first_name, last_name);
		break;
	case 2:
		cout << "Enter employee ID to fire : ";
		cin >> id;
		database.fire(id);
		break;
	case 3:
		cout << "Enter employee ID to promote : ";
		cin >> id;
		cout << "Enter salary : ";
		cin >> salary;
		database.promote(id, salary);
		break;
	case 4:
		database.list_all();
		break;
	case 5:
		database.list_current();
		break;
	case 6:
		database.list_former();
		break;
	case 0:
		return 0;
	}
	return 1;
}
void select() {
	cout << "Employee Database" << endl;
	cout << "-----------------------------" << endl;
	cout << "1) Hire a new  employee" << endl;
	cout << "2) Fire an employee" << endl;
	cout << "3) Promote  an employee" << endl;
	cout << "4) List all employees" << endl;
	cout << "5) List all current employees" << endl;
	cout << "6) List all former employees" << endl;
	cout << "0) Quit" << endl;
	cout << "select : ";
}
```

<br>

#### Database.cpp

```cpp
#include"Database.hpp"

// Employee 클래스 생성자 구현
Employee::Employee(string first_name, string last_name, int id, int salary, bool isEmployed)
	: first_name(first_name), last_name(last_name), id(id), salary(salary), isEmployed(isEmployed) {
}
int Database::get_id_cnt() {
	return id_cnt;
}

void Database::hire(string first_name, string last_name) {
	int new_id = id_cnt++;
	employees.push_back(Employee(first_name, last_name, new_id, 30000,1));
}
void Database::fire(int id) {
	for (auto& emp : employees) {
		if (emp.id == id && emp.isEmployed) {
			emp.isEmployed = false;
			cout << "Employee " << id << " fired." << endl;
			return;
		}
	}
	cout << "ERR : No employee found." << endl;
}
void Database::promote(int id, int salary) {
	for (auto& emp : employees) {
		if (emp.id == id && emp.isEmployed) {
			emp.salary += salary;
			cout << "Employee " << emp.first_name << ", " << emp.last_name << " promoted." << endl;
			return;
		}
	}
	cout << "ERR : No employee found." << endl;
}
void Database::list_all() {
	cout << "All  Employee" << endl;
	for (const auto& emp : employees) {
		cout << "Employee ID : " << emp.id << "  ";
		cout << "Name : " << emp.first_name << ", " << emp.last_name << "  ";
		cout << "Salary : " << emp.salary << endl;
	}
}
void Database::list_current() {
	cout << "Current  Employee" << endl;
	for (const auto& emp : employees) {
		if (emp.isEmployed) {
			cout << "Employee ID : " << emp.id << "  ";
			cout << "Name : " << emp.first_name << ", " << emp.last_name << "  ";
			cout << "Salary : " << emp.salary << endl;
		}
	}
}
void Database::list_former() {
	cout << "Former  Employee" << endl;
	for (const auto& emp : employees) {
		if (!emp.isEmployed) {
			cout << "Employee ID : " << emp.id << "  ";
			cout << "Name : " << emp.first_name << ", " << emp.last_name << "  ";
			cout << "Salary : " << emp.salary << endl;
		}
	}
}

```

<br>

#### Database.hpp

```cpp
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee {
public:
    string first_name, last_name;
    int id;
    int salary;
    bool isEmployed;

    //인자가 있는 생성자
    Employee(string first_name, string last_name, int id, int salary, bool isEmployed);

};

class Database {
private:
    vector<Employee> employees;  // 직원 정보를 저장하는 벡터
    int id_cnt;
   

public:
    //생성자 초기화 목록
    Database():id_cnt(1000){}


public:
    int get_id_cnt();

    // 직원 고용 함수
    void hire(string first_name, string last_name);

    // 직원 해고 함수
    void fire(int id);

    // 직원 승진 함수
    void promote(int id, int salary);

    // 전체 직원 목록 출력 함수
    void list_all();

    // 현재 고용 중인 직원 목록 출력 함수
    void list_current();

    // 퇴직한 직원 목록 출력 함수
    void list_former();
};

#endif // DATABASE_HPP
```

<br>

