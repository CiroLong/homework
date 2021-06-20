#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int KeyType; 
typedef struct {
     KeyType  key;
     int ID;
     char name[20];
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{    //二叉链表结点的定义
      TElemType data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

typedef struct{  //二叉树的集合类型定义
     struct { char name[30];
               BiTree T;    
      } elem[10];
      int nums;
      int Forestsize;
 }Forest;

status CreateBiTree(BiTree &T,TElemType definition[]);
status DestroyBiTree(BiTree &T);//销毁树
status ClearBiTree(BiTree &T);status subClearBiTree(BiTree &T);
status EmptyBiTree(BiTree &T);//判空
int BiTreeDepth(BiTree T);int subBiTreeDepth(BiTree T);//非递归
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
BiTNode* GetSibling(BiTree T,KeyType e);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));


status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T,  char FileName[]);

status AddTree(Forest &f,char TreeName[]);
status RemoveTree(Forest &f,char TreeName[]);
int LocateTree(Forest &f,char TreeName[]);
status Treerabverse(Forest &f);

//补充函数
void visitBiTree(BiTree T)//打印节点值
{   
    printf("%4d%4d%8s\n",T->data.key, T->data.ID, T->data.name);
    return;
}


status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(definition[0].key == 0){
        T =NULL;
        return OK;
    }
    BiTree stack[100] = {NULL};
    int top = 0;
    KeyType buf[1000] = {0};

    int i=0;
    if(buf[definition[i].key] == 1) return ERROR;
    else buf[definition[i].key] = 1;
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->lchild = root->rchild = NULL;
    root->data = definition[i++];
    stack[top++] = root;
    BiTree now = root;
    while(definition[i].key != -1){
      //向左建树
      while(definition[i].key != 0 && now->lchild == NULL)
      {
            if(buf[definition[i].key] == 1) return ERROR;
                  else buf[definition[i].key] = 1;
            now->lchild =(BiTree)malloc(sizeof(BiTNode));
            now->lchild->lchild = now->lchild->rchild = NULL;
            now->lchild->data = definition[i++];
            stack[top++] = now;
            now =now->lchild;
      }
      if(now->lchild == NULL) i++;
      
      if(definition[i].key != 0){
            if(buf[definition[i].key] == 1) return ERROR;
                  else buf[definition[i].key] = 1;
            now->rchild =(BiTree)malloc(sizeof(BiTNode));
            now->rchild->lchild = now->rchild->rchild = NULL;
            now->rchild->data = definition[i++];
            now = now->rchild;
      }
      else if(definition[i].key == -1){
            break;
      }
      else {
            i++;
            now = stack[--top];
      }
    }

    T = root;
    return OK;
    /********** End **********/
}


status DestroyBiTree(BiTree &T)//销毁树
{
    if(T == NULL) return ERROR;
    if(T->lchild == NULL && T->rchild ==NULL){
          free(T);
          T = NULL;
          return OK;
    }
    if(T->lchild)DestroyBiTree(T->lchild);
    if(T->rchild)DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

status ClearBiTree(BiTree &T)//递归算法
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return OK;
    if(T->lchild == NULL && T->rchild ==NULL){
          free(T);
          T = NULL;
          return OK;
    }
    if(T->lchild)ClearBiTree(T->lchild);
    if(T->rchild)ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
    /********** End **********/
}

status subClearBiTree(BiTree &T)//非递归算法
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL)return OK;
      BiTree stack[100] = {NULL};
      int top = 0;
      stack[top++] = T;
      while(top != 0){
            BiTree now = stack[--top];
            if(now -> lchild != NULL)stack[top++]=now ->lchild;
            if(now -> rchild != NULL)stack[top++]=now ->rchild;
            free(now);
      }
      T = NULL;
      return OK;
    /********** End **********/
}

status EmptyBiTree(BiTree &T){
    if(T == NULL)return OK;
    else return ERROR;
}

int BiTreeDepth(BiTree T){//递归
      if(T==NULL) {
		return 0;
	}
	int nLeft=BiTreeDepth(T->lchild);
	int nRight=BiTreeDepth(T->rchild);
	return nLeft>nRight?nLeft+1:nRight+1;
}

BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T->data.key == e)return T;
    BiTree ret = NULL;
    if(T->lchild){
          ret = LocateNode(T->lchild, e);
          if(ret)return ret;
    }
    if(T -> rchild){
          ret = LocateNode(T->rchild, e);
          if(ret)return ret;
    }
    return NULL;
    /********** End **********/
}

status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int buf[1000]= {0};

    BiTree queue[100];
    int top = 0, base = 0;

    BiTree now, find=NULL;
    queue[top++] = T;

    while(top > base){
        now = queue[base++];
        if(now -> lchild)queue[top++] = now ->lchild;
        if(now -> rchild)queue[top++] = now -> rchild;
        if( now ->data.key == e){
            find = now;
            continue;
        }
        buf[now ->data.key] = 1;
    }
    if( buf[value.key] == 1)return ERROR;
    if( !find)return ERROR;
    find ->data = value;
    return OK;
    /********** End **********/
}

BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T->data.key == e)return NULL;
    BiTree queue[100];
    int top = 0, base = 0;
    int tag =0;
    BiTree now;
    queue[top++] = T;
    while(top > base){
        now = queue[base++];
        if(now -> lchild){
            if(now->lchild->data.key == e){
                now = now ->rchild;
                tag = 1;
                break;
            }
            else
                queue[top++] = now ->lchild;
        }
        if(now -> rchild){
            if( now ->rchild->data.key == e){
                now  = now->lchild;
                tag = 1;
                break;
            }
            else 
                queue[top++] = now -> rchild;
        }
    }
    if(tag == 1)
        return now;
    else return NULL;
    /********** End **********/
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(LR == -1){
        BiTree now = (BiTree)malloc(sizeof(BiTNode));
        now ->lchild = NULL;
        now ->rchild = T;
        now -> data = c;
        T = now;
        return OK;
    }
    int buf[1000]= {0};

    BiTree queue[100];
    int top = 0, base = 0;

    BiTree now, find=NULL;
    queue[top++] = T;

    while(top > base){
        now = queue[base++];
        if(now -> lchild)queue[top++] = now ->lchild;
        if(now -> rchild)queue[top++] = now -> rchild;
        if( now ->data.key == e){
            find = now;
        }
        buf[now ->data.key] = 1;
    }
    if( buf[c.key] == 1)return ERROR;
    if( !find)return ERROR;
    
    if(LR){
        BiTree t = (BiTree)malloc(sizeof(BiTNode));
        t -> lchild = NULL;
        t -> rchild = find -> rchild;
        t -> data = c;
        find -> rchild = t;
    }
    else {
        BiTree t = (BiTree)malloc(sizeof(BiTNode));
        t -> lchild = NULL;
        t -> rchild = find -> lchild;
        t -> data = c;
        find -> lchild = t;
    }
    return OK;
    /********** End **********/
}

status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree find = NULL;
    int tag =0;
    if(T->data.key == e){
        if(T->lchild){
            BiTree t = T->lchild;
            while(t->rchild !=NULL)t=t->rchild;
            t->rchild = T->rchild;
            find =T;
            T=T->lchild;
            free(find);
        }
        else if(T->rchild){
            find =T;
            T=T->rchild;
            free(find);
        }
        else{
            free(T);
            T= NULL;
        }
        return OK;
    }
else{
    BiTree queue[100];
    int top = 0, base = 0;
    BiTree now;
    queue[top++] = T;
    while(top > base){
        now = queue[base++];
        if(now -> lchild){
            if(now->lchild->data.key == e){
                find  = now;
                break;
            }
            else
                queue[top++] = now ->lchild;
        }
        if(now -> rchild){
            if( now ->rchild->data.key == e){
                find = now;
                tag = 1;
                break;
            }
            else 
                queue[top++] = now -> rchild;
        }
    }
    if(!find)return ERROR;
    BiTree todel = tag?find->rchild:find->lchild;
    if(todel->lchild){
        BiTree t = todel->lchild;
        while(t->rchild != NULL)t = t->rchild;
        t->rchild=todel->rchild;
        if(tag) find ->rchild = todel->lchild;
        else find ->lchild = todel -> lchild;
        free(todel);
        return OK;
    }
    else{
        if(tag) find ->rchild = todel->rchild;
        else find ->lchild = todel -> rchild;
        free(todel);
        return OK;
    }
}
    /********** End **********/
}

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T , 非递归
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL)return OK;
    BiTree stack[100];
    int top =0;
    stack[top++] =T;
    BiTree now;
    while(top!= 0){
        now = stack[--top];
        visit(now);
        if(now->rchild != NULL){
            stack[top++] = now->rchild;
        }
        if( now ->lchild != NULL)stack[top++] = now ->lchild;
    }
    return OK;
    /********** End **********/
}

status subPreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T 递归
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL)return OK;
    (*visit)(T);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL)return OK;
    InOrderTraverse(T->lchild, visit);
    (*visit)(T);
    InOrderTraverse(T->rchild, visit);
    return OK;

    /********** End **********/
}

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL)return OK;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    (*visit)(T);
    return OK;

    /********** End **********/
}


status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree queue[100];
    int top =0, base=0;
    queue[top++] = T;
    BiTree now;
    while(top>base){
        now =queue[base++];
        (*visit)(now);
        if(now->lchild) queue[top++] = now->lchild;
        if(now->rchild) queue[top++] = now->rchild;
    }
    return OK;
    /********** End **********/
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE* fp = fopen(FileName, "w");
    if(T == NULL){
        fprintf(fp, "\n");
    }
    else{
        BiTree stack[100];
        int top=0;
        stack[top++] = T;
        BiTree now ;
        while(top != 0){//先序
            now = stack[--top];
            if(now == NULL){
                fprintf(fp, "0 0 null\n");
                continue;
            }
            while(now -> lchild != NULL){
                 fprintf(fp, "%d %d %s\n", now->data.key, now->data.ID, now->data.name);
                 if( now -> rchild ){
                    stack[top++] = now -> rchild;
                 }
                 else {
                     stack[top++] = NULL;
                 }
                 now = now -> lchild;
            }
            fprintf(fp, "%d %d %s\n", now->data.key, now->data.ID, now->data.name);
            fprintf(fp, "0 0 null\n");
            if(now->rchild){
                stack[top++] = now -> rchild;
            }
            else {
                fprintf(fp, "0 0 null\n");
            }
        }
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}
status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE* fp = fopen(FileName, "r");
    TElemType definition[100];
    int i = 0;
    fscanf(fp, "%d", &definition[i].key);
     fscanf(fp, "%d", &definition[i].ID);
    fscanf(fp, "%s",definition[i].name);
    i++;
    fgetc(fp);
    while(fscanf(fp, "%d", &definition[i].key) != EOF ){
        fscanf(fp, "%d", &definition[i].ID);
        fscanf(fp, "%s",definition[i].name);
        i++;
        fgetc(fp);
    }
    definition[i].key = -1;
    definition[i].ID = 0;
    sprintf(definition[i].name,"null");
    free(T);
    T = NULL;
    CreateBiTree(T, definition);
    fclose(fp);
    return OK;

    /********** End 2 **********/
}


status AddTree(Forest &f,char TreeName[])
// 只需要在Forest中增加一个名称为TreeName的空二叉树
{
    int i = f.nums++;
    int j=0;
    while(TreeName[j]!='\0'){
        f.elem[i].name[j]=TreeName[j];
        j++;
    }
    f.elem[i].name[j]=TreeName[j];
    f.elem[i].T ==NULL;
	return 0;
}

status RemoveTree(Forest &f,char TreeName[])
// f中删除一个名称为TreeName的二叉树
{
    int index = LocateTree(f, TreeName);
    if(index == 0){
        printf("无此二叉树！\n");
        return ERROR;
    }
    DestroyBiTree(f.elem[index-1].T);
    for(int i = index-1;i<f.nums-1;i++){
        strcpy(f.elem[i].name , f.elem[i+1].name);
        f.elem[i].T = f.elem[i+1].T;       
    }
    f.nums--;
    return OK;
}

int LocateTree(Forest &f,char TreeName[])
// 在f中查找一个名称为TreeName的二叉树，成功返回逻辑序号，否则返回0
{
    
    int ok=0;
    int i=0;
    for(; i<f.nums; i++){
        int tag = 1;
        int c=0;
        while(TreeName[c] != '\0'){
            if(f.elem[i].name[c]  != TreeName[c]){
                tag = 0;
                break;
            }
            c++;
        }
        if(tag){
            ok=1;
            break;
        }
    }
    if(ok){
        return i+1;
    }
    return 0;
}
status Treerabverse(Forest &f)
{//遍历二叉树集合，并打印
	int i;
	printf("\n----------------- all trees -------------------\n");
	for(i=0;i<f.nums;i++) printf("%4d:   %s \n", i+1, f.elem[i].name);
	printf("\n------------------ end ------------------------\n");
	return f.nums;
}