#include<cstdio>
#include<cstring>
#include<string>
#include<malloc.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

// 定义一个结构体
struct dl_node
{
	int x;
	dl_node *pre;
	dl_node *next;
};

//结点的初始化
void list_init(dl_node ** h)
{
	*h=(dl_node *)malloc(sizeof(dl_node));
	(*h)->x=0;
	(*h)->pre=*h;
	(*h)->next=*h;
}


//插入一个元素，循环双向链表
void list_insert(dl_node *h,int x)
{
	h->x++;
	dl_node *s;
	s=(dl_node *)malloc(sizeof(dl_node));
	s->x=x;
	s->pre=h->pre;
	h->pre->next=s;
	s->next=h;
	h->pre=s;
}


//打印输出
void prin(dl_node *h)
{
	//cout<<h->x<<endl;
	dl_node *p;
	p=h->next;
	if(p==h)                //如果头结点为空，则直接输出0
	{
		puts("0");return;
	}
	cout<<p->x;
	p=p->next;
	while(p!=h)          //循环双向链表一直往右找，直到找到头结点为止
	{
		printf(",%04d",p->x); //%04d为对齐方式，当一个结点值不足4位则补齐
		p=p->next;
	}
	//cout<<p->x;
	puts("");
}


//元素值相加，已处理好h1比h2的长度大于等于h1的长度
//最后结果保存在h1（即长串中）
void list_add(dl_node *h1,dl_node *h2)
{
	dl_node *p=h1->pre,*q=h2->pre;
	int e=0;
	while(q!=h2)					//每次相加，如果有进位则保存到e变量中
	{
		int tmp=p->x+q->x+e;
		if(tmp>9999)
		{
			p->x=tmp%10000;
			e=tmp/10000;
		}
		else
			p->x=tmp;
		p=p->pre;
		q=q->pre;
	}
	//p=p->pre;

//当h1长度大于h2的时候，还要对未相加的部分进行操作
	while(p!=h1)
	{
		int tmp=p->x+e;
		if(tmp>9999)
		{
			p->x=tmp%10000;
			e=tmp/10000;
		}
		else p->x=tmp;
		p=p->pre;
	}
	p=h1->next;

//如果最高位得到的结果还有进位，那么就要再创建一个结点
	if(e!=0)
	{
		dl_node *s;
		s=(dl_node *)malloc(sizeof(dl_node));
		s->x=e;
		s->pre=p->pre;
		p->pre->next=s;
		s->next=p;
		p->pre=s;
	}
}


//元素值相减  方法同相加类似
//最后结果保存在h1（即长串中）
void list_sub(dl_node *h1,dl_node *h2)
{
	dl_node *p=h1->pre,*q=h2->pre;


//此处flag的值即位借位的值，借位的值为0或者为1，因为减0无关紧要
	int flag=0;
	while(q!=h2)
	{
		if(p->x-flag>=q->x)
		{
			p->x-=q->x+flag;
			flag=0;
		}
		else
		{
			p->x=p->x+10000-q->x-flag;
			//p->pre->x--;
			flag=1;
		}
		p=p->pre;
		q=q->pre;
	}
	//p=p->pre;
	//cout<<p->x<<endl;
//同样的，如果h1的长度大于h2的长度，那么对剩下的操作
	while(p!=h1)
	{
		if(p->x-flag<0)
		{
			p->x=p->x+10000-flag;
			flag=1;
		}
		else
		{
			p->x=p->x-flag;
			flag=0;
		}
		p=p->pre;
	}
	//cout<<p->x<<endl;
//如果最高位为0的话，那么就要删除最高位的结点了
	p=h1->next;
	while(p->x==0)
	{
		p->pre->next=p->next;
		p->next->pre=p->pre;
		p=h1->next;
	}
}
int main()
{
   // freopen("大数求和.txt","r",stdin);
	while(1)
	{
		puts("");
		char c;
		int a;
		dl_node *h1,*h2;
		list_init(&h1);
//输入元素，直到读入   " ;  "则停止输入第一个链表值
		while(1)
		{
		    //cout<<"asdfa";
			scanf("%d%c",&a,&c);
			//cout<<c<<endl;
			list_insert(h1,a);
			if(c==';') break;
		}
//如果第一个元素小于0，则取正值，并在头结点当中保存信息
		if(h1->next->x<0)
		{
			h1->x=-h1->x;
			h1->next->x=-h1->next->x;
		}
		//prin(h1);
		list_init(&h2);
		int r=0;
//相同方法输入第二个链表，碰到  " ; "则停止，并且读到文件结束
		while(1)
		{
			if(scanf("%d%c",&a,&c)==EOF)   {r=1;break;}
			list_insert(h2,a);
			if(c==';')break;
		}
		//cout<<r<<endl;
//如果第一个元素小于0，则取正值，并在头结点当中保存信息
		if(h2->next->x<0)
		{
			h2->x=-h2->x;
			h2->next->x=-h2->next->x;
		}

// h1_num和h2_num分别表示长度
		int h1_num=h1->x,h2_num=h2->x;

//把长的放到h1里面，是为了后面的加减操作更顺利
		if(abs(h1_num)<abs(h2_num))
		{
			dl_node *tmp=h1;
			h1=h2;
			h2=tmp;
			h1_num=h1->x,h2_num=h2->x;

		}
		//cout<<h1_num<<" "<<h2_num<<endl;

/*
此处为重点部分，分为两个部分，如果h1大于h2四种情况
     如果h1等于h2也有四种情况
*/

//其实在此处，可以缩减为6种情况，但为了方便，写了8种




//如果他们的长度不相等，即h1大于 h2了
		if(abs(h1_num)!=abs(h2_num))
		{
//如果都为正数
			if(h1_num>0&&h2_num>0)
			{
				//prin(h1);
				list_add(h1,h2);
				prin(h1);
				continue;
			}
//如果都为负数
			else if(h1_num<0&&h2_num<0)
			{
				list_add(h1,h2);
				cout<<"-";
				prin(h1);
				continue;
			}
//如果h1为正而h2为负
			else if(h1_num>0&&h2_num<0)
			{
				list_sub(h1,h2);
				prin(h1);
				continue;
			}
//如果h1为负而h2为正
			else if(h1_num<0&&h2_num>0)
			{
				cout<<"-";
				list_sub(h1,h2);
				prin(h1);
			}
		}
//否则，如果他们长度都相等的话：
		else
		{
//如果都为正数
			if(h1_num>0&&h2_num>0)
			{
				list_add(h1,h2);
				prin(h1);
				continue;
			}
//如果都为负数
			else if(h1_num<0&&h2_num<0)
			{
				list_add(h1,h2);
				cout<<"-";
				prin(h1);
				continue;
			}
//如果h1为正而h2为负
			else if(h1_num>0&&h2_num<0)
			{
//这种情况，如果h1最高结点元素大于h2的最高元素，那么交换链表
				if(h1->next->x<h2->next->x)
				{
					dl_node *tmp=h1;
					h1=h2;
					h2=tmp;
					//h1_num=h1->x,h2_num=h2->x;
					//prin(h1);
					//prin(h2);
//这种情况得先输出一个负号
					cout<<"-";
				}
//交换之后加法还是一样
				list_sub(h1,h2);
				prin(h1);
				continue;
			}
//如果h1为负而h2为正
			else if(h1_num<0&&h2_num>0)
			{
				if(h1->next->x<h2->next->x)
				{
					dl_node *tmp=h1;
					h1=h2;
					h2=tmp;
					//cout<<"-";
				}
//否则为负值，要输出负号
				else cout<<"-";
				list_sub(h1,h2);
				prin(h1);
			}
		}
		//puts("");
//r的值 为1，说明读到了文件结束，整个循环结束
		if(r==1) break;
	}
	return 0;
}


