#include <stdio.h>
#include "menu.h"

int main(void)
{
    printf("欢迎进入计费管理系统\n");
    int i = -1; //选项
    do
    {
        outputmeun(); //输出初始菜单
        scanf("%d", &i);
        switch (i)
        {
        case 1:
        {
            add();
            break;
        }
        case 2:
        {
            query();
            break;
        }
        case 3:
        {
            logon();
            break;
        }
        case 4:
        {
            settle();
            break;
        }
        case 5:
        {
            addMoney();
            break;
        }
        case 6:
        {
            refundMoney();
            break;
        }
        case 7:
        {
            //TODO
            break;
        }
        case 8:
        {
            //TODO
            break;
        }
        case 0:
        {
            Quit();
            break;
        }
        default:
            printf("输入错误，请重新输入");
        }
        printf("\n");
    } while (i != 0);
    return 0;
}
