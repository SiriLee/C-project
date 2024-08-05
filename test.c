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
//操作选项

void menu() {
	printf("                   主页                  \n\n");
	printf("          1.新建           2.删除        \n");
	printf("          3.搜索           4.修改        \n");
	printf("          5.排序           6.打印        \n");
	printf("          0.退出                         \n");
	printf("\n请选择：");
}
//菜单主页

int main() {
	Contact con;
	InitContact(&con);
	//初始化通讯录

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
			printf("输入错误，请重新输入：\n");
			goto again;
			break;
		}

	} while (input);

	return 0;
}
//程序入口