#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "service.h"
#include "tools.h"
#include "global.h"
using namespace std;

extern IpCardNode cardList; //对全局卡信息链表头指针进行外部说明

void outputmeun()
{
    cout << "--------菜单--------" << endl;
    cout << "1.添加卡\n";
    cout << "2.查询卡\n";
    cout << "3.上机\n";
    cout << "4.下机\n";
    cout << "5.充值\n";
    cout << "6.退费\n";
    cout << "7.查询统计\n";
    cout << "8.注销卡\n";
    cout << "0.退出\n";
    cout << "请选择菜单项编号 (0-8):";
}

//添加卡菜单操作函数
void add()
{
    printf("\n-----------添加卡-----------\n");
    Card card;
    char aName[32] = {0}, aPwd[16] = {0};
    char status[20] = {0};
    cout << "请输入卡号（18位以内）：";
    scanf("%s", aName);
    cout << "请输入密码（8位以下）：";
    scanf("%s", aPwd);
    if (strlen(aName) > 18 || strlen(aPwd) > 8)
    {
        cout << "输入的卡号或密码不符合规定,添加失败。";
        return;
    }
    strcpy(card.aName, aName);
    strcpy(card.aPwd, aPwd);
    //查询是否已存在同名卡 调用findcardname
    if (findName(card.aName))
    {
        cout << "\n同名卡已存在,添加失败。";
        return;
    }
    //初始化卡信息
    cout << "请输入开卡金额: ";
    scanf("%f", &card.nBalance);
    card.fTotalUse = card.nBalance;
    card.nDel = 0;
    card.nUseCount = 0;
    card.nStatus = 0;
    card.tStart = card.tLastTime = card.tEnd = time(NULL);
    struct tm *starttime = localtime(&card.tStart);
    struct tm *endtime = localtime(&card.tEnd);
    endtime->tm_year = starttime->tm_year + 1;
    card.tEnd = mktime(endtime);
    InitcardListinfo();
    addCardinfo(card);
    statusInttoChar(card.nStatus, status);
    cout << "\n----添加的卡信息如下----\n卡号\t密码\t状态\t\t开卡金额\n"
         << card.aName << "\t" << card.aPwd << "\t" << status << "\t" << card.nBalance;
}

//查询卡菜单操作函数
void query()
{
    char aName[18] = {0};
    char aTime[20] = {0};
    char status[20] = {0};
    Card *pCard = NULL;
    int nIndex = 0;
    cout << "\n-----------查询-----------\n请输入查询卡号： ";
    bool cZ = false;
    do
    {
        cZ = false;
        cin >> aName;
        pCard = queryCardsinfo(aName, nIndex); //通过卡名模糊查找所有卡信息，保存至链表头
        if (pCard == NULL || nIndex == 0)
        {
            cZ = true;
            cout << "\n查找失败，无对应卡号，请重新输入查询卡号: ";
        }
    } while (cZ);
    cout << "\n您所查询的所有卡信息为:";
    for (int i = 0; i < nIndex; i++)
    {
        timeToString(pCard[i].tLastTime, aTime);
        statusInttoChar(pCard[i].nStatus, status);
        cout << "\n卡号\t状态\t\t余额\t累计使用\t使用次数\t上次使用时间\n";
        cout << pCard[i].aName << "\t" << status << "\t" << pCard[i].nBalance << "\t" << pCard[i].fTotalUse << "\t\t" << pCard[i].nUseCount << "\t\t" << aTime;
    }
}

void logon()
{
    cout << "----------上机---------\n";
    char aName[32] = {0}, aPwd[16] = {0}, aTime[20] = {0};
    cout << "请输入卡号（18位以内）：";
    scanf("%s", aName);
    cout << "请输入密码（8位以下）：";
    scanf("%s", aPwd);
    while (strlen(aName) > 18 || strlen(aPwd) > 8)
    {
        cout << "输入的卡号或密码不符合规定。";
        cout << "请重新输入卡号：";
        scanf("%s", aName);
        cout << "请重新输入密码：";
        scanf("%s", aPwd);
    }
    int result;
    LogonInfo pLogonInfo;
    result = dologon(aName, aPwd, &pLogonInfo);
    switch (result)
    {
    case 1:
    {
        //时间形式转换
        timeToString(pLogonInfo.tLogon, aTime);
        cout << "\n----------上机信息如下---------";
        cout << "\n卡号\t余额\t上机时间\n";
        cout << pLogonInfo.aCardName << "\t" << pLogonInfo.fBalance << "\t" << aTime;
        break;
    }
    case 2:
        cout << "卡状态错误，上机失败";
        break;
    case 3:
        cout << "余额不足，上机失败";
        break;
    default:
        cout << "查询信息有误,上机失败";
        break;
    }
}

void settle()
{
    cout << "----------下机---------\n";
    char aName[32] = {0}, aPwd[16] = {0}, aTime1[20] = {0}, aTime2[20] = {0};
    cout << "请输入下机卡号（18位以内）：";
    scanf("%s", aName);
    cout << "请输入密码（8位以下）：";
    scanf("%s", aPwd);
    while (strlen(aName) > 18 || strlen(aPwd) > 8)
    {
        cout << "输入的卡号或密码不符合规定。";
        cout << "请重新输入卡号：";
        scanf("%s", aName);
        cout << "请重新输入密码：";
        scanf("%s", aPwd);
    }
    int result;
    SettleInfo pSettleInfo;
    result = doSettle(aName, aPwd, &pSettleInfo);
    switch (result)
    {
    case 1:
    {
        timeToString(pSettleInfo.tStart, aTime1);
        timeToString(pSettleInfo.tEnd, aTime2);
        cout << "\n----------下机信息如下---------";
        cout << "\n卡号\t消费金额\t余额\t上机时间\t\t下机时间\n";
        cout << pSettleInfo.aCardName << "\t" << pSettleInfo.fAmount << "\t\t" << pSettleInfo.fBalance << "\t" << aTime1 << "\t" << aTime2;
        break;
    }
    case 2:
        cout << "卡状态错误，下机失败";
        break;
    case 3:
        cout << "余额不足，下机失败";
        break;
    default:
        cout << "查询信息有误,下机失败";
        break;
    }
}

void addMoney()
{
    cout << "----------充值---------\n";
    char aName[32] = {0}, aPwd[16] = {0};
    cout << "请输入充值卡号（18位以内）：";
    scanf("%s", aName);
    cout << "请输入密码（8位以下）：";
    scanf("%s", aPwd);
    while (strlen(aName) > 18 || strlen(aPwd) > 8)
    {
        cout << "输入的卡号或密码不符合规定。";
        cout << "请重新输入卡号：";
        scanf("%s", aName);
        cout << "请重新输入密码：";
        scanf("%s", aPwd);
    }
    cout << "请输入充值金额：";
    int result;
    MoneyInfo pMoneyInfo;
    cin >> pMoneyInfo.money;
    result = doAddMoney(aName, aPwd, &pMoneyInfo);
    switch (result)
    {
    case 1:
    {
        cout << "\n----------充值信息如下---------";
        cout << "\n卡号\t充值金额\t余额\n";
        cout << pMoneyInfo.aCardName << "\t" << pMoneyInfo.money << "\t\t" << pMoneyInfo.fBalance;
        break;
    }
    case 2:
        cout << "卡状态错误，充值失败";
        break;
    case 3:
        cout << "余额不足，充值失败";
        break;
    default:
        cout << "查询信息有误,充值失败";
        break;
    }
}

void refundMoney()
{
    cout << "----------退费---------\n";
    char aName[32] = {0}, aPwd[16] = {0};
    cout << "请输入退费卡号（18位以内）:";
    scanf("%s", aName);
    cout << "请输入密码（8位以下）:";
    scanf("%s", aPwd);
    while (strlen(aName) > 18 || strlen(aPwd) > 8)
    {
        cout << "输入的卡号或密码不符合规定。";
        cout << "请重新输入卡号：";
        scanf("%s", aName);
        cout << "请重新输入密码：";
        scanf("%s", aPwd);
    }
    int result;
    MoneyInfo pMoneyInfo;
    result = doRefundMoney(aName, aPwd, &pMoneyInfo);
    switch (result)
    {
    case 1:
    {
        cout << "\n----------退费信息如下---------";
        cout << "\n卡号\t退费金额\t余额\n";
        cout << pMoneyInfo.aCardName << "\t" << pMoneyInfo.money << "\t\t" << pMoneyInfo.fBalance;
        break;
    }
    case 2:
        cout << "卡状态错误，退费失败";
        break;
    case 3:
        cout << "余额不足，退费失败";
        break;
    default:
        cout << "查询信息有误,退费失败";
        break;
    }
}

void Quit()
{
    printf("---------退出--------");
    releaseList();
}
