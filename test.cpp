#include <stdio.h>
#include <stdlib.h>

// ����ڵ�
typedef struct RingNode
{
    int value;  // ֵ
    struct RingNode *next;
}RingNode, *RingNodePtr;

// ����Լɪ�򻷣�pHead:����ͷָ�룬count:����Ԫ�ظ���
void CreateRing(RingNodePtr pHead, int count)
{
    RingNodePtr pCurr = NULL, pPrev = NULL;
    int i = 1;
    pPrev = pHead;
    while(--count > 0)
    {
        pCurr = (RingNodePtr)malloc(sizeof(RingNode));
        i++;
        pCurr->value = i;
        pPrev->next = pCurr;
        pPrev = pCurr;
    }
    pCurr->next = pHead;  // ���ɻ�״����
}

void PrintRing(RingNodePtr pHead)
{
    RingNodePtr pCurr;
    printf("%d", pHead->value);
    pCurr = pHead->next;
    while(pCurr != NULL)
    {
        if(pCurr->value == 1)
            break;
        printf("\n%d", pCurr->value);
        pCurr = pCurr->next;
    }
}

void JosephuRing(RingNodePtr pHead, int m)
{
    RingNodePtr pCurr, pPrev;
    int i = 1;    // ����
    pCurr = pPrev = pHead;
    while(pCurr != NULL)
    {
        if (i == m)
        {
            // �߳���
            printf("\n%d", pCurr->value);    // ��ʾ��Ȧѭ��
            pPrev->next = pCurr->next;
            free(pCurr);
            pCurr = pPrev->next;
            i = 1;
        }
        pPrev = pCurr;
        pCurr = pCurr->next;
        if (pPrev == pCurr)
        {
            // ���һ��
            printf("\n%d", pCurr->value);    // ��ʾ��Ȧѭ��
            free(pCurr);
            break;
        }
        i++;
    }
}

int main()
{
    int m = 0, n = 0;
    RingNodePtr pHead = NULL;
    printf("***************   Josephus Ring   ****************\n");
    printf("  please input the numbers of the whole people:");
    scanf("%d", &n);
    printf("  input the member you don't want=");
    scanf("%d", &m);
    if(n <= 0 || m <= 0)
    {
        printf("Input Error\n");
        system("pause");
        return 0;
    }
    // ��������
    pHead = (RingNodePtr)malloc(sizeof(RingNode));
    pHead->value = 1;
    pHead->next = NULL;
    CreateRing(pHead, n);
#ifdef _DEBUG
    PrintRing(pHead);
#endif

    // ��ʼ��Ȧ
    printf("\nKick Order: ");
    JosephuRing(pHead, m);    
    printf("\n");
    system("pause");
    return 0;
}
