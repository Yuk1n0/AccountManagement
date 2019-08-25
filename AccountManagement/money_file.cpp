#include<iostream>
using namespace std;
#include"model.h"
#include"global.h"

int saveMoney(const Money *pMoney ,const char *pPath)
{
	FILE *fp = NULL;
	fp = fopen(pPath ,"ab");
	if (fp==NULL)
	{
		fp=fopen(pPath,"wb");
		if (fp==NULL) 
		{
			printf("打开文件失败");
			return FALSE;
		}
	}
	//将充值退费信息写进文件
	fwrite(pMoney, sizeof(Money),1,fp);
	fclose(fp);
	return TRUE;

}