#ifndef BILLING_FILE_H
#define BILLING_FILE_H
#include "model.h"
int saveBilling(const Billing *pBilling, const char *pPath);
int readBilling(Billing *pBilling, const char *pPath);
int getBillingCount(const char *Path);
int updataBilling(const Billing *pBilling, const char *pPath, int nIndex);
int FindBillingName(const char *pName, const char *pPath);
int putBillings(const char *pName, const int a);
void staticiseall();
#endif
