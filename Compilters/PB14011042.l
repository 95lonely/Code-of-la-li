%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define string 258
//#define num 259
#define creator 260
#define graph 261
#define node 262
#define id 263
#define number 264
#define label 265
#define edge 266
#define Source 267
#define Target 268
#define Value 269
#define Endinput 0

int syntax_error = 0;
int lookhead;
int num_lex_val;
char str_lex_val[64];
int lines=0;
typedef struct NODE{
	int nid;
	char nlabel[65];
	struct NODE *next;
}NODE;
NODE *head=NULL;

%}

digit	[0-9]
num		{digit}+
str		\"(\\.|[^\\"])*\"

%%
[ \t]+	{}
{str}	{strcpy(str_lex_val,yytext);return string;}
{num}	{num_lex_val=atoi(yytext);return number;}
"Creator"	{return creator;}
"graph" {return graph;}
"node"	{return node;}
"id"	{return id;}
"label"	{return label;}
"edge"	{return edge;}
"source" {return Source;}
"target" {return Target;}
"value" {return Value;}
\n		{lines++;}
.		{return yytext[0];}
%%

/*LL(1)Grammar for gml file
GML		-> Author Graph
Author	-> creator string
Graph	-> graph '[' Nodes Edges ']'
Node	-> node '[' id number label string ']'
Nodes	-> Node MoreNodes
MoreNodes -> Node MoreNodes
MoreNodes ->//EMPTY PRODUCTION

Edge	->edge '[' source number target number value ']'
Edges	->Edge MoreEdges
MoreEdges ->Edge MoreEdges
MoreEdges ->
*/



int next_token(){
    return yylex();
}

void error(char * msg){
	syntax_error = 1; // set error flag
	printf("%s",msg);
}

void match( int t ){    
    if ( lookhead == t ) { 
	    lookhead = next_token(); 
	}
	else{
		printf("token %d needed at line %d.\n",t,lines);
		error("\ninvalid input\n");  /* 否则，语法错误*/
		  }
}
void skip(){
	while ( lookhead != '\n' )  lookhead=next_token();
	syntax_error = 0 ; // clear error flag
			/* pass all input untill '\n' */
}
                            
void insertNode(int gid,char *glabel){
	NODE *nptr;
	nptr = (NODE *)malloc(sizeof(NODE));
	nptr->nid=gid;
	strcpy(nptr->nlabel,glabel);
	nptr->next = head;
	head = nptr;
} 

NODE *searchNode(int gid){	
	int i,n;
	NODE *p;
	p=head;
	n=head->nid;
	for(i=0;i<n-gid;i++)
		p=p->next;
	return p;
}

void Edge(){
	if(syntax_error)
		return;
	match(edge);
//	match('\n');
	match('[');
//	match('\n');
	int sid,tid,val;
	NODE *sptr,*tptr;
	if(lookhead == Source){
	match(Source);
	match(number);
	sid=num_lex_val;
	match(Target);
	match(number);
	tid=num_lex_val;
	match(Value);
	match(number);
	val=num_lex_val;
	match(']');
	sptr=searchNode(sid);
	tptr=searchNode(tid);
	if(sptr == NULL||tptr == NULL)
		error("Bad node!");
	printf("Source: %s ----> Target: %s   Value: %d\n",sptr->nlabel,tptr->nlabel,val);
	}
}

void MoreEdges(){
	if(lookhead==edge){
	Edge();
	MoreEdges();
	}
	else return ;
}

void Edges(){	
	if(lookhead==edge)
	Edge();
	MoreEdges();
}

void Node(){
	if(syntax_error)
		return;

		match(node);

	match('[');

	int gid;
	char *glabel;
	if(lookhead == id){
		match(id);
		match(number);
		gid=num_lex_val;

		match(label);
		match(string);
		glabel=str_lex_val;
		insertNode(gid,glabel);
		match(']');

	}
	else return ;
	
}

void MoreNodes(){
	if(lookhead==node){
	Node();
	MoreNodes();
	}
	else return ;
}

void Nodes(){
	if(lookhead==node)
	Node();
	MoreNodes();
}

void Graph(){
	if(syntax_error)
		return ;	
	if(lookhead =='['){
		match('[');

		Nodes();
		Edges();
	}
	if(lookhead ==']'){
		match(']');
		return ;
	}
}

void Author(){
	if(syntax_error)
		return ;
	while(lookhead!= graph)
		lookhead=next_token();
	return ;
}
void GML(){
	if ( lookhead==Endinput ) {
		printf("\n\nFinished!!!\n");
		return;
	}

	Author();
	match(graph);
	Graph();
	if ( syntax_error ) 
		skip();

}	
int main(){
	lookhead = next_token();
	GML();
	return 0;
}
int yywrap(){
	return 1;
}







