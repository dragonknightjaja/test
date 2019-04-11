#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
测试样例
-2345,6789
-7654,3211

-9999,9999
1,0000,0000

0
0

1,0001,0001
-1,0001,0001

1,0001,0001
-1,0001,0000

-9999,9999,9999
-9999,9999,9999

1,0000,9999,9999
1

*/

// 设置输出的最长的整数长度
const int SIZE = 1000;

// 双向循环链表结点
struct DualNode
{
    int data;           // 链表每个结点的值
    int len;            // 链表的长度
    DualNode* prior;    // 前继结点
    DualNode* next;     // 后继结点
};

typedef DualNode* DuLinkList;

// 将字符串转换成链表
// 建的是无头的双向循环链表
void InitList(DuLinkList *L, char *str);
// 做加法
DuLinkList add(DuLinkList a1, DuLinkList b1);
// 做减法
DuLinkList sub(DuLinkList a1, DuLinkList b1);
// 选择何种计算方法
DuLinkList solve(DuLinkList a1, DuLinkList b1);
// 输出链表的结果
void print(DuLinkList a);



int main(int argc, char const *argv[])
{
    char a1[SIZE], b1[SIZE];
    printf("请输入第一个整数(每四位一组，组间用逗号隔开): ");
    scanf("%s", a1);

    printf("请输入第一个整数(每四位一组，组间用逗号隔开): ");
    scanf("%s", b1);

    DuLinkList *a = (DuLinkList*)malloc(sizeof(DuLinkList));
    DuLinkList *b = (DuLinkList*)malloc(sizeof(DuLinkList));
    InitList(a, a1);    // 初始化链表
    InitList(b, b1);    // 初始化链表

    // print(*a);
    // print(*b);
    DuLinkList res;
    res = solve(*a, *b);
    printf("结果: ");
    print(res);

    return 0;
}


// 将字符串转换成链表
// 建的是有头的双向循环链表
// 头部是符号位
void InitList(DuLinkList *L, char *str)
{
    DuLinkList p, q;
    (*L) = (DuLinkList)malloc(sizeof(DualNode));
    (*L)->prior = NULL;
    (*L)->next = NULL;
    (*L)->data = '+';           // 默认符号位为'+'
    p = (*L);

    int len = strlen(str);
    int cc = 1;
    int LEN = 0;

    int end = 0;
    if(str[0] == '-')
    {
        (*L)->data = '-';  
        end = 1;    // 如果是符号， 则只要到字符串第二个字符位置
    }

    for (int i = len-1; i >= end; --i)
    {
        if(cc % 5)
        {
            q = (DuLinkList)malloc(sizeof(DualNode));
            q->data = str[i] - '0';         // 字符串ascii值要减去'0'才是真的int值
            q->prior = p;
            p->next = q;
            p = q;
            ++LEN;
        }
        ++cc;
    }

    // 循环连接
    p->next = (*L);
    (*L)->prior = p;
    (*L)->len = LEN;                    // 记录链表的长度-1 ———— 不带符号位的长度
}

// 做加法
DuLinkList add(DuLinkList a1, DuLinkList b1)
{
    int len1 = a1->len;
    int len2 = b1->len;
    DuLinkList a, b;        // a为较长的整数链表， b为较短的整数链表
    if(len1 > len2)
    {
        a = a1;
        b = b1;
    }
    else 
    {
        a = b1;
        b = a1;
    }
    len1 = a->len;          // 较长链表长度
    len2 = b->len;          // 较短链表长度

    int cnt = 0;
    int ex = 0;             // 保存进位值
    while (cnt != len1)
    {
        a = a->next;
        b = b->next;

        if (cnt >= len2)    // 已经超过较短链表长度，所以不需要加b->data
            a->data = a->data + ex;
        else
            a->data = a->data + b->data + ex;
        ex = 0;
        if (a->data >= 10) a->data -= 10, ex = 1;   // 超过10表示有进位值
        ++cnt;
    }

    if (ex)
    {   // 如果最后一位还有进位
        // 则创建一个新的结点放到首部
        // 注意插入的顺序
        DuLinkList p = (DuLinkList)malloc(sizeof(DualNode));
        p->data = ex;

        p->next = a->next;
        a->next->prior = p;
        p->prior = a;
        a->next = p;

        a = p;
        ++len1;
    }
    a = a->next;       // 回到符号位
    a->len = len1;      // 注意头部长度变化
    return a;
}

// 做减法
DuLinkList sub(DuLinkList a1, DuLinkList b1)
{
    int len1 = a1->len;
    int len2 = b1->len;
    DuLinkList a, b;        // a为较长的整数链表， b为较短的整数链表
    if(len1 > len2)
    {
        a = a1;
        b = b1;
    }
    else if(len1 < len2)
    {
        a = b1;
        b = a1;
    }
    else
    {
        // 链表长度相同时， 以绝对值大的数为链表a
        DuLinkList tmp1 = a1, tmp2 = b1;
        int cnt = 0;
        tmp1 = tmp1->prior;
        tmp2 = tmp2->prior;
        while (cnt != len1)
        {
            if(tmp1->data > tmp2->data)
            {
                a = a1;
                b = b1;
                break;
            }
            else if(tmp1->data < tmp2->data)
            {
                a = b1;
                b = a1;
                break;
            }
            tmp1 = tmp1->prior;
            tmp2 = tmp2->prior;
            ++cnt;
        }
        if(cnt == len1)
        { // 如果两个数是一样的话， 就得执行这里了
            a = a1;
            b = b1;
        }
    }

    len1 = a->len;          // 较长链表长度
    len2 = b->len;          // 较短链表长度

    int cnt = 0;
    int ex = 0;             // 保存借位值
    while (cnt != len1)
    {
        a = a->next;
        b = b->next;

        if (cnt >= len2)    // 已经超过较短链表长度，所以不需要减b->data
            a->data = a->data - ex;
        else
            a->data = a->data - b->data - ex;
        ex = 0;
        if (a->data < 0) a->data += 10, ex = 1;   // 小于0表示有借位
        ++cnt;
    }

    // 由于是较大的绝对值减去较小的绝对值， 所以最终不会有最高位的借位
    a = a->next;       // 回到符号位
    a->len = len1;      // 注意头部长度变化
    return a;
}

DuLinkList solve(DuLinkList a1, DuLinkList b1)
{
    DuLinkList res;
    if(!(a1->data ^ b1->data))
    {   // 同号做加法
        res = add(a1, b1);
    }
    else
    {   // 异号做减法
        res = sub(a1, b1);
    }
    return res;
}


// 输出链表的结果
void print(DuLinkList a)
{
    int len = a->len;

    DuLinkList tmp = a;
    if(a->data == '-')
    {
        printf("%c", a->data);
        a = a->prior;
        while(a->data == 0 && a->prior != tmp) 
        { // 第二个条件是避免把 0 的结果去掉
            a = a->prior; // 去掉前导零
            --len;
        }
    }
    else
    {
        a = a->prior;
        while(a->data == 0 && a->prior != tmp) 
        { // 第二个条件是避免把 0 的结果去掉
            a = a->prior; // 去掉前导零
            --len;
        }
    }
    while (len)
    { // 从头开始输出链表
        printf("%d", a->data);
        a = a->prior;
        --len;
        if(!(len%4) && len) putchar(',');
    }
    puts("");
}

