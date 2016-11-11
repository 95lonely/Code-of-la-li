#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RED		0
#define BLACK		1
//#define NUM		10
#define MAX		150
typedef struct RB_TREENODE{		//红黑树结点结构
	int key;
	int color;
	int size;
	struct RB_TREENODE *p;
	struct RB_TREENODE *l;
	struct RB_TREENODE *r;
}RB_TREENODE;
typedef struct RBTREE{		
    RB_TREENODE *root;
    RB_TREENODE *til;
} RBTREE;
void rand_num(int num[],FILE *datain)		//随机生成1~150之间的随机数 
{
	int a[MAX];//定义一个数组，下标a[0]~a[N-1]  
    int n=0;  
    int i=0,j=0;  
    int temp;  
  
    a[0]=rand()%MAX+1;  
    for(i=0;i<MAX;i++){  
        temp=rand()%MAX+1;  
        for(j=0;j<i;j++){ //判断重复  
           if(temp==a[j]){  
                i--;  
                break;  
            }  
            else{  
                a[i]=temp;  
            }  
        }  
    }
	for(i=0;i<MAX;i++){
		num[i]=a[i];
		fprintf(datain,"%d\n",num[i]);
	}
}

//插入操作，包含重新着色操作，实际上除了多了倒数第二行对重新操作的调用以外和普通二叉搜索树的插入操作没有什么区别-_-|||
//左旋操作，进行左旋的是x与其右孩子y
void LEFT_ROTATE(RBTREE *T,RB_TREENODE *x){
	if(x->r == T->til)
	{
		printf("x have not a right child can not be right-rotate\n");
		exit(1);
	}
	RB_TREENODE *y;
	y=x->r;
	x->r=y->l;
	if(y->l!=T->til)
		y->l->p=x;
	y->p=x->p;
	if(x->p==T->til)
		T->root=y;
	else if(x==x->p->l)
		x->p->l=y;
	else x->p->r=y;
	y->l=x;
	x->p=y;
}
//右旋操作
void RIGHT_ROTATE(RBTREE *T,RB_TREENODE *x){
	if(x->l == T->til)
	{
		printf("x have not a left child can not be right-rotate\n");
		exit(1);
	}
	RB_TREENODE *y;
	y=x->l;
	x->l=y->r;
	if(y->r!=T->til)
		y->r->p=x;
	y->p=x->p;
	if(x->p==T->til)
		T->root=y;
	else if(x==x->p->l)
		x->p->l=y;
	else x->p->r=y;
	y->r=x;
	x->p=y;
}
//重新着色，包括左旋和右旋操作
RB_TREENODE *RB_INSERT_FIXUP(RBTREE *T,RB_TREENODE *z){
	RB_TREENODE *y;
	while(z->p->color==RED){
		if(z->p==z->p->p->l){
			y=z->p->p->r;
			if(y->color==RED){
				z->p->color=BLACK;
				y->color=BLACK;
				z->p->p->color=RED;
				z=z->p->p;
			}
			else{
				if(z==z->p->r){
				z=z->p;
				LEFT_ROTATE(T,z);
			}
			z->p->color=BLACK;
			z->p->p->color=RED;
			RIGHT_ROTATE(T,z->p->p);
			}
		}
		else{
			y=z->p->p->l;
			if(y->color==RED){
				z->p->color=BLACK;
				y->color=BLACK;
				z->p->p->color=RED;
				z=z->p->p;
			}
			else{ 
				if(z==z->p->l){
				z=z->p;
				RIGHT_ROTATE(T,z);
				}
			z->p->color=BLACK;
			z->p->p->color=RED;
			LEFT_ROTATE(T,z->p->p);
			}
		}
	}
	T->root->color=BLACK;
	return T->root;
}
//中序遍历RB树
void INORDER_TREE_WALK(RBTREE *T,RB_TREENODE *t,FILE *fp){		
	if(t!=T->til){
		INORDER_TREE_WALK(T,t->l,fp);
		fprintf(fp,"key = %d,color = %d(0为红，1为黑),size = %d,parent = %d,leftchlid = %d,rightchild = %d\n",t->key,t->color,t->size,t->p->key,t->l->key,t->r->key);
		INORDER_TREE_WALK(T,t->r,fp);
	}
}
//前序遍历RB树
void PREORDER_TREE_WALK(RBTREE *T,RB_TREENODE *t,FILE *fp){		
	if(t!=T->til){
		fprintf(fp,"key = %d,color = %d(0为红，1为黑),size = %d,parent = %d,leftchlid = %d,rightchild = %d\n",t->key,t->color,t->size,t->p->key,t->l->key,t->r->key);
		PREORDER_TREE_WALK(T,t->l,fp);
		PREORDER_TREE_WALK(T,t->r,fp);
	}
}
//后序遍历RB树
void POSTORDER_TREE_WALK(RBTREE *T,RB_TREENODE *t,FILE *fp){		
	if(t!=T->til){
		POSTORDER_TREE_WALK(T,t->l,fp);
		POSTORDER_TREE_WALK(T,t->r,fp);
		fprintf(fp,"key = %d,color = %d(0为红，1为黑),size = %d,parent = %d,leftchlid = %d,rightchild = %d\n",t->key,t->color,t->size,t->p->key,t->l->key,t->r->key);
	}
}
//插入操作，包含重新着色操作，实际上除了多了倒数第二行对重新操作的调用以外和普通二叉搜索树的插入操作没有什么区别-_-|||
RB_TREENODE *RB_INSERT(RBTREE *T,int key){
	RB_TREENODE *t,*x,*y;

	t=(RB_TREENODE *)malloc(sizeof(RB_TREENODE));
	if(t==T->til){
		printf("malloc failed!");
		
	}
	t->size=0;
	t->key=key;
	t->color=RED;
	x=T->root;
	y=T->til;
	while(x!=T->til){
		y=x;
		if(t->key<x->key)
			x=x->l;
		else x=x->r;
	}
	t->p=y;
	if(y==T->til)
		T->root=t;
	else if(t->key<y->key)
		y->l=t;
	else y->r=t;
	t->l=T->til;
	t->r=T->til;
	T->root=RB_INSERT_FIXUP(T,t);
	return T->root;
}
//寻找最小元素结点
RB_TREENODE *MINIMUM(RBTREE *T,RB_TREENODE *t){
	while(t->l!=T->til)
		t=t->l;
	return t;
}
//删除操作，包括移接，修复和删除红黑树性质的操作
void RB_TRANSPLANT(RBTREE *T,RB_TREENODE *u,RB_TREENODE *v){
	if(u->p==T->til)
		T->root=v;
	else if(u==u->p->l)
		u->p->l=v;
	else u->p->r=v;
	if(v!=T->til)		//书上这里是无条件执行下一句，然而v=T->til会报错
		v->p=u->p;
}
//红黑树性质修复操作
void RB_DELETE_FIXUP(RBTREE *T,RB_TREENODE *x){
	RB_TREENODE *w;				
	while(x!=T->root&&x->color==BLACK){
		if(x==x->p->l){
			w=x->p->r;
			if(w->color==RED){
				w->color=BLACK;
				x->p->color=RED;
				LEFT_ROTATE(T,x->p);
				w=x->p->r;
			}
			else if(w->l->color==BLACK){
				w->l->color=BLACK;
				w->color=RED;
				RIGHT_ROTATE(T,w);
				w=x->p->r;
			}
			else{
				w->color=x->p->color;
				x->p->color=BLACK;
				w->r->color=BLACK;
				LEFT_ROTATE(T,x->p);
				x=T->root;
			}
		}
		else{
			w=x->p->l;
			if(w->color==RED){
				w->color=BLACK;
				x->p->color=RED;
				LEFT_ROTATE(T,x->p);
				w=x->p->l;
			}
			else if(w->r->color==BLACK){
				w->r->color=BLACK;
				w->color=RED;
				RIGHT_ROTATE(T,w);
				w=x->p->l;
			}
			else{
				w->color=x->p->color;
				x->p->color=BLACK;
				w->l->color=BLACK;
				LEFT_ROTATE(T,x->p);
				x=T->root;
			}
		}
	}
	x->color=BLACK;
}
//删除操作
void RB_DELETE(RBTREE *T,RB_TREENODE *z){
	RB_TREENODE *x;
	RB_TREENODE *y=z;
	RB_TREENODE *y0=y;
	y0->color=y->color;
	if(z->l==T->til){
		x=z->r;
		RB_TRANSPLANT(T,z,z->r);
	}
	else if(z->r==T->til){
		x=z->l;
		RB_TRANSPLANT(T,z,z->l);
	}
	else{
		y=MINIMUM(T,z->r);
		y0->color=y->color;
		x=y->r;
		if(y->p==z)
			x->p=y;
		else{
			RB_TRANSPLANT(T,y,y->r);
			y->r=z->r;
			y->r->p=y;
		}
		RB_TRANSPLANT(T,z,y);
		y->l=z->l;
		y->l->p=y;
		y->color=z->color;
	}
	if(y0->color==BLACK&&x!=T->til)	//这里比算法书上多了判断x不为T->til的条件，如果x为T->til会报错！！
		RB_DELETE_FIXUP(T,x);
}
RB_TREENODE *OS_SELECT(RB_TREENODE *x,int i){
	int r;
	r=x->l->size+1;
	if(i==r)
		return x;
	else if(i<r)
		return OS_SELECT(x->l,i);
	else return OS_SELECT(x->r,i-r);
}

void SizeAdjust(RBTREE *T,RB_TREENODE *t){  
	if(t!=T->til){
	SizeAdjust(T,t->l);  
	SizeAdjust(T,t->r);  
	t->size=t->l->size+t->r->size+1;  
    }  
}
	//所有操作都并不会改变原来数组中数字的顺序！！所以按数组输出的顺序仍是未排序的，只有遍历操作才能输出已经排序好的结果！！
int main(){
	int i,j,k;
	int n;
	int *num;
	FILE *datain;
   	datain = fopen("input.txt","w");  //随机生成数据并且将它放如input.txt中
   	if(datain==NULL)
		printf("inputtxt open failed!");
   	num = (int *)malloc(sizeof(int) * MAX);
   	if(num==NULL)
   		printf("malloc num failed!");
   	char size[5];
	srand((int)time(0));
   	rand_num(num,datain);
	fclose(datain);    //以上是输入

	for(k=1 ; k < 5; k++){
		n = 20*k;
		clock_t start,finish;
		int duration;
		int *key;    //新建一个key数组放置排序后的 
		key = (int *)malloc( sizeof(int) * n);
		
		for(i=0;i<n;i++)        
	    	key[i] = num[i];
		
		printf("node size %d is ready~\n",n);
		
		RBTREE *T;
		T=(RBTREE *)malloc(sizeof(RBTREE));
		if(T==NULL)
			printf("T malloc failed!");
		T->til=(RB_TREENODE *)malloc(sizeof(RB_TREENODE));
		if(T->til==NULL)
			printf("root malloc failed!");
		T->til->size=0;
		T->til->key=0;
		T->til->color=BLACK;
		T->til->p=NULL;
		T->til->l=NULL;
		T->til->r=NULL;
		T->root=T->til;

		char route[100] = "/home/lila/workspace/code/Code-of-la-li/algorithms/test/";
		sprintf(size,"%d",n);
		strcat(route,size);
		char timeout[20] = "time1.txt";
		strcat(route,timeout);
		FILE *ftimeout = fopen(route,"w"); 
		if(ftimeout==NULL)
			printf("inorder_out open failed!");
		start=clock();
		for(j=0;j<n;j++){
			T->root=RB_INSERT(T,key[j]);
			finish=clock();
			if((j+1)%10==0){
				duration = finish - start;
				fprintf(ftimeout,"number is %d, time is %d\n",j+1,duration);
			}
		}
		
		char route1[100] = "/home/lila/workspace/code/Code-of-la-li/algorithms/test/";	//中序遍历
		strcat(route1,size);
		char name1[20] = "inorder.txt";
		strcat(route1,name1);
		FILE *inorder_out = fopen(route1,"w");
		if(inorder_out==NULL)
			printf("inorder_out open failed!");
		SizeAdjust(T,T->root);
		INORDER_TREE_WALK(T,T->root,inorder_out);
		fclose(inorder_out);
		
		char route2[100] = "/home/lila/workspace/code/Code-of-la-li/algorithms/test/";	//前序遍历
		strcat(route2,size);
		char name2[20] = "preorder.txt";
		strcat(route2,name2);
		FILE *preorder_out = fopen(route2,"w");
		if(preorder_out==NULL)
			printf("preorder_out open failed!");
		PREORDER_TREE_WALK(T,T->root,preorder_out);
		fclose(preorder_out);

		char route3[100] = "/home/lila/workspace/code/Code-of-la-li/algorithms/test/";	//后序遍历
		strcat(route3,size);
		char name3[20] = "postrder.txt";
		strcat(route3,name3);
		FILE *postorder_out = fopen(route3,"w");
		if(postorder_out==NULL)
			printf("postorder_out open failed!");
		POSTORDER_TREE_WALK(T,T->root,postorder_out);
		fclose(postorder_out);
		fclose(ftimeout);

		RB_TREENODE *del1,*del2;	//两个待删除节点
		del1=OS_SELECT(T->root,n/4);	//输出第一个被删除结点的信息
		char route4[100] = "/home/lila/workspace/code/Code-of-la-li/algorithms/test/";	
		strcat(route4,size);
		char delete[20] = "delete_data.txt";
		strcat(route4,delete);
		FILE *del = fopen(route4,"w");
		if(del==NULL)
			printf("del open failed!");
		fprintf(del,"Info of the n/4 less node:key = %d,color = %d(0为红，1为黑),size = %d,parent = %d,leftchlid = %d,rightchild = %d\n",del1->key,del1->color,del1->size,del1->p->key,del1->l->key,del1->r->key);
			
		start=clock();	//对第一个被删除的结点计时
		RB_DELETE(T,del1);
		finish=clock();
		duration=finish-start;
		char route5[100] = "/home/lila/workspace/code/Code-of-la-li/algorithms/test/";	
		strcat(route5,size);
		char timeout1[20] = "time2.txt";
		strcat(route5,timeout1);
		FILE *ftimeout2 = fopen(route5,"w");
		if(ftimeout2==NULL)
			printf("timeout open failed!");
		fprintf(ftimeout2,"删除第n/4小的结点耗时：%d\n",duration);
		
		del2=OS_SELECT(T->root,n/2);	//输出第二个被删除结点的信息
		fprintf(del,"Info of the n/2 less node :key = %d,color = %d(0为红，1为黑),size = %d,parent = %d,leftchlid = %d,rightchild = %d\n",del2->key,del2->color,del2->size,del2->p->key,del2->l->key,del2->r->key);
		
		start=clock();	//对第二个被删除的结点计时
		RB_DELETE(T,del2);
		finish=clock();
		duration=finish-start;
		fprintf(ftimeout2,"删除第n/2小的结点耗时：%d\n",duration);
	
		fclose(del);
		fclose(ftimeout2);
		
		char route6[100] = "/home/lila/workspace/code/Code-of-la-li/algorithms/test/";	//删除两个结点后的中序遍历
		strcat(route6,size);
		char delout[20] = "delete_inorder.txt";
		strcat(route6,delout);
		FILE *delete_out = fopen(route6,"w");
		if(delete_out==NULL)
			printf("inorder_out open failed!");
		SizeAdjust(T,T->root);
		INORDER_TREE_WALK(T,T->root,delete_out);
		fclose(delete_out);
		
		free(key);
		free(T);
		free(T->til);
	}
	free(num);
	//system("pause");
	return 0;
}

