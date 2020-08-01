#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "billing_file.h"
#include "global.h"
#include "model.h"
#include "tools.h"
using namespace std;

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
        BillingList = new BillingNode;
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
        delete thisNode;
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
        cout << "读取失败";
        free(pBilling);
        return FALSE;
    }
    //将读取的消费信息添加到链表中
    IpBillingNode p1 = BillingList, p2 = NULL;
    for (; i < nbillingCount; i++)
    {
        p2 = new BillingNode;
        p2->BillingData = pBilling[i];
        p2->NextNode = NULL;
        p1 = p1->NextNode = p2;
    }
    free(pBilling);
    return TRUE;
}

//通过卡号查找对应消费信息并保存索引号
Billing *checkBilling(const char *pName, int &nIndex)
{
    if (getBilling() != 0)
    {
        IpBillingNode BillingNow = NULL;
        nIndex = 0;
        //遍历链表进行查询
        for (BillingNow = BillingList->NextNode; BillingNow != NULL; BillingNow = BillingNow->NextNode)
        {
            if ((strcmp(BillingNow->BillingData.aCardName, pName) == 0) && (BillingNow->BillingData.nStatus == 0))
            {
                return &BillingNow->BillingData;
            }
            nIndex++;
        }
    }
    return NULL;
}
