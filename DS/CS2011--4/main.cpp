#include "def.h"
/*
5 线性表 2 3
8 集合 2
7 二叉树 1 3 0
6 无向图 2 0
*/
//VertexType V[] = {
//   {5,"线性表"},{8, "jihe"},{7,"ercs"},{6, "wuxiangtu"},{-1,"sada"}
//};
//KeyType VR[][2]={{5,6},{5,7},{6,7},{7,8},{-1,-1}};

void menu2(ALGraph &G, int op, char tname[]);

int main(){
	Graphs graphs;
	memset(&graphs, 0, sizeof(Graphs));//设置为空
	graphs.nums = 0;  
	int op=1;

	while(op){
		system("cls");	printf("\n\n");
		printf("          基于邻接表的图操作演示系统 \n");
		printf("-------------------------------------------------\n");
		printf("          1.列出当前的图名    	               \n");
		printf("    	  2.切换到指定图              \n");
		printf("    	  3.增加一个图                   \n");
		printf("    	  4.删除一个图                         \n");
        printf("    	  5.导入一个图                         \n");
		printf("    	  6.保存一个图                         \n");
		printf("    	  0.退出\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~6]:");
		scanf("%d",&op);
		switch (op)
		{
		case 1:
            if(0 == Grabverse(graphs))
                printf("当前无图！");
			getchar();getchar();
			break;
		case 2:
			{
                //切换到指定图
				int index;
				printf("请输入需要切换到的图序号:");
				scanf("%d",&index);
				if(index <= graphs.nums){ 
					menu2( graphs.elem[index-1].G, 1, graphs.elem[index-1].name);
				}
				else printf("输入不正确！\n");
				getchar();getchar();
				break;
			}
		case 3:{
            //插入一个图
            char name[30];
            getchar();
            printf("请输入增加图的名称:");
            scanf("%s",name);
            int con = AddG(graphs, name);
            if(con == OK)printf("增加成功！\n");
			getchar();getchar();
			break;
		}
			
		case 4:{
            char name[30];
            getchar();
            printf("请输入删除图名:");
            scanf("%s",name);
            int con = RemoveG(graphs, name);
            if(con == OK)printf("删除成功！\n");
			getchar();getchar();
			break;
		}
        case 5:{
            char name[30];
            getchar();
            printf("请输入导入文件的文件名:");
            scanf("%s",name);getchar();
            AddG(graphs, name);
            int con = LoadGraph(graphs.elem[graphs.nums-1].G, name);
            if(con == OK){
                printf("导入成功！\n");
            }
            else{
                printf("导入失败！\n");
            }
			getchar();getchar();
			break;
		}
        case 6:{
            char name[30];
            getchar();
            printf("请输入保存的图名:");
            scanf("%s",name);getchar();
            int index = LocateG(graphs, name);
            int con = SaveGraph(graphs.elem[index-1].G, name);
            if(con == OK){
                printf("保存成功！\n");
            }
			getchar();getchar();
			break;
		}
		case 0:
			break;
		default:
			break;
		}
	}
 	printf("欢迎下次再使用本系统！\n");
	return 0;
}

void menu2(ALGraph &G, int op, char tname[]){
	while(op){
	system("cls");	printf("\n\n");
	printf("           基于邻接表的图演示系统 \n");
	printf("                图名: %s \n",tname);
	printf("-------------------------------------------------\n");
	printf("    	  1. 创建无向图             7. 插入顶点\n");
	printf("    	  2. 销毁图                 8. 删除顶点\n");
	printf("    	  3. 查找顶点               9. 插入弧 \n");
	printf("    	  4. 顶点赋值              10. 删除弧\n");
	printf("    	  5. 获得第一邻接点         11. DFS\n");
	printf("    	  6. 获得下一邻接点         12. BFS\n");
	printf("    	  0. 退出\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~12]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
			{
                VertexType V[20];KeyType VR[20][2];
                int i = 0;
                printf("请输入顶点序列:\n");
                scanf("%d %s", &V[i].key, V[i].others);
                while (V[i].key != -1)
                {
                    i++;
                    scanf("%d %s", &V[i].key, V[i].others);
                }
                printf("请输入边序列:\n");
                int j = 0;
                scanf("%d %d", &VR[j][0],  &VR[j][1]);
                while (VR[j][0] != -1)
                {
                    j++;
                    scanf("%d %d", &VR[j][0],  &VR[j][1]);
                }
                int con = CreateCraph(G, V, VR);
                if(con == OK)printf("创建成功！");
                else printf("创建失败");
                printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 2:
			{
                int con = DestroyGraph(G);
                if(con == OK)printf("销毁成功！");
                printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 3:
			{
                KeyType e;
                printf("请输入关键字：");
                scanf("%d", &e);
                int con = LocateVex(G, e);
                if(con == -1){
                    printf("查找失败！");
                }
                else{
                    printf("该顶点位序为%d,data为:\n", con);
                    Visit(G.vertices[con].data);
                }
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 4:
			{
                KeyType u;VertexType value;
                printf("请输入关键字：");
                scanf("%d", &u);
                int con = LocateVex(G, u);
                if(con == -1){
                    printf("查找失败！");
                }
                else{
                    printf("请输入新值(key,others):");
                    scanf("%d %s",&value.key, value.others);
                    int a = PutVex(G,u,value);
                    if(a == ERROR)printf("关键字不唯一！");
                    else printf("修改成功！");
                }
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 5:
			{
                KeyType e;
                printf("请输入关键字：");
                scanf("%d", &e);
                int con = FirstAdjVex(G, e);
                if(con == ERROR){
                    printf("查找失败！");
                }
                else{
                    printf("该顶点第一邻接点位序为%d,data为:\n", con);
                    Visit(G.vertices[con].data);
                }
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 6:
			{
                KeyType v,w;
                printf("请输入一对关键字(1:顶点 2：相对顶点)：");
                scanf("%d %d", &v, &w);
                int con = NextAdjVex(G, v, w);
                if(con == -1){
                    printf("查找失败！");
                }
                else{
                    printf("该顶点相对%d顶点下一邻接点位序为%d,data为:\n", w, con);
                    Visit(G.vertices[con].data);
                }
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 7:
			{
                VertexType value;
                printf("请输入新值(key,others):");
                scanf("%d %s",&value.key, value.others);
                int con = InsertVex(G,value);
                if(con == ERROR)printf("插入失败！");
                else printf("插入成功！");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 8:
			{
                KeyType e;
                printf("请输入关键字：");
                scanf("%d", &e);
                int con = DeleteVex(G, e);
                if(con == ERROR)printf("删除失败！");
                else printf("删除成功！");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 9:
			{
                KeyType v,w;
                printf("请输入一对关键字(两个顶点)：");
                scanf("%d %d", &v, &w);
                int con = InsertArc(G, v, w);
                if(con == ERROR)printf("插入失败！");
                else printf("插入成功！");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 10:
			{
                KeyType v,w;
                printf("请输入一对关键字(两个顶点)：");
                scanf("%d %d", &v, &w);
                int con = DeleteArc(G, v, w);
                if(con == ERROR)printf("删除失败！");
                else printf("删除成功！");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 11:
			{
                DFSTraverse(G, &Visit);
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 12:
			{
                BFSTraverse(G, &Visit);
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 0:
              break;
	}//end of switch
  }//end of while

}