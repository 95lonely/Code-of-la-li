#include <stdio.h>
#include "finput.c"
#define LENGTH 10
void QUICKSORT(int a[],int p,int r){
	int q=0;
	if(p<r){
		q=PARTITION(a,p,r);
		QUICKSORT(a,p,q-1);
		QUICKSORT(a,q+1,r);
	}
}
int PARTITION(int a[],int p,int r){
	int x=a[r];
	int i,j;
	i=p-1;
	for(j=p;j<r;j++){
		if(a[j]<=x){
			i++;
			swap(a,i,j);
		}
	}
	swap(a,i+1,r);
	return i+1;
}

void main(){
	int a[LENGTH];
	int i;
	input(a,LENGTH);
	QUICKSORT(a,0,LENGTH-1);
	printf("\nQuicksort result: ");
	for(i=0;i<LENGTH;i++)
		printf("%d ",a[i]);
}
