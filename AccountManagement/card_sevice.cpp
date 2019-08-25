#include<iostream>
#include"card_file.h"
#include"model.h"
#include"global.h"
#include<stdio.h>
#include"billing_service.h"
using namespace std;

IpCardNode cardList = NULL;	//ȫ�ֶ��忨��Ϣ�����������п���Ϣ
int ncardCount=0;	

int initcardList()
{
	if (!cardList)
	{
		cardList = new CardNode;	
		cardList->NextNode = NULL;
		return TRUE;
	}
	return FALSE;
}

void releaseCardList()
{
	IpCardNode thisNode=cardList, nextNode=NULL;
	while (thisNode!=NULL)
	{
		nextNode = thisNode->NextNode;
		delete thisNode;
		thisNode = nextNode;
		cardList=NULL;
	}
}

int getCard()
{
	int i=0;
	Card* pCard=NULL;		
	releaseCardList();
	initcardList();
	ncardCount=getCardCount(CARDPATH);
	pCard = (Card*)malloc(sizeof(Card)*ncardCount);
	if (readCard(pCard ,CARDPATH)==0)//���ļ��ж�ȡ����Ϣ�����ӵ��ݴ�ָ����
	{
		cout<<"��ȡʧ��";
		free(pCard);
		return FALSE;
	}
	//����ȡ�Ŀ���Ϣ���ӵ�������
	IpCardNode p1=cardList,p2=NULL;
	for (;i<ncardCount;i++)
	{
		p2=new CardNode;
		p2->CardData=pCard[i];
		p2->NextNode=NULL;
		p1=p1->NextNode=p2;
	}
	free(pCard);
	return TRUE;
}

int addCard(Card card)
{
	return saveCard(&card,CARDPATH);
}

Card* queryCard(const char *pName)
{
	if (getCard()!=0)
	{
		IpCardNode cardNow= NULL;
		for(cardNow= cardList;cardNow!=NULL;cardNow=cardNow->NextNode)
		{
			if (strcmp(cardNow->CardData.aName,pName)==0) return &cardNow->CardData;
		}
	}
	return NULL;
} 

Card *queryCards(const char *pName,int &nIndex)
{
	//����һ����ָ�������в�ѯ	
	IpCardNode cardNow= NULL;
	//һ��ָ����������ҵ����п���Ϣ 
	Card* putCards=NULL;
	//Ϊ�ڵ����һ���¿ռ�
	putCards=new Card;
	if (getCard()!=0)
	{
	for (IpCardNode NOW=cardList;NOW!=NULL;NOW=NOW->NextNode)
	{
		if (strstr(NOW->CardData.aName,pName)!=NULL)
		{
			putCards[nIndex++]=NOW->CardData;
			putCards=(Card*)realloc(putCards,sizeof(Card)*(nIndex+1));
		}
	}
	if(nIndex!=0) return putCards;
	else free(putCards);
	}
	return NULL;
} 


Card* checkCard(const char *pName,const char *aPwd,int &nIndex)
{
	if (getCard()!=0)
	{
		IpCardNode cardNow= NULL;
		nIndex=0;
		for(cardNow= cardList->NextNode;cardNow!=NULL;cardNow=cardNow->NextNode)
		{
			if ((strcmp(cardNow->CardData.aName,pName)==0)&&(strcmp(cardNow->CardData.aPwd,aPwd)==0)) 
			{
				return &cardNow->CardData;				
			}
			nIndex++;
		}
	}
	return NULL;
}