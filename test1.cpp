#include<cstdio>
#include<cstring>
#include<string>
#include<malloc.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

// ����һ���ṹ��
struct dl_node
{
	int x;
	dl_node *pre;
	dl_node *next;
};

//���ĳ�ʼ��
void list_init(dl_node ** h)
{
	*h=(dl_node *)malloc(sizeof(dl_node));
	(*h)->x=0;
	(*h)->pre=*h;
	(*h)->next=*h;
}


//����һ��Ԫ�أ�ѭ��˫������
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


//��ӡ���
void prin(dl_node *h)
{
	//cout<<h->x<<endl;
	dl_node *p;
	p=h->next;
	if(p==h)                //���ͷ���Ϊ�գ���ֱ�����0
	{
		puts("0");return;
	}
	cout<<p->x;
	p=p->next;
	while(p!=h)          //ѭ��˫������һֱ�����ң�ֱ���ҵ�ͷ���Ϊֹ
	{
		printf(",%04d",p->x); //%04dΪ���뷽ʽ����һ�����ֵ����4λ����
		p=p->next;
	}
	//cout<<p->x;
	puts("");
}


//Ԫ��ֵ��ӣ��Ѵ����h1��h2�ĳ��ȴ��ڵ���h1�ĳ���
//�����������h1���������У�
void list_add(dl_node *h1,dl_node *h2)
{
	dl_node *p=h1->pre,*q=h2->pre;
	int e=0;
	while(q!=h2)					//ÿ����ӣ�����н�λ�򱣴浽e������
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

//��h1���ȴ���h2��ʱ�򣬻�Ҫ��δ��ӵĲ��ֽ��в���
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

//������λ�õ��Ľ�����н�λ����ô��Ҫ�ٴ���һ�����
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


//Ԫ��ֵ���  ����ͬ�������
//�����������h1���������У�
void list_sub(dl_node *h1,dl_node *h2)
{
	dl_node *p=h1->pre,*q=h2->pre;


//�˴�flag��ֵ��λ��λ��ֵ����λ��ֵΪ0����Ϊ1����Ϊ��0�޹ؽ�Ҫ
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
//ͬ���ģ����h1�ĳ��ȴ���h2�ĳ��ȣ���ô��ʣ�µĲ���
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
//������λΪ0�Ļ�����ô��Ҫɾ�����λ�Ľ����
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
   // freopen("�������.txt","r",stdin);
	while(1)
	{
		puts("");
		char c;
		int a;
		dl_node *h1,*h2;
		list_init(&h1);
//����Ԫ�أ�ֱ������   " ;  "��ֹͣ�����һ������ֵ
		while(1)
		{
		    //cout<<"asdfa";
			scanf("%d%c",&a,&c);
			//cout<<c<<endl;
			list_insert(h1,a);
			if(c==';') break;
		}
//�����һ��Ԫ��С��0����ȡ��ֵ������ͷ��㵱�б�����Ϣ
		if(h1->next->x<0)
		{
			h1->x=-h1->x;
			h1->next->x=-h1->next->x;
		}
		//prin(h1);
		list_init(&h2);
		int r=0;
//��ͬ��������ڶ�����������  " ; "��ֹͣ�����Ҷ����ļ�����
		while(1)
		{
			if(scanf("%d%c",&a,&c)==EOF)   {r=1;break;}
			list_insert(h2,a);
			if(c==';')break;
		}
		//cout<<r<<endl;
//�����һ��Ԫ��С��0����ȡ��ֵ������ͷ��㵱�б�����Ϣ
		if(h2->next->x<0)
		{
			h2->x=-h2->x;
			h2->next->x=-h2->next->x;
		}

// h1_num��h2_num�ֱ��ʾ����
		int h1_num=h1->x,h2_num=h2->x;

//�ѳ��ķŵ�h1���棬��Ϊ�˺���ļӼ�������˳��
		if(abs(h1_num)<abs(h2_num))
		{
			dl_node *tmp=h1;
			h1=h2;
			h2=tmp;
			h1_num=h1->x,h2_num=h2->x;

		}
		//cout<<h1_num<<" "<<h2_num<<endl;

/*
�˴�Ϊ�ص㲿�֣���Ϊ�������֣����h1����h2�������
     ���h1����h2Ҳ���������
*/

//��ʵ�ڴ˴�����������Ϊ6���������Ϊ�˷��㣬д��8��




//������ǵĳ��Ȳ���ȣ���h1���� h2��
		if(abs(h1_num)!=abs(h2_num))
		{
//�����Ϊ����
			if(h1_num>0&&h2_num>0)
			{
				//prin(h1);
				list_add(h1,h2);
				prin(h1);
				continue;
			}
//�����Ϊ����
			else if(h1_num<0&&h2_num<0)
			{
				list_add(h1,h2);
				cout<<"-";
				prin(h1);
				continue;
			}
//���h1Ϊ����h2Ϊ��
			else if(h1_num>0&&h2_num<0)
			{
				list_sub(h1,h2);
				prin(h1);
				continue;
			}
//���h1Ϊ����h2Ϊ��
			else if(h1_num<0&&h2_num>0)
			{
				cout<<"-";
				list_sub(h1,h2);
				prin(h1);
			}
		}
//����������ǳ��ȶ���ȵĻ���
		else
		{
//�����Ϊ����
			if(h1_num>0&&h2_num>0)
			{
				list_add(h1,h2);
				prin(h1);
				continue;
			}
//�����Ϊ����
			else if(h1_num<0&&h2_num<0)
			{
				list_add(h1,h2);
				cout<<"-";
				prin(h1);
				continue;
			}
//���h1Ϊ����h2Ϊ��
			else if(h1_num>0&&h2_num<0)
			{
//������������h1��߽��Ԫ�ش���h2�����Ԫ�أ���ô��������
				if(h1->next->x<h2->next->x)
				{
					dl_node *tmp=h1;
					h1=h2;
					h2=tmp;
					//h1_num=h1->x,h2_num=h2->x;
					//prin(h1);
					//prin(h2);
//��������������һ������
					cout<<"-";
				}
//����֮��ӷ�����һ��
				list_sub(h1,h2);
				prin(h1);
				continue;
			}
//���h1Ϊ����h2Ϊ��
			else if(h1_num<0&&h2_num>0)
			{
				if(h1->next->x<h2->next->x)
				{
					dl_node *tmp=h1;
					h1=h2;
					h2=tmp;
					//cout<<"-";
				}
//����Ϊ��ֵ��Ҫ�������
				else cout<<"-";
				list_sub(h1,h2);
				prin(h1);
			}
		}
		//puts("");
//r��ֵ Ϊ1��˵���������ļ�����������ѭ������
		if(r==1) break;
	}
	return 0;
}


