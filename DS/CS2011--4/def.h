#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;

typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode {         //表结点类型定义
        int adjvex;              //顶点位置编号 
     struct ArcNode  *nextarc;       //下一个表结点指针
} ArcNode;

typedef struct VNode{                //头结点及其数组类型定义
        VertexType data;           //顶点信息
     ArcNode *firstarc;           //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];


typedef  struct {  //邻接表的类型定义
    AdjList vertices;          //头结点数组
    int vexnum,arcnum;         //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;

typedef struct{  //图的集合类型定义
     struct { char name[30];
               ALGraph G;    
      } elem[10];
      int nums;
      int Graphs_size;
}Graphs;

//这样可以通过说明语句：ALGraph G;   定义结构变量G，使得G可以表示一个图。

//函数声明
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);

//
status Grabverse(Graphs &g);
status AddG(Graphs &f,char GName[]);
status RemoveG(Graphs &f,char GName[]);
int LocateG(Graphs &f,char GName[]);

void Visit(VertexType v){
    printf("key:%8d   others:%8s\n",v.key, v.others);
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
     if(V[0].key == -1)return ERROR;
     KeyType buf[100] = {0};

     G.vexnum = 0;
     G.arcnum = 0;
     G.kind = UDG;
     int i =0;
     while( V[i].key != -1 ){
          if(i>=20)return ERROR;
          if( buf[V[i].key] == 1)return ERROR;
          else buf[V[i].key] = 1;
          G.vexnum++;
          G.vertices[i].data = V[i];
          G.vertices[i].firstarc = NULL;
          i++;
     }

     int vri = 0;
     while ( VR[vri][0] != -1 )
     {
          if( buf[VR[vri][0]] == 0 || buf[VR[vri][1]] == 0)return ERROR;

          int ii=0;
          while(ii<G.vexnum&& G.vertices[ii].data.key != VR[vri][1]) ii++;
          ArcNode* ti = (ArcNode*)malloc(sizeof(ArcNode));
          ti->adjvex =  ii;
          ti->nextarc = NULL;

          int jj = 0;
          while(jj<G.vexnum&& G.vertices[jj].data.key != VR[vri][0]) jj++;
          ArcNode* tj = (ArcNode*)malloc(sizeof(ArcNode));
          tj->adjvex =  jj;
          tj->nextarc = NULL;
          
          tj->nextarc =G.vertices[ii].firstarc;
          G.vertices[ii].firstarc = tj;

          ti->nextarc =G.vertices[jj].firstarc;
          G.vertices[jj].firstarc = ti;

          G.arcnum++;
          vri++;
     }
     return OK;
    /********** End **********/
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
     for(int i= 0;i<G.arcnum;i++){
         if(G.vertices[i].firstarc == NULL)continue;
         ArcNode* t = G.vertices[i].firstarc;
         G.vertices[i].firstarc = NULL;
         ArcNode* c;
         while(t != NULL){
              c=t;
              t=t->nextarc;
              free(c);
         }
     }
     G.arcnum=0;
     G.vexnum=0;
     return OK;
    /********** End **********/
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i= 0;
     for(;i<G.vexnum;i++){
          if(G.vertices[i].data.key == u)break;
     }
     return (i>= G.vexnum)?-1:i;
    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int index = LocateVex(G,u);
    if(index == -1)return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    {
         if(i==index)continue;
         if(G.vertices[i].data.key == value.key)return ERROR;
    }
    G.vertices[index].data = value;
    return OK;
    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
     int index = LocateVex(G,u);
     if(index == -1)return ERROR;
     if(G.vertices[index].firstarc == NULL)return -1;
     else return G.vertices[index].firstarc->adjvex;
    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
     int inv = LocateVex(G,v);
     int inw = LocateVex(G,w);
     if(inv == -1 || inw == -1)return -1;
     ArcNode* t;
     if(G.vertices[inv].firstarc == NULL)return -1;
     t = G.vertices[inv].firstarc;
     while(t->adjvex != inw && t!= NULL)t=t->nextarc;
     if(t==NULL || t->nextarc == NULL)return -1;
     return t->nextarc->adjvex;
    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
     if(LocateVex(G,v.key) != -1)return ERROR;
     if(G.vexnum >= MAX_VERTEX_NUM)return ERROR;
     G.vertices[G.vexnum].data = v;
     G.vertices[G.vexnum].firstarc =NULL;
     G.vexnum++;
     return OK;
    /********** End **********/
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum == 1)return ERROR;
    int index = LocateVex(G,v);
    if( index == -1)return ERROR;
    if(G.vertices[index].firstarc != NULL){//删除弧
        ArcNode* prv = G.vertices[index].firstarc;
        while(prv != NULL){
            int todel = prv->adjvex;
            ArcNode* todelpr = G.vertices[todel].firstarc;
            ArcNode* last;
            if(todelpr->adjvex == index){
                G.vertices[todel].firstarc = todelpr->nextarc;
                free(todelpr);
            }
            else{
                last = todelpr;
                todelpr = todelpr->nextarc;
                while(todelpr->adjvex != index){
                    last = todelpr;
                    todelpr = todelpr->nextarc;
                }
                last->nextarc = todelpr->nextarc;
                free(todelpr);
            }
            G.arcnum--;
            last = prv;
            prv = prv->nextarc;
            free(last);
        }
        G.vertices[index].firstarc = NULL;
    }
    //顶点删除
    for(int i = index; i<G.vexnum-1;i++){
        G.vertices[i] = G.vertices[i+1];
    }
    G.vexnum--;
    for(int i = 0; i < G.vexnum;i++){
        ArcNode* pr = G.vertices[i].firstarc;
        while(pr!= NULL){
            if(pr->adjvex > index)pr->adjvex-=1;
            pr=pr->nextarc;
        }
    }
    return OK;
    /********** End **********/
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int inv  = LocateVex(G, v);
    int inw  = LocateVex(G, w);
    if( inv == -1)return ERROR;
    if( inw == -1)return ERROR;
    ArcNode* pr = G.vertices[inv].firstarc;
    while(pr!= NULL){
        if(pr->adjvex == inw)return ERROR;
        pr = pr->nextarc;
    }
    ArcNode* newone = (ArcNode*)malloc(sizeof(ArcNode));
    newone->adjvex = inw;
    newone->nextarc = G.vertices[inv].firstarc;
    G.vertices[inv].firstarc = newone;

    ArcNode* newone1 = (ArcNode*)malloc(sizeof(ArcNode));
    newone1->adjvex = inv;
    newone1->nextarc = G.vertices[inw].firstarc;
    G.vertices[inw].firstarc = newone1;
    G.arcnum++;
    return OK;

    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int inv  = LocateVex(G, v);
    int inw  = LocateVex(G, w);
    if( inv == -1)return ERROR;
    if( inw == -1)return ERROR;
    int tag = 0;
    ArcNode* pr = G.vertices[inv].firstarc;
    while(pr!= NULL){
        if(pr->adjvex == inw)tag = 1;
        pr = pr->nextarc;
    }
    if(!tag)return ERROR;
    ArcNode* last;
    pr = G.vertices[inv].firstarc;
    if(G.vertices[inv].firstarc->adjvex == inw){
        G.vertices[inv].firstarc = pr->nextarc;
        free(pr);
    }
    else{
        last = pr;
        pr=pr->nextarc;
        while(pr->adjvex != inw){
            last = pr;
            pr=pr->nextarc;
        }
        last->nextarc = pr->nextarc;
        free(pr);
    }

    pr = G.vertices[inw].firstarc;
    if(G.vertices[inw].firstarc->adjvex == inv){
        G.vertices[inw].firstarc = pr->nextarc;
        free(pr);
    }
    else{
        last = pr;
        pr=pr->nextarc;
        while(pr->adjvex != inv){
            last = pr;
            pr=pr->nextarc;
        }
        last->nextarc = pr->nextarc;
        free(pr);
    }
    G.arcnum--;
    return OK;
    /********** End **********/
}

status DFS(ALGraph &G, void (*visit)(VertexType), int buf[], int index){
    buf[index] = 1;
    visit(G.vertices[index].data);
    ArcNode* pr = G.vertices[index].firstarc;
    while( pr!= NULL){
        if(buf[pr->adjvex] == 0)DFS(G, visit, buf, pr->adjvex);
        pr=pr->nextarc;
    }
    return OK;
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int buf[MAX_VERTEX_NUM+1] = {0};
    for(int i = 0; i<G.vexnum ;i++){
        if(buf[i] == 0)DFS(G, visit, buf, i);
    }
    return OK;
    /********** End **********/
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int queue[MAX_VERTEX_NUM +2] = {0};
    int top=0,rear=0;
    int buf[MAX_VERTEX_NUM+2] = {0};
    int num = 0;
    
    while(num != G.vexnum){
        for(int i=0;i<G.vexnum;i++){
            if(buf[i]==0){
                queue[top++] = i;
                buf[i]=1;
                num++;
                break;
            }
        }
        while(top != rear){
            int index = queue[rear++];
            visit(G.vertices[index].data);
            ArcNode* pr = G.vertices[index].firstarc;
            while(pr!= NULL){
                if(buf[pr->adjvex] == 0){
                    queue[top++] = pr->adjvex;
                    buf[pr->adjvex] = 1;
                    num++;
                }
                pr=pr->nextarc;
            }
        } 
    }
    return OK;
    /********** End **********/
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE* fp = fopen(FileName, "w");
    fprintf(fp, "%d %d %d\n", G.kind, G.vexnum, G.arcnum);
    for(int i=0; i<G.vexnum; i++){
        fprintf(fp, "%d %s ",G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode* pr = G.vertices[i].firstarc;
        while(pr != NULL){
            fprintf(fp, "%d ", pr->adjvex);
            pr = pr->nextarc;
        }
        fprintf(fp, "-1\n");
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE* fp = fopen(FileName, "r");
    fscanf(fp, "%d %d %d", &G.kind, &G.vexnum, &G.arcnum);
    for(int i=0; i<G.vexnum; i++){
        fscanf(fp, "%d %s",&G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
        ArcNode* now =NULL;
        int readc=-1;
        fscanf(fp, "%d", &readc);
        while(readc != -1){
            if(G.vertices[i].firstarc == NULL){
                ArcNode* newone = (ArcNode*)malloc(sizeof(ArcNode));
                newone->nextarc = NULL;
                newone->adjvex = readc;
                G.vertices[i].firstarc = newone;
                now = newone;
            }
            else{
                ArcNode* newone = (ArcNode*)malloc(sizeof(ArcNode));
                newone->nextarc = NULL;
                newone->adjvex = readc;
                now->nextarc = newone;
                now = newone;
            }
            fscanf(fp, "%d", &readc);
        }
    }
    fclose(fp);

    return OK;
    /********** End 2 **********/
}




status Grabverse(Graphs &g)
{//遍历图集合，并打印
	int i;
	printf("\n----------------- all graphs -------------------\n");
	for(i=0;i<g.nums;i++) printf("%4d:   %s \n", i+1, g.elem[i].name);
	printf("\n------------------ end ------------------------\n");
	return g.nums;
}

status AddG(Graphs &f,char GName[])
// 只需要在Graphs中增加一个名称为GName的空二叉树
{
    int i = f.nums++;
    int j=0;
    while(GName[j]!='\0'){
        f.elem[i].name[j]=GName[j];
        j++;
    }
    f.elem[i].name[j]=GName[j];
    f.elem[i].G.vexnum=0;
	return 0;
}

status RemoveG(Graphs &f,char GName[])
// f中删除一个名称为GName的图
{
    int index = LocateG(f, GName);
    if(index == 0){
        printf("无此图！\n");
        return ERROR;
    }
    DestroyGraph(f.elem[index-1].G);
    for(int i = index-1;i<f.nums-1;i++){
        strcpy(f.elem[i].name , f.elem[i+1].name);
        f.elem[i].G= f.elem[i+1].G;       
    }
    f.nums--;
    return OK;
}

int LocateG(Graphs &f,char GName[])
// 在f中查找一个名称为GName的图，成功返回逻辑序号，否则返回0
{
    
    int ok=0;
    int i=0;
    for(; i<f.nums; i++){
        int tag = 1;
        int c=0;
        while(GName[c] != '\0'){
            if(f.elem[i].name[c]  != GName[c]){
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