#ifndef MODEL_H
#define MODEL_H
#include <time.h>

//卡信息结构体定义
typedef struct Card
{
    char aName[18];   //卡号
    char aPwd[10];    //密码
    int nStatus;      //卡状态 0 未上机 1正在上机 2已注销 3失效
    time_t tStart;    //开卡时间
    time_t tEnd;      //截止时间
    float fTotalUse;  //累计金额
    time_t tLastTime; //上次修改时间
    int nUseCount;    //累计使用次数
    float nBalance;   //余额
    int nDel;         //删除标识 0未删除 1已删除
} Card;

//卡信息结构体结点定义
typedef struct CardNode
{
    Card CardData;
    CardNode *NextNode;
} CardNode, *IpCardNode;

//消费信息结构体定义
typedef struct Billling
{
    char aCardName[18]; //卡号
    time_t tStart;      //上机时间
    time_t tEnd;        //下机时间
    float fAmount;      //消费金额
    int nStatus;        //消费状态 0未结算 1已结算
    int nDel;           //删除标识 0未删除 1已删除
} Billing;

//消费信息结构体结点定义
typedef struct BillingNode
{
    Billing BillingData;
    BillingNode *NextNode;
} BillingNode, *IpBillingNode;

//上机信息结构体
typedef struct LogonInfo
{
    char aCardName[18]; //卡号
    time_t tLogon;      //上机时间
    float fBalance;     //上机时的卡余额
} LogonInfo;

//下机信息结构体
typedef struct SettleInfo
{
    char aCardName[18]; //卡号
    time_t tStart;      //上机时间
    time_t tEnd;        //下机时间
    float fAmount;      //消费金额
    float fBalance;     //余额
} SettleInfo;

//充值退费结构体定义
typedef struct Money
{
    char aCardName[18]; //卡号
    time_t time;        //充值退费时间
    int nStatus;        //状态 0充值 1退费
    float money;        //充值退费金额
    int nDel;           //删除标识 0未删除 1已删除
} Money;

//充值退费信息结构体定义
typedef struct MoneyInfo
{
    char aCardName[18]; //卡号
    float money;        //充值退费金额
    float fBalance;     //余额
} MoneyInfo;
#endif
