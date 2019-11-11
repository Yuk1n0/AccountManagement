#ifndef TOOLS_H
#define TOOLS_H
void timeToString(time_t t, char *pBuf);
time_t stringTotime(char *pBuf);
void statusInttoChar(int status, char *pbuf);
#endif