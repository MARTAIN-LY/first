/*******************
**实验九
**创建人：刘远
**学号：  200111223

文件从score.txt读取
如果成功从文件中读取了数据，就不需要再从键盘输入
文件以添加方式写入newscore.txt
-------------------
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
#define CUR 6
#define LEN 20

typedef struct
{
    long ID;
    char name[LEN];
    int score[CUR];
    int sum;
    float average;
} STUDENT;

void InputRecord(STUDENT stu[], int *n, int *m);
void EachCourse(STUDENT stu[], int n, int m);
void EachStudent(STUDENT *ps[], int n, int m);
void SelectionSort(int (*func)(int a, int b), STUDENT *ps[], int n, int m);
int Descending(int a, int b);
int Ascending(int a, int b);
void FollowID(STUDENT *ps[], int n, int m);
void FollowName(STUDENT *ps[], int n, int m);
void IDSearch(STUDENT *ps[], int n, int m);
void NameSearch(STUDENT *ps[], int n, int m);
void Analysis(STUDENT stu[], int n, int m);
void Print1(STUDENT *ps[], int n);
void Print2(STUDENT *ps[], int n, int m);
void Swap(STUDENT *ps[MAX], int a, int b);
void WritetoFile(STUDENT *ps[], FILE *fp, int n, int m);
int ReadfromFile(STUDENT *ps[], FILE *fp, int *n, int *m);

int main(void)
{
    printf("Number: 200111223\nsubject No.9--program No.1\n\n");

    STUDENT stu[MAX];
    STUDENT *ps[MAX];

    for (int i = 0; i < MAX; i++)
    {
        ps[i] = &stu[i];
    }

    int choice, n, m;
    int flag = 0;
    FILE *fp = NULL;

    do
    {
        do
        {
            do
            {
                choice = -1;
                printf("\n\n-----------\n 1. Input record\n");
                printf(" 2. Calculate total and average score of every course \n");
                printf(" 3. Calculate total and average score of every student \n");
                printf(" 4. Sort in descending order by total score of every student \n");
                printf(" 5. Sort in ascending order by total score of every student \n");
                printf(" 6. Sort in ascending order by number \n");
                printf(" 7. Sort in dictionary order by name \n");
                printf(" 8. Search by number \n 9. Search by name \n");
                printf("10. Statistic analysis for every course \n");
                printf("11. List record \n12. Write to a file.\n");
                printf("13. Read from a file.\n");
                printf(" 0. Exit\n-------------\n");
                printf("    Please enter your choice:         ");
                fflush(stdin); //该函数作用是清空缓冲区
                scanf("%d", &choice);
                if (choice < 0 || choice > 13)
                    printf("Input error! Please enter your choice again!!!         ");
            } while (choice < 0 || choice > 13); //检测选择是否在范围内

            if (choice == 13)
                goto READ;
            if (choice == 1)
                flag++;
            if (choice == 0)
                exit(0);
            if (flag == 0 && choice > 1)
            {
                printf("Please input the data first!!!!\n");
            }
        } while (flag == 0 && choice > 1); //提醒用户先输入数据再进行其他操作

        switch (choice)
        {
        case 1:
            InputRecord(stu, &n, &m); //....
            break;
        case 2:
            EachCourse(stu, n, m); //....
            break;
        case 3:
            EachStudent(ps, n, m); //....
            Print1(ps, n);
            break;
        case 4:
            SelectionSort(Descending, ps, n, m); //
            Print1(ps, n);
            break;
        case 5:
            SelectionSort(Ascending, ps, n, m); //
            Print1(ps, n);
            break;
        case 6:
            FollowID(ps, n, m); //
            Print2(ps, n, m);
            break;
        case 7:
            FollowName(ps, n, m); //
            Print2(ps, n, m);
            break;
        case 8:
            IDSearch(ps, n, m); //....
            break;
        case 9:
            NameSearch(ps, n, m); //....
            break;
        case 10:
            Analysis(stu, n, m); //....
            break;
        case 11:
            SelectionSort(Descending, ps, n, m); //
            Print2(ps, n, m);
            break;
        case 12:
            SelectionSort(Descending, ps, n, m); //
            WritetoFile(ps, fp, n, m);
            break;
        case 13:
        READ:
            flag = ReadfromFile(ps, fp, &n, &m);
            break;
        }
    } while (choice >= 0 && choice <= 13);

    return 0;
}

//1. 函数功能：录入每个学生的学号、姓名和各科考试成绩。
void InputRecord(STUDENT stu[], int *n, int *m)
{
    int ret;
    do
    {   ret = -1;
        printf("Please enter the number of the students(no more than 30):    ");
        fflush(stdin);
        ret = scanf("%d", n);
    } while (*n < 1 || *n > 30 || ret != 1); //检测人数是否合法

    putchar('\n');

    do
    {   ret = -1;
        printf("Please enter the number of the courses(no more than 6):    ");
        fflush(stdin);
        ret = scanf("%d", m);
    } while (*m < 1 || *m > 6 || ret != 1); //检测课程数是否合法

    putchar('\n');
    printf("Please enter student's ID, name and score according to the tip: \n");
    for (int i = 0; i < *n; i++)
    {

        do
        {
            ret = -1;
            printf("student %2d's ID:      ", i + 1);
            fflush(stdin);
            ret = scanf("%ld", &stu[i].ID);
            if (ret != 1 || stu[i].ID < 0)
                printf("Input error!!! Please enter the ID again!!!\n");

        } while (ret != 1 || stu[i].ID < 0); //对非法字符输入的检测

        printf("student %2d's name:      ", i + 1);
        fflush(stdin);
        gets(stu[i].name);

        for (int j = 0; j < *m; j++)
        {
            do
            {   ret = -1;
                printf("the score of course%2d:     ", j + 1);
                fflush(stdin);
                ret = scanf("%d", &stu[i].score[j]);

                if (stu[i].score[j] < 0 || stu[i].score[j] > 100 || ret != 1)
                    printf("Input error!!! Please enter the score again!!!\n");

            } while (stu[i].score[j] < 0 || stu[i].score[j] > 100 || ret != 1); //对非法字符的检测
        }
        putchar('\n');
    }
    puts("You have input all the data successfully! Congratulations!\n");
}

//2. 函数功能：计算每门课程的总分和平均分。...
void EachCourse(STUDENT stu[], int n, int m)
{
    int SumCourse[CUR] = {0};
    double AverCourse[CUR] = {0};

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            SumCourse[i] += stu[j].score[i];
        }
        AverCourse[i] = (double)SumCourse[i] / n;
        printf("\nThe total score of course%2d is:    %d\n", i + 1, SumCourse[i]);
        printf("The average score of course%2d is:  %.2f\n", i + 1, AverCourse[i]);
    }
}

//3. 计算每个学生的总分和平均分。...
void EachStudent(STUDENT *ps[], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        ps[i]->sum = 0; //初始化总分为0，当多次调用该函数时不会出现累积结果
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ps[i]->sum += ps[i]->score[j];
        }
        ps[i]->average = (float)ps[i]->sum / m;
    }
}

//对每个学生的总分按某种顺序排出名次表。
void SelectionSort(int (*func)(int a, int b), STUDENT *ps[], int n, int m)
{
    EachStudent(ps, n, m); //无论用户是否已经选择过功能三，都能实现正常排序
    int i, j, k;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if ((*func)(ps[j]->sum, ps[k]->sum))
                k = j;
        }
        if (k != i)
        {
            Swap(ps, k, i);
        }
    }
}

//4.函数功能：按成绩由高到低.
int Descending(int a, int b)
{
    return a > b;
}

//5.函数功能：按成绩由低到高.
int Ascending(int a, int b)
{
    return a < b;
}

//6.函数功能：按学号由小到大排出成绩表
void FollowID(STUDENT *ps[], int n, int m)
{
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (ps[j]->ID < ps[k]->ID)
                k = j;
        }
        if (k != i)
        {
            Swap(ps, k, i);
        }
    }
}

//7.函数功能：按姓名的字典顺序排出成绩表
void FollowName(STUDENT *ps[], int n, int m)
{
    int i, j, k;

    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(ps[j]->name, ps[k]->name) < 0)
                k = j;
        }
        if (k != i)
        {
            Swap(ps, k, i);
        }
    }
}

//8.函数功能：按学号查询学生排名及其各科考试成绩
void IDSearch(STUDENT *ps[], int n, int m)
{
    SelectionSort(Descending, ps, n, m);
    int k = -1;
    long x;

    putchar('\n');
    printf("Please enter one's ID:    ");
    fflush(stdin);
    scanf("%ld", &x);

    for (int i = 0; i < n; i++)
    {
        if (x == ps[i]->ID)
        {
            k = i;
            break;
        }
    }
    if (k == -1)
        printf("Don't exist!!!\n");
    else
    {
        printf("\nname:   %15s    ranking:%2d\n", ps[k]->name, k + 1); ////////////////
        for (int i = 0; i < m; i++)
        {
            printf("the score of course%2d:%4d\n", i + 1, ps[k]->score[i]);
        }
    }
}

//9.函数功能：按姓名查询学生排名以及分数
void NameSearch(STUDENT *ps[], int n, int m)
{
    SelectionSort(Descending, ps, n, m);

    int i, k = -1;
    char a[15];
    printf("Please enter the name:    ");
    fflush(stdin);
    gets(a);

    for (i = 0; i < n; i++)
    {
        if (strcmp(a, ps[i]->name) == 0)
        {
            k = i;
            break;
        }
    }
    if (k == -1)
        printf("Don't exist!!!\n");
    else
    {
        printf("\nID: %-15ld    ranking:%d\n", ps[k]->ID, k + 1);
        for (int i = 0; i < m; i++)
        {
            printf("the score of course%2d:%4d\n", i + 1, ps[k]->score[i]);
        }
    }
}

//10.函数功能：统计每个类别的人数以及所占的百分比
void Analysis(STUDENT stu[], int n, int m)
{
    int Each[CUR][5] = {0};
    double Rate[CUR][5] = {0};

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (stu[j].score[i] >= 90 && stu[j].score[i] <= 100)
                Each[i][0]++;
            else if (stu[j].score[i] >= 80 && stu[j].score[i] <= 89)
                Each[i][1]++;
            else if (stu[j].score[i] >= 70 && stu[j].score[i] <= 79)
                Each[i][2]++;
            else if (stu[j].score[i] >= 60 && stu[j].score[i] <= 69)
                Each[i][3]++;
            else
                Each[i][4]++;
        }
        Rate[i][0] = (double)Each[i][0] / n * 100;
        Rate[i][1] = (double)Each[i][1] / n * 100;
        Rate[i][2] = (double)Each[i][2] / n * 100;
        Rate[i][3] = (double)Each[i][3] / n * 100;
        Rate[i][4] = (double)Each[i][4] / n * 100;
    }
    for (int i = 0; i < m; i++)
    {
        printf("\n              course%2d         \n", i + 1);
        printf("---------------------------------------");
        printf("\n  优秀  人数：%2d   ， 优秀率： %.2f%%", Each[i][0], Rate[i][0]);
        printf("\n  良好  人数：%2d   ， 良好率： %.2f%%", Each[i][1], Rate[i][1]);
        printf("\n  中等  人数：%2d   ， 中等率： %.2f%%", Each[i][2], Rate[i][2]);
        printf("\n  及格  人数：%2d   ， 及格率： %.2f%%", Each[i][3], Rate[i][3]);
        printf("\n不及格  人数：%2d   ，不及格率：%.2f%%\n", Each[i][4], Rate[i][4]);
    }
}

//函数功能：输出学生姓名、学号、总分
void Print1(STUDENT *ps[], int n)
{
    printf("\nID                   name         total            average");
    printf("\n-----------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%ld  %15s         %4d            %.2f\n", ps[i]->ID, ps[i]->name, ps[i]->sum, ps[i]->average);
    }
}

//函数功能：输出学号、姓名、各科分数
void Print2(STUDENT *ps[], int n, int m)
{
    printf("ranking            ID              name");
    for (int i = 0; i < m; i++)
        printf("   C%d", i + 1);
    printf("         sum           average");
    printf("\n------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%6d) %15ld %15s", i + 1, ps[i]->ID, ps[i]->name);
        for (int j = 0; j < m; j++)
        {
            printf("%5d", ps[i]->score[j]);
        }
        printf("           %4d            %.2f", ps[i]->sum, ps[i]->average);
        putchar('\n');
    }
}

void Swap(STUDENT *ps[MAX], int a, int b)
{
    STUDENT *temp;
    temp = ps[a];
    ps[a] = ps[b];
    ps[b] = temp;
}

//函数功能：将每个学生信息写入文件
void WritetoFile(STUDENT *ps[], FILE *fp, int n, int m)
{
    fp = fopen("newscore.txt", "a");
    if (fp == NULL)
    {
        printf("No enough memory!!!\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(fp, "%16ld%20s", ps[i]->ID, ps[i]->name);
            for (int j = 0; j < m; j++)
            {
                fprintf(fp, "%5d", ps[i]->score[j]);
            }
            fprintf(fp, "%10d%10.2f", ps[i]->sum, ps[i]->average);
            fputc('\n', fp);
        }
        printf("The data has been written to newscore.txt!\n");
    }
    fclose(fp);
}

//从文件读取信息并显示在屏幕上
int ReadfromFile(STUDENT *ps[], FILE *fp, int *n, int *m)
{
    fp = fopen("score.txt", "r");
    if (fp == NULL)
    {
        printf("Haven't found the file!\n");
        fclose(fp);
        return 0;
    }
    else
    {
        do
        {
            printf("Please enter the number of the students(no more than 30):    ");
            fflush(stdin);
            scanf("%d", n);
        } while (*n < 1 || *n > 30); //检测人数是否合法

        do
        {
            printf("Please enter the number of the courses(no more than 6):    ");
            fflush(stdin);
            scanf("%d", m);
        } while (*m < 1 || *m > 6); //检测课程数是否合法
        for (int i = 0; i < (*n); i++)
        {
            fscanf(fp, "%ld%s", &(ps[i]->ID), ps[i]->name);
            for (int j = 0; j < (*m); j++)
            {
                fscanf(fp, "%d", &(ps[i]->score[j]));
            }
        }
        EachStudent(ps, *n, *m);
        Print2(ps, *n, *m);
        fclose(fp);
        return 1;
    }
}
