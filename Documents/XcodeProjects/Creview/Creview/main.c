//
//  main.c
//  Creview
//
//  Created by Johnson Johnson on 2017-06-19.
//  Copyright © 2017 Johnson Johnson. All rights reserved.
//

//#include <stdio.h>
//#include <stdlib.h>
//#include "math.h"
//#include "string.h"
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QUEEN 50   //皇后的数目
#define INITIAL -10000   //棋盘的初始值

int a[QUEEN];    //一维数组表示棋盘

void init()  //对棋盘进行初始化
{
    int *p;
    for (p = a; p < a + QUEEN; ++p)
    {
        *p = INITIAL;
    }
}

int valid(int row, int col)    //判断第row行第col列是否可以放置皇后
{
    int i;
    for (i = 0; i < QUEEN; ++i)   //对棋盘进行扫描
    {
        if (a[i] == col || abs(i - row) == abs(a[i] - col))   //判断列冲突与斜线上的冲突
            return 0;
    }
    return 1;
}

void print()    //打印输出N皇后的一组解
{
    int i, j;
    for (i = 0; i < QUEEN; ++i)
    {
        for (j = 0; j < QUEEN; ++j)
        {
            if (a[i] != j)      //a[i]为初始值
                printf("%c ", '.');
            else                //a[i]表示在第i行的第a[i]列可以放置皇后
                printf("%c ", '#');
        }
        printf("\n");
    }
    for (i = 0; i < QUEEN; ++i)
        printf("%d ", a[i]);
    printf("\n");
    printf("--------------------------------\n");
}

void queen()      //N皇后程序
{
    int n = 0;
    int i = 0, j = 0;
    while (i < QUEEN)
    {
        while (j < QUEEN)        //对i行的每一列进行探测，看是否可以放置皇后
        {
            if(valid(i, j))      //该位置可以放置皇后
            {
                a[i] = j;        //第i行放置皇后
                j = 0;           //第i行放置皇后以后，需要继续探测下一行的皇后位置，所以此处将j清零，从下一行的第0列开始逐列探测
                break;
            }
            else
            {
                ++j;             //继续探测下一列
            }
        }
        if(a[i] == INITIAL)         //第i行没有找到可以放置皇后的位置
        {
            if (i == 0)             //回溯到第一行，仍然无法找到可以放置皇后的位置，则说明已经找到所有的解，程序终止
                break;
            else                    //没有找到可以放置皇后的列，此时就应该回溯
            {
                --i;
                j = a[i] + 1;        //把上一行皇后的位置往后移一列
                a[i] = INITIAL;      //把上一行皇后的位置清除，重新探测
                continue;
            }
        }
        if (i == QUEEN - 1)          //最后一行找到了一个皇后位置，说明找到一个结果，打印出来
        {
            printf("answer %d : \n", ++n);
            print();
            //不能在此处结束程序，因为我们要找的是N皇后问题的所有解，此时应该清除该行的皇后，从当前放置皇后列数的下一列继续探测。
            //_sleep(600);
            j = a[i] + 1;             //从最后一行放置皇后列数的下一列继续探测
            a[i] = INITIAL;           //清除最后一行的皇后位置
            continue;
        }
        ++i;              //继续探测下一行的皇后位置
    }
}

int main(void)
{
    init();
    queen();
    system("pause");
    return 0;
}

//typedef struct ListNode{
//    int val;
//    struct ListNode *next;
//} node;
//
//void printList(node* l1){
//    while(l1){
//        if(l1->next!=NULL)
//            printf("%d->",l1->val);
//        else
//            printf("%d\n",l1->val);
//        l1=l1->next;
//    }
//}
////-------------------------------------------------
//// delete with pointer to pointer
//void remove_(node **head, int value) {
//    while (*head) {
//        if ((*head)->val == value) {
//        node *next = (*head)->next;
//            free(*head);
//            *head = next;
//        } else {
//          head = &(*head)->next;
//        }
//    }
//}
////-------------------------------------------------
//// insert node with pointer to pointer
//void insert1_(node **head,int value,int idx){
//    node *prev = NULL;
//    while(*head){
//        if(idx==0){
//            node *added = (node*)malloc(sizeof(node));
//            added->val = value;
//            if(prev==NULL)
//                added->next = *head;
//            else{
//                prev->next = added;
//                added->next = *head;
//                return;
//            }
//        }
//        else{
//            prev = *head;
//            head = &(*head)->next;
//            idx--;
//        }
//    }
//}
//
//void insert2_(node **head,int value,int idx){
//    while(*head){
//        printf("%d,%d\n",*head,**head);
//        if(idx==0){
//            printf("%d,",(*head)->val);
//            node *added = (node*)malloc(sizeof(node));
//            added->val = value;
//            added->next = *head;
//            *head = added;
//            return;
//        }
//        else{
//            head = &(*head)->next;
//            idx--;
//        }
//    }
//}
////-------------------------------------------------
//int main(){
//    int a = 10;
//    node *prev = (node*)malloc(sizeof(node));
//    node *head =(node*)malloc(sizeof(node));
//    for(int i=0;i<a;++i){
//        node* tmp = (node*)malloc(sizeof(node));
//        tmp->val = i;
//        if(i==0) prev = tmp,head = prev;
//        else {
//            prev->next = tmp;
//            prev = tmp;
//        }
//    }
// //   remove_(&head,0);
//    insert2_(&head,100,4);
//    printList(head);
//    // delete or insert
//    
//    
//}

//typedef struct{
//    int *a;
//    int head;
//    int tail;
//    int maxNum;
//}queue;
//
//queue* createQueue(int size){
//    queue *q = (queue*)malloc(sizeof(queue));
//    q->maxNum = size;
//    q->a = (int*)malloc(size*sizeof(int));
//    q->head = 0;
//    q->tail = -1;
//    return q;
//}
//
//void insert(int input, queue* q){
//    if(q->tail-q->head+1>q->maxNum){
//        printf("The queue is full...\n");
//        return;
//    }
//    q->tail+=1;
//    q->a[q->tail] = input;
//    return;
//}
//
//int pop(queue* q){
//    if(q->tail-q->head+1==-1){
//        printf("The queue is null...\n");
//        return -1;
//    }
//    int res = q->a[q->head];
//    q->head+=1;
//    return res;
//}
//
//void deleteQueue(queue *q){
//    if(q->tail-q->head==-1) return;
//    free(q->a);
//    free(q);
//    return;
//}
//
//int main(){
//    queue *Q = (queue*)malloc(sizeof(queue));
//    Q =  createQueue(10);
//    for(int i=0;i<10;++i)
//        insert(i,Q);
//    while(Q->tail-Q->head!=-1){
//        printf("%d",pop(Q));
//    }
//    return 0;
//}
//typedef struct{
//    int top;
//    int num;
//    int *a;
//}stack_struct;
//
//stack_struct *createStk(int size){
//    if(size<0) return NULL;
//    stack_struct *s = (stack_struct*)malloc(size*sizeof(stack_struct));
//    if(s==NULL) return NULL;
//    s->num  = size;
//    s->top = -1;
//    s->a = (int*)malloc(sizeof(int)*size);
//    return s;
//}
//
//void insert(int input,stack_struct *s){
//    
//    if(s->top ==s->num-1){
//        printf("The stack is full...");
//        return;
//    }
//    s->top+=1;
//    s->a[s->top]= input;
//    return;
//}
//
//int pop(stack_struct *s){
//    if(s->top==-1)
//        printf("The stack is empty...");
//    int res = s->a[s->top];
//    s->top-=1;
//    return res;
//}
//int queryELement(stack_struct *s,int idx){
//    if(idx>s->num-1){
//        printf("The idx is bigger than stack size...\n");
//        return -INFINITY;
//    }
//    return s->a[idx];
//}
//void destructStack(stack_struct *s){
//    if(s==NULL) return;
//    free(s->a);
//    free(s);
//    return;
//}
//
//int main(){
//    stack_struct *tmp  = createStk(10);
//    for(int i=0;i<10;++i)
//        insert(i,tmp);
//    
//    printf("%d,",queryELement(tmp, 11));
//    return(0);
//}
