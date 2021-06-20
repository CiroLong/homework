#include "def.h"

//1 a 2 b 0 null  0 null 3 c 4 d  0 null  0 null 5 e  0 null  0 null -1 null
void menu2(BiTree &T,int op, char tname[]);
/*TElemType definition[100]= {
        {1,1,"a"},
        {2,2,"b"},
        {0,1, "null"},
        {0,1,"null"},
        {3,3,"c"},
        {4,4,"d"}, {0,1,"null"},{0,1,"null"},{5,5,"e"},{0,1,"null"},{0,1,"null"},{-1,1,"null"}
};*/
int main(){
	Forest f;
	memset(&f, 0, sizeof(Forest));//设置为空
	f.nums = 0;  
	int op=1;

	while(op){
		system("cls");	printf("\n\n");
		printf("          基于二叉链表的二叉树操作演示系统 \n");
		printf("-------------------------------------------------\n");
		printf("          1.列出当前的二叉树名    	               \n");
		printf("    	  2.切换到指定二叉树              \n");
		printf("    	  3.增加一个二叉树                   \n");
		printf("    	  4.删除一个二叉树                         \n");
        printf("    	  5.导入一个二叉树                         \n");
		printf("    	  6.保存一个二叉树                         \n");
		printf("    	  0.退出\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~6]:");
		scanf("%d",&op);
		switch (op)
		{
		case 1:
			if(0 == Treerabverse(f))
                printf("当前无树！");
			printf("按任意键继续...\n");
			getchar();getchar();
			break;
		case 2:
			{
                //切换到指定tree
				int index;
				printf("请输入需要切换到的树序号:");
				scanf("%d",&index);
				if(index <= f.nums){ 
					menu2( f.elem[index-1].T, 1, f.elem[index-1].name);
				}
				else printf("输入不正确！\n");
				getchar();getchar();
				break;
			}
		case 3:{
			//插入一个tree
            char name[30];
            getchar();
            printf("请输入增加树的名称:");
            scanf("%s",name);
            int con = AddTree(f, name);
            printf("增加成功！\n");
			getchar();getchar();
			break;
		}
			
		case 4:{
            //删除一个tree
            char name[30];
            getchar();
            printf("请输入删除树名:");
            scanf("%s",name);
            int con = RemoveTree(f, name);
            printf("删除成功！\n");
			getchar();getchar();
			break;
		}
        case 5:{
			//导入一个tree
            char name[30];
            getchar();
            printf("请输入导入文件的文件名:");
            scanf("%s",name);getchar();
            AddTree(f, name);
			f.elem[f.nums-1].T = NULL;
            int con = LoadBiTree(f.elem[f.nums-1].T, name);
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
            //保存一个tree
            char name[30];
            getchar();
            printf("请输入保存的树名:");
            scanf("%s",name);getchar();
            int index = LocateTree(f, name);
            int con = SaveBiTree(f.elem[index-1].T, name);
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

void menu2(BiTree &T,int op, char tname[]){
	while(op){
	system("cls");	printf("\n\n");
	printf("           基于二叉链表的二叉树演示系统 \n");
	printf("           二叉树名: %s \n",tname);
	printf("-------------------------------------------------\n");
	printf("    	  1. 创建二叉树          9. 插入节点\n");
	printf("    	  2. 销毁二叉树         10. 删除节点\n");
	printf("    	  3. 清空二叉树         11. 先序遍历 \n");
	printf("    	  4. 判空二叉树         12. 中序遍历\n");
	printf("    	  5. 求二叉树深         13. 后序遍历\n");
	printf("    	  6. 查找节点           14. 层序遍历\n");
    printf("    	  7. 节点赋值           15. 保存二叉树\n");
	printf("    	  8. 获取兄弟节点       16. 导入二叉树\n");
	printf("    	  0. 退出\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~16]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
			{
				printf("请选择输入建树序列：");
				TElemType definition[100]={0};
				int i=0;
				do{
					scanf("%d %d %s",&definition[i].key, &definition[i].ID, definition[i].name);
				}while(definition[i++].key != -1);
				if(CreateBiTree(T, definition) == OK){
					printf("建树成功！\n");
				}
				else 
					printf("建树失败！\n");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 2:
			{
				if( DestroyBiTree(T) == OK){
					printf("二叉树销毁成功!\n");
				}
			 	else printf("二叉树已销毁！\n");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 3:
			{
				if( ClearBiTree(T) == OK){
					printf("二叉树清空成功!\n");
				}
			 	else printf("二叉树已经为空!\n");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 4:
			{
				if( EmptyBiTree(T) == OK){
					printf("二叉树为空！\n");
				}
				else printf("二叉树不为空!\n");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 5:
			{
				int depth = BiTreeDepth(T);
				printf("二叉树深度为%d!\n", depth);
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 6:
			{
				KeyType e;
				printf("请给出节点关键字：");
				scanf("%d",&e);
				BiTree now = LocateNode(T, e);
				if( now != NULL){
					printf("关键字为%d的节点数据域为:\n",e);
					printf("id:%d, name:%s\n",now->data.ID,now->data.name);
				}else{
					printf("没有关键字为%d的节点!\n",e);
				}
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 7:
			{
				KeyType e;
				printf("请给出节点关键字：");
				scanf("%d",&e);
				getchar();
				BiTree now = LocateNode(T, e);
				if( now != NULL){
					printf("关键字为%d的节点数据域为:\n",e);
					printf("id:%d, name:%s\n",now->data.ID,now->data.name);
					TElemType value={0};
					printf("请给出新的key:");
					scanf("%d",&value.key);
					getchar();
					printf("请给出新的id:");
					scanf("%d",&value.ID);
					getchar();
					printf("请给出新的name:");
					scanf("%s",value.name);
					if(Assign(T, e, value) == OK){
						printf("赋值成功！\n");
					}
					else printf("赋值失败！\n");
				}else{
					printf("赋值失败，没有关键字为%d的节点!\n",e);
				}
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 8:
			{
				KeyType e;
				printf("请给出节点关键字：");
				scanf("%d",&e);
				BiTree now = GetSibling(T, e);
				if( now != NULL){
					printf("关键字为%d的节点的兄弟节点关键字为:%d,数据域为\n",e,now->data.key);
					printf("id:%d, name:%s\n",now->data.ID,now->data.name);
				}else{
					printf("关键字为%d的节点没有兄弟节点!\n",e);
				}
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 9:
			{
				TElemType value={0};
				printf("请给出待插入节点的key:");
				scanf("%d",&value.key);
				getchar();
				printf("请给出待插入节点的id:");
				scanf("%d",&value.ID);
				getchar();
				printf("请给出待插入节点的name:");
				scanf("%s",value.name);

				int LR;
				printf("请给出插入节点为左子树或右子树：(0左 1右 -1插入为根节点)\n");
				scanf("%d",&LR);getchar();
				KeyType e;
				if(LR != -1){
					printf("请给出插入节点父节点的关键字：");
					scanf("%d",&e);
					getchar();
				}

				if(InsertNode(T,e,LR,value) == OK){
					printf("插入成功！\n");
				}
				 else printf("插入失败！\n");

				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 10:
			{
				KeyType e;
				printf("请给出需删除节点关键字：");
				scanf("%d",&e);
				getchar();
				if( DeleteNode(T, e) == OK ){
					printf("删除成功！\n");
				}else{
					printf("删除失败，没有关键字为%d的节点!\n",e);
				}
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 11:
			{
				if(EmptyBiTree(T) == OK){
					printf("二叉树为空！\n");
					printf("请按任意键继续...");
					getchar();getchar();
		 			continue;
				}
				printf("二叉树先序遍历如下：\n");
				printf("%4s%4s%8s\n","key","ID","name");
				PreOrderTraverse(T, visitBiTree);
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 12:
			{
				if(EmptyBiTree(T) == OK){
					printf("二叉树为空！\n");
					printf("请按任意键继续...");
					getchar();getchar();
		 			continue;
				}
				printf("二叉树中序遍历如下：\n");
				printf("%4s%4s%8s\n","key","ID","name");
				InOrderTraverse(T, visitBiTree);
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 13:
			{
				if(EmptyBiTree(T) == OK){
					printf("二叉树为空！\n");
					printf("请按任意键继续...");
					getchar();getchar();
		 			continue;
				}
				printf("二叉树后序遍历如下：\n");
				printf("%4s%4s%8s\n","key","ID","name");
				PostOrderTraverse(T, visitBiTree);
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 14:
			{
				if(EmptyBiTree(T) == OK){
					printf("二叉树为空！\n");
					printf("请按任意键继续...");
					getchar();getchar();
		 			continue;
				}
				printf("二叉树层序遍历如下：\n");
				printf("%4s%4s%8s\n","key","ID","name");
				LevelOrderTraverse(T, visitBiTree);
				printf("请按任意键继续...");
				getchar();getchar();
				getchar();getchar();
		 		continue;
			}
	   case 15:
			{
				printf("请输入写入文件名：");
				char filename[100];
				scanf("%s",filename);
				if(OK == SaveBiTree(T, filename) ){
					printf("保存成功！\n");
				}
				else printf("保存失败！\n");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 16:  
			{
				printf("请输入导入文件名：");
				char filename[100];
				scanf("%s",filename);
				if(OK == LoadBiTree(T, filename) ){
					printf("导入成功！\n");
				}
				else printf("导入失败！\n");
				printf("请按任意键继续...");
				getchar();getchar();
		 		continue;
			}
	   case 0:
              break;
	}//end of switch
  }//end of while

}