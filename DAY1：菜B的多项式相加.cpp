#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

/**���嵥��������������� mulpoly */
typedef
struct node {
	double coef;    // ϵ��
	int exp;        // ָ��
	struct node *next;    // ָ����һ�����ָ��
} mulpoly;

/**ָ���Ӹߵ��ͣ���������ϵ����ָ��������[��ͷ����]������ */
mulpoly *create() {
	mulpoly *h, *p, *q;
	h = new mulpoly;    // ����ͷ���(���洢����)
	p = h;     // ͷ�����Ϊ��ʼ��ǰ��

	double x; //ϵ��
	int y; //ָ��

	while(1) { //ѭ��...
		/*(A)����ϵ��(x)��ָ��(y) */
		cin >> x;    // ����ϵ��
		cin >> y;    // ����ָ��

		/*(B)����ϵ��(x)���ж���ʽ��Ĵ���,... */
		if( x==0 && y==0 ) {	//����Լ��, ϵ�� & ָ�� ��Ϊ0, �����ʽ�������
			break;
		} else if( x == 0 ) { //�˶���ʽ'��'��ϵ��=0, ���Բ���Ҫ�ζ���ʽ'��'!
			continue;
		}

		/*(C)��Ч�Ķ���ʽ��,������Ӧ�������� */
		//(C.1)����һ���½��(�����ϵ����ָ��)
		q = new mulpoly;

		//(C.2)��ֵ[ϵ��+ָ��]
		q->coef = x;
		q->exp = y;

		/*(D)ά��ָ��p��ָ�� */
		p->next = q;
		p = q;
	}

	// ���һ(��&���)�޺��
	p->next = NULL;

	return h;  // ����ͷָ��
}

/**�������������һԪ����ʽ */
void output(mulpoly *h) {
	mulpoly *p;

	cout<<"Y=";

	p = h->next; //pָ��ͷ���֮��Ľ��(��һ�����)

	if(p == NULL) { //(1)����ʽΪ��(NULL)
		cout << "0";
	} else {   //(2.1)�������ʽ�ĵ�1��
		//(a)���ϵ��
		cout << p->coef;

		//(b)��ָ����Ϊ0,�����X����
		if(p->exp != 0) //���������ĸx
			cout << "X";

		//(c)��ָ��>1,�����ָ������
		if(p->exp > 1) //���ָ��
			cout << "^" << p->exp;

		//(d)ά���α�ָ�룬ָ����һ���
		p = p->next;
	}

	//(2.2)���������������
	while(p != NULL) {
		//(a)��ϵ��Ϊ"��",�������ʽ��"+"��� "-"�������봦��
		if(p->coef > 0)
			cout << "+";
		//	else //ϵ�����з���'-'������Ҫ���⴦������
		//	cout << "-";

		//(b)���ϵ��
		cout << p->coef;

		//(c)��ָ����Ϊ0,�����X����
		if(p->exp != 0)
			cout << "X";

		//(d)��ָ��>1,�����ָ������
		if(p->exp > 1)
			cout << "^" << p->exp;

		//(e)ά���α�ָ�룬ָ����һ���
		p = p->next;
	}

	//(3)�������
	cout << endl;
}

/**��������ʽ��ͺ��� */
mulpoly *poly_add(mulpoly *a, mulpoly *b) {
	mulpoly *c, *pa, *pb, *pc, *q;
	c = new mulpoly;     // �����������ʽ�������ͷ���
pa= a->next;//ָ��paָ��a  
pb= b->next;//ָ��pbָ��b 
pc = c;//ָ��pcָ��c 
  while((pa!= NULL)&&(pb!= NULL)) //�����Ա�a��b��û��¼����ʱ 
  {
	if(pa->exp > pb->exp)//��a��ָ������b��ָ��ʱ a¼�� 
	{
		q = new mulpoly;//�½�� 
		q->coef = pa->coef; //ָ��qָ��pbϵ����ָ��
		q->exp = pa->exp;
		pa = pa->next;//paָ���¸���� 
		pc->next = q;//¼��pa 
		pc = q;
		
	}
	else if(pa->exp < pb->exp)//��b��ָ������a��ָ��ʱ b¼�� 
	{
		q = new mulpoly;//�½�� 	
		q->coef = pb->coef;//ָ��qָ��pb��ϵ����ָ�� 
		q->exp = pb->exp;
		pb = pb->next;// //pbָ���¸����
		pc->next = q;//¼��pb 
		pc = q;
	}
	else if(fabs(pa->coef + pb->coef) > 1e-9)// ��a��b���ʱ���� a��b������ϵ�� �ľ���ֵ����1e-9 
	{
		q = new mulpoly;//�½�� 
		q->coef = pa->coef + pb->coef ;//�ϲ�ϵ�� 
		q->exp = pa->exp ;//�ϲ�ָ�� 
		pa= pa->next;	pb=pb->next;//ά��pa��pb 
		pc->next = q;//¼�� 
		pc = q;
	}
	else//��a��bϵ����ӵ���0ʱ 
	{
		pa = pa->next;// ������ǰpa��pb 
		pb = pb->next;
	}
}
while(pa!= NULL)//�����Ա�aû����ȫ¼��ʱ 
{
 	q = new mulpoly;//Ϊqָ�뿪�ٿռ� 
 	q->coef = pa->coef; //¼��pa 
	q->exp = pa->exp;
	pa = pa->next;
	pc->next = q;
	pc = q;
}
while(pb != NULL)//�����Ա�bû����ȫ¼��ʱ 
{
 	q = new mulpoly;//Ϊqָ�뿪�ٿռ� 	
	q->coef = pb->coef;//¼��pb 
	q->exp = pb->exp;
	pb = pb->next;
	pb->next = q;
	pb = q;
}
pc->next = NULL;// ά��ָ�� 


	return c;     // ������Ӻ�Ľ������ʽ��ͷ���
}

int main() {
	mulpoly *ha, *hb, *hc;
	//(A.1)���ú���create()����һ������ʽ(ָ��ha:ָ��ͷ���)
	//cout<<"Input each item of a multipoly:\n";
	ha=create();

	//(A.2)���ú���create()������һ������ʽ(ָ��hb:ָ��ͷ���)
	//cout<<"Input each item of another multipoly:\n";
	hb=create();

	//(B)���ú���poly_add(...)
	hc=poly_add(ha,hb);

	//(C)�������ʽ������ӽ��
	output(hc); //(C.3)�������ʽ ����ʽ(ha) �Ͷ���ʽ(hb)֮��

	return 0;
}
