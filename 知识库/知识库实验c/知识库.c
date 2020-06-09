#define _CRT_SECURE_NO_WARNINGS
#include "txt.h"


int main()
{
    int Flag;

    ReadFile_animal();     //读取知识库的文件
    ReadFile_rule();        //读取规则库的数据
    ReadFile_result();       //读取结果库的数据

    //choose(12);//给之后输出知识库的规则使用

    printf("输入已知的知识序号：");
    //获取输入已知的序号
    for (int i = 0; i <= input_max; i++)
    {
        scanf("%d",&Input[i]);
        char gc = getchar();
        if (gc == '\n')
            break;
    }
    
    printf("\n用户的初始事实为：");
    for (int n = 0; n <= input_max; n++)
        choose(Input[n]);
    printf("\n");

    while (true)
    {
        Flag = reload();

        if (Input[2] == 0)
        {
            printf("\n推理失败\n");

            exit(0);
        }

        if (Flag == 3)
        {
            printf("\n推导结果：");
            choose(date[0]);
            break;
        }
    }

    printf("\n");
    return 0;
}