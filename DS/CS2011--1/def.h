#ifndef DRF_H
#define DRF_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 3
#define LISTINCREMENT  10
typedef int status;
typedef int ElemType; //数据元素类型定义

typedef int ElemType;
typedef struct{  //顺序表（顺序结构）的定义
	      ElemType * elem;
	      int length;
	      int listsize;
}SqList;

typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               SqList L;    
      } elem[10];
      int length;
 }LISTS;

#endif