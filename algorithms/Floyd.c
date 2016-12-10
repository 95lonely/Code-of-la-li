#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INF 100000
#define MAXN 4500

FILE *ifp,*dfp,*tfp;
int n,m;//顶点数和边数 
int Edge[MAXN][MAXN];
int A[MAXN][MAXN],path[MAXN][MAXN];
void Floyd(){
	int i,j,k;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			A[i][j]=Edge[i][j];
			if(i != j && A[i][j] < INF)
			path[i][j]=i;
			else path[i][j]=-1;
		}
	}
			
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(k==i||k==j)
				continue;
				if(A[i][k]+A[k][j]<A[i][j]){
					A[i][j]=A[i][k]+A[k][j];
					path[i][j]=path[k][j];
				}
			}
		}
	}
}

int main()
{	
	clock_t s;
	clock_t f;
	clock_t t;
	
	printf("请输入文件名：");
	char filename[255];
	scanf("%s",filename);
	ifp=fopen(filename,"r");
	dfp=fopen("output2.txt","w");
	tfp=fopen("time2.txt","w");
	if(ifp==NULL){
		printf("打开文件失败\n");
		system("pause");
		return 0;
	} 	
	
	int i,j,h;
	int u,v,w;
	fscanf(ifp,"%d %d",&n,&m);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		Edge[i][j]=INF;
		
	}
	for(i=0;i<n;i++)
	Edge[i][i]=0;
	for(h=1;h<=m;h++){
		fscanf(ifp,"%d %d %d",&u,&v,&w);
		Edge[u][v]=w;
	
	}
	s = clock();
	Floyd();
	f = clock();	
	t=f-s;	
	fprintf(tfp,"顶点数：%d\t 算法运行时间：%f\n",n,(double)t/CLOCKS_PER_SEC);
	int shortest[MAXN];

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)
			continue;
			//printf("%d->%d\t%d\t",i,j,A[i][j]);
			if(A[i][j]!=INF){
			fprintf(dfp,"起点：%d\t终点：%d\t长度：%d",i,j,A[i][j]);
			memset(shortest,0,sizeof(shortest));
			int k=0;
			shortest[k]=j;
			while((path[i][shortest[k]]!=i)&&path[i][shortest[k]]>=0){
				k++;
				shortest[k]=path[i][shortest[k-1]];
			}
			k++;
			shortest[k]=i;
			int l;
			fprintf(dfp,"\n最短路径：{");
			for(l=k;l>0;l--)
				fprintf(dfp,"%d->",shortest[l]);
			fprintf(dfp,"%d}\n",shortest[0]);
			}
			else continue;
		}
	}
	fclose(ifp);
	fclose(dfp);
	fclose(tfp);
	system("pause");
	return 0;	
}
