#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BS_TREE.h"
#define NUM 10
//二叉搜索树数据结构
typedef struct BS_TREENODE{
	int key;					//关键字
	struct BS_TREENODE *p;		//双亲
	struct BS_TREENODE *l;		//左孩子
	struct BS_TREENODE *r;		//右孩子
}BS_TREENODE;

BS_TREENODE *root=NULL;
//中序遍历
void INORDER_TREE_WALK(BS_TREENODE *t){		
	if(t!=NULL){
		INORDER_TREE_WALK(t->l);
		printf("%d ",t->key);
		INORDER_TREE_WALK(t->r);
	}
}
//查找（递归）
BS_TREENODE *SEARCH(int key){
	BS_TREENODE *x;
	x=root;
	if(x==NULL|key==x->key)
		return x;
	if(key<x->key)
		return SEARCH(x->l,key);
	else return SEARCH(x->l,key);
}
//查找（迭代，效率高）
BS_TREENODE *search(int key){
	BS_TREENODE *x;
	x=root;
	while((x!=NULL)&&(key!=(x->key))){
			if(key<x->key)
				x=x->l;
			else x=x->r;
	}
	return x;
}
//寻找最大元素节点
BS_TREENODE *MAXIMUM(BS_TREENODE *t){
	while(t->r!=NULL)
		t=t->r;
	return t;
}
//寻找最小元素结点
BS_TREENODE *MINIMUM(BS_TREENODE *t){
	while(t->l!=NULL)
		t=t->l;
	return t;
}
//寻找后继节点
BS_TREENODE *SUCCESSOR(BS_TREENODE *t){
	BS_TREENODE *x;
	x=t;
	if(x->r!=NULL)
		return MAXIMUM(x);
	BS_TREENODE *y=x->p;
	while((y!=NULL)&&(x==y->r)){
		x=y;
		y=y->p;
	}
	return y;
}
//寻找前驱结点
BS_TREENODE *PREDECESSOR(BS_TREENODE *t){
	BS_TREENODE *x;
	x=t;
	if(x->l!=NULL)
		return MINIMUM(x);
	BS_TREENODE *y=x->p;
	while((y!=NULL)&&(x==y->l)){
		x=y;
		y=y->p;
	}
	return y;
}
//插入结点
void TREE_INSERT(int key){
	BS_TREENODE *t;
	t=(BS_TREENODE *)malloc(sizeof(BS_TREENODE));
	if(t==NULL){
		printf("malloc failed!");
		return ;
	}
	t->key=key;
	t->p=NULL;
	t->l=NULL;
	t->r=NULL;

	BS_TREENODE *y=NULL;
	BS_TREENODE *x;
	x=root;
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
}
//删除结点：包含两个操作，TRASPLANT：将一个结点代替另一个接到它的双亲结点下；TREE_DELETE：删除结点操作
//移接操作,将v代替u接在它的双亲下
void TRANSPLANT(BS_TREENODE *u,BS_TREENODE *v){
	if(u->p==NULL)
		root=v;
	else if(u==u->p->l)
		u->p->l=v;
	else u->p->r=v;
	if(v!=NULL)
		v->p=u->p;
}
//删除操作
void TREE_DELETE(BS_TREENODE *z){
	BS_TREENODE *y;
	if(z->l==NULL)
		TRANSPLANT(z,z->r);
	else if(z->r==NULL)
		TRANSPLANT(z,z->l);
	else{
		y=MINIMUM(z->r);
		if(y->p!=z){
			TRANSPLANT(y,y->r);
			y->r=z->r;
			y->r->p=y;
		}
		else TRANSPLANT(z,y);
		y->l=z->l;
		y->l->p=y;
	}
}

int main(){
	int i;
	int key[NUM];
	BS_TREENODE *k,*m,*n,*max,*min;
	printf("input numbers :");
	for(i=0;i<NUM;i++){
		scanf("%d",&key[i]);
		printf("%d ",key[i]);
	}
//插入结点，建立二叉搜索树	
	for(i=0;i<NUM;i++)
		TREE_INSERT(key[i]);
	printf("\nreslut is :");
//遍历树	
	INORDER_TREE_WALK(root);
//查找关键字为60的结点，指向该结点的指针为k
	k=search(60);
	printf("\nsearch result is: %d",k->key);
//寻找60的前驱
	m=PREDECESSOR(k);
	printf("\nThe predecessor of 60 is %d",m->key);
//寻找60的后继
	n=SUCCESSOR(k);
	printf("\nThe successor of 60 is %d",n->key);
//寻找整个树最大结点
	max=MAXIMUM(root);
	printf("\nresult is %d",max->key);
//寻找整个树最小结点
	min=MINIMUM(root);
	printf("\nresult is %d",min->key);
//删除60结点
	TREE_DELETE(k);
	printf("\nThe result after delete is ");
	INORDER_TREE_WALK(root);
}			
