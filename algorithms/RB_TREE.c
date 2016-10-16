#include "includex.h"

#define RED		0
#define BLACK	1
#define NUM		10

typedef struct RB_TREENODE{
	int key;
	int color;
	struct RB_TREENODE *p;
	struct RB_TREENODE *l;
	struct RB_TREENODE *r;
}RB_TREENODE;
RB_TREENODE *root=NULL;
//RB_TREENODE *leaf;//叶子，也称哨兵结点
//插入操作，包含重新着色操作，实际上除了多了倒数第二行对重新操作的调用以外和普通二叉搜索树的插入操作没有什么区别-_-|||
//左旋操作，进行左旋的是x与其右孩子y
void LEFT_ROTATE(RB_TREENODE *x){
	RB_TREENODE *y;
	y=x->r;
	x->r=y->l;
	if(y->l!=NULL)
		y->l->p=x;
	y->p=x->p;
	if(x->p==NULL)
		root=y;
	else if(x==x->p->l)
		x->p->l=y;
	else x->p->r=y;
	y->l=x;
	x->p=y;
}
//右旋操作
void RIGHT_ROTATE(RB_TREENODE *x){
	RB_TREENODE *y;
	y=x->l;
	x->l=y->r;
	if(y->r!=NULL)
		y->r->p=x;
	y->p=x->p;
	if(x->p==NULL)
		root=y;
	else if(x==x->p->r)
		x->p->r=y;
	else x->p->l=y;
	y->r=x;
	x->p=y;
}
//重新着色，包括左旋和右旋操作
void RB_INSERT_FIXUP(RB_TREENODE *z){
	RB_TREENODE *y,*pe,*gp;
	while((pe=z->p)!=NULL&&pe->color==RED){
		gp=pe->p;
		if(pe!=NULL&&pe==gp->l){
			y=gp->r;
			if(y!=NULL&&y->color==RED){
				pe->color=BLACK;
				y->color=BLACK;
				gp->color=RED;
				z=gp;
			}
			else{
				if(z==pe->r){
				z=pe;
				LEFT_ROTATE(z);
				pe=z->p;
			}
			pe->color=BLACK;
			pe->color=RED;
			RIGHT_ROTATE(gp);
			}
		}
		else{
			y=gp->l;
			if(y!=NULL&&y->color==RED){
				pe->color=BLACK;
				y->color=BLACK;
				gp->color=RED;
				z=gp;
			}
			else{ 
				if(z==pe->l){
				z=pe;
				RIGHT_ROTATE(z);
				pe=z->p;
			}
			pe->color=BLACK;
			gp->color=RED;
			LEFT_ROTATE(gp);
			}
		}
	}
	root->color=BLACK;
}
//中序遍历RB树
void INORDER_TREE_WALK(RB_TREENODE *t){		
	if(t!=NULL){
		INORDER_TREE_WALK(t->l);
		printf("%d ",t->key);
		INORDER_TREE_WALK(t->r);
	}
}

//插入操作，包含重新着色操作，实际上除了多了倒数第二行对重新操作的调用以外和普通二叉搜索树的插入操作没有什么区别-_-|||
void RB_INSERT(int key){
	RB_TREENODE *t,*x,*y;
	t=(RB_TREENODE *)malloc(sizeof(RB_TREENODE));
	if(t==NULL){
		printf("malloc failed!");
		return ;
	}
	t->key=key;
	t->color=RED;
	t->p=NULL;
	t->l=NULL;
	t->r=NULL;

	x=root;
	y=NULL;
	while(x!=NULL){
		y=x;
		if(t->key<x->key)
			x=x->l;
		else x=x->r;
	}
	t->p=y;
	if(y==NULL)
		root=t;
	else if(t->key<y->key)
		y->l=t;
	else y->r=t;
	RB_INSERT_FIXUP(t);
}

int main(){
	int i;
	int key[NUM];
	printf("input numbers :");
	for(i=0;i<NUM;i++){
		scanf("%d",&key[i]);
		printf("%d ",key[i]);
	}
	for(i=0;i<NUM;i++)
		RB_INSERT(key[i]);
	printf("\nresult is :");
	INORDER_TREE_WALK(root);
	
}
