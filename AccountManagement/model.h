#ifndef MODEL_H
#define MODEL_H
#include<time.h>

//����Ϣ�ṹ�嶨��
typedef struct Card
{
    char aName[18];		//����
    char aPwd[10];	//����
    int nStatus;	//��״̬ 0 δ�ϻ� 1�����ϻ� 2��ע�� 3ʧЧ
    time_t tStart;	//����ʱ��
    time_t tEnd;	//��ֹʱ��
    float fTotalUse;//�ۼƽ��
    time_t tLastTime;	//�ϴ��޸�ʱ��
    int nUseCount;	//�ۼ�ʹ�ô���
    float nBalance;	//���
    int nDel;	//ɾ����ʶ 0δɾ�� 1��ɾ��
}Card;

//����Ϣ�ṹ���㶨��
typedef struct CardNode
{
    Card CardData;
    CardNode *NextNode;
}CardNode,*IpCardNode;

//������Ϣ�ṹ�嶨��
typedef struct Billling
{
    char aCardName[18];		//����
    time_t tStart;	//�ϻ�ʱ��
    time_t tEnd;	//�»�ʱ��
    float fAmount;	//���ѽ��
    int nStatus;	//����״̬ 0δ���� 1�ѽ���
    int nDel;	//ɾ����ʶ 0δɾ�� 1��ɾ��
}Billing;

//������Ϣ�ṹ���㶨��
typedef struct BillingNode
{
    Billing BillingData;
    BillingNode *NextNode;
}BillingNode,*IpBillingNode;

//�ϻ���Ϣ�ṹ��
typedef struct LogonInfo
{
    char aCardName[18];		//����
    time_t tLogon;		//�ϻ�ʱ��
    float fBalance;		//�ϻ�ʱ�Ŀ����
}LogonInfo;

//�»���Ϣ�ṹ��
typedef struct SettleInfo
{
    char aCardName[18];		//����
    time_t tStart;	//�ϻ�ʱ��
    time_t tEnd;	//�»�ʱ��
    float fAmount;	//���ѽ��
    float fBalance;	//���
}SettleInfo;

//��ֵ�˷ѽṹ�嶨��
typedef struct Money
{
    char aCardName[18];		//����
    time_t time;		//��ֵ�˷�ʱ��
    int nStatus;	//״̬ 0��ֵ 1�˷�
    float money;	//��ֵ�˷ѽ��
    int nDel;	//ɾ����ʶ 0δɾ�� 1��ɾ��
}Money;

//��ֵ�˷���Ϣ�ṹ�嶨��
typedef struct MoneyInfo
{
    char aCardName[18];		//����
    float money;	//��ֵ�˷ѽ��
    float fBalance;		//���
}MoneyInfo;
#endif
