#ifndef BILLING_SERVICE_H
#define BILLING_SERVICE_H
#include "model.h"
int addBilling(Billing billing);
int initBillingList();
void releaseBillingList();
int getBilling();
Billing *checkBilling(const char *pName, int &nIndex);
#endif
