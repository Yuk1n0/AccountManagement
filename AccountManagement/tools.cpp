#include<time.h>
#include<stdio.h>
#include<string.h>

void timeToString(time_t t, char *pBuf)//将年月日时分转换成时间字符的形式
{
	struct tm *pTimeInfo;
	pTimeInfo=localtime(&t);
	strftime(pBuf,20,"%Y-%m-%d %H:%M",pTimeInfo);
}

time_t stringTotime(char *pBuf)//将时间字符转换成年月日时分的形式
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

void statusInttoChar(int status,char* pbuf)//将卡状态数字转换成文字的形式
{
	switch(status)
	{
	case 0: sprintf(pbuf,"卡状态正常");break;
	case 1: sprintf(pbuf,"正在上机");break;
	case 2: sprintf(pbuf,"卡已注销");break;
	default: sprintf(pbuf,"卡已失效");
	}
}