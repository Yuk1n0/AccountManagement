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
			printf("���ļ�ʧ��");
			return FALSE;
		}
	}
	//����ֵ�˷���Ϣд���ļ�
	fwrite(pMoney, sizeof(Money),1,fp);
	fclose(fp);
	return TRUE;

}