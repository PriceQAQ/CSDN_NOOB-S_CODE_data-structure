#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

/**定义单链表结点的数据类型 mulpoly */
typedef
struct node {
	double coef;    // 系数
	int exp;        // 指数
	struct node *next;    // 指向下一项结点的指针
} mulpoly;

/**指数从高到低，逐项输入系数和指数，建立[带头结点的]单链表 */
mulpoly *create() {
	mulpoly *h, *p, *q;
	h = new mulpoly;    // 建立头结点(不存储数据)
	p = h;     // 头结点作为初始的前驱

	double x; //系数
	int y; //指数

	while(1) { //循环...
		/*(A)输入系数(x)和指数(y) */
		cin >> x;    // 输入系数
		cin >> y;    // 输入指数

		/*(B)根据系数(x)进行多项式项的处理,... */
		if( x==0 && y==0 ) {	//根据约定, 系数 & 指数 都为0, 则多项式输入结束
			break;
		} else if( x == 0 ) { //此多项式'项'的系数=0, 可以不需要次多项式'项'!
			continue;
		}

		/*(C)有效的多项式项,创建对应的链表结点 */
		//(C.1)创建一个新结点(保存此系数和指数)
		q = new mulpoly;

		//(C.2)赋值[系数+指数]
		q->coef = x;
		q->exp = y;

		/*(D)维护指针p的指向 */
		p->next = q;
		p = q;
	}

	// 最后一(项&结点)无后继
	p->next = NULL;

	return h;  // 返回头指针
}

/**遍历单链表，输出一元多项式 */
void output(mulpoly *h) {
	mulpoly *p;

	cout<<"Y=";

	p = h->next; //p指向头结点之后的结点(第一个结点)

	if(p == NULL) { //(1)多项式为空(NULL)
		cout << "0";
	} else {   //(2.1)输出多项式的第1项
		//(a)输出系数
		cout << p->coef;

		//(b)若指数不为0,则输出X符号
		if(p->exp != 0) //输出变量字母x
			cout << "X";

		//(c)若指数>1,则输出指数符号
		if(p->exp > 1) //输出指数
			cout << "^" << p->exp;

		//(d)维护游标指针，指向下一结点
		p = p->next;
	}

	//(2.2)逐项输出后续各项
	while(p != NULL) {
		//(a)若系数为"正",输出多项式的"+"号项， "-"号项无须处理
		if(p->coef > 0)
			cout << "+";
		//	else //系数带有符号'-'，不需要特殊处理此情况
		//	cout << "-";

		//(b)输出系数
		cout << p->coef;

		//(c)若指数不为0,则输出X符号
		if(p->exp != 0)
			cout << "X";

		//(d)若指数>1,则输出指数符号
		if(p->exp > 1)
			cout << "^" << p->exp;

		//(e)维护游标指针，指向下一结点
		p = p->next;
	}

	//(3)输出换行
	cout << endl;
}

/**两个多项式求和函数 */
mulpoly *poly_add(mulpoly *a, mulpoly *b) {
	mulpoly *c, *pa, *pb, *pc, *q;
	c = new mulpoly;     // 建立结果多项式单链表的头结点
pa= a->next;//指针pa指向a  
pb= b->next;//指针pb指向b 
pc = c;//指针pc指向c 
  while((pa!= NULL)&&(pb!= NULL)) //当线性表a，b都没有录入完时 
  {
	if(pa->exp > pb->exp)//当a的指数大于b的指数时 a录入 
	{
		q = new mulpoly;//新结点 
		q->coef = pa->coef; //指针q指向pb系数和指数
		q->exp = pa->exp;
		pa = pa->next;//pa指向下个结点 
		pc->next = q;//录入pa 
		pc = q;
		
	}
	else if(pa->exp < pb->exp)//当b的指数大于a的指数时 b录入 
	{
		q = new mulpoly;//新结点 	
		q->coef = pb->coef;//指针q指向pb的系数和指数 
		q->exp = pb->exp;
		pb = pb->next;// //pb指向下个结点
		pc->next = q;//录入pb 
		pc = q;
	}
	else if(fabs(pa->coef + pb->coef) > 1e-9)// 当a，b相等时，且 a，b相加项的系数 的绝对值大于1e-9 
	{
		q = new mulpoly;//新结点 
		q->coef = pa->coef + pb->coef ;//合并系数 
		q->exp = pa->exp ;//合并指针 
		pa= pa->next;	pb=pb->next;//维护pa，pb 
		pc->next = q;//录入 
		pc = q;
	}
	else//当a，b系数相加等于0时 
	{
		pa = pa->next;// 跳过当前pa和pb 
		pb = pb->next;
	}
}
while(pa!= NULL)//当线性表a没有完全录入时 
{
 	q = new mulpoly;//为q指针开辟空间 
 	q->coef = pa->coef; //录入pa 
	q->exp = pa->exp;
	pa = pa->next;
	pc->next = q;
	pc = q;
}
while(pb != NULL)//当线性表b没有完全录入时 
{
 	q = new mulpoly;//为q指针开辟空间 	
	q->coef = pb->coef;//录入pb 
	q->exp = pb->exp;
	pb = pb->next;
	pb->next = q;
	pb = q;
}
pc->next = NULL;// 维护指针 


	return c;     // 返回相加后的结果多项式的头结点
}

int main() {
	mulpoly *ha, *hb, *hc;
	//(A.1)调用函数create()创建一个多项式(指针ha:指向头结点)
	//cout<<"Input each item of a multipoly:\n";
	ha=create();

	//(A.2)调用函数create()创建另一个多项式(指针hb:指向头结点)
	//cout<<"Input each item of another multipoly:\n";
	hb=create();

	//(B)调用函数poly_add(...)
	hc=poly_add(ha,hb);

	//(C)输出多项式及其相加结果
	output(hc); //(C.3)输出多项式 多项式(ha) 和多项式(hb)之和

	return 0;
}
