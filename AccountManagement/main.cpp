#include<iostream>
#include"menu.h"
using namespace std;

int main(void)
{
    cout<<"��ӭ����Ʒѹ���ϵͳ\n";
    int i=-1;	//ѡ��
    do
    {
        outputmeun();	//�����ʼ�˵�
        cin>>i;
        switch(i)
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
            default:cout<<"�����������������";
        }
        cout<<endl;
    }while (i!=0);
    return 0;
}
