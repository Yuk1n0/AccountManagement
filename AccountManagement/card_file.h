#ifndef CARD_FILE_H
#define CARD_FILE_H
#include "model.h"
int saveCard(const Card *pCard, const char *pPath);
int readCard(Card *pCard, const char *pPath);
int getCardCount(const char *Path);
int updataCard(const Card *pCard, const char *pPath, int nIndex);
int FindCardName(const char *pName, const char *pPath);
#endif
