#pragma once

#define _CRT_SECURE_NO_WARNINGS 1  //使scanf()函数适用于VS平台

#define MAX_NAME 20//名字最大长度
#define MAX_TELE_NUM 15//电话号码最大长度
#define MAX_ADDR 30//地址最大长度
#define MAX_SEX 5 //性别字符最大长度

#define MAX_NUM 1000//通讯录最大容量

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>


enum search_type {
	name = 1,
	tele_num,
	addr
};
//搜索类型

enum modify_type {
	name_m = 1,
	sex_m,
	age_m,
	tele_num_m,
	addr_m
};
//修改类型

enum sort_type {
	name_s = 1,
	age_s,
	tele_num_s,
	addr_s
};
//排序类型


typedef struct PeoInfo {
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele_num[MAX_TELE_NUM];
	char addr[MAX_ADDR];
	//int code;
}PeoInfo;
//通讯录个人信息

typedef struct Contact {
	PeoInfo data[MAX_NUM + 1];//个人信息合集   +1作为缓冲空间
	size_t size;//当前通讯录长度
}Contact;
//通讯录总体结构


void getchar_clean();//清理缓冲区
void wait_enter();//等待输入回车
void InitContact(Contact* main_con
);//初始化通讯录

void add(		Contact* main_con
);//增加联系人

void del(		Contact* main_con
);//删除联系人
void del_m(		Contact* main_con, 
				size_t code_m
);//删除联系人算法

void search(	const Contact* main_con
);//搜索联系人
int search_m(	const Contact* main_con, 
				enum search_type search_t, 
				const char* content
);//搜索联系人算法

void modify(	Contact* main_con
);//修改联系人信息
void modify_m(	Contact* main_con, 
				enum modify_type modify_t, 
				const char* content, 
				size_t i
);//修改联系人信息算法

void sort(		Contact* main_con
);//排序

void print(		const Contact* main_con
);//展示通讯录
void print_m(	const Contact* main_con
);//展示通讯录算法


/*代码缺陷：无法避免信息(名字、电话号码)重复问题，
且当重复时(名字、电话号码、地址)使用搜索功能只能找到唯一对象*/
