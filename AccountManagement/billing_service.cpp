#include<iostream>
#include<stdio.h>
#include"model.h"
#include"global.h"
#include"tools.h"
#include"billing_file.h"
using namespace std;

IpBillingNode BillingList = NULL;	//ȫ�ֶ���������Ϣ����������������Ϣ
int nbillingCount=0;	

int addBilling(Billing billing)
{
    return saveBilling (&billing,BILLINGPATH);
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
    IpBillingNode thisNode=BillingList, nextNode=NULL;
    while (thisNode!=NULL)
    {
        nextNode = thisNode->NextNode;
        delete thisNode;
        thisNode = nextNode;
        BillingList=NULL;
    }
}

int getBilling()
{
    int i=0;
    Billing* pBilling=NULL;	
    
    releaseBillingList();
    initBillingList();
    nbillingCount=getBillingCount(BILLINGPATH);
    pBilling = (Billing*)malloc(sizeof(Billing)*nbillingCount);//��̬�����ڴ�
    //���ļ��ж�ȡ������Ϣ����ӵ��ݴ�ָ����
    if (readBilling(pBilling ,BILLINGPATH)==0)
    {
        cout<<"��ȡʧ��";
        free(pBilling);
        return FALSE;
    }
    //����ȡ��������Ϣ��ӵ�������
    IpBillingNode p1=BillingList,p2=NULL;
    for (;i<nbillingCount;i++)
    {
        p2=new BillingNode;
        p2->BillingData=pBilling[i];
        p2->NextNode=NULL;
        p1=p1->NextNode=p2;
    }
    free(pBilling);
    return TRUE;
}

//ͨ�����Ų��Ҷ�Ӧ������Ϣ������������
Billing* checkBilling(const char *pName,int &nIndex)
{
    if (getBilling()!=0)
    {
        IpBillingNode BillingNow= NULL;
        nIndex=0;
        //����������в�ѯ
        for(BillingNow= BillingList->NextNode;BillingNow!=NULL;BillingNow=BillingNow->NextNode)
        {
            if ((strcmp(BillingNow->BillingData.aCardName,pName)==0)&&(BillingNow->BillingData.nStatus==0)) 
            {
                return &BillingNow->BillingData;				
            }
            nIndex++;
        }
    }
    return NULL;
}
