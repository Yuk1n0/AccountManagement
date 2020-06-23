#include <iostream>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "model.h"
#include "tools.h"
using namespace std;

int saveBilling(const Billing* pBilling ,const char * pPath)
{
	FILE *fp = NULL;	//�����ļ�ָ��
	//׷�ӷ�ʽ���ļ�
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
	fwrite(pBilling, sizeof(Billing),1,fp);	//���Ʒ���Ϣд���ļ�
	fclose(fp);
	return TRUE;
}

int getBillingCount (const char *Path)
{
	int Index=0;
	FILE *fp = NULL;
	fp = fopen(Path ,"rb");
	if (fp==NULL)
	{
			printf("���ļ�ʧ��");
			return FALSE;
	}

	Billing* pBilling=new Billing;
	while (!feof(fp))
	{
		if (fread(pBilling,sizeof(Billing),1,fp)==1) //��fread������ȡ�ļ��е����Ѽ�¼
		{
			Index++;
		}
	}
	fclose(fp);
	return Index;
}


int readBilling (Billing* pBilling ,const char *pPath) //���ļ��ж�ȡ���Ѽ�¼
{
	int i=0;
	Billing* NBilling=new Billing;
	FILE *fp = NULL;
	fp = fopen(pPath ,"rb");
	while (!feof(fp))
	{
		memset(NBilling,0,sizeof(Billing));	//��ȡһ��֮ǰ���ָ���е���Ϣ
		if (fread(NBilling,sizeof(Billing),1,fp)==1) 
		{
			pBilling[i++]=*NBilling;
		}
	}
	fclose(fp);
	delete NBilling;
	return TRUE;
}

int updataBilling (const Billing* pBilling,const char *pPath,int nIndex){
	FILE *fp = NULL;
	Billing* NBilling=new Billing;
	int nLine=0;	//�ļ�����
	long lPosition = 0;		//�ļ�λ�ñ�ʶ
	fp = fopen(pPath ,"rb+");
	if (fp==NULL) return FALSE;
	while ( (!feof(fp)) && (nLine<nIndex))
	{
		memset(NBilling,0,sizeof(Billing));		//���֮ǰָ�뱣�����Ϣ
		if (fread(NBilling,sizeof(Billing),1,fp)==1) 
		{
			lPosition=ftell(fp);		//��ftell���������ļ���ָ�뵱ǰλ��
			nLine++;
		}
	}
	fseek(fp, lPosition, 0);	//�ƶ����ļ���ʶλ��
	fwrite(pBilling, sizeof(Billing),1,fp);
	fclose(fp);
	delete NBilling;
	return TRUE;
}


int FindBillingName (const char* pName, const char* pPath)//���ļ���Ѱ��ͬ���Ʒ���Ϣ�Ƿ���� ���ڷ���TRUE
{
	FILE *fp=NULL;
	Billing* NBilling=new Billing;
	fp = fopen(pPath ,"rb");
	if (fp==NULL) return FALSE;	
	while (!feof(fp))
	{
		memset(NBilling,0,sizeof(Billing));	//��ȡһ��֮ǰ���ָ���е���Ϣ
		if (fread(NBilling,sizeof(Billing),1,fp)==1)
		{
			if (strcmp(pName,NBilling->aCardName)==0 && NBilling->nStatus==1)	
			{
				fclose(fp);
				delete NBilling;
				return TRUE;
			}
		}
	}
	fclose(fp);
	delete NBilling;
	return FALSE;
}


int putBillings(const char* pName,const int a)//���ݲ�ͬ�������Ʒ���Ϣ
{
	FILE *fp = NULL;
	fp = fopen(BILLINGPATH,"rb");
	if (fp==NULL) return FALSE;
	Billing* pBilling=new Billing;
	char atime[20]={0};
	int i=0;		//�жϲ�ѯ���ļƷ���Ϣ����
	//����ǿ��Ų�ѯ
	if (a==1)
	{
		while ( !feof(fp))
		{
			memset(pBilling,0,sizeof(Billing));		//���֮ǰָ�뱣�����Ϣ
			if (fread(pBilling,sizeof(Billing),1,fp)==1) 
			{		
				if(strcmp(pBilling->aCardName,pName)==0 && pBilling->nStatus==1)
				{
					i++;
					if (i==1)
					{
						cout<<"\n����\t���ѽ��\t����ʱ��\n";
					}
					timeToString(pBilling->tStart,atime);
					cout<<pBilling->aCardName<<"\t"<<pBilling->fAmount<<"\t\t"<<atime<<"\n";		
				}
			}
		}
	}
	//�����ʱ���ѯ
	else {
		tm *time=NULL;
		while ( !feof(fp))
		{
			memset(pBilling,0,sizeof(Billing));		
			if (fread(pBilling,sizeof(Billing),1,fp)==1) 
			{		
				time=localtime(&pBilling->tStart);
				time->tm_year+=1900;
				if(pBilling->nStatus==1 &&  time->tm_year==atoi(pName))
				{
					i++;
					if (i==1)
					{
						cout<<"\n����\t���ѽ��\t����ʱ��\n";
					}
					timeToString(pBilling->tStart,atime);
					cout<<pBilling->aCardName<<"\t"<<pBilling->fAmount<<"\t\t"<<atime<<"\n";
				}
			}
		}
	}
	if (i==0) 
	{
		cout<<"\n�޶�Ӧ�Ʒ���Ϣ��\n";
		fclose(fp);
		delete pBilling;
		return FALSE;
	}
	fclose(fp);
	delete pBilling;
	return TRUE;
}



void staticiseall()//ͳ����Ӫҵ��
{
	FILE *fp = NULL;
	fp = fopen(BILLINGPATH,"rb");
	if (fp==NULL)
	{
		return;
	}
	Billing* pBilling=new Billing;
	float all=0.0;
	while ( !feof(fp))
	{
		memset(pBilling,0,sizeof(Billing));		//���֮ǰָ�뱣�����Ϣ
		if (fread(pBilling,sizeof(Billing),1,fp)==1) 
		{		
			if(pBilling->nStatus==1)
				//�ܶ�������ѽ��
				all+=pBilling->fAmount;		
		}
	}
	cout<<"\n��Ӫҵ��Ϊ�� "<<all<<endl;
	fclose(fp);
	delete pBilling;
}