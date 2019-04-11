#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include<math.h> 
#define N 100 

typedef int DataType;

typedef struct DoubleNode //定义链表元素 
{ 
 	DataType data; 
 	struct DoubleNode *prior; 
 	struct DoubleNode *next; 
}DLNode; 

void InitNode(DLNode **head) //初始化链表
{
    if((*head=(DLNode*)malloc(sizeof(DLNode)))==NULL)
    	exit(1); 
    (*head)->prior=*head; 
    (*head)->next=*head; 
}

int InsertNode(DLNode *head,int n,DataType x) //向链表第N个位置插入元素X 
{ 
 	DLNode *p,*nt; 
 	int i=0; 
 	p=head->next; 
 	while(p!=head&&i<n)
 	{ 
 		p=p->next; i++; 
 	} 
 	if(i!=n)
 	{ 
 		printf("插入位置错误\n"); 
 		return 0;
 	} 
 	if((nt=(DLNode *)malloc(sizeof(DLNode)))==NULL)
 		exit(1); 
 	nt->data=x; 
 	nt->prior=p->prior;
 	nt->prior->next=nt; 
 	nt->next=p; 
 	p->prior=nt; 
 	return 1;
}

int digit(int n) //判断整数N有几位
{ 
 	int i; 
 	for(i=1;;n/=10,i++) 
 	{
 		if(n/10==0)
 			return i;
 	}
 } 

void PrintNode(DLNode *head) //打印链表 
{ 
	DLNode *p=head->next;
 	int i; 
   	while(p->data==0) //去掉前面的一串0 
   	{ 
   		p=p->next;
   		if(p==head) 
   		{ 
   			printf("0\n"); 
   			return;
   		}
   	}
   	printf("%d",p->data); //最前面的一个数进行特殊处理,不用补零
   	p=p->next;
   	while(p!=head) //打印后面的数字 
   	{ 
   		printf(","); 
   		if(p->data==0) 
  		{ 
   			printf("0000"); 
   			p=p->next; 
   			continue;
   		} 
 		for(i=0;i<4-digit(p->data);i++) //补零 
 			printf("0"); 
 		printf("%d",p->data); 
 		p=p->next; 
	} 
	printf("\n"); 
} 

void DestroyNode(DLNode **head)
{ 
	DLNode *p,*p1;
	p=(*head)->next; 
	while(p!=*head) 
		{ 
			p1=p;
			p=p->next;
			free(p1);
		}
		free(p);
		head=NULL;
	}

void calculate(DLNode *h1,DLNode *h2) //计算
{ 
	DLNode *p1=h1->prior,*p2=h2->prior; 
	while(p1!=h1&&p2!=h2) //每个链表元素相加 
	{ 
		p1->data+=p2->data ; 
		p1=p1->prior; p2=p2->prior; 
	}
	p1=h1->prior;
   	while(p1!=h1->next) //处理链表元素 
   	{ 
   		if(p1->data>=10000) 
   		{ 
   			p1->prior->data+=p1->data/10000; 
    		p1->data%=10000; 
    	} 
    	if(p1->data<0) //处理负数 
    	{ 
	    	if(h1->next!=0) 
	    	{ 
	    		p1->prior->data-=1;
	    		p1->data+=10000; 
	    	} 
    	} 
    	p1=p1->prior; 
    } 
   	if(h1->next->data>=10000) //处理最前面的数
   	{ 
   		InsertNode(h1,0,h1->next->data/10000); 
   		h1->next->next->data%=10000; 
   	} 
   	if(h1->data<=-10000) 
   	{ 
   		InsertNode(h1,0,h1->next->data/10000);
   		h1->next->next->data%=-10000; 
   	}
   	PrintNode(h1); 
} 

int main() //主函数
{ 
	DLNode *head1,*head2;
	InitNode(&head1); 
	InitNode(&head2); 
	char data1[N],data2[N];
	char d1[10],d2[10]; 
	int i,j,k; 
	int choice;
	while(1) 
	{ 
		printf("\n"); 
		printf("请输入数据：\n");
		scanf("%s %s",data1,data2);
		InitNode(&head1);
		InitNode(&head2); 
		i=0;k=0; 
   	while(data1[i]!=';') //将数1用链表储存 
  	{
   		for(j=0;j<10;j++) 
   			d1[j]=0; 
   		j=0; 
   		while(data1[i]!=';'&&data1[i]!=',') 
   			d1[j++]=data1[i++]; 
   		if(data1[i]==',') 
   		i++; 
   		if(data1[0]=='-') //处理正负数 
	 		j=-(int)fabs(atoi(d1));//将字符串转换成整数 
		else j=atoi(d1); 
		InsertNode(head1,k++,j);
	}
	i=0;
	k=0; 
   	while(data2[i]!=';') //将数2用链表储存
   	{ 
   		for(j=0;j<10;j++) 
   			d2[j]=0; j=0;
   		while(data2[i]!=';'&&data2[i]!=',') 
   			d2[j++]=data2[i++]; 
   		if(data2[i]==',') 
   			i++; 
   		if(data2[0]=='-') //处理正负数
   			j=-(int)fabs(atoi(d2));
   		else j=atoi(d2); 
   		InsertNode(head2,k++,j); }
   		if(strlen(data1)>strlen(data2)) //较长的数作为被加数 
		   	calculate(head1,head2); 
		else calculate(head2,head1);
		DestroyNode(&head1); 
		DestroyNode(&head2); 
	} 
	return 0; 
}

