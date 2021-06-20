#include "list2.h"
void menu2(LinkList &L,int op, char lname[]);

int main(){
	LISTS lists;
	memset(&lists, 0, sizeof(LISTS));//设置为空
	lists.length = 0;  
	int op=1;

	while(op){
		system("cls");	printf("\n\n");
		printf("          基于链表的线性表操作演示系统 \n");
		printf("-------------------------------------------------\n");
		printf("          1.列出当前的线性表名    	               \n");
		printf("    	  2.切换到指定线性表              \n");
		printf("    	  3.增加一个线性表                   \n");
		printf("    	  4.删除一个线性表                         \n");
        printf("    	  5.导入一个线性表                         \n");
		printf("    	  6.保存一个线性表                         \n");
		printf("    	  0.退出\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~12]:");
		scanf("%d",&op);
		switch (op)
		{
		case 1:
            //列出线性表名
			if(0 == LISTSTrabverse(lists))
                printf("当前无线性表！");
			printf("按任意键继续...\n");
			getchar();getchar();
			break;
		case 2:
			{
                //切换到指定线性表
				int index;
				printf("请输入需要切换到的线性表序号:");
				scanf("%d",&index);
				if(index <= lists.length){
					menu2( lists.elem[index-1].L, 1,lists.elem[index-1].name);
				}
				else printf("输入不正确！\n");
				getchar();getchar();
				break;
			}
		case 3:{
			//插入一个线性表
            char name[30];
            getchar();
            printf("请输入增加表的名称:");
            scanf("%s",name);
            int con = AddList(lists, name);
            printf("增加成功！\n");
			getchar();getchar();
			break;
		}
			
		case 4:{
            //删除一个线性表
            char name[30];
            getchar();
            printf("请输入删除表的文件名:");
            scanf("%s",name);
            int con = RemoveList(lists, name);
            printf("删除成功！\n");
			getchar();getchar();
			break;
		}
        case 5:{
			//导入一个线性表
            char name[30];
            getchar();
            printf("请输入导入文件的文件名:");
            scanf("%s",name);getchar();
            AddList(lists, name);
            int con = LoadList(lists.elem[lists.length-1].L, name);
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
            //保存一个线性表
            char name[30];
            getchar();
            printf("请输入保存的线性表名:");
            scanf("%s",name);getchar();
            int index = LocateList(lists, name);
            int con = SaveList(lists.elem[index-1].L, name);
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
}//end of main()

void menu2(LinkList &L,int op,  char lname[]){
	while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Chain Structure \n");
    printf("                List name : %s\n",lname);
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       7. LocateElem\n");
	printf("    	  2. DestroyList    8. PriorElem\n");
	printf("    	  3. ClearList      9. NextElem \n");
	printf("    	  4. ListEmpty      10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem        12. ListTrabverse\n");
	printf("    	  0. Exit this list\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~12]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 if(InitList(L)==OK) printf("单链表创建成功！\n");
		     else printf("单链表已存在！\n");
		 getchar();getchar();
		 break;
	   case 2:
		 if(OK == DestroyList(L)) printf("线性表销毁成功！\n");
		 	else printf("线性表销毁失败！\n");
		 getchar();getchar();
		 break;
	   case 3:
		 if(OK == ClearList(L)) printf("线性表清空成功！\n");
		  else printf("线性表不存在！\n");     
		 getchar();getchar();
		 break;
	   case 4:{
		 int c = ListEmpty(L);
		 if(c == INFEASIBLE) printf("线性表不存在！\n");
		 else if(c == TRUE) printf("线性表为空！\n");
		 else printf("线性表不为空！\n");
		 getchar();getchar();
		 break;
		 }
	   case 5:
		 {
		 int l = ListLength(L);
		 if(l == INFEASIBLE) printf("线性表不存在！\n");
		 else printf("线性表长度为%d",l);  
		 getchar();getchar();
		 break;}
	   case 6:
		 {
		 int tof;
		 printf("请问您要查询哪个元素：");
		 scanf("%d", &tof);
		 ElemType e;
		 status con = GetElem(L, tof, e);
		 if(con == INFEASIBLE) printf("线性表不存在！\n");
		 else if(con == OK) printf("线性表L的第%d个元素是%d\n", tof, e);
		 else printf("输入不合法！\n");    
		 getchar();getchar();
		 break;}
	   case 7:
		 {
		 ElemType e;
		 printf("请问您要查询元素的值是：");
		 scanf("%d", &e);
		 status con = LocateElem(L, e);
		 if(con == INFEASIBLE) printf("线性表不存在！\n");
		 else if(con == ERROR) printf("该元素不存在！\n");  
		 else printf("该元素在线性表L中序号是%d\n",con);  
		 getchar();getchar();
		 break;}
	   case 8:
		 {
		 ElemType e, pre;
		 printf("请问当前元素的值是：");
		 scanf("%d", &e);
		 status con = PriorElem(L, e, pre);
		 if(INFEASIBLE == con) printf("线性表不存在！\n");
		 else if(con == ERROR) printf("该元素没有前驱！\n");
		 else printf("线性表L中该元素的前驱是%d\n", pre);
		 getchar();getchar();
		 break;}
	   case 9:
		 {  
		 ElemType e, next;
		 printf("请问当前元素的值是：");
		 scanf("%d", &e);
		 status con = NextElem(L, e, next);
		 if(INFEASIBLE == con) printf("线性表不存在！\n");
		 else if(con == ERROR) printf("该元素没有后继！\n");
		 else printf("线性表L中该元素的后继是%d\n", next);
		 getchar();getchar();
		 break;}
	   case 10:
		 {
		 ElemType e;
		 int pos = 0;
		 printf("请问要插入元素的值是(仅支持数字)：");
		 scanf("%d", &e);
		 printf("请问要插入元素的位置是：");
		 scanf("%d",&pos);
		 status con = ListInsert(L, pos, e);
		 if(con == INFEASIBLE) printf("线性表不存在！\n");
		 else if(con == ERROR) printf("插入位置不正确\n");
		 else printf("插入成功\n");
		 getchar();getchar();
		 break;}
	   case 11:
		 {
		 ElemType e;
		 int pos = 0;
		 printf("请问要删除元素的位置是：");
		 scanf("%d",&pos);
		 status con = ListDelete(L, pos, e);
		 if(con == INFEASIBLE) printf("线性表不存在！\n");
		 else if(con == ERROR) printf("输入位置不正确\n");
		 else printf("删除成功, 删除的值为%d\n", e);  
		 getchar();getchar();
		 break;}
	   case 12:    
		 {
            status con =ListTraverse(L);
            if(con == INFEASIBLE){
                printf("线性表不存在！\n");
            }
            else if(con == 0)
             printf("线性表是空表！\n");
            getchar();getchar();
		    break;}
	case 0:
         break;
	}//end of switch
  }//end of while
}

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L != NULL)return INFEASIBLE;
    LinkList n = (LinkList)malloc(sizeof(LNode));
    if( n == NULL)return INFEASIBLE;
    L= n;
    n->next =NULL;
    return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL) return INFEASIBLE;
    LinkList now = L->next;
    free(L);
    L = NULL;
    while(now != NULL){
        LinkList last = now;
        now = now->next;
        free(last); 
    }
    return OK;
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL)return INFEASIBLE;
    LinkList now = L->next;
    L->next = NULL;
    while(now!=NULL){
        LinkList last = now;
        now = now->next;
        free(last);
    }
    return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)return INFEASIBLE;
    if(L->next == NULL)return TRUE;
    return FALSE;
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L == NULL) return INFEASIBLE;
    int length = 0;
    LinkList now = L->next;
    while(now != NULL){
        now = now->next;
        length++;
    }
    return length;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(i<1)return ERROR;
    if(L == NULL) return INFEASIBLE;
    LinkList now = L->next;
    int n = 0;
    while(now != NULL){
        n++;
        if(n == i){
            e = now ->data;
            return OK; 
        }
        now =now->next;
    }
    return ERROR;
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L == NULL) return INFEASIBLE;
    LinkList now = L->next;
    int i = 0;
    while(now != NULL){
        i++;
        if(now->data == e){
            return i; 
        }
        now =now->next;
    }
    return ERROR;
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL) return INFEASIBLE;
    LinkList now = L->next;
    LinkList last;
    int n = 0;
    while(now != NULL){
        n++;
        if(now->data == e){
            if(n == 1){
                return ERROR;
            }
            pre = last->data;
            return OK;
        }
        last = now;
        now =now->next;
    }
    return ERROR;
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL) return INFEASIBLE;
    LinkList now = L->next;
    int n = 0;
    while(now != NULL){
        n++;
        if(now->data == e){
            if(now->next == NULL){
                return ERROR;
            }
            next = now->next->data;
            return OK;
        }
        now =now->next;
    }
    return ERROR;
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(i<1)return ERROR;
    if(L == NULL) return INFEASIBLE;
    LinkList now = L;
    int x;
    for(x= 1 ; (x<i && now!=NULL); now=now->next,x++);
    if(i==1)now = L;
    if( x == i && now == NULL){
        return ERROR;
    }
    LinkList New = (LinkList)malloc(sizeof(LNode));
    if(New == NULL) return OVERFLOW;
    New->data = e;
    New->next = now->next;
    now->next = New;
    return OK;
    /********** End **********/
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    int length = ListLength(L);
    
    if(L == NULL) return INFEASIBLE;
    if( i<=0 || i>length)return ERROR;
    LinkList pre = L;
    int x;
    for(x= 1 ; (x<i && pre!=NULL); pre=pre->next,x++);
    if(i==1)pre = L;
    if( x == i && pre == NULL){
        return ERROR;
    }
    LinkList now = pre ->next;
    pre->next = now ->next;
    e = now->data;
    free(now);
    return OK;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL) return INFEASIBLE;
    LinkList now = L->next;
    int i = 0;
    printf("\n-----------all elements -----------------------\n");
    printf("%4s %16s\n","元素序号", "元素值");
    while(now != NULL){
        printf("%4d %16d\n",1+i, now->data);
        i++;
        now = now->next;
    }
    printf("\n------------------ end ------------------------\n");
    return i;
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL)return INFEASIBLE;
    FILE* fp = fopen(FileName,"w");
    LinkList now = L->next;
    while(now != NULL){
        fprintf(fp, "%d\n",now->data);
        now = now->next;
    }
    fclose(fp);
    return OK;
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if(L != NULL)return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    L->next =NULL;
    LinkList now = L;
    FILE* fp = fopen(FileName,"r");
    ElemType e;
    while(fscanf(fp, "%d", &e) != EOF){
        LinkList New = (LinkList)malloc(sizeof(LNode));
        New->data = e;
        New->next =NULL;
        now->next = New;
        now=New;
    }
    fclose(fp);
    return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int i = Lists.length++;
    int j=0;
    while(ListName[j]!='\0'){
        Lists.elem[i].name[j]=ListName[j];
        j++;
    }
    Lists.elem[i].name[j]=ListName[j];
    Lists.elem[i].L = NULL;
    Lists.elem[i].L = 0;
	return 0;
}

status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    
    int ok = 0;
    for(int i=0; i<Lists.length; i++){
        int tag = 1;
        int c=0;
        while(ListName[c] != '\0'){
            if(Lists.elem[i].name[c]  != ListName[c]){
                tag = 0;
                break;
            }
            c++;
        }

        if(tag){
            DestroyList(Lists.elem[c].L);
            Lists.length--;
            if( i == Lists.length){
                break;
            }
            for(int j = i; j<Lists.length;j++){
                Lists.elem[j] =Lists.elem[j+1];
            }
            ok =1;
            break;
        }
    }
    if(ok){
        return OK;
    }
    return ERROR;
}


int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    
    int ok=0;
    int i=0;
    for(; i<Lists.length; i++){
        int tag = 1;
        int c=0;
        while(ListName[c] != '\0'){
            if(Lists.elem[i].name[c]  != ListName[c]){
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

status LISTSTrabverse(LISTS &Lists){//遍历线性表集合，并打印
	int i;
	printf("\n----------------- all lists -------------------\n");
	for(i=0;i<Lists.length;i++) printf("%4d:   %s \n", i+1, Lists.elem[i].name);
	printf("\n------------------ end ------------------------\n");
	return Lists.length;
}