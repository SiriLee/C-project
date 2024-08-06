#pragma once

#define _CRT_SECURE_NO_WARNINGS 1  //ʹscanf()����������VSƽ̨

#define MAX_NAME 20//������󳤶�
#define MAX_TELE_NUM 15//�绰������󳤶�
#define MAX_ADDR 30//��ַ��󳤶�
#define MAX_SEX 5 //�Ա��ַ���󳤶�

#define DEFAULT_CAP 100 //��ʼ�ռ��������
#define INC_CAP 10 //�ռ䲻��ʱ���ӵĵ�λ����


#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>


enum search_type {
	name = 1,
	tele_num,
	addr
};
//��������

enum modify_type {
	name_m = 1,
	sex_m,
	age_m,
	tele_num_m,
	addr_m
};
//�޸�����

enum sort_type {
	name_s = 1,
	age_s,
	tele_num_s,
	addr_s
};
//��������


typedef struct PeoInfo {
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele_num[MAX_TELE_NUM];
	char addr[MAX_ADDR];
}PeoInfo;
//ͨѶ¼������Ϣ

typedef struct Contact {
	PeoInfo* data;//���������ָ�루���飩���ɱ��С
	size_t size;//��ǰͨѶ¼����
	size_t capacity;//��ǰͨѶ¼����
}Contact;
//ͨѶ¼����ṹ


void getchar_clean();//��������
void wait_enter();//�ȴ�����س�
void InitContact(Contact* main_con
);//��ʼ��ͨѶ¼

void add(Contact* main_con
);//������ϵ��

void del(Contact* main_con
);//ɾ����ϵ��
void del_m(Contact* main_con,
	size_t code_m
);//ɾ����ϵ���㷨

void search(const Contact* main_con
);//������ϵ��
int search_m(const Contact* main_con,
	enum search_type search_t,
	const char* content
);//������ϵ���㷨

void modify(Contact* main_con
);//�޸���ϵ����Ϣ
void modify_m(Contact* main_con,
	enum modify_type modify_t,
	const char* content,
	size_t i
);//�޸���ϵ����Ϣ�㷨

void sort(Contact* main_con
);//����

void print(const Contact* main_con
);//չʾͨѶ¼
void print_m(const Contact* main_con
);//չʾͨѶ¼�㷨

void exit_m(Contact* main_con
);//���ն�̬�ڴ�ռ䣬ָ�븳��ֵ

void SaveContact(Contact* main_con
);//����ͨѶ¼��Ϣ���ļ���

/*����ȱ�ݣ��޷�������Ϣ(���֡��绰����)�ظ����⣬
�ҵ��ظ�ʱ(���֡��绰���롢��ַ)ʹ����������ֻ���ҵ�Ψһ����*/
