#include "contact.h"

enum choice {
	Exit,
	Add,
	Del,
	Search,
	Modify,
	Sort,
	Print
};
//����ѡ��

void menu() {
	printf("                   ��ҳ                  \n\n");
	printf("          1.�½�           2.ɾ��        \n");
	printf("          3.����           4.�޸�        \n");
	printf("          5.����           6.��ӡ        \n");
	printf("          0.�˳�                         \n");
	printf("\n��ѡ��");
}
//�˵���ҳ

int main() {
	Contact con;
	InitContact(&con);
	//��ʼ��ͨѶ¼

	int input = 0;
	do {
		menu();
	again:
		scanf("%d", &input);

		switch ((enum choice)input) {
		case Add:
			add(&con);
			break;
		case Del:
			del(&con);
			break;
		case Search:
			search(&con);
			break;
		case Modify:
			modify(&con);
			break;
		case Sort:
			sort(&con);
			break;
		case Print:
			print(&con);
			break;
		case Exit:
			exit_m(&con);
			break;
		default:
			printf("����������������룺\n");
			goto again;
			break;
		}

	} while (input);

	return 0;
}
//�������