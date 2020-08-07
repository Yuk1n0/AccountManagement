#ifndef CARD_SEVICE_H
#define CARD_SEVICE_H
#include "model.h"
int initcardList();
int addCard(Card);
int getCard();
Card *queryCard(const char *);
Card *queryCards(const char *, int *);
Card *checkCard(const char *pName, const char *aPwd, int *nIndex);
void releaseCardList();
#endif
