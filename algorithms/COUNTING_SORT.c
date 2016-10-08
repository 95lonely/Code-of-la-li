#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void COUNTING_SORT(int a[],int b[],int k){
	int c[k];
	int i,j;
	memset(c,0,k*sizeof(int));
	for(j=0;j<10;j++)
		c[a[j]]++;
	for(i=1;i<k;i++)
		c[i]=c[i]+c[i-1];
	for(j=9;j>=0;j--){
		if(c[a[j]]){
		b[c[a[j]]-1]=a[j];			//由于b是从0开始，所以需要c[a[j]]-1,确保下表对齐
		c[a[j]]--;
		}
	}
}

int main(){
	int a[10];
	int b[10];
	memset(a,0,10*sizeof(int));
	memset(b,0,10*sizeof(int));
	int i;
	int k=9;						//k的值大于等于a中最大元素的值+1即可
	printf("input numbers: \n");
	for(i=0;i<10;i++){
		scanf("%d",&a[i]);			//输入的值在0～k之间
		printf("%d ",a[i]);
	}
	COUNTING_SORT(a,b,k);
	printf("\nresult :");
	for(i=0;i<10;i++)
		printf("%d ",b[i]);
	return 0;
}
		
