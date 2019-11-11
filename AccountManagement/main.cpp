#include <iostream>
#include "menu.h"
using namespace std;

int main(void)
{
    cout << "欢迎进入计费管理系统\n";
    int i = -1; //选项
    do
    {
        outputmeun(); //输出初始菜单
        cin >> i;
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
            break;
        }
        case 8:
        {
            break;
        }
        case 0:
        {
            Quit();
            break;
        }
        default:
            cout << "输入错误，请重新输入";
        }
        cout << endl;
    } while (i != 0);
    return 0;
}
