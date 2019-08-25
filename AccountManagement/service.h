#ifndef SERVICE_H
#define SERVICE_H
int findName(const char* pName);
void releaseList();
bool InitcardListinfo();
int dologon(const char *pName ,const char *aPwd, LogonInfo *pLogonInfo);
Card* queryCardsinfo(const char *pName,int &nIndex);
Card* queryCardinfo(const char *pName);
int doSettle(const char *pName,const char *aPwd,SettleInfo* pInfo);
int addCardinfo(Card card);
int doAddMoney(const char *pName,const char *aPwd,MoneyInfo* pMoneyInfo);
int doRefundMoney(const char *pName,const char *aPwd,MoneyInfo* pMoneyInfo);
#endif