#include "contact.h"

void getchar_clean() {
	while (getchar() != '\n');
}

void wait_enter() {
	printf("\n\n点击回车以继续...\n");
	getchar_clean();
	while (getchar() != '\n');//等待回车
	system("cls");
}

void InitContact(Contact* main_con) {

	FILE* pfile_info = fopen("coninfo.dat", "r");//打开文件
	
	if (pfile_info == NULL) { //第一次使用程序
		main_con->size = 0;
		main_con->capacity = DEFAULT_CAP;
	}
	else//第n次使用，继承size和capacity数据
		fscanf(pfile_info, "%zd %zd", &(main_con->size), &(main_con->capacity));


	//calloc函数分配动态空间
	PeoInfo* ptr = (PeoInfo*)calloc(main_con->capacity, sizeof(PeoInfo));
	if (ptr != NULL)
		main_con->data = ptr;//分配动态内存空间
	else
		perror("InitContact");//空间不足时报错
	

	if (pfile_info == NULL)
		return;//第一次使用程序，函数直接结束

	FILE* pfile_data = fopen("condata.dat", "r");
	for (size_t i = 0; i < main_con->size; i++)
		fread(main_con->data + i, sizeof(PeoInfo), 1, pfile_data);
	//第n次使用，将data的数据拷贝
}


void add(Contact* main_con) {
	system("cls");

	if (main_con->size == main_con->capacity - 1) {
		//-1保证有缓冲空间，利于del_m函数稳定实现
		PeoInfo* ptr = realloc(main_con->data, (main_con->capacity += INC_CAP) * sizeof(PeoInfo));
		//realloc函数调整
		if (ptr != NULL)
			main_con->data = ptr;
		else {
			perror("add");
			printf("\n     _______________________________________\n\n");
			printf("                    警告\n\n\t通讯录空间不足，无法增加联系人！\n\n");
			printf("     _______________________________________\n");
			wait_enter();
			return;
		}
	}
	//空间不足时微调


	printf("         新建联系人\n_____________________________\n");

	printf("\n姓名：");
	scanf("%s", main_con->data[main_con->size].name);

	printf("\n年龄：");
	scanf("%d", &(main_con->data[main_con->size].age));

	printf("\n性别：");
	scanf("%s", main_con->data[main_con->size].sex);

	printf("\n电话号码：");
	scanf("%s", main_con->data[main_con->size].tele_num);

	printf("\n地址：");
	scanf("%s", main_con->data[main_con->size].addr);

	main_con->size++;

	printf("\n\n新建联系人成功！\n");

	wait_enter();
}


void del_m(Contact* main_con, size_t code_m) {
	for (size_t i = code_m; i < main_con->size; i++) {
		main_con->data[i] = main_con->data[i + 1];
	}
	main_con->size--;//size数值减一
}

void del(Contact* main_con) {
	system("cls");

	if (main_con->size == 0) {
		printf("     _______________________________________\n\n");
		printf("                    警告\n\n\t通讯录内容空白，无法删除联系人！\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}

	printf("         删除联系人\n_____________________________\n");
	printf("请输入要删除联系人的姓名：");

	char search_name[MAX_NAME];
	scanf("%s", search_name);
	int ret = search_m(main_con, name, search_name);

	if (ret == -1) {
		printf("\n\n未查找到指定联系人！\n");
		wait_enter();
		return;
	}

	system("cls");
	printf("\n已找到指定联系人\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "姓名", "性别", "年龄", "电话号码", "地址");
	printf("%-20s\t%-5s\t%-5d\t%-20s\t%-30s\n",
		main_con->data[ret].name,
		main_con->data[ret].sex,
		main_con->data[ret].age,
		main_con->data[ret].tele_num,
		main_con->data[ret].addr);

	printf("\n请确认是否将其删除(1:确认/2：取消)\n");
	int input;
	scanf("%d", &input);

	if (input == 1) {
		del_m(main_con, ret);
		printf("\n\n删除成功！\n");
	}
	else
		printf("\n\n已取消删除\n");

	wait_enter();
}


int search_m(const Contact* main_con, enum search_type search_t, const char* content) {
	size_t i = 0;

	switch (search_t) {
	case name:
		for (i = 0; i < main_con->size; i++) {
			if (strcmp(content, main_con->data[i].name) == 0)
				return (int)i;
		}
		return -1;
		break;
	case tele_num:
		for (i = 0; i < main_con->size; i++) {
			if (strcmp(content, main_con->data[i].tele_num) == 0)
				return (int)i;
		}
		return -1;
		break;
	case addr:
		for (i = 0; i < main_con->size; i++) {
			if (strcmp(content, main_con->data[i].addr) == 0)
				return (int)i;
		}
		return -1;
		break;
	default:
		return -2;
		break;
	}
}

void search(const Contact* main_con) {
	system("cls");
	if (main_con->size == 0) {
		printf("     _______________________________________\n\n");
		printf("                    警告\n\n\t通讯录内容空白，无法搜索联系人！\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}
	//空白

	printf("   \t\t\t搜索联系人\n________________________________________________________\n");
	printf("请选择搜索联系人的方式（1：姓名  2：电话号码  3：地址）：\n");
	int input;
	scanf("%d", &input);

	if (input != 1 && input != 2 && input != 3) {
		printf("\n\n输入错误\n");
		wait_enter();
		return;
	}
	//输入

	printf("请输入查找内容：");
	char src[MAX_ADDR];
	scanf("%s", src);
	int ret = search_m(main_con, (enum search_type)input, src);

	if (ret == -1) {
		printf("\n\n未查找到指定联系人！\n");
		wait_enter();
		return;
	}

	system("cls");
	printf("\n已找到指定联系人\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "姓名", "性别", "年龄", "电话号码", "地址");
	printf("%-20s\t%-5s\t%-5d\t%-20s\t%-30s\n",
		main_con->data[ret].name,
		main_con->data[ret].sex,
		main_con->data[ret].age,
		main_con->data[ret].tele_num,
		main_con->data[ret].addr);

	wait_enter();
}


void modify_m(Contact* main_con, enum modify_type modify_t, const char* content, size_t i) {
	switch (modify_t) {
	case name_m:
		strcpy(main_con->data[i].name, content);
		break;
	case sex_m:
		strcpy(main_con->data[i].sex, content);
		break;
	case tele_num_m:
		strcpy(main_con->data[i].tele_num, content);
		break;
	case addr_m:
		strcpy(main_con->data[i].addr, content);
		break;
	default:
		break;
	}
}

void modify(Contact* main_con) {
	system("cls");
	if (main_con->size == 0) {
		printf("     _______________________________________\n\n");
		printf("                    警告\n\n\t通讯录内容空白，无法修改联系人信息！\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}
	//空白

	printf("         修改联系人信息\n_____________________________\n");
	printf("请输入要修改联系人的电话号码：");
	char search_tele[MAX_TELE_NUM];
	scanf("%s", search_tele);
	int ret = search_m(main_con, tele_num, search_tele);
	//输入

	if (ret == -1) {
		printf("\n\n未查找到指定联系人！\n");
		wait_enter();
		return;
	}

	system("cls");
	printf("\n已找到指定联系人\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "姓名", "性别", "年龄", "电话号码", "地址");
	printf("%-20s\t%-5s\t%-5d\t%-20s\t%-30s\n",
		main_con->data[ret].name,
		main_con->data[ret].sex,
		main_con->data[ret].age,
		main_con->data[ret].tele_num,
		main_con->data[ret].addr);

	printf("\n请输入修改类型(1.姓名  2.性别  3.年龄  4.电话号码  5.地址)：\n");
	int input;
	scanf("%d", &input);

	if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5) {
		printf("\n\n输入错误\n");
		wait_enter();
		return;
	}

	(enum modify_type)input;
	if (input == age_m) {
		printf("请输入修改的值：");
		scanf("%d", &(main_con->data[ret].age));
	}
	else {
		printf("请输入修改内容：");
		char src[MAX_ADDR];
		scanf("%s", src);
		modify_m(main_con, input, src, ret);
	}

	system("cls");
	printf("\n修改成功!\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "姓名", "性别", "年龄", "电话号码", "地址");
	printf("%-20s\t%-5s\t%-5d\t%-20s\t%-30s\n",
		main_con->data[ret].name,
		main_con->data[ret].sex,
		main_con->data[ret].age,
		main_con->data[ret].tele_num,
		main_con->data[ret].addr);

	wait_enter();
}


static int sort_by_name(const void* p1, const void* p2) {
	return strcmp(((PeoInfo*)p1)->name, ((PeoInfo*)p2)->name);
}

static int sort_by_age(const void* p1, const void* p2) {
	return ((PeoInfo*)p1)->age - ((PeoInfo*)p2)->age;
}

static int sort_by_tele(const void* p1, const void* p2) {
	return strcmp(((PeoInfo*)p1)->tele_num, ((PeoInfo*)p2)->tele_num);
}

static int sort_by_addr(const void* p1, const void* p2) {
	return strcmp(((PeoInfo*)p1)->addr, ((PeoInfo*)p2)->addr);
}

void sort(Contact* main_con) {
	system("cls");
	if (main_con->size == 0) {
		printf("     _______________________________________\n\n");
		printf("                    警告\n\n\t通讯录内容空白，无法修改联系人信息！\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}
	//空白

	printf("\n请输入排序标准(1.姓名  2.年龄  3.电话号码  4.地址)：\n");
	int input;
	scanf("%d", &input);

	if (input != 1 && input != 2 && input != 3 && input != 4) {
		printf("\n\n输入错误\n");
		wait_enter();
		return;
	}

	(enum sort_type)input;
	int (*sort_func)(const void* p1, const void* p2) = NULL;//比较函数指针变量

	if (input == name_s)
		sort_func = sort_by_name;
	else if (input == age_s)
		sort_func = sort_by_age;
	else if (input == tele_num_s)
		sort_func = sort_by_tele;
	else if (input == addr_s)
		sort_func = sort_by_addr;

	qsort((void*)main_con->data, main_con->size, sizeof(main_con->data[0]), sort_func);

	system("cls");
	printf("排序成功！\n\n");
	print_m((const Contact*)main_con);

	wait_enter();
}


void print_m(const Contact* main_con) {
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "姓名", "性别", "年龄", "电话号码", "地址");
	for (size_t i = 0; i < main_con->size; i++) {
		printf("%-20s\t%-5s\t%-5d\t%-20s\t%-30s\n",
			main_con->data[i].name,
			main_con->data[i].sex,
			main_con->data[i].age,
			main_con->data[i].tele_num,
			main_con->data[i].addr);
	}
}

void print(const Contact* main_con) {
	system("cls");
	printf("                               通讯录列表\n\n");
	print_m(main_con);

	wait_enter();
}

void exit_m(Contact* main_con) {
	free(main_con->data);
	main_con->data = NULL;
}

void SaveContact(Contact* main_con) {
	FILE* pfile_data = fopen("condata.dat", "w");
	FILE* pfile_info = fopen("coninfo.dat", "w");//打开文件
	if (pfile_data == NULL) {
		perror("File Open");
		return;
	}
	if (pfile_info == NULL) {
		perror("File Open");
		return;
	}//错误情况

	
	for (size_t i = 0; i < main_con->size; i++)
		fwrite(main_con->data + i, sizeof(PeoInfo), 1, pfile_data);
	//写data文件
	
	fprintf(pfile_info, "%zd %zd", main_con->size, main_con->capacity);
	//写info文件

	//关闭文件
	fclose(pfile_data);
	pfile_data = NULL;
	fclose(pfile_info);
	pfile_info = NULL;

	printf("\n\n通讯录保存成功！程序已退出\n");
	wait_enter();
}