#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>


#define MAX_LINE 1024
#define input_max 4

#define fact_num  31      //֪ʶ���е�֪ʶ:31��֪ʶ  
#define rule_num  15      //֪ʶ���еĹ���15������  
#define rule_volume  4    //������ÿ����������4��ǰ������  
#define object_range_begin  6  //�ӵ�6��֪ʶ��ʼ��Ϊ�Ƶ��ڶ����۵�֪ʶ
#define object_range_end  11    //����11��Ϊֹ��֮��Ϊ�Ƶ����ս��۵�֪ʶ 
#define object_middle_begin  5     //�����Ƶ��м���۵ĳ�ʼ������ 
#define object_final_begin  12    //12��֮��Ϊ�Ƶ����ս��۵�֪ʶ
#define object_final_end  20
//21~25Ϊ�м����

int rule_prerequisite[rule_num][rule_volume] = {0}; //���򴢴����鲢��ʼ��
int rule_result[rule_num] = {0};        //�����Ӧ�Ľ�������鲢��ʼ��

int Input[input_max] = { 0,0,0,0 };
int buff[];
int date[4] = { 0,0,0,0 };
int flag = 0;

int sulotion = 0;

int result[3] = {0};  //����ÿһ����չ��������ʵ

void ReadFile_animal()
{
    int count = 1;

    char buf[MAX_LINE];  /*������*/
    FILE* fp;            /*�ļ�ָ��*/
    int len;             /*���ַ�����*/
    if ((fp = fopen("feature.txt", "r")) == NULL)
    {
        perror("fail to read");
        exit(1);
    }
    while (fgets(buf, MAX_LINE, fp) != NULL)
    {
        len = strlen(buf);
        buf[len - 1] = '\0';  /*ȥ�����з�*/
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
    FILE* fp = fopen("rule_num.txt", "r"); //���ļ�
    if (fp == NULL)
    {
        perror("fail to read");
        exit(1);
    }
    for (i = 0; i < rule_num; i++)
    {
        for (j = 0; j < rule_volume; j++)
        {
            fscanf(fp, "%d", &rule_prerequisite[i][j]);/*ÿ�ζ�ȡһ������fscanf���������ո���߻��н���*/
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
    
    /*������*/
    //for (i = 0; i < rule_num; i++)
    //{
    //    for (j = 0; j < rule_volume; j++)
    //    {
    //        printf("%d ", rule_prerequisite[i][j]);//���
    //    }
    //    printf("\n");
    //}
}

void ReadFile_result()
{
    int i;
    FILE* fp = fopen("result_num.txt", "r"); //���ļ�
    if (fp == NULL)
    {
        perror("fail to read");
        exit(1);
    }
    for (i = 0; i < rule_num; i++)
    {
        fscanf(fp, "%d", &rule_result[i]);/*ÿ�ζ�ȡһ������fscanf���������ո���߻��н���*/
        fscanf(fp, "\n");
    }
    fclose(fp);

    /*������*/
    //for (i = 0; i < rule_num; i++)
    //{
    //    printf("%d ", rule_result[i]);//���
    //    printf("\n");
    //}
}

void choose(int num)
{
    int count =0;

    char buf[MAX_LINE];  /*������*/
    FILE* fp;            /*�ļ�ָ��*/
    int len;             /*���ַ�����*/

    fp = fopen("feature.txt", "r");
    while (fgets(buf, MAX_LINE, fp) != NULL)
    {
        count++;
        len = strlen(buf);
        buf[len - 1] = '\0';  /*ȥ�����з�*/
        if (count == num)
            printf("%s  ", buf);
    }
    fclose(fp);
}

/*��һ���޵��Թ��ܵ�����*/
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

    //m,n�ֱ�Ϊ�������к���
    for (m = 0; m < rule_num; m++)
    {
        for (n = 0; n <= rule_volume; n++)
        {
            //�涨��Χ���Թ����ָ����ֵ���и�ֵ����
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
            count = 0;//Ϊ�´ε����¼���׼��
        }

        if (count == 4)
        {
            flag++;
            break;
        }
    }

  /*  if (count == 4)
        flag++;*/
   

    count = 0;//Ϊ�´ε����¼���׼��

    if (flag == 1)
    {   
        date[0] = rule_result[num_m];
        result[0] = date[0];        

        printf("\nʹ�ù���");
        for (int m = 0; m <= flag - 1; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }
        choose(rule_result[num_m]); //��ι�����ĵڶ������ʵ

        printf("\n��ǰ��̬���ݿ�Ϊ��");
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

        printf("\nʹ�ù���");
        for (int m = 0; m <= flag-1; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }
        choose(rule_result[num_m]); //��ι�����ĵڶ������ʵ
        
        printf("\n��ǰ��̬���ݿ�Ϊ��");
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

        printf("\nʹ�ù���");
        for (int m = 0; m <= flag-1; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }

        choose(rule_result[num_m]); //��ι�����ĵڶ������ʵ
        
        printf("\n��ǰ��̬���ݿ�Ϊ��");
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
            printf("����ʧ��\n");

            exit(0);
        }
    }
    else if(flag==0)
    {
        date[0] = rule_result[num_m];

        printf("\nʹ�ù���");
        for (int m = 0; m <= 2; m++)
        {
            choose(rule_prerequisite[num_m][m]);
        }
        choose(rule_result[num_m]); //��ι�����ĵڶ������ʵ

        printf("\n��ǰ��̬���ݿ�Ϊ��");
        for (int n = 0; n <= input_max-1; n++)
        {
            choose(Input[n]);
        }


        printf("\n\n����ʧ��\n");
        printf("\n\n");
        exit(0);
    }

    if (flag != 3)
    {
        if (Input[2] == 0)
        {
            printf("\n����ʧ��\n");

            exit(0);
        }
    }

    return flag;
}