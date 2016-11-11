#include "includex.h"

#define RED		0
#define BLACK	1
#define NUM		100

typedef struct RB_TREENODE{
	int key;
	int color;
	struct RB_TREENODE *p;
	struct RB_TREENODE *l;
	struct RB_TREENODE *r;
}RB_TREENODE;
RB_TREENODE *root=NULL;
//RB_TREENODE *leaf;//叶子，也称哨兵结点
//查找操作
RB_TREENODE *search(int key){
	RB_TREENODE *x;
	x=root;
	while(x!=NULL&&(key!=x->key)){
		if(key<x->key)
			x=x->l;
		else x=x->r;
	}
	return x;
}
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
//寻找最小元素结点
RB_TREENODE *MINIMUM(RB_TREENODE *t){
	while(t->l!=NULL)
		t=t->l;
	return t;
}
//删除操作，包括移接，修复和删除红黑树性质的操作
void RB_TRANSPLANT(RB_TREENODE *u,RB_TREENODE *v){
	if(u->p==NULL)
		root=v;
	else if(u==u->p->l)
		u->p->l=v;
	else u->p->r=v;
	if(v!=NULL)		//书上这里是无条件执行下一句，然而v=NULL会报错
		v->p=u->p;
}
//红黑树性质修复操作
void RB_DELETE_FIXUP(RB_TREENODE *x){
	RB_TREENODE *w;				
	while(x!=root&&x->color==BLACK){
		if(x==x->p->l){
			w=x->p->r;
			if(w->color==RED){
				w->color=BLACK;
				x->p->color=RED;
				LEFT_ROTATE(x->p);
				w=x->p->r;
			}
			else if(w->l->color==BLACK){
				w->l->color=BLACK;
				w->color=RED;
				RIGHT_ROTATE(w);
				w=x->p->r;
			}
			else{
				w->color=x->p->color;
				x->p->color=BLACK;
				w->r->color=BLACK;
				LEFT_ROTATE(x->p);
				x=root;
			}
		}
		else{
			w=x->p->l;
			if(w->color==RED){
				w->color=BLACK;
				x->p->color=RED;
				LEFT_ROTATE(x->p);
				w=x->p->l;
			}
			else if(w->r->color==BLACK){
				w->r->color=BLACK;
				w->color=RED;
				RIGHT_ROTATE(w);
				w=x->p->l;
			}
			else{
				w->color=x->p->color;
				x->p->color=BLACK;
				w->l->color=BLACK;
				LEFT_ROTATE(x->p);
				x=root;
			}
		}
	}
	x->color=BLACK;
}
//删除操作
void RB_DELETE(RB_TREENODE *z){
	RB_TREENODE *x;
	RB_TREENODE *y=z;
	RB_TREENODE *y0=y;
	y0->color=y->color;
	if(z->l==NULL){
		x=z->r;
		RB_TRANSPLANT(z,z->r);
	}
	else if(z->r==NULL){
		x=z->l;
		RB_TRANSPLANT(z,z->l);
	}
	else{
		y=MINIMUM(z->r);
		y0->color=y->color;
		x=y->r;
		if(y->p==z)
			x->p=y;
		else{
			RB_TRANSPLANT(y,y->r);
			y->r=z->r;
			y->r->p=y;
		}
		RB_TRANSPLANT(z,y);
		y->l=z->l;
		y->l->p=y;
		y->color=z->color;
	}
	if(y0->color==BLACK&&x!=NULL)	//这里比算法书上多了判断x不为NULL的条件，如果x为NULL会报错！！
		RB_DELETE_FIXUP(x);
}
//所有操作都并不会改变原来数组中数字的顺序！！所以按数组输出的顺序仍是未排序的，只有遍历操作才能输出已经排序好的结果！！
int main(){
	int i;
	int key[NUM];
	RB_TREENODE *x;
	printf("input numbers :");
	for(i=0;i<NUM;i++){
		scanf("%d",&key[i]);
		printf("%d ",key[i]);
	}
	for(i=0;i<NUM;i++)
		RB_INSERT(key[i]);
	printf("\ninsert result is :");
	INORDER_TREE_WALK(root);
	for(i=0;i<NUM;i++)
		printf("\narray is :%d",key[i]);
	x=search(key[6]);
	RB_DELETE(x);
	printf("\ndelete result is :");
	INORDER_TREE_WALK(root);
	return 0;
}
