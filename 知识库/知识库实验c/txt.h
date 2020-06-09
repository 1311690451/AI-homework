#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>


#define MAX_LINE 1024
#define input_max 4

#define fact_num  31      //知识库中的知识:31种知识  
#define rule_num  15      //知识库中的规则：15条规则  
#define rule_volume  4    //规则中每个结果最多有4个前提条件  
#define object_range_begin  6  //从第6个知识开始，为推导第二结论的知识
#define object_range_end  11    //到第11个为止，之后为推导最终结论的知识 
#define object_middle_begin  5     //可以推导中间结论的初始结论数 
#define object_final_begin  12    //12个之后为推导最终结论的知识
#define object_final_end  20
//21~25为中间结论

int rule_prerequisite[rule_num][rule_volume] = {0}; //规则储存数组并初始话
int rule_result[rule_num] = {0};        //规则对应的结果的数组并初始话

int Input[input_max] = { 0,0,0,0 };
int buff[];
int date[4] = { 0,0,0,0 };
int flag = 0;

int sulotion = 0;

int result[3] = {0};  //储存每一次拓展出来的事实

void ReadFile_animal()
{
    int count = 1;

    char buf[MAX_LINE];  /*缓冲区*/
    FILE* fp;            /*文件指针*/
    int len;             /*行字符个数*/
    if ((fp = fopen("feature.txt", "r")) == NULL)
    {
        perror("fail to read");
        exit(1);
    }
    while (fgets(buf, MAX_LINE, fp) != NULL)
    {
        len = strlen(buf);
        buf[len - 1] = '\0';  /*去掉换行符*/
        printf("%d.%s  ", count, buf);
        if (count % 5 == 0)
            printf("\n");
        count++;
    }
    fclose(fp);
    printf("\n");
}

void ReadFile_rule()
{
    int i, j;
    FILE* fp = fopen("rule_num.txt", "r"); //打开文件
    if (fp == NULL)
    {
        perror("fail to read");
        exit(1);
    }
    for (i = 0; i < rule_num; i++)
    {
        for (j = 0; j < rule_volume; j++)
        {
            fscanf(fp, "%d", &rule_prerequisite[i][j]);/*每次读取一个数，fscanf函数遇到空格或者换行结束*/
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
    
    /*调试用*/
    //for (i = 0; i < rule_num; i++)
    //{
    //    for (j = 0; j < rule_volume; j++)
    //    {
    //        printf("%d ", rule_prerequisite[i][j]);//输出
    //    }
    //    printf("\n");
    //}
}

void ReadFile_result()
{
    int i;
    FILE* fp = fopen("result_num.txt", "r"); //打开文件
    if (fp == NULL)
    {
        perror("fail to read");
        exit(1);
    }
    for (i = 0; i < rule_num; i++)
    {
        fscanf(fp, "%d", &rule_result[i]);/*每次读取一个数，fscanf函数遇到空格或者换行结束*/
        fscanf(fp, "\n");
    }
    fclose(fp);

    /*调试用*/
    //for (i = 0; i < rule_num; i++)
    //{
    //    printf("%d ", rule_result[i]);//输出
    //    printf("\n");
    //}
}

void choose(int num)
{
    int count =0;

    char buf[MAX_LINE];  /*缓冲区*/
    FILE* fp;            /*文件指针*/
    int len;             /*行字符个数*/

    fp = fopen("feature.txt", "r");
    while (fgets(buf, MAX_LINE, fp) != NULL)
    {
        count++;
        len = strlen(buf);
        buf[len - 1] = '\0';  /*去掉换行符*/
        if (count == num)
            printf("%s  ", buf);
    }
    fclose(fp);
}

/*第一次无调试功能的数据*/
//int rule_prerequisite[15][4] =
//{
//    {1,0,0,0},
//    {2,0,0,0},
//    {3,0,0,0},
//    {4,5,0,0},
//    {21,6,0,0},
//    {7,8,9,0},
//    {21,10,0,0},
//    {21,11,0,0},
//    {23,12,13,0},
//    {23,12,14,0},
//    {24,15,16,13},
//    {24,14,0,0},
//    {22,15,16,4},
//    {22,18,19,4},
//    {22,20,0,0}
//};
//
//int rule_result[15] =
//{
//    21,
//    21,
//    22,
//    22,
//    23,
//    23,
//    24,
//    24,
//    25,
//    26,
//    27,
//    28,
//    29,
//    30,
//    31
//};

int reload() 
{
    int num=0;
    int num_m=0;
    int count=0;
    int n ,m = 0;

    //m,n分别为规则库的行和列
    for (m = 0; m < rule_num; m++)
    {
        for (n = 0; n <= rule_volume; n++)
        {
            //规定范围来对规则的指定数值进行赋值操作
            switch (flag)
            {
            case 0:
                for (n = 0; n < rule_volume; n++)
                {
                    if (Input[n] <= object_middle_begin)
                    {
                        date[num] = Input[n];
                        num++;
                    }
                }break;
            case 1:
                num = 1;
                for (n = 0; n < rule_volume; n++)
                {
                    if (Input[n] <= object_range_end && Input[n] >= object_range_begin && Input[n] != 0)
                    {
                        date[num] = Input[n];
                        num++;
                    }
                }break;
            case 2:
                num = 1;
                for (n = 0; n < rule_volume; n++)
                {
                    if (Input[n] <= object_final_end && Input[n] >= object_final_begin && Input[n] != 0)
                    {
                        date[num] = Input[n];
                        num++;
                    }
                }break;
            default:
                break;
            }

            for (n = 0; n < rule_volume; n++)
            {
                if (date[n] == rule_prerequisite[m][n])
                {
                    count++;
                }
                else count = 0;
                
                //if (date[n] == 0)
                //    break;
            }


            if (count == 4)
            {
                num_m = m;
                break;
            }
        }
        if (count < 4)
        {
            count = 0;//为下次的重新计数准备
        }

        if (count == 4)
        {
            flag++;
            break;
        }
    }

  /*  if (count == 4)
        flag++;*/
   

    count = 0;//为下次的重新计数准备

    if (flag == 1)
    {   
        date[0] = rule_result[num_m];
        result[0] = date[0];        

        printf("\n使用规则：");
        for (int m = 0; m <= flag - 1; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }
        choose(rule_result[num_m]); //这次规则导向的第二层的事实

        printf("\n当前动态数据库为：");
        for (int n = 0; n <= input_max-1; n++)
        {
            choose(Input[n]);
        }
        choose(date[0]);

        printf("\n\n");
    }
    else if (flag == 2)
    {
        date[0] = rule_result[num_m];
        result[1] = date[0];

        printf("\n使用规则：");
        for (int m = 0; m <= flag-1; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }
        choose(rule_result[num_m]); //这次规则导向的第二层的事实
        
        printf("\n当前动态数据库为：");
        for (int n = 0; n <= input_max-1; n++)
        {
            choose(Input[n]);
        }

        choose(result[0]);
        choose(date[0]);


        printf("\n\n");
    }
    else if (flag == 3)
    {
        date[0] = rule_result[num_m];
        result[2] = date[0];

        printf("\n使用规则：");
        for (int m = 0; m <= flag-1; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }

        choose(rule_result[num_m]); //这次规则导向的第二层的事实
        
        printf("\n当前动态数据库为：");
        for (int n = 0; n <= input_max-1; n++)
        {
            choose(Input[n]);
        }

        choose(result[0]);
        choose(result[1]);
        choose(date[0]);


        printf("\n\n");
    }
    else if (Input[0]==4&&Input[1]==0)
    {
        if (Input[flag-1] == 0)
        {
            printf("推理失败\n");

            exit(0);
        }
    }
    else if(flag==0)
    {
        date[0] = rule_result[num_m];

        printf("\n使用规则：");
        for (int m = 0; m <= 2; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }
        choose(rule_result[num_m]); //这次规则导向的第二层的事实

        printf("\n当前动态数据库为：");
        for (int n = 0; n <= input_max-1; n++)
        {
            choose(Input[n]);
        }


        printf("\n\n推理失败\n");
        printf("\n\n");
        exit(0);
    }

    if (flag != 3)
    {
        if (Input[2] == 0)
        {
            printf("\n推理失败\n");

            exit(0);
        }
    }

    return flag;
}