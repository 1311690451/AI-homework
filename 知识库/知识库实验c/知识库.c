#define _CRT_SECURE_NO_WARNINGS
#include "txt.h"


int main()
{
    int Flag;

    ReadFile_animal();     //��ȡ֪ʶ����ļ�
    ReadFile_rule();        //��ȡ����������
    ReadFile_result();       //��ȡ����������

    //choose(12);//��֮�����֪ʶ��Ĺ���ʹ��

    printf("������֪��֪ʶ��ţ�");
    //��ȡ������֪�����
    for (int i = 0; i <= input_max; i++)
    {
        scanf("%d",&Input[i]);
        char gc = getchar();
        if (gc == '\n')
            break;
    }
    
    printf("\n�û��ĳ�ʼ��ʵΪ��");
    for (int n = 0; n <= input_max; n++)
        choose(Input[n]);
    printf("\n");

    while (true)
    {
        Flag = reload();

        if (Input[2] == 0)
        {
            printf("\n����ʧ��\n");

            exit(0);
        }

        if (Flag == 3)
        {
            printf("\n�Ƶ������");
            choose(date[0]);
            break;
        }
    }

    printf("\n");
    return 0;
}