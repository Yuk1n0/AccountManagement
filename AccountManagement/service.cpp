#include<iostream>
#include<stdio.h>
#include"model.h"
#include"global.h"
#include"card_sevice.h"
#include"billing_service.h"
#include"card_file.h"
#include"billing_file.h"
#include"money_file.h"
using namespace std;

float getAmount(time_t tStart);
//查询同名卡
int findName(const char* pName)
{
    return FindCardName(pName, CARDPATH);
}

int addCardinfo(Card card)
{
    return addCard(card);
}

Card* queryCardinfo(const char* pName)
{
    Card* pCard = NULL;
    pCard = queryCard(pName);
    return pCard;
}

Card* queryCardsinfo(const char* pName, int& nIndex)
{
    Card* pCard = NULL;
    pCard = queryCards(pName, nIndex);
    return pCard;
}

int dologon(const char* pName, const char* aPwd, LogonInfo* pLogonInfo)
{
    Card* CardData = NULL;
    int nIndex = 0;
    CardData = checkCard(pName, aPwd, nIndex);
    if (CardData != NULL)
    {
        //未上机的卡才能上机
        if (CardData->nStatus != 0)
        {
            return UNUSE;
        }
        //余额大于等于0 才能上机
        if (CardData->nBalance <= 0)
        {
            return ENOUGHMONEY;
        }
        CardData->nStatus = 1;
        CardData->nUseCount++;
        CardData->tLastTime = time(NULL);
        if (updataCard(CardData, CARDPATH, nIndex))
        {
            Billing billing;
            strcpy(billing.aCardName, pName);
            billing.tStart = CardData->tLastTime;
            billing.nStatus = 0;
            billing.nDel = 0;
            if (addBilling(billing))
            {
                strcpy(pLogonInfo->aCardName, pName);
                pLogonInfo->fBalance = CardData->nBalance;
                pLogonInfo->tLogon = billing.tStart;
                return TRUE;
            }
        }
    }
    return FALSE;
}

int doSettle(const char* pName, const char* aPwd, SettleInfo* pInfo)
{
    Card* CardData = NULL;
    int ncardIndex = 0;
    CardData = checkCard(pName, aPwd, ncardIndex);
    Billing* BillingData;
    int nbillingIndex = 0;
    BillingData = checkBilling(pName, nbillingIndex);
    if ((CardData != NULL) && (BillingData != NULL))
    {
        if (CardData->nStatus != 1)
        {
            return UNUSE;
        }
        if (CardData->nBalance <= 0)
        {
            return ENOUGHMONEY;
        }
        float monUse = getAmount(BillingData->tStart);
        //计算下机卡余额 余额小于消费金额不能下机
        float fbalance = CardData->nBalance - monUse;
        if (fbalance < 0)
        {
            return ENOUGHMONEY;
        }
        CardData->nStatus = 0;
        CardData->nBalance = fbalance;
        CardData->tLastTime = time(NULL);
        if (updataCard(CardData, CARDPATH, ncardIndex))
        {
            BillingData->fAmount = monUse;
            BillingData->nStatus = 1;
            BillingData->tEnd = CardData->tLastTime;
            if (updataBilling(BillingData, BILLINGPATH, nbillingIndex))
            {
                strcpy(pInfo->aCardName, pName);
                pInfo->fAmount = monUse;
                pInfo->fBalance = fbalance;
                pInfo->tStart = BillingData->tStart;
                pInfo->tEnd = BillingData->tEnd;
                return TRUE;
            }
        }
    }
    return FALSE;
}

float getAmount(time_t tStart)
{
    time_t tEnd = time(NULL);
    int sec = tEnd - tStart;
    int min = UNIT * 60;
    if (sec % min == 0)
        return sec / min * CHARGE;
    else
        return (sec / min + 1) * CHARGE;
}

bool InitcardListinfo()
{
    return initcardList();
}

void releaseList()
{
    releaseCardList();
    releaseBillingList();
}

int doAddMoney(const char* pName, const char* aPwd, MoneyInfo* pMoneyInfo)
{
    Card* CardData = NULL;
    int ncardIndex = 0;	//保存卡信息索引号
    CardData = checkCard(pName, aPwd, ncardIndex);
    if (CardData != NULL) 
    {
        if (CardData->nStatus > 1)
        {
            return UNUSE;
        }
        CardData->nBalance += pMoneyInfo->money;
        CardData->fTotalUse += pMoneyInfo->money;
        if (updataCard(CardData, CARDPATH, ncardIndex))
        {
            Money sMoney;
            strcpy(sMoney.aCardName, CardData->aName);
            sMoney.money = pMoneyInfo->money;
            sMoney.nStatus = 0;
            sMoney.time = time(NULL);
            sMoney.nDel = 0;
            if (saveMoney(&sMoney, MONEYPATH))
            {
                strcpy(pMoneyInfo->aCardName, CardData->aName);
                pMoneyInfo->fBalance = CardData->nBalance;
                return TRUE;
            }
        }
    }
    return FALSE;
}

int doRefundMoney(const char* pName, const char* aPwd, MoneyInfo* pMoneyInfo)
{
    Card* CardData = NULL;
    int ncardIndex = 0;	//保存卡信息索引号
    CardData = checkCard(pName, aPwd, ncardIndex);
    if (CardData != NULL)
    {
        if (CardData->nStatus != 0)
        {
            return UNUSE;
        }
        if (CardData->nBalance <= 0)
        {
            return ENOUGHMONEY;
        }
        pMoneyInfo->money = CardData->nBalance;
        CardData->nBalance = 0;
        CardData->fTotalUse -= pMoneyInfo->money;
        if (updataCard(CardData, CARDPATH, ncardIndex))
        {
            Money sMoney;
            strcpy(sMoney.aCardName, CardData->aName);
            sMoney.money = pMoneyInfo->money;
            sMoney.nStatus = 1;
            sMoney.time = time(NULL);
            sMoney.nDel = 0;
            if (saveMoney(&sMoney, MONEYPATH))
            {
                strcpy(pMoneyInfo->aCardName, CardData->aName);
                pMoneyInfo->fBalance = CardData->nBalance;
                return TRUE;
            }
        }
    }
    return FALSE;
}

extern IpCardNode cardList;		//卡信息链表头结点外部说明
