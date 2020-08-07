#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "model.h"
#include "tools.h"

int saveBilling(const Billing *pBilling, const char *pPath)
{
    FILE *fp = NULL; //定义文件指针
    //追加方式打开文件
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
    fwrite(pBilling, sizeof(Billing), 1, fp); //将计费信息写进文件
    fclose(fp);
    return TRUE;
}

int getBillingCount(const char *Path)
{
    int Index = 0;
    FILE *fp = NULL;
    fp = fopen(Path, "rb");
    if (fp == NULL)
    {
        printf("打开文件失败");
        return FALSE;
    }

    Billing *pBilling = (Billing *)malloc(sizeof(Billing));
    while (!feof(fp))
    {
        if (fread(pBilling, sizeof(Billing), 1, fp) == 1) //用fread逐条读取文件中的消费记录
        {
            Index++;
        }
    }
    fclose(fp);
    return Index;
}

int readBilling(Billing *pBilling, const char *pPath) //从文件中读取消费记录
{
    int i = 0;
    Billing *NBilling = (Billing *)malloc(sizeof(Billing));
    FILE *fp = NULL;
    fp = fopen(pPath, "rb");
    if (fp == NULL)
    {
        return FALSE;
    }
    while (!feof(fp))
    {
        memset(NBilling, 0, sizeof(Billing)); //获取一行之前清空指针中的信息
        if (fread(NBilling, sizeof(Billing), 1, fp) == 1)
        {
            pBilling[i++] = *NBilling;
        }
    }
    fclose(fp);
    free(NBilling);
    return TRUE;
}

int updataBilling(const Billing *pBilling, const char *pPath, int nIndex)
{
    FILE *fp = NULL;
    Billing *NBilling = (Billing *)malloc(sizeof(Billing));
    int nLine = 0;      //文件行数
    long lPosition = 0; //文件位置标识
    fp = fopen(pPath, "rb+");
    if (fp == NULL)
    {
        return FALSE;
    }
    while ((!feof(fp)) && (nLine < nIndex))
    {
        memset(NBilling, 0, sizeof(Billing)); //清空之前指针保存的信息
        if (fread(NBilling, sizeof(Billing), 1, fp) == 1)
        {
            lPosition = ftell(fp); //用ftell函数保存文件中指针当前位置
            nLine++;
        }
    }
    fseek(fp, lPosition, 0); //移动到文件标识位置
    fwrite(pBilling, sizeof(Billing), 1, fp);
    fclose(fp);
    free(NBilling);
    return TRUE;
}

int FindBillingName(const char *pName, const char *pPath) //从文件中寻找同名计费信息是否存在 存在返回TRUE
{
    FILE *fp = NULL;
    Billing *NBilling = (Billing *)malloc(sizeof(Billing));
    fp = fopen(pPath, "rb");
    if (fp == NULL)
    {
        return FALSE;
    }
    while (!feof(fp))
    {
        memset(NBilling, 0, sizeof(Billing)); //获取一行之前清空指针中的信息
        if (fread(NBilling, sizeof(Billing), 1, fp) == 1)
        {
            if (strcmp(pName, NBilling->aCardName) == 0 && NBilling->nStatus == 1)
            {
                fclose(fp);
                free(NBilling);
                return TRUE;
            }
        }
    }
    fclose(fp);
    free(NBilling);
    return FALSE;
}

int putBillings(const char *pName, const int a) //根据不同情况输出计费信息
{
    FILE *fp = NULL;
    fp = fopen(BILLINGPATH, "rb");
    if (fp == NULL)
    {
        return FALSE;
    }
    Billing *pBilling = (Billing *)malloc(sizeof(Billing));
    char atime[20] = {0};
    int i = 0; //判断查询到的计费信息数量

    //如果是卡号查询
    if (a == 1)
    {
        while (!feof(fp))
        {
            memset(pBilling, 0, sizeof(Billing)); //清空之前指针保存的信息
            if (fread(pBilling, sizeof(Billing), 1, fp) == 1)
            {
                if (strcmp(pBilling->aCardName, pName) == 0 && pBilling->nStatus == 1)
                {
                    i++;
                    if (i == 1)
                    {
                        printf("\n卡号\t消费金额\t消费时间\n");
                    }
                    timeToString(pBilling->tStart, atime);
                    printf("%s\t%f\t\t%s\n", pBilling->aCardName, pBilling->fAmount, atime);
                }
            }
        }
    }

    //如果是时间查询
    else
    {
        struct tm *time = NULL;
        while (!feof(fp))
        {
            memset(pBilling, 0, sizeof(Billing));
            if (fread(pBilling, sizeof(Billing), 1, fp) == 1)
            {
                time = localtime(&pBilling->tStart);
                time->tm_year += 1900;
                if (pBilling->nStatus == 1 && time->tm_year == atoi(pName))
                {
                    i++;
                    if (i == 1)
                    {
                        printf("\n卡号\t消费金额\t消费时间\n");
                    }
                    timeToString(pBilling->tStart, atime);
                    printf("%s\t%f\t\t%s\n", pBilling->aCardName, pBilling->fAmount, atime);
                }
            }
        }
    }

    if (i == 0)
    {
        printf("\n无对应计费信息。\n");
        fclose(fp);
        free(pBilling);
        return FALSE;
    }
    fclose(fp);
    free(pBilling);
    return TRUE;
}

void staticiseall() //统计总营业额
{
    FILE *fp = NULL;
    fp = fopen(BILLINGPATH, "rb");
    if (fp == NULL)
    {
        return;
    }
    Billing *pBilling = (Billing *)malloc(sizeof(Billing));
    float all = 0.0;
    while (!feof(fp))
    {
        memset(pBilling, 0, sizeof(Billing)); //清空之前指针保存的信息
        if (fread(pBilling, sizeof(Billing), 1, fp) == 1)
        {
            if (pBilling->nStatus == 1)
            {
                //总额加上消费金额
                all += pBilling->fAmount;
            }
        }
    }
    printf("\n总营业额为： %f\n", all);
    fclose(fp);
    free(pBilling);
}
