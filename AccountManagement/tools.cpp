#include<time.h>
#include<stdio.h>
#include<string.h>

void timeToString(time_t t, char *pBuf)//��������ʱ��ת����ʱ���ַ�����ʽ
{
	struct tm *pTimeInfo;
	pTimeInfo=localtime(&t);
	strftime(pBuf,20,"%Y-%m-%d %H:%M",pTimeInfo);
}

time_t stringTotime(char *pBuf)//��ʱ���ַ�ת����������ʱ�ֵ���ʽ
{
	time_t time1;
	struct tm tm1;
	memset(&tm1,0,sizeof(struct tm));
	sscanf(pBuf,"%d-%d-%d %d:%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min);
	tm1.tm_year-=1900;
	tm1.tm_mon-=1;
	tm1.tm_sec=0;
	time1 = mktime(&tm1);
	return time1;
}

void statusInttoChar(int status,char* pbuf)//����״̬����ת�������ֵ���ʽ
{
	switch(status)
	{
	case 0: sprintf(pbuf,"��״̬����");break;
	case 1: sprintf(pbuf,"�����ϻ�");break;
	case 2: sprintf(pbuf,"����ע��");break;
	default: sprintf(pbuf,"����ʧЧ");
	}
}