#include "contact.h"

void getchar_clean() {
	while (getchar() != '\n');
}

void wait_enter() {
	printf("\n\n����س��Լ���...\n");
	getchar_clean();
	while (getchar() != '\n');//�ȴ��س�
	system("cls");
}

void InitContact(Contact* main_con) {

	FILE* pfile_info = fopen("coninfo.dat", "r");//���ļ�
	
	if (pfile_info == NULL) { //��һ��ʹ�ó���
		main_con->size = 0;
		main_con->capacity = DEFAULT_CAP;
	}
	else//��n��ʹ�ã��̳�size��capacity����
		fscanf(pfile_info, "%zd %zd", &(main_con->size), &(main_con->capacity));


	//calloc�������䶯̬�ռ�
	PeoInfo* ptr = (PeoInfo*)calloc(main_con->capacity, sizeof(PeoInfo));
	if (ptr != NULL)
		main_con->data = ptr;//���䶯̬�ڴ�ռ�
	else
		perror("InitContact");//�ռ䲻��ʱ����
	

	if (pfile_info == NULL)
		return;//��һ��ʹ�ó��򣬺���ֱ�ӽ���

	FILE* pfile_data = fopen("condata.dat", "r");
	for (size_t i = 0; i < main_con->size; i++)
		fread(main_con->data + i, sizeof(PeoInfo), 1, pfile_data);
	//��n��ʹ�ã���data�����ݿ���
}


void add(Contact* main_con) {
	system("cls");

	if (main_con->size == main_con->capacity - 1) {
		//-1��֤�л���ռ䣬����del_m�����ȶ�ʵ��
		PeoInfo* ptr = realloc(main_con->data, (main_con->capacity += INC_CAP) * sizeof(PeoInfo));
		//realloc��������
		if (ptr != NULL)
			main_con->data = ptr;
		else {
			perror("add");
			printf("\n     _______________________________________\n\n");
			printf("                    ����\n\n\tͨѶ¼�ռ䲻�㣬�޷�������ϵ�ˣ�\n\n");
			printf("     _______________________________________\n");
			wait_enter();
			return;
		}
	}
	//�ռ䲻��ʱ΢��


	printf("         �½���ϵ��\n_____________________________\n");

	printf("\n������");
	scanf("%s", main_con->data[main_con->size].name);

	printf("\n���䣺");
	scanf("%d", &(main_con->data[main_con->size].age));

	printf("\n�Ա�");
	scanf("%s", main_con->data[main_con->size].sex);

	printf("\n�绰���룺");
	scanf("%s", main_con->data[main_con->size].tele_num);

	printf("\n��ַ��");
	scanf("%s", main_con->data[main_con->size].addr);

	main_con->size++;

	printf("\n\n�½���ϵ�˳ɹ���\n");

	wait_enter();
}


void del_m(Contact* main_con, size_t code_m) {
	for (size_t i = code_m; i < main_con->size; i++) {
		main_con->data[i] = main_con->data[i + 1];
	}
	main_con->size--;//size��ֵ��һ
}

void del(Contact* main_con) {
	system("cls");

	if (main_con->size == 0) {
		printf("     _______________________________________\n\n");
		printf("                    ����\n\n\tͨѶ¼���ݿհף��޷�ɾ����ϵ�ˣ�\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}

	printf("         ɾ����ϵ��\n_____________________________\n");
	printf("������Ҫɾ����ϵ�˵�������");

	char search_name[MAX_NAME];
	scanf("%s", search_name);
	int ret = search_m(main_con, name, search_name);

	if (ret == -1) {
		printf("\n\nδ���ҵ�ָ����ϵ�ˣ�\n");
		wait_enter();
		return;
	}

	system("cls");
	printf("\n���ҵ�ָ����ϵ��\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "����", "�Ա�", "����", "�绰����", "��ַ");
	printf("%-20s\t%-5s\t%-5d\t%-20s\t%-30s\n",
		main_con->data[ret].name,
		main_con->data[ret].sex,
		main_con->data[ret].age,
		main_con->data[ret].tele_num,
		main_con->data[ret].addr);

	printf("\n��ȷ���Ƿ���ɾ��(1:ȷ��/2��ȡ��)\n");
	int input;
	scanf("%d", &input);

	if (input == 1) {
		del_m(main_con, ret);
		printf("\n\nɾ���ɹ���\n");
	}
	else
		printf("\n\n��ȡ��ɾ��\n");

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
		printf("                    ����\n\n\tͨѶ¼���ݿհף��޷�������ϵ�ˣ�\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}
	//�հ�

	printf("   \t\t\t������ϵ��\n________________________________________________________\n");
	printf("��ѡ��������ϵ�˵ķ�ʽ��1������  2���绰����  3����ַ����\n");
	int input;
	scanf("%d", &input);

	if (input != 1 && input != 2 && input != 3) {
		printf("\n\n�������\n");
		wait_enter();
		return;
	}
	//����

	printf("������������ݣ�");
	char src[MAX_ADDR];
	scanf("%s", src);
	int ret = search_m(main_con, (enum search_type)input, src);

	if (ret == -1) {
		printf("\n\nδ���ҵ�ָ����ϵ�ˣ�\n");
		wait_enter();
		return;
	}

	system("cls");
	printf("\n���ҵ�ָ����ϵ��\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "����", "�Ա�", "����", "�绰����", "��ַ");
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
		printf("                    ����\n\n\tͨѶ¼���ݿհף��޷��޸���ϵ����Ϣ��\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}
	//�հ�

	printf("         �޸���ϵ����Ϣ\n_____________________________\n");
	printf("������Ҫ�޸���ϵ�˵ĵ绰���룺");
	char search_tele[MAX_TELE_NUM];
	scanf("%s", search_tele);
	int ret = search_m(main_con, tele_num, search_tele);
	//����

	if (ret == -1) {
		printf("\n\nδ���ҵ�ָ����ϵ�ˣ�\n");
		wait_enter();
		return;
	}

	system("cls");
	printf("\n���ҵ�ָ����ϵ��\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "����", "�Ա�", "����", "�绰����", "��ַ");
	printf("%-20s\t%-5s\t%-5d\t%-20s\t%-30s\n",
		main_con->data[ret].name,
		main_con->data[ret].sex,
		main_con->data[ret].age,
		main_con->data[ret].tele_num,
		main_con->data[ret].addr);

	printf("\n�������޸�����(1.����  2.�Ա�  3.����  4.�绰����  5.��ַ)��\n");
	int input;
	scanf("%d", &input);

	if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5) {
		printf("\n\n�������\n");
		wait_enter();
		return;
	}

	(enum modify_type)input;
	if (input == age_m) {
		printf("�������޸ĵ�ֵ��");
		scanf("%d", &(main_con->data[ret].age));
	}
	else {
		printf("�������޸����ݣ�");
		char src[MAX_ADDR];
		scanf("%s", src);
		modify_m(main_con, input, src, ret);
	}

	system("cls");
	printf("\n�޸ĳɹ�!\n\n");
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "����", "�Ա�", "����", "�绰����", "��ַ");
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
		printf("                    ����\n\n\tͨѶ¼���ݿհף��޷��޸���ϵ����Ϣ��\n\n");
		printf("     _______________________________________\n");
		wait_enter();
		return;
	}
	//�հ�

	printf("\n�����������׼(1.����  2.����  3.�绰����  4.��ַ)��\n");
	int input;
	scanf("%d", &input);

	if (input != 1 && input != 2 && input != 3 && input != 4) {
		printf("\n\n�������\n");
		wait_enter();
		return;
	}

	(enum sort_type)input;
	int (*sort_func)(const void* p1, const void* p2) = NULL;//�ȽϺ���ָ�����

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
	printf("����ɹ���\n\n");
	print_m((const Contact*)main_con);

	wait_enter();
}


void print_m(const Contact* main_con) {
	printf("%-20s\t%-5s\t%-5s\t%-20s\t%-30s\n", "����", "�Ա�", "����", "�绰����", "��ַ");
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
	printf("                               ͨѶ¼�б�\n\n");
	print_m(main_con);

	wait_enter();
}

void exit_m(Contact* main_con) {
	free(main_con->data);
	main_con->data = NULL;
}

void SaveContact(Contact* main_con) {
	FILE* pfile_data = fopen("condata.dat", "w");
	FILE* pfile_info = fopen("coninfo.dat", "w");//���ļ�
	if (pfile_data == NULL) {
		perror("File Open");
		return;
	}
	if (pfile_info == NULL) {
		perror("File Open");
		return;
	}//�������

	
	for (size_t i = 0; i < main_con->size; i++)
		fwrite(main_con->data + i, sizeof(PeoInfo), 1, pfile_data);
	//дdata�ļ�
	
	fprintf(pfile_info, "%zd %zd", main_con->size, main_con->capacity);
	//дinfo�ļ�

	//�ر��ļ�
	fclose(pfile_data);
	pfile_data = NULL;
	fclose(pfile_info);
	pfile_info = NULL;

	printf("\n\nͨѶ¼����ɹ����������˳�\n");
	wait_enter();
}