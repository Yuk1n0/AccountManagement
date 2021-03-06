#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "model.h"

int saveCard(const Card *pCard, const char *pPath)
{
    FILE *fp = NULL;
    fp = fopen(pPath, "ab");
    if (fp == NULL)
    {
        fp = fopen(pPath, "wb");
        if (fp == NULL)
        {
            printf("打开文件失败");
            return FALSE;
        }
    }
    fwrite(pCard, sizeof(Card), 1, fp);
    fclose(fp);
    return TRUE;
}

int readCard(Card *pCard, const char *pPath)
{
    int i = 0;
    Card *NCard = (Card *)malloc(sizeof(Card));
    FILE *fp = NULL;
    fp = fopen(pPath, "rb");
    if (fp == NULL)
    {
        return FALSE;
    }
    while (!feof(fp))
    {
        memset(NCard, 0, sizeof(Card)); //获取一行之前清空指针中的信息
        if (fread(NCard, sizeof(Card), 1, fp) == 1)
        {
            pCard[i++] = *NCard;
        }
    }
    fclose(fp);
    free(NCard);
    return TRUE;
}

int FindCardName(const char *pName, const char *pPath)
{
    FILE *fp = NULL;
    Card *NCard = (Card *)malloc(sizeof(Card));
    fp = fopen(pPath, "rb");
    if (fp == NULL)
    {
        return FALSE;
    }
    while (!feof(fp))
    {
        memset(NCard, 0, sizeof(Card)); //获取一行之前清空指针中的信息
        if (fread(NCard, sizeof(Card), 1, fp) == 1)
        {
            if (strcmp(pName, NCard->aName) == 0)
            {
                fclose(fp);
                free(NCard);
                return TRUE;
            }
        }
    }
    fclose(fp);
    free(NCard);
    return FALSE;
}

int getCardCount(const char *Path)
{
    int Index = 0;
    FILE *fp = NULL;
    Card *NCard = (Card *)malloc(sizeof(Card));
    fp = fopen(Path, "rb");
    if (fp == NULL)
    {
        return FALSE;
    }
    while (!feof(fp))
    {
        memset(NCard, 0, sizeof(Card)); //清空之前指针保存的信息
        if (fread(NCard, sizeof(Card), 1, fp) == 1)
        {
            Index++;
        }
    }
    free(NCard);
    fclose(fp);
    return Index;
}

int updataCard(const Card *pCard, const char *pPath, int nIndex)
{
    FILE *fp = NULL;
    Card *NCard = (Card *)malloc(sizeof(Card));
    int nLine = 0;      //文件行数
    long lPosition = 0; //文件位置标示
    fp = fopen(pPath, "rb+");
    if (fp == NULL)
    {
        return FALSE;
    }
    while ((!feof(fp)) && (nLine < nIndex))
    {
        memset(NCard, 0, sizeof(Card)); //清空之前指针保存的信息
        if (fread(NCard, sizeof(Card), 1, fp) == 1)
        {
            lPosition = ftell(fp); //用ftell函数保存文件中指针当前位置
            nLine++;
        }
    }
    fseek(fp, lPosition, 0); //移动到文件标识位置
    fwrite(pCard, sizeof(Card), 1, fp);
    free(NCard);
    fclose(fp);
    return TRUE;
}
