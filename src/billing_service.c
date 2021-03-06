#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing_file.h"
#include "global.h"

IpBillingNode BillingList = NULL; //全局定义消费信息链表保存所有消费信息
int nbillingCount = 0;

int addBilling(Billing billing)
{
    return saveBilling(&billing, BILLINGPATH);
}

int initBillingList()
{
    if (!BillingList)
    {
        BillingList = (BillingNode *)malloc(sizeof(BillingNode));
        BillingList->NextNode = NULL;
        return TRUE;
    }
    return FALSE;
}

void releaseBillingList()
{
    IpBillingNode thisNode = BillingList, nextNode = NULL;
    while (thisNode != NULL)
    {
        nextNode = thisNode->NextNode;
        free(thisNode);
        thisNode = nextNode;
        BillingList = NULL;
    }
}

int getBilling()
{
    int i = 0;
    Billing *pBilling = NULL;

    releaseBillingList();
    initBillingList();
    nbillingCount = getBillingCount(BILLINGPATH);
    pBilling = (Billing *)malloc(sizeof(Billing) * nbillingCount); //动态分配内存

    //从文件中读取消费信息并添加到暂存指针中
    if (readBilling(pBilling, BILLINGPATH) == 0)
    {
        printf("读取失败");
        free(pBilling);
        return FALSE;
    }

    //将读取的消费信息添加到链表中
    IpBillingNode p1 = BillingList, p2 = NULL;
    for (; i < nbillingCount; i++)
    {
        p2 = (BillingNode *)malloc(sizeof(BillingNode));
        p2->BillingData = pBilling[i];
        p2->NextNode = NULL;
        p1 = p1->NextNode = p2;
    }
    free(pBilling);
    return TRUE;
}

//通过卡号查找对应消费信息并保存索引号
Billing *checkBilling(const char *pName, int *nIndex)
{
    if (getBilling() != 0)
    {
        IpBillingNode BillingNow = NULL;
        *nIndex = 0;
        //遍历链表进行查询
        for (BillingNow = BillingList->NextNode; BillingNow != NULL; BillingNow = BillingNow->NextNode)
        {
            if ((strcmp(BillingNow->BillingData.aCardName, pName) == 0) && (BillingNow->BillingData.nStatus == 0))
            {
                return &BillingNow->BillingData;
            }
            *nIndex = (*nIndex) + 1;
        }
    }
    return NULL;
}
