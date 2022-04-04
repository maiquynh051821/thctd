#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jval.h"
#include "jrb.h"
#include "ctype.h"

char *strLWR(char *str);
void readfile(FILE *ptr, JRB stopW);
void word_normalize1(char *word);
char *ItoC(int number, char *target);
int countC(char *A);
int lastNumber(char *A);

int main()
{

    JRB txt, txt1, p, Txt = make_jrb(), stopW = make_jrb(), countTxt = make_jrb();
    char A[20], B[20], C[20];
    char c, c1;
    int count, count1, a, b, d;
    int len, row = 0;
    FILE *ptr = fopen("alice30.txt", "r");
    FILE *fptr = fopen("test1.txt", "w");
    FILE *ptr_stop = fopen("stopw.txt", "r");
    readfile(ptr_stop, stopW);
    while (fscanf(ptr, "%s", A) == 1)
    {

        len = strlen(A); // lay do dai chuoi
        if (A[len - 1] != '.')
            a = 1;
        if (A[len - 1] == '.')
            a = 2;
        word_normalize1(A);
        if (A[0] >= 'A' && A[0] <= 'Z' && b == 1 && d == 1)
        {
            fprintf(fptr, "%s\n", A);
            d = 0;
            b = 0;
        }

        else
        {
            strLWR(A); // dua het ve dang chu khong dau
            txt = jrb_find_str(Txt, strdup(A));
            if (txt == NULL)
            {
                if (strlen(A) != 0)
                {
                    if (jrb_find_str(stopW, strdup(A)) == NULL)
                    {
                        ItoC(row + 1, B); // chuyen tu int sang string roi gan vao B
                        len = strlen(B);
                        B[len - 1] = '\0';
                        jrb_insert_str(countTxt, strdup(A), new_jval_i(1));
                        jrb_insert_str(Txt, strdup(A), new_jval_s(strdup(B)));
                    }
                }
            }
            else

            {
                strcpy(B, jval_s(txt->val)); // copy val vao B
                // count = countC(B);
                txt1 = jrb_find_str(countTxt, strdup(A));
                count1 = jval_i(txt1->val); // gan value
                jrb_delete_node(txt1);
                jrb_insert_str(countTxt, strdup(A), new_jval_i(count1 + 1));

                if (lastNumber(B) < row + 1) // neu so cuoi cung nho hon so dong thi gan vao
                {
                    ItoC(row + 1, C);
                    len = strlen(C);
                    C[len - 1] = '\0';
                    strcat(B, ",");
                    strcat(B, C);
                    // printf("%s", B);
                    count = countC(B);
                    jrb_delete_node(txt);
                    jrb_insert_str(Txt, strdup(A), new_jval_s(strdup(B)));
                }
            }
        }
        fscanf(ptr, "%c", &c);
        if (c == '\n')
        {
            row++;
            b = 2;
        }
        if (c == ' ')
            b = 1;
        d = a;
    }

    jrb_traverse(txt, Txt)
    {
        txt1 = jrb_find_str(countTxt, strdup(jval_s(txt->key)));
        printf("%-20s %d,%s\n", jval_s(txt->key), jval_i(txt1->val), jval_s(txt->val));
    }
    fclose(ptr);
    fclose(fptr);
    fclose(ptr_stop);
    return 0;
}

// gcc -I ~/Arima/C_Advance/Libfdr/ -o ex1 ex1.c ~/Arima/C_Advance/Libfdr/libfdr.a

char *strLWR(char *str) // Chuyển đổi chữ hoa thành chữ thường,
{
    unsigned char *p = (unsigned char *)str;

    while (*p)
    {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

void readfile(FILE *ptr, JRB stopW)
{
    char c, A[10];
    JRB stop;

    while (fscanf(ptr, "%s%*c", A) == 1)
    {
        // printf("%s\n", A);
        stop = jrb_find_str(stopW, strdup(A));
        if (stop == NULL)
        {
            jrb_insert_str(stopW, strdup(A), new_jval_i(1));
        }
    }
}

void word_normalize1(char *word) // xoá kí tự lạ
{
    int i, j;
    for (i = 0; i < strlen(word); i++)
    {
        if (!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')))
        {
            for (j = i; j < strlen(word); j++)
            {
                word[j] = word[j + 1];
            }
            i--;
            continue;
        }
    }
}

char *ItoC(int number, char *target) // chuyen tu int sang string
{
    sprintf(target, "%d\n", number);

    return target;
}

int countC(char *A) // dem so dau phay
{
    int i, count = 0;
    for (i = 0; i < strlen(A); i++)
    {
        if (A[i] == ',')
            count++;
    }
    return count;
}

int lastNumber(char *A) // lay ra so cuoi cung
{
    int i, j = 0, k = 0;
    char B[20];
    int count = countC(A);
    if (count == 0)
    {
        return atoi(A);
    }
    else
    {

        for (i = 0; i < strlen(A); i++)
        {
            if (A[i] == ',')
            {
                k++;
            }
            if (k == count)
            {
                if (A[i + 1] != '\0')
                {
                    B[j] = A[i + 1];
                    j++;
                }
            }
        }
    }

    return atoi(B);
}
