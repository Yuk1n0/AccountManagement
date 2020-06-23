#include<iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"model.h"
#include"service.h"
#include"tools.h"
#include"global.h"
using namespace std;

extern IpCardNode cardList;		//��ȫ�ֿ���Ϣ����ͷָ������ⲿ˵��

void outputmeun()
{
    cout<<"--------�˵�--------"<<endl;
    cout<<"1.��ӿ�\n";
    cout<<"2.��ѯ��\n";
    cout<<"3.�ϻ�\n";
    cout<<"4.�»�\n";
    cout<<"5.��ֵ\n";
    cout<<"6.�˷�\n";
    cout<<"7.��ѯͳ��\n";
    cout<<"8.ע����\n";
    cout<<"0.�˳�\n";
    cout<<"��ѡ��˵����� (0-8):";
}

//��ӿ��˵���������
void add()
{
    printf("\n-----------��ӿ�-----------\n");
    Card card;
    char aName[32]={0},aPwd[16]={0};
    char status[20]={0};
    cout<<"�����뿨�ţ�18λ���ڣ���";
    scanf("%s",aName);
    cout<<"���������루8λ���£���";
    scanf("%s",aPwd);
    if (strlen(aName)>18 ||strlen(aPwd)>8)
    {
        cout<<"����Ŀ��Ż����벻���Ϲ涨,���ʧ�ܡ�";
        return ;
    }
    strcpy(card.aName,aName);
    strcpy(card.aPwd,aPwd);
    //��ѯ�Ƿ��Ѵ���ͬ���� ����findcardname
    if (findName(card.aName))
    {
        cout<<"\nͬ�����Ѵ���,���ʧ�ܡ�";
        return ;
    }
    //��ʼ������Ϣ
    cout<<"�����뿪�����: ";
    scanf("%f",&card.nBalance);
    card.fTotalUse = card.nBalance;
    card.nDel=0;
    card.nUseCount=0;
    card.nStatus=0;
    card.tStart=card.tLastTime=card.tEnd=time(NULL);
    struct tm *starttime=localtime(&card.tStart);
    struct tm *endtime=localtime(&card.tEnd);
    endtime->tm_year=starttime->tm_year+1;
    card.tEnd=mktime(endtime);
    InitcardListinfo();
    addCardinfo(card);
    statusInttoChar(card.nStatus,status);
    cout<<"\n----��ӵĿ���Ϣ����----\n����\t����\t״̬\t\t�������\n"<<card.aName<<"\t"<<card.aPwd<<"\t"<<status<<"\t"<<card.nBalance;
}

//��ѯ���˵���������
void query(){
    char aName[18]={0};
    char aTime[20]={0};
    char status[20]={0};
    Card* pCard=NULL;
    int nIndex=0;
    cout<<"\n-----------��ѯ-----------\n�������ѯ���ţ� ";
    bool cZ=false;
    do
    {
        cZ=false;
        cin>>aName;
        pCard=queryCardsinfo(aName,nIndex);		//ͨ������ģ���������п���Ϣ������������ͷ
        if (pCard==NULL||nIndex==0) 
        {
            cZ=true;cout<<"\n����ʧ�ܣ��޶�Ӧ���ţ������������ѯ����: ";
        }
    }while (cZ);
    cout<<"\n������ѯ�����п���ϢΪ:";
    for (int i=0;i<nIndex;i++)
    {
        timeToString(pCard[i].tLastTime,aTime);
        statusInttoChar(pCard[i].nStatus,status);
        cout<<"\n����\t״̬\t\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n";
        cout<<pCard[i].aName<<"\t"<<status<<"\t"<<pCard[i].nBalance<<"\t"<<pCard[i].fTotalUse<<"\t\t"<<pCard[i].nUseCount<<"\t\t"<<aTime;
    }		
}

void logon()
{
    cout<<"----------�ϻ�---------\n";
    char aName[32]={0},aPwd[16]={0},aTime[20]={0};
    cout<<"�����뿨�ţ�18λ���ڣ���";
    scanf("%s",aName);
    cout<<"���������루8λ���£���";
    scanf("%s",aPwd);
    while (strlen(aName)>18 ||strlen(aPwd)>8)
    {
        cout<<"����Ŀ��Ż����벻���Ϲ涨��";
        cout<<"���������뿨�ţ�";
        scanf("%s",aName);
        cout<<"�������������룺";
        scanf("%s",aPwd);
    }
    int result;
    LogonInfo pLogonInfo;
    result= dologon(aName,aPwd,&pLogonInfo);
    switch(result)
    {
        case 1: 
        {
            //ʱ����ʽת��
            timeToString(pLogonInfo.tLogon,aTime);
            cout<<"\n----------�ϻ���Ϣ����---------";
            cout<<"\n����\t���\t�ϻ�ʱ��\n";
            cout<<pLogonInfo.aCardName<<"\t"<<pLogonInfo.fBalance<<"\t"<<aTime;
            break;
        }
        case 2:	cout<<"��״̬�����ϻ�ʧ��";break;
        case 3:	cout<<"���㣬�ϻ�ʧ��";break;
        default :cout<<"��ѯ��Ϣ����,�ϻ�ʧ��";break;
    }
}

void settle()
{
    cout<<"----------�»�---------\n";
    char aName[32]={0},aPwd[16]={0},aTime1[20]={0},aTime2[20]={0};
    cout<<"�������»����ţ�18λ���ڣ���";
    scanf("%s",aName);
    cout<<"���������루8λ���£���";
    scanf("%s",aPwd);
    while (strlen(aName)>18 ||strlen(aPwd)>8)
    {
        cout<<"����Ŀ��Ż����벻���Ϲ涨��";
        cout<<"���������뿨�ţ�";
        scanf("%s",aName);
        cout<<"�������������룺";
        scanf("%s",aPwd);
    }
    int result;
    SettleInfo pSettleInfo;
    result=doSettle(aName,aPwd,&pSettleInfo);
    switch (result)
    {
        case 1: 
        {
            timeToString(pSettleInfo.tStart,aTime1);
            timeToString(pSettleInfo.tEnd,aTime2);
            cout<<"\n----------�»���Ϣ����---------";
            cout<<"\n����\t���ѽ��\t���\t�ϻ�ʱ��\t\t�»�ʱ��\n";
            cout<<pSettleInfo.aCardName<<"\t"<<pSettleInfo.fAmount<<"\t\t"<<pSettleInfo.fBalance<<"\t"<<aTime1<<"\t"<<aTime2;
            break;
        }
        case 2:	cout<<"��״̬�����»�ʧ��";break;
        case 3:	cout<<"���㣬�»�ʧ��";break;
        default :cout<<"��ѯ��Ϣ����,�»�ʧ��";break;
    }
}

void addMoney()
{
    cout<<"----------��ֵ---------\n";
    char aName[32]={0},aPwd[16]={0};
    cout<<"�������ֵ���ţ�18λ���ڣ���";
    scanf("%s",aName);
    cout<<"���������루8λ���£���";
    scanf("%s",aPwd);
    while (strlen(aName)>18 ||strlen(aPwd)>8)
    {
        cout<<"����Ŀ��Ż����벻���Ϲ涨��";
        cout<<"���������뿨�ţ�";
        scanf("%s",aName);
        cout<<"�������������룺";
        scanf("%s",aPwd);
    }
    cout<<"�������ֵ��";
    int result;
    MoneyInfo pMoneyInfo;
    cin>>pMoneyInfo.money;
    result=doAddMoney(aName,aPwd,&pMoneyInfo);
    switch(result)
    {
        case 1: 
        {
            cout<<"\n----------��ֵ��Ϣ����---------";
            cout<<"\n����\t��ֵ���\t���\n";
            cout<<pMoneyInfo.aCardName<<"\t"<<pMoneyInfo.money<<"\t\t"<<pMoneyInfo.fBalance;
            break;
        }
        case 2:	cout<<"��״̬���󣬳�ֵʧ��";break;
        case 3:	cout<<"���㣬��ֵʧ��";break;
        default :cout<<"��ѯ��Ϣ����,��ֵʧ��";break;
    }
}

void refundMoney()
{
    cout<<"----------�˷�---------\n";
    char aName[32]={0},aPwd[16]={0};
    cout<<"�������˷ѿ��ţ�18λ���ڣ�:";
    scanf("%s",aName);
    cout<<"���������루8λ���£�:";
    scanf("%s",aPwd);
    while (strlen(aName)>18 ||strlen(aPwd)>8)
    {
        cout<<"����Ŀ��Ż����벻���Ϲ涨��";
        cout<<"���������뿨�ţ�";
        scanf("%s",aName);
        cout<<"�������������룺";
        scanf("%s",aPwd);
    }
    int result;
    MoneyInfo pMoneyInfo;
    result=doRefundMoney(aName,aPwd,&pMoneyInfo);
    switch(result)
    {
        case 1: 
        {
            cout<<"\n----------�˷���Ϣ����---------";
            cout<<"\n����\t�˷ѽ��\t���\n";
            cout<<pMoneyInfo.aCardName<<"\t"<<pMoneyInfo.money<<"\t\t"<<pMoneyInfo.fBalance;
            break;
        }
        case 2:	cout<<"��״̬�����˷�ʧ��";break;
        case 3:	cout<<"���㣬�˷�ʧ��";break;
        default:cout<<"��ѯ��Ϣ����,�˷�ʧ��";break;
    }
}

void Quit()
{
    printf("---------�˳�--------");
    releaseList();
}
