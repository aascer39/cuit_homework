#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <Windows.h>
#include <conio.h>

#define MAX 100//����ְ����Ϣ�ı�
#define account 1
#define password 1
#define TRUE 1
#define FALSE 0

typedef struct staff { //�ṹ�嶨�壬���ţ��������Ա����䣬ѧ�������ʣ���ַ���绰����
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


int log_in(); //�û���¼ ���˺�������ȷ�ſ��Ե�¼��
void menu(node *head2); //�˵�
node *filesave(node *head); //��ְ����Ϣ���浽�ļ�
int listread(node *head2); //���������ְ����Ϣ���
void input(node *head2); //����1ְ����Ϣ¼��
int Eduserch(node *head2); //ְ����Ϣ��ѯ������ѧ����
int Numberserch(node *head2); //ְ����Ϣ��ѯ������ְ���Ų�ѯ��Ϣ��
void Modify(node *head2); //�޸�ְ����Ϣ�����չ��ţ�
int Delete(node *head2); //ɾ��ְ����Ϣ(���չ��ţ�
node *Fileread(void); //��ȡ�ļ���ְ����Ϣ��������
void View(node *head2); //���ȫ��Ա��������Ϣ
void count(node *head);//ͳ��Ա����Ϣ
void search(node *head);//���������˵�����
int nameSearch(node *head2);//������������
node* mergeSort(node* head);//����ְ��������
int checkPerson(node *head, int person);//���������Ƿ��������
int whichToModify();//ѡ�����Ҫ��ϸ�޸�ʲô
int checkPhoneNumber(node *head, char phoneNumber[20]);//���绰�����Ƿ��ظ�

int main() {
	node *head = Fileread(); //��ȡ�ļ���ְ����Ϣ�������� ,ͷ���������
	int R = log_in();

	if (R) {
		system("cls"); //��������<stdlib.h>
		printf("��½�ɹ���\n");
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
		printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
		printf("����������˺�:\n");
		scanf("%d", &acc);
		getchar();
		printf("�������������:\n");
		while(1){
			ch = getch();
			if(ch == '\r'){
				ps[i] = '\0';
				break;
			}else if (ch == '\b' && i > 0) {  // �����˸����ɾ��һ���ַ�
				printf("\b \b");  // ���ն���ɾ��һ���ַ�
				i--;
			}else {
				printf("*");  // ���ն�����ʾ*
				ps[i++] = ch;
			}
		}
		pass = atoi(ps);
		if (acc == account && pass == password) {
			printf("\n\n\n\t�˺�������ȷ,��ӭ����ϵͳ!\n");
            Sleep(1000);
			return 1;
		} else {
			printf("\n\n\n\t���ź�����˺Ż������������!\n");
			Sleep(2000);
		}
	}
}


int s_select() { //����ѡ��
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	int n;
	printf("1       ְ����Ϣ¼��           \n\n");
	printf("2       ְ����Ϣ���           \n\n");
	printf("3       ְ����Ϣ��ѯ  \n\n");
	printf("4       ְ����Ϣɾ��           \n\n");
	printf("5       ְ����Ϣ�޸�            \n\n");
	printf("6       ְ����Ϣͳ��\n\n");
	printf("0       �˳�ְ��ϵͳ            \n\n\n");
	printf("��������ѡ��:\t");
	scanf("%d", &n);
	while (n < 0 || n > 8) {
		printf("�޴�ѡ����������룺\n");
		scanf("%d", &n);
	}
	return n;
}


node *Fileread() { //��ȡ�ļ���ְ����Ϣ��������
	FILE *fp;
	node *p, *pre, *tail, *head;
	head = (node *) malloc(sizeof(node));
	tail = pre = head;
	fp = fopen("work.txt", "r");
	if (fp == NULL) {
		printf("�ļ���ʧ��!!!");
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

void menu(node *head2) { //�˵�
	system("cls"); //��������
	int m = s_select();
	switch (m) {
		case 1:
			printf("ѡ��1:ְ����Ϣ¼��\n");
			system("cls"); //��������
			input(head2); //����ְ����Ϣ�����浽�ļ�
			break;
		case 2:
			printf("ѡ��2:ְ����Ϣ���\n");
			system("cls"); //��������
			listread(head2); //���ȫ��ְ����Ϣ
			break;
		case 3:
			printf("ѡ��3:ְ����Ϣ��ѯ\n");
			system("cls"); //��������
			search(head2); //ְ����Ϣ��ѯ
			break;
		case 4:
			printf("ѡ��4:ְ����Ϣɾ��\n");
			system("cls"); //��������
			Delete(head2); //ɾ��ְ����Ϣ(����ְ���ţ�
			break;
		case 5:
			printf("ѡ��5:ְ����Ϣ�޸�\n");
			system("cls"); //��������
			Modify(head2); //�޸�ְ����Ϣ
			break;
		case 6:
			printf("ѡ��6����������ͳ��\n");
			system("cls");
			count(head2);
			break;
		case 0:
			printf("ѡ��0:�˳�ְ��ϵͳ\n");
			system("cls"); //��������
			printf("\n\n\n\t\t\t\t��л����ʹ�ã���ӭ�ٴι��٣�\n\n\n");
			getchar(); //���\n
			getchar();
			exit(0);
	}
}


void input(node *head2) { //����ְ����Ϣ
	system("cls"); //��������
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
		printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
		
		p = (node *) malloc(sizeof(node));
		printf("������ְ����(������100-999)��");
		scanf("%d", &number);
		while ((number < 100 || number > 999) || checkPerson(head2, number) == 1) {
			if((number < 100 || number > 999))	printf("����ְ������Ч,������100-999֮���ְ����:");
			else if(checkPerson(head2, number) == 1){
				printf("��ְ�����Ѵ���,����������:");
			}
			scanf("%d", &number);
		}
		p->number = number;
		
		char s[100];
		printf("����������:");
		scanf("%s", s);
		while (strlen(s) > 10 ) {
			printf("��Ч����!���ٴ�����:");
			scanf("%s", s);
		}
		strcpy(p->name, s);

		printf("�������Ա�:");
		scanf("%s", s);
		while (strcmp("��", s) != 0 && strcmp("Ů", s)) {
			printf("��Ч����!���ٴ�����:");
			scanf("%s", s);
		}
		strcpy(p->sex, s);
		

		int num;
		printf("����������:");
		scanf("%d", &num);
		char t[200];
		sprintf(t, "%d", num);
		while (num > 120 || num < 0 || strcmp(t, p->age) == 0) {
			printf("��Ч����!���ٴ�����:");
			scanf("%d", &num);
		}
		sprintf(p->age, "%d", num);

		printf("������ѧ��:");
		scanf("%s", s);
		while (strcmp(s, "����") != 0 && strcmp(s, "����") != 0 && strcmp(s, "ר��") != 0 && strcmp(s, "�о���") != 0 && strcmp(s, "��ʿ") != 0) {
			printf("��Ч����!���ٴ�����:");
			scanf("%s", s);
		}
		strcpy(p->edu, s);

		printf("�����빤��:");
		scanf("%s", s);
		while (strlen(s) > 20 ) {
			printf("��Ч����!���ٴ�����:");
			scanf("%s", s);
		}
		strcpy(p->money, s);

		printf("�������ַ:");
		scanf("%s", s);
		while (strlen(s) > 25) {
			printf("��Ч����!���ٴ�����:");
			scanf("%s", s);
		}
		strcpy(p->addr, s);

		printf("������绰����:");
		scanf("%s", s);
		while (strlen(s) != 11 || checkPhoneNumber(head2, s) == 1) {
			if(strlen(s) != 11){
				printf("�绰����λ������,����������:");
			}else{
				printf("�õ绰�����Ѵ���,����������:");
			}
			scanf("%s", s);
		}
		strcpy(p->phoneNum, s);
		printf("�Ѿ���ɵ�%d��ְ����Ϣ����ӣ�", i++);
		p->next = NULL;
		q->next = p;
		q = p;
		Sleep(1000);
		
		printf("\n����0�������룡����1������ӣ�\n");
		printf("������ѡ��");
		scanf("%d", &n);
		if(n == 0){
			break;
		}
	}
	filesave(head2);
	printf("�������˵�������0, ���ȫ����Ϣ������1\n");
	printf("������:");
	int choice;
	node* ptr = Fileread();
	scanf("%d", &choice);
	while(choice != 0 && choice != 1){
		printf("��Чѡ��,���ٴ�����:");
		scanf("%d", &choice);
	}
	if(choice == 1){
		listread(ptr);
	}else{
		menu(ptr);
	}
}

void search(node *head) {//��ѯ�����˵�
	system("cls");
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	printf("����������Ҫ��ѯ�ķ�ʽ��\n\n1 ����ְ���Ų�ѯ\n\n2 ����ѧ����ѯ\n\n3 ����������ѯ\n\n0 �������˵�\n\n");
	printf("���������ѡ��:");
	int choice;
	scanf("%d", &choice);
	while (choice < 0 || choice > 3) {
		printf("�޴�ѡ����������룺\n");
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

int Eduserch(node *head2) { //����ְ����Ϣ������ѧ����
	system("cls"); //��������
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	printf("�𾴵��û�����ӭ����ְ������Ϣ������ѧ�����ң���\n");
	char edu[MAX];
	printf("������������ҵ�ְ����ѧ����");
	scanf("%s", edu);
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("��ϵͳ���޼�¼!\n");
		exit(0);
	}
	int flag = 0;
	for (p = head->next; p != NULL; p = p->next) {
		if (strcmp(p->edu, edu) == 0) {
			if (flag == 0) {
				printf("\nְ����\t����\t�Ա�\t����\tѧ��\t����\t\t��ַ\t\t\t\t\t�绰����\n");
				flag = 1;
			}
			printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
			       p->addr,
			       p->phoneNum);
		}
	}

	if (flag == 0 ) {
		printf("�����ѧ��������,���ٴμ���Ƿ�������ȷ!\n");
	}
	int m;
	printf("������һ���˵�����1���ٴβ���������2, �������˵�������0��\n");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("�����ѡ����Ч,���ٴ�����:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("�����ϼ��˵�!\n");
		search(head);
	} else if (m == 0) {
		printf("�������˵���\n");
		menu(head2);
	} else {
		printf("�ٴν���ѧ������!");
		Eduserch(head2);
	}
	return 0;
}


int Numberserch(node *head2) { //����ְ����Ϣ������ְ��ְ���Ų��ң�
	system("cls"); //��������
	printf("�𾴵��û�����ӭ����ְ������Ϣ������ְ���Ų��ң���\n");
	int number;
	printf("������������ҵ�ְ����ְ���ţ�");
	scanf("%d", &number);
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("��ϵͳ���޼�¼!\n");
		exit(0);
	}
	int flag = 0;
	for (p = head->next; p != NULL; p = p->next) {
		if (p->number == number) {
			if (flag == 0) {
				printf("\nְ����\t����\t�Ա�\t����\tѧ��\t����\t\t��ַ\t\t\t\t\t�绰����\n");
				flag = 1;
			}
			printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
			       p->addr,
			       p->phoneNum);
		}
	}
	if (flag == 0) {
		printf("δ�ҵ���ְ����,���ٴκ�ʵְ����!\n");
	}

	int m;
	printf("������һ���˵�����1���ٴβ���������2, �������˵�������0��\n");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("������Ч, ���ٴ�����:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("�����ϼ��˵�!\n");

		search(head);
	} else if (m == 0) {
		printf("�������˵���\n");
		menu(head2);
	} else {
		Numberserch(head2);
	}
	return 0;
}

void Modify(node *head2) { //�޸�ְ����Ϣ�����չ��ţ�
	system("cls");
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	node *head = head2;
	node *p = head->next;
	int number;
	if (head == NULL) {
		printf("��ϵͳΪ��!\n");
		menu(head);
		exit(0);
	}
	printf("������Ҫ�޸�ְ����ְ���ţ�\n");
	scanf("%d", &number);
	while (checkPerson(head2, number) == 0) {
		printf("û���ҵ���Ա��!���������Ƿ���ȷ���ٴ�����!�����Ҫ����ְ����������-1.\n���������ѡ��:");
		scanf("%d", &number);
		if (number == -1) {
			search(head2);
		}
	}
	while (p != NULL && p->number != number) {

		p = p->next;
	}
	system("cls");
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	printf("�Ѿ��ҵ���Ա��,��ϸ��Ϣ����:\n");
	printf("ְ����\t����\t�Ա�\t����\tѧ��\t����\t\t��ַ\t\t\t\t\t�绰����\n");
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
	       p->addr,
	       p->phoneNum);

	int choice = whichToModify(head2);
	switch (choice) {
		case 1:
			int number;
			printf("������ְ����:");
			scanf("%d", &number);
			while (number < 100 || number > 999 || number == p->number) {
				printf("����ְ������Ч,������100-999֮���ְ����:");
				scanf("%d", &number);
			}
			p->number = number;
			break;
		case 2:
			char s[100];
			printf("����������:");
			scanf("%s", s);
			while (strlen(s) > 10 || strcmp(s, p->name) == 0) {
				printf("��Ч����!���ٴ�����:");
				scanf("%s", s);
			}
			strcpy(p->name, s);
			break;
		case 3:
			printf("�������Ա�:");
			scanf("%s", s);
			while ((strcmp("��", s) != 0 && strcmp("Ů", s)) != 0 || strcmp(s, p->sex) == 0) {
				printf("��Ч����!���ٴ�����:");
				scanf("%s", s);
			}
			strcpy(p->sex, s);
			break;
		case 4:
			int num;
			printf("����������:");
			scanf("%d", &num);
			char t[200];
			sprintf(t, "%d", num);
			while (num > 120 || num < 0 || strcmp(t, p->age) == 0) {
				printf("��Ч����!���ٴ�����:");
				scanf("%d", &num);
			}
			sprintf(p->age, "%d", num);
			break;
		case 5:
			printf("������ѧ��:");
			scanf("%s", s);
			while ((strcmp(s, "����") != 0 && strcmp(s, "����") != 0 && strcmp(s, "ר��") != 0 && strcmp(s, "�о���") != 0 && strcmp(s, "��ʿ") != 0) || strcmp(s, p->edu) == 0) {
				printf("��Ч����!���ٴ�����:");
				scanf("%s", s);
			}
			strcpy(p->edu, s);
			break;
		case 6:
			printf("�����빤��:");
			scanf("%s", s);
			while (strlen(s) > 20 || strcmp(s, p->money) == 0) {
				printf("��Ч����!���ٴ�����:");
				scanf("%s", s);
			}
			strcpy(p->money, s);
			break;
		case 7:
			printf("�������ַ:");
			scanf("%s", s);
			while (strlen(s) > 25 || strcmp(s, p->addr) == 0) {
				printf("��Ч����!���ٴ�����:");
				scanf("%s", s);
			}
			strcpy(p->addr, s);
			break;
		case 8:
			printf("������绰����:");
			scanf("%s", s);
			while (strlen(s) != 11 || strcmp(s, p->phoneNum) == 0) {
				printf("��Ч����!���ٴ�����:");
				scanf("%s", s);
			}
			strcpy(p->phoneNum, s);
			break;
		default:
			menu(head2);
			break;
	}
	printf("\n�޸ĳɹ�\n");
	printf("������һ���˵�����1���ٴ��޸�������2, ����������0��\n");
	int m;
	scanf("%d", &m);
	filesave(head2);
	node *ptr = Fileread();
	if (m == 1) {
		printf("�������˵�!\n");
		menu(ptr);
	} else if (m == 0) {
		printf("����������\n");
		exit(0);
	} else {
		Modify(ptr);
	}
}

int whichToModify() {
	printf("1.�޸�ְ����\n2.�޸�����\n3.�޸��Ա�\n4.�޸�����\n5.�޸�ѧ��\n6.�޸Ĺ���\n7.�޸ĵ�ַ\n8.�޸ĵ绰����\n0.�������˵�\n");
	printf("����������Ҫ�޸ĵ���Ŀ:");
	int choice;
	scanf("%d", &choice);
	while (choice < 0 || choice > 8) {
		printf("��Чѡ��! ���ٴ�����:");
		scanf("%d", &choice);
	}
	return choice;
}

int Delete(node *head2) { //ɾ��ְ����Ϣ(����ְ���ţ�
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	node *head;
	head = head2;
	int number; //�Ȳ��� ��ɾ��
	node *p = head->next, *p1 = head->next;

	if (head == NULL) {
		printf("��ͨѶ¼Ϊ�գ�\n");
		printf("�������˵���\n");
		menu(head);
		return 0;
	}
	printf("������Ҫɾ��ְ����ְ���ţ�\n");
	scanf("%d", &number);
	while (checkPerson(head2, number) == 0) {
		printf("δ�ҵ���ְ��,��Ҫ��������������-1,���ٴ�����:");
		scanf("%d", &number);
		if (number == -1) {
			nameSearch(head2);
		}
	}
	while (p != NULL && p->number != number) {
		p = p->next;
	}
	if (number == p->number) { //���ɾ����Ϣ
		if (p == head->next && p != NULL)
			head->next = p->next;
		else if (p == head->next && p->next == NULL) {
			head->next = p->next;
			printf("��Ϣ��ɾ�����ȴ�ͨѶ¼Ϊ�գ���\n");
			return 0;
		} else
			p1->next = p->next;
	} else {
		printf("����Ϣ�����ڣ�����\n");
		return 0;
	}
	printf("\n����Ϣ��ɾ����\n");
	printf("ְ����\t����\t�Ա�\t����\tѧ��\t����\t\t��ַ\t\t\t\t\t�绰����\n");
	printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
		p->addr,
		p->phoneNum);
	filesave(head2);
	printf("������һ���˵�����1������������0��\n");
	int m;
	scanf("%d", &m);
	node *ptr = Fileread();
	if (m == 1) {
		printf("�������˵�!\n");
		menu(ptr);
	}
	if (m == 0) {
		printf("����������\n");
		exit(0);
	}
	return 0;
}


node *filesave(node *head) { // ��ְ����Ϣ���浽�ļ�
	int n;
	printf("�Ƿ���Ҫ���浽�ļ�����������1����������0.\n");
	scanf("%d", &n);
	if (n == 1) {
		FILE *fp;
		fp = fopen("work.txt", "w");
		if (fp == NULL) {
			printf("�ļ��޷���!\n");
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


int listread(node *head2) { //��ȡ������ְ����Ϣ
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("��ϵͳ���޼�¼!�Զ��������˵�\n");
		menu(head);
		exit(0);
	}
	system("cls");     
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	printf("ְ����\t����\t�Ա�\t����\tѧ��\t����\t\t��ַ\t\t\t\t\t�绰����\n");
	for (p = head->next; p != NULL; p = p->next)
		printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
		       p->addr,
		       p->phoneNum);
	int m;
	printf("������һ���˵�����1���˳�ϵͳ������0��\n");
	scanf("%d", &m);
	while (m < 0 || m > 1) {
		printf("�����ѡ����Ч,���ٴ�����:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("�������˵�!\n");
		menu(head);
	} else if (m == 0) {
		printf("�˳�ϵͳ��\n");
		exit(0);
	}
	return 0;
}

void count(node *head) {//ͳ�Ƹ���ָ��!
	node *p = head;
	system("cls");
	printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
	printf("����������Ҫ��ѯ����Ŀ��\n1 ְ����Ŀ\n2 ����ѧ��ˮƽ����\n3 ��Ůְ������\n0 �������˵�\n");
	int choice;
	int work_sum = 0;
	int edu_sum[5] = {0, 0, 0, 0, 0};
	int sex_sum[2] = {0, 0};
	scanf("%d", &choice);
	while (choice < 0 || choice > 3) {
		printf("������Ч,��������ȷ��ѡ��:");
		scanf("%d", &choice);
	}
	if (choice == 1) {
		while (p != NULL) {
			work_sum++;
			p = p->next;
		}
		system("cls");
		printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
		printf("ְ��������Ϊ��%d\n", work_sum - 1);
	} else if (choice == 2) {
		while (p != NULL) {
			if (strcmp(p->edu, "ר��") == 0) {
				edu_sum[0]++;
			} else if (strcmp(p->edu, "����") == 0) {
				edu_sum[1]++;
			} else if (strcmp(p->edu, "�о���") == 0) {
				edu_sum[2]++;
			} else if (strcmp(p->edu, "��ʿ") == 0) {
				edu_sum[3]++;
			} else if (strcmp(p->edu, "����") == 0) {
				edu_sum[4]++;
			}
			p = p->next;
		}
		system("cls");
		printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
		printf("��ѧ������: ����:%d  ר��:%d  ����:%d  �о���:%d  ��ʿ:%d\n", edu_sum[4], edu_sum[0], edu_sum[1], edu_sum[2], edu_sum[3]);
	} else if (choice == 3) {
		while (p != NULL) {
			if (strcmp(p->sex, "��") == 0) {
				sex_sum[0]++;
			} else if (strcmp(p->sex, "Ů") == 0) {
				sex_sum[1]++;
			}
			p = p->next;
		}
		system("cls");
		printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
		printf("����ְ������:%d  Ů��ְ������:%d\n", sex_sum[0], sex_sum[1]);
	}
	int m;
	printf("�ٴ�ͳ������������1, �������˵�����2, ����������0��\n");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("����ѡ����Ч, ���ٴ�����:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("ͳ������!\n");
		count(head);
	} else if (m == 2) {
		printf("�������˵���\n");
		menu(head);
	} else {
		system("cls"); //��������
		printf("\t\t\t\t\tְ����Ϣ����ϵͳ!\n");
		printf("\n\n\n\t\t\t\t��л����ʹ�ã���ӭ�ٴι��٣�\n\n\n");
		exit(0);
	}
}



int nameSearch(node *head2) {
	system("cls"); //��������
	printf("�𾴵��û�����ӭ����ְ������Ϣ�������������ң���\n");
	char name[MAX];
	printf("������������ҵ�ְ����������");
	scanf("%s", name);
	node *head;
	head = head2;
	node *p;
	if (head->next == NULL) {
		printf("��ϵͳ���޼�¼!\n");
		exit(0);
	}
	int flag = 0;
	for (p = head->next; p != NULL; p = p->next) {
		if (strcmp(p->name, name) == 0) {
			if (flag == 0) {
				printf("\nְ����\t����\t�Ա�\t����\tѧ��\t����\t\t��ַ\t\t\t\t\t�绰����\n");
			}
			flag = 1;
			printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%-9s\t\t\t\t%s\n", p->number, p->name, p->sex, p->age, p->edu, p->money,
			       p->addr,
			       p->phoneNum);
		}
	}
	if (flag == 0) {
		printf("������Ч!");
	}
	int m;
	printf("������һ���˵�����1���ٴβ���������2, �������˵�������0��\n������:");
	scanf("%d", &m);
	while (m < 0 || m > 2) {
		printf("������Ч,���ٴ�����:");
		scanf("%d", &m);
	}
	if (m == 1) {
		printf("������һ���˵�!\n");
		search(head);
	} else if (m == 0) {
		printf("�������˵���\n");
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


int checkPerson(node *head, int person) {//�ж�������Ƿ���������
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

