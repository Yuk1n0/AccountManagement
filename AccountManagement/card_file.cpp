#include"model.h"
#include"global.h"
#include<stdio.h>
#include"tools.h"
#include<string.h>
#include<stdlib.h>
#include<iostream>

int saveCard (const Card* pCard ,const char * pPath)
{
    FILE *fp = NULL;
    fp = fopen(pPath ,"ab");
    if (fp==NULL)
    {
        fp=fopen(pPath,"wb");
        if (fp==NULL) 
        {
            std::cout<<"���ļ�ʧ��";
            return FALSE;
        }
    }
    fwrite(pCard, sizeof(Card),1,fp);
    fclose(fp);
    return TRUE;
}

int readCard (Card *pCard ,const char *pPath)
{
    int i=0;
    Card* NCard=new Card;
    FILE *fp = NULL;
    fp = fopen(pPath ,"rb");
    while (!feof(fp))
    {
        memset(NCard,0,sizeof(Card));	//��ȡһ��֮ǰ���ָ���е���Ϣ
        if (fread(NCard,sizeof(Card),1,fp)==1) 
        {
            pCard[i++]=*NCard;
        }
    }
    fclose(fp);
    delete NCard;
    return TRUE;
}

int FindCardName (const char* pName, const char* pPath)
{
    FILE *fp=NULL;
    Card* NCard=new Card;
    fp = fopen(pPath ,"rb");
    if (fp==NULL) 
    {
        return FALSE;
    }
    while (!feof(fp))
    {
        memset(NCard,0,sizeof(Card));	//��ȡһ��֮ǰ���ָ���е���Ϣ
        if (fread(NCard,sizeof(Card),1,fp)==1) 
        {
            if (strcmp(pName,NCard->aName)==0)	
            {
                fclose(fp);
                delete NCard;
                return TRUE;
            }
        }
    }
    fclose(fp);
    delete NCard;
    return FALSE;
}

int getCardCount(const char *Path)
{
    int Index=0;
    FILE *fp=NULL;
    Card *NCard=new Card;
    fp = fopen(Path ,"rb");
    if (fp==NULL) return FALSE;
    while (!feof(fp))
    {
        memset(NCard,0,sizeof(Card));		//���֮ǰָ�뱣�����Ϣ
        if (fread(NCard,sizeof(Card),1,fp)==1) 
        {
            Index++;
        }
    }
    delete NCard;
    fclose(fp);
    return Index;
}

int updataCard(const Card *pCard,const char *pPath,int nIndex)
{
    FILE *fp = NULL;
    Card *NCard=new Card;
    int nLine=0;	//�ļ�����
    long lPosition = 0;		//�ļ�λ�ñ�ʶ
    fp = fopen(pPath ,"rb+");
    if (fp==NULL) 
    {
        return FALSE;
    }
    while ( (!feof(fp)) && (nLine<nIndex))
    {
        memset(NCard,0,sizeof(Card));		//���֮ǰָ�뱣�����Ϣ
        if (fread(NCard,sizeof(Card),1,fp)==1) 
        {
            lPosition=ftell(fp);		//��ftell���������ļ���ָ�뵱ǰλ��
            nLine++;
        }
    }
    fseek(fp, lPosition, 0);	//�ƶ����ļ���ʶλ��
    fwrite(pCard, sizeof(Card),1,fp);
    delete NCard;
    fclose(fp);
    return TRUE;
}
