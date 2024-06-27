#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <Windows.h>
#include <conio.h>

#define MAX 100//根据职工信息改变
#define account 1
#define password 1
#define TRUE 1
#define FALSE 0

typedef struct staff { //结构体定义，工号，姓名，性别，年龄，学历，工资，地址，电话号码
	int number;
	char name[MAX];
	char sex[MAX];
	char age[MAX];
	char edu[MAX];
	char money[MAX];
	char addr[MAX];
	char phoneNum[MAX];
	struct staff *next;
} node;


int log_in(); //用户登录 （账号密码正确才可以登录）
void menu(node *head2); //菜单
node *filesave(node *head); //将职工信息保存到文件
int listread(node *head2); //从链表进行职工信息浏览
void input(node *head2); //函数1职工信息录入
int Eduserch(node *head2); //职工信息查询（按照学历）
int Numberserch(node *head2); //职工信息查询（按照职工号查询信息）
void Modify(node *head2); //修改职工信息（按照工号）
int Delete(node *head2); //删除职工信息(按照工号）
node *Fileread(void); //读取文件中职工信息到链表中
void View(node *head2); //浏览全部员工基本信息
void count(node *head);//统计员工信息
void search(node *head);//搜索二级菜单界面
int nameSearch(node *head2);//按照姓名查找
node* mergeSort(node* head);//按照职工号排序
int checkPerson(node *head, int person);//检查表里面是否有这个人
int whichToModify();//选择具体要精细修改什么
int checkPhoneNumber(node *head, char phoneNumber[20]);//检查电话号码是否重复

int main() {
	node *head = Fileread(); //读取文件中职工信息到链表中 ,头结点无数据
	int R = log_in();

	if (R) {
		system("cls"); //清屏函数<stdlib.h>
		printf("登陆成功！\n");
	}

	menu(head);

	return 0;
}


int log_in() {
	int acc, pass;
	char ps[200] , ch;
	int i = 0;
	while (1) {
		system("cls");
		printf("\t\t\t\t\t职工信息管理系统!\n");
		printf("请输入你的账号:\n");
		scanf("%d", &acc);
		getchar();
		printf("请输入你的密码:\n");
		while(1){
			ch = getch();
			if(ch == '\r'){
				ps[i] = '\0';
				break;
			}else if (ch == '\b' && i > 0) {  // 按下退格键，删除一个字符
				printf("\b \b");  // 在终端上删除一个字符
				i--;
			}else {
				printf("*");  // 在终端上显示*
				ps[i++] = ch;
			}
		}
		pass = atoi(ps);
		if (acc == account && pass == password) {
			printf("\n\n\n\t账号密码正确,欢迎进入系统!\n");
            Sleep(1000);
			return 1;
		} else {
			printf("\n\n\n\t很遗憾你的账号或密码输入错误!\n");
			Sleep(2000);
		}
	}
}


int s_select() { //功能选择
	printf("\t\t\t\t\t职工信息管理系统!\n");
	int n;
	printf("1       职工信息录入           \n\n");
	printf("2       职工信息浏览           \n\n");
	printf("3       职工信息查询  \n\n");
	printf("4       职工信息删除           \n\n");
	printf("5       职工信息修改            \n\n");
	printf("6       职工信息统计\n\n");
	printf("0       退出职工系统            \n\n\n");
	printf("请您输入选择:\t");
	scanf("%d", &n);
	while (n < 0 || n > 8) {
		printf("无此选项，请重新输入：\n");
		scanf("%d", &n);
	}
	return n;
}


node *Fileread() { //读取文件中职工信息到链表中
	FILE *fp;
	node *p, *pre, *tail, *head;
	head = (node *) malloc(sizeof(node));
	tail = pre = head;
	fp = fopen("work.txt", "r");
	if (fp == NULL) {
		printf("文件打开失败!!!");
		exit(0);
	}
	p = (node *) malloc(sizeof(node));
	p->next = NULL;
	head->next = NULL;
	while (fscanf(fp, "%d %s %s %s %s %s %s %s\n", &p->number, p->name, p->sex, p->age, p->edu, p->money, p->addr,
	              p->phoneNum) != EOF) {
		pre = tail;
		tail->next = p;
		tail = p;
		p = (node *) malloc(sizeof(node));
		p->next = NULL;
	}
	fclose(fp);
	return head;
}

void menu(node *head2) { //菜单
	system("cls"); //清屏操作
	int m = s_select();
	switch (m) {
		case 1:
			printf("选择1:职工信息录入\n");
			system("cls"); //清屏操作
			input(head2); //输入职工信息并保存到文件
			break;
		case 2:
			printf("选择2:职工信息浏览\n");
			system("cls"); //清屏操作
			listread(head2); //浏览全部职工信息
			break;
		case 3:
			printf("选择3:职工信息查询\n");
			system("cls"); //清屏操作
			search(head2); //职工信息查询
			break;
		case 4:
			printf("选择4:职工信息删除\n");
			system("cls"); //清屏操作
			Delete(head2); //删除职工信息(按照职工号）
			break;
		case 5:
			printf("选择5:职工信息修改\n");
			system("cls"); //清屏操作
			Modify(head2); //修改职工信息
			break;
		case 6:
			printf("选择6：基本数据统计\n");
			system("cls");
			count(head2);
			break;
		case 0:
			printf("选择0:退出职工系统\n");
			system("cls"); //清屏操作
			printf("\n\n\n\t\t\t\t感谢您的使用，欢迎再次光临！\n\n\n");
			getchar(); //清除\n
			getchar();
			exit(0);
	}
}


void input(node *head2) { //输入职工信息
	system("cls"); //清屏操作
	int i = 1;
	node *p, *q;
	q = head2;
	while (q->next != NULL) {
		q = q->next;
	}
	int n = 1;
	int number;
	while (1) {
		system("cls");
		printf("\t\t\t\t\t职工信息管理系统!\n");
		
		p = (node *) malloc(sizeof(node));
		printf("请输入职工号(长度在100-999)：");
		scanf("%d", &number);
		while ((number < 100 || number > 999) || checkPerson(head2, number) == 1) {
			if((number < 100 || number > 999))	printf("输入职工号无效,请输入100-999之间的职工号:");
			else if(checkPerson(head2, number) == 1){
				printf("该职工号已存在,请重新输入:");
			}
			scanf("%d", &number);
		}
		p->number = number;
		
		char s[100];
		printf("请输入姓名:");
		scanf("%s", s);
		while (strlen(s) > 10 ) {
			printf("无效输入!请再次输入:");
			scanf("%s", s);
		}
		strcpy(p->name, s);

		printf("请输入性别:");
		scanf("%s", s);
		while (strcmp("男", s) != 0 && strcmp("女", s)) {
			printf("无效输入!请再次输入:");
			scanf("%s", s);
		}
		strcpy(p->sex, s);
		

		int num;
		printf("请输入年龄:");
		scanf("%d", &num);
		char t[200];
		sprintf(t, "%d", num);
		while (num > 120 || num < 0 || strcmp(t, p->age) == 0) {
			printf("无效输入!请再次输入:");
			scanf("%d", &num);
		}
		sprintf(p->age, "%d", num);

		printf("请输入学历:");
		scanf("%s", s);
		while (strcmp(s, "本科") != 0 && strcmp(s, "高中") != 0 && strcmp(s, "专科") != 0 && strcmp(s, "研究生") != 0 && strcmp(s, "博士") != 0) {
			printf("无效输入!请再次输入:");
			scanf("%s", s);
		}
		strcpy(p->edu, s);

		printf("请输入工资:");
		scanf("%s", s);
		while (strlen(s) > 20 ) {
			printf("无效输入!请再次输入:");
			scanf("%s", s);
		}
		strcpy(p->money, s);

		printf("请输入地址:");
		scanf("%s", s);
		while (strlen(s) > 25) {
			printf("无效输入!请再次输入:");
			scanf("%s", s);
		}
		strcpy(p->addr, s);

		printf("请输入电话号码:");
		scanf("%s", s);
		while (strlen(s) != 11 || checkPhoneNumber(head2, s) == 1) {
			if(strlen(s) != 11){
				printf("电话号码位数不对,请重新输入:");
			}else{
				printf("该电话号码已存在,请重新输入:");
			}
			scanf("%s", s);
		}
		strcpy(p->phoneNum, s);
		printf("已经完成第%d个职工信息的添加！", i++);
		p->next = NULL;
		q->next = p;
		q = p;
		Sleep(1000);
		
		printf("\n输入0结束输入！输入1继续添加！\n");
		printf("请输入选择：");
		scanf("%d", &n);
		if(n == 0){
			break;
		}
	}
	filesave(head2);
	printf("返回主菜单请输入0, 浏览全部信息请输入1\n");
	printf("请输入:");
	int choice;
	node* ptr = Fileread();
	scanf("%d", &choice);
	while(choice != 0 && choice != 1){
		printf("无效选择,请再次输入:");
		scanf("%d", &choice);
	}
	if(choice == 1){
		listread(ptr);
	}else{
		menu(ptr);
	}
}

void search(node *head) {//查询二级菜单
	system("cls");
	printf("\t\t\t\t\t职工信息管理系统!\n");
	printf("请输入你想要查询的方式：\n\n1 按照职工号查询\n\n2 按照学历查询\n\n3 按照姓名查询\n\n0 返回主菜单\n\n");
	printf("请输入你的选择:");
	int choice;
	scanf("%d", &choice);
	while (choice < 0 || choice > 3) {
		printf("无此选项，请重新输入：\n");
		scanf("%d", &choice);
	}
	if (choice == 1) {
		Numberserch(head);
	} else if (choice == 2) {
		Eduserch(head);
	} else if (choice == 3) {
		nameSearch(head);
	} else if (choice == 0) {
		menu(head);
	}
}

int Eduserch(node *head2) { //查找职工信息（按照学历）
	system("cls"); //清屏操作
	printf("\t\t\t\t\t职工信息管理系统!\n");
	printf("尊敬的用户，欢迎查找职工的信息（按照学历查找）！\n");
	char edu[MAX];
	printf("请输入你想查找的职工的学历：");
	scanf("%s", edu);
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("此系统中无记录!\n");
		exit(0);
	}
	int flag = 0;
	for (p = head->next; p != NULL; p = p->next) {
		if (strcmp(p->edu, edu) == 0) {
			if (flag == 0) {
				printf("\n职工号\t姓名\t性别\t年龄\t学历\t工资\t\t地址\t\t\t\t\t电话号码\n");
				flag = 1;
			}
			printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
			       p->addr,
			       p->phoneNum);
		}
	}

	if (flag == 0 ) {
		printf("输入的学历不存在,请再次检查是否输入正确!\n");
	}
	int m;
	printf("返回上一级菜单输入1，再次查找请输入2, 返回主菜单请输入0！\n");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("输入的选择无效,请再次输入:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("返回上级菜单!\n");
		search(head);
	} else if (m == 0) {
		printf("返回主菜单！\n");
		menu(head2);
	} else {
		printf("再次进行学历查找!");
		Eduserch(head2);
	}
	return 0;
}


int Numberserch(node *head2) { //查找职工信息（按照职工职工号查找）
	system("cls"); //清屏操作
	printf("尊敬的用户，欢迎查找职工的信息（按照职工号查找）！\n");
	int number;
	printf("请输入你想查找的职工的职工号：");
	scanf("%d", &number);
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("此系统中无记录!\n");
		exit(0);
	}
	int flag = 0;
	for (p = head->next; p != NULL; p = p->next) {
		if (p->number == number) {
			if (flag == 0) {
				printf("\n职工号\t姓名\t性别\t年龄\t学历\t工资\t\t地址\t\t\t\t\t电话号码\n");
				flag = 1;
			}
			printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
			       p->addr,
			       p->phoneNum);
		}
	}
	if (flag == 0) {
		printf("未找到该职工号,请再次核实职工号!\n");
	}

	int m;
	printf("返回上一级菜单输入1，再次查找请输入2, 返回主菜单请输入0！\n");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("输入无效, 请再次输入:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("返回上级菜单!\n");

		search(head);
	} else if (m == 0) {
		printf("返回主菜单！\n");
		menu(head2);
	} else {
		Numberserch(head2);
	}
	return 0;
}

void Modify(node *head2) { //修改职工信息（按照工号）
	system("cls");
	printf("\t\t\t\t\t职工信息管理系统!\n");
	node *head = head2;
	node *p = head->next;
	int number;
	if (head == NULL) {
		printf("此系统为空!\n");
		menu(head);
		exit(0);
	}
	printf("请输入要修改职工的职工号：\n");
	scanf("%d", &number);
	while (checkPerson(head2, number) == 0) {
		printf("没有找到该员工!请检查输入是否正确并再次输入!如果需要查找职工号请输入-1.\n请输入你的选择:");
		scanf("%d", &number);
		if (number == -1) {
			search(head2);
		}
	}
	while (p != NULL && p->number != number) {

		p = p->next;
	}
	system("cls");
	printf("\t\t\t\t\t职工信息管理系统!\n");
	printf("已经找到该员工,详细信息如下:\n");
	printf("职工号\t姓名\t性别\t年龄\t学历\t工资\t\t地址\t\t\t\t\t电话号码\n");
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
	       p->addr,
	       p->phoneNum);

	int choice = whichToModify(head2);
	switch (choice) {
		case 1:
			int number;
			printf("请输入职工号:");
			scanf("%d", &number);
			while (number < 100 || number > 999 || number == p->number) {
				printf("输入职工号无效,请输入100-999之间的职工号:");
				scanf("%d", &number);
			}
			p->number = number;
			break;
		case 2:
			char s[100];
			printf("请输入姓名:");
			scanf("%s", s);
			while (strlen(s) > 10 || strcmp(s, p->name) == 0) {
				printf("无效输入!请再次输入:");
				scanf("%s", s);
			}
			strcpy(p->name, s);
			break;
		case 3:
			printf("请输入性别:");
			scanf("%s", s);
			while ((strcmp("男", s) != 0 && strcmp("女", s)) != 0 || strcmp(s, p->sex) == 0) {
				printf("无效输入!请再次输入:");
				scanf("%s", s);
			}
			strcpy(p->sex, s);
			break;
		case 4:
			int num;
			printf("请输入年龄:");
			scanf("%d", &num);
			char t[200];
			sprintf(t, "%d", num);
			while (num > 120 || num < 0 || strcmp(t, p->age) == 0) {
				printf("无效输入!请再次输入:");
				scanf("%d", &num);
			}
			sprintf(p->age, "%d", num);
			break;
		case 5:
			printf("请输入学历:");
			scanf("%s", s);
			while ((strcmp(s, "本科") != 0 && strcmp(s, "高中") != 0 && strcmp(s, "专科") != 0 && strcmp(s, "研究生") != 0 && strcmp(s, "博士") != 0) || strcmp(s, p->edu) == 0) {
				printf("无效输入!请再次输入:");
				scanf("%s", s);
			}
			strcpy(p->edu, s);
			break;
		case 6:
			printf("请输入工资:");
			scanf("%s", s);
			while (strlen(s) > 20 || strcmp(s, p->money) == 0) {
				printf("无效输入!请再次输入:");
				scanf("%s", s);
			}
			strcpy(p->money, s);
			break;
		case 7:
			printf("请输入地址:");
			scanf("%s", s);
			while (strlen(s) > 25 || strcmp(s, p->addr) == 0) {
				printf("无效输入!请再次输入:");
				scanf("%s", s);
			}
			strcpy(p->addr, s);
			break;
		case 8:
			printf("请输入电话号码:");
			scanf("%s", s);
			while (strlen(s) != 11 || strcmp(s, p->phoneNum) == 0) {
				printf("无效输入!请再次输入:");
				scanf("%s", s);
			}
			strcpy(p->phoneNum, s);
			break;
		default:
			menu(head2);
			break;
	}
	printf("\n修改成功\n");
	printf("返回上一级菜单输入1，再次修改请输入2, 结束请输入0！\n");
	int m;
	scanf("%d", &m);
	filesave(head2);
	node *ptr = Fileread();
	if (m == 1) {
		printf("返回主菜单!\n");
		menu(ptr);
	} else if (m == 0) {
		printf("结束操作！\n");
		exit(0);
	} else {
		Modify(ptr);
	}
}

int whichToModify() {
	printf("1.修改职工号\n2.修改姓名\n3.修改性别\n4.修改年龄\n5.修改学历\n6.修改工资\n7.修改地址\n8.修改电话号码\n0.返回主菜单\n");
	printf("请输入你想要修改的条目:");
	int choice;
	scanf("%d", &choice);
	while (choice < 0 || choice > 8) {
		printf("无效选择! 请再次输入:");
		scanf("%d", &choice);
	}
	return choice;
}

int Delete(node *head2) { //删除职工信息(按照职工号）
	printf("\t\t\t\t\t职工信息管理系统!\n");
	node *head;
	head = head2;
	int number; //先查找 后删除
	node *p = head->next, *p1 = head->next;

	if (head == NULL) {
		printf("此通讯录为空！\n");
		printf("返回主菜单！\n");
		menu(head);
		return 0;
	}
	printf("请输入要删除职工的职工号：\n");
	scanf("%d", &number);
	while (checkPerson(head2, number) == 0) {
		printf("未找到该职工,若要姓名查找请输入-1,请再次输入:");
		scanf("%d", &number);
		if (number == -1) {
			nameSearch(head2);
		}
	}
	while (p != NULL && p->number != number) {
		p = p->next;
	}
	if (number == p->number) { //输出删除信息
		if (p == head->next && p != NULL)
			head->next = p->next;
		else if (p == head->next && p->next == NULL) {
			head->next = p->next;
			printf("信息已删除，先此通讯录为空！！\n");
			return 0;
		} else
			p1->next = p->next;
	} else {
		printf("此信息不存在！！！\n");
		return 0;
	}
	printf("\n此信息已删除！\n");
	printf("职工号\t姓名\t性别\t年龄\t学历\t工资\t\t地址\t\t\t\t\t电话号码\n");
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
		p->addr,
		p->phoneNum);
	filesave(head2);
	printf("返回上一级菜单输入1，结束请输入0！\n");
	int m;
	scanf("%d", &m);
	node *ptr = Fileread();
	if (m == 1) {
		printf("返回主菜单!\n");
		menu(ptr);
	}
	if (m == 0) {
		printf("结束操作！\n");
		exit(0);
	}
	return 0;
}


node *filesave(node *head) { // 将职工信息保存到文件
	int n;
	printf("是否想要保存到文件？是请输入1，否则输入0.\n");
	scanf("%d", &n);
	if (n == 1) {
		FILE *fp;
		fp = fopen("work.txt", "w");
		if (fp == NULL) {
			printf("文件无法打开!\n");
			return NULL;
		}
		node *pStaff = mergeSort(head->next);
		while (pStaff != NULL) {
			fprintf(fp, "%d %s %s %s %s %s %s %s\n", pStaff->number, pStaff->name, pStaff->sex, pStaff->age, pStaff->edu, pStaff->money, pStaff->addr,
			        pStaff->phoneNum);
			pStaff = pStaff->next;
		}
		fclose(fp);
	}
	return head;
}


int listread(node *head2) { //读取链表中职工信息
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("此系统中无记录!自动返回主菜单\n");
		menu(head);
		exit(0);
	}
	system("cls");     
	printf("\t\t\t\t\t职工信息管理系统!\n");
	printf("职工号\t姓名\t性别\t年龄\t学历\t工资\t\t地址\t\t\t\t\t电话号码\n");
	for (p = head->next; p != NULL; p = p->next)
		printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
		       p->addr,
		       p->phoneNum);
	int m;
	printf("返回上一级菜单输入1，退出系统请输入0！\n");
	scanf("%d", &m);
	while (m < 0 || m > 1) {
		printf("输入的选择无效,请再次输入:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("返回主菜单!\n");
		menu(head);
	} else if (m == 0) {
		printf("退出系统！\n");
		exit(0);
	}
	return 0;
}

void count(node *head) {//统计各个指标!
	node *p = head;
	system("cls");
	printf("\t\t\t\t\t职工信息管理系统!\n");
	printf("请输入你想要查询的条目：\n1 职工数目\n2 各个学历水平人数\n3 男女职工人数\n0 返回主菜单\n");
	int choice;
	int work_sum = 0;
	int edu_sum[5] = {0, 0, 0, 0, 0};
	int sex_sum[2] = {0, 0};
	scanf("%d", &choice);
	while (choice < 0 || choice > 3) {
		printf("输入无效,请输入正确的选项:");
		scanf("%d", &choice);
	}
	if (choice == 1) {
		while (p != NULL) {
			work_sum++;
			p = p->next;
		}
		system("cls");
		printf("\t\t\t\t\t职工信息管理系统!\n");
		printf("职工总人数为：%d\n", work_sum - 1);
	} else if (choice == 2) {
		while (p != NULL) {
			if (strcmp(p->edu, "专科") == 0) {
				edu_sum[0]++;
			} else if (strcmp(p->edu, "本科") == 0) {
				edu_sum[1]++;
			} else if (strcmp(p->edu, "研究生") == 0) {
				edu_sum[2]++;
			} else if (strcmp(p->edu, "博士") == 0) {
				edu_sum[3]++;
			} else if (strcmp(p->edu, "高中") == 0) {
				edu_sum[4]++;
			}
			p = p->next;
		}
		system("cls");
		printf("\t\t\t\t\t职工信息管理系统!\n");
		printf("各学历人数: 高中:%d  专科:%d  本科:%d  研究生:%d  博士:%d\n", edu_sum[4], edu_sum[0], edu_sum[1], edu_sum[2], edu_sum[3]);
	} else if (choice == 3) {
		while (p != NULL) {
			if (strcmp(p->sex, "男") == 0) {
				sex_sum[0]++;
			} else if (strcmp(p->sex, "女") == 0) {
				sex_sum[1]++;
			}
			p = p->next;
		}
		system("cls");
		printf("\t\t\t\t\t职工信息管理系统!\n");
		printf("男性职工人数:%d  女性职工人数:%d\n", sex_sum[0], sex_sum[1]);
	}
	int m;
	printf("再次统计其他请输入1, 返回主菜单输入2, 结束请输入0！\n");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("输入选择无效, 请再次输入:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("统计其他!\n");
		count(head);
	} else if (m == 2) {
		printf("返回主菜单！\n");
		menu(head);
	} else {
		system("cls"); //清屏操作
		printf("\t\t\t\t\t职工信息管理系统!\n");
		printf("\n\n\n\t\t\t\t感谢您的使用，欢迎再次光临！\n\n\n");
		exit(0);
	}
}



int nameSearch(node *head2) {
	system("cls"); //清屏操作
	printf("尊敬的用户，欢迎查找职工的信息（按照姓名查找）！\n");
	char name[MAX];
	printf("请输入你想查找的职工的姓名：");
	scanf("%s", name);
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("此系统中无记录!\n");
		exit(0);
	}
	int flag = 0;
	for (p = head->next; p != NULL; p = p->next) {
		if (strcmp(p->name, name) == 0) {
			if (flag == 0) {
				printf("\n职工号\t姓名\t性别\t年龄\t学历\t工资\t\t地址\t\t\t\t\t电话号码\n");
			}
			flag = 1;
			printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
			       p->addr,
			       p->phoneNum);
		}
	}
	if (flag == 0) {
		printf("输入无效!");
	}
	int m;
	printf("返回上一级菜单输入1，再次查找请输入2, 返回主菜单请输入0！\n请输入:");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("输入无效,请再次输入:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("返回上一级菜单!\n");
		search(head);
	} else if (m == 0) {
		printf("返回主菜单！\n");
		menu(head2);
	} else {
		nameSearch(head2);
	}
	return 0;
}

node* merge(node* a, node* b) {
	node dummy;
	node* tail = &dummy;
	dummy.next = NULL;

	while (a != NULL && b != NULL) {
		if (a->number < b->number) {
			tail->next = a;
			a = a->next;
		} else {
			tail->next = b;
			b = b->next;
		}
		tail = tail->next;
	}

	tail->next = (a != NULL) ? a : b;
	return dummy.next;
}

node* mergeSort(node* head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}

	node* slow = head;
	node* fast = head;
	node* prev;

	while (fast != NULL && fast->next != NULL) {
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	prev->next = NULL;

	node* left = mergeSort(head);
	node* right = mergeSort(slow);

	return merge(left, right);
}


int checkPerson(node *head, int person) {//判断这个人是否在链表中
	int flag = 0;
	node *p = head;
	while (p != NULL) {
		if (p->number == person) {
			flag = 1;
			return 1;
		}
		p = p->next;
	}
	if (flag == 0) {
		return 0;
	}
	return 0;
}


int checkPhoneNumber(node *head, char phoneNumber[20]) {
	int flag = 0;
	node *p = head;
	while (p != NULL) {
		if (strcmp(phoneNumber, p->phoneNum) == 0) {
			flag = 1;
			return 1;
		}
		p = p->next;
	}
	if (flag == 0) {
		return 0;
	}
	return 0;
}

