#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "finput.c"

#define LENGTH 10

void MAX_HEAPIFY(int a[],int i,int length){
	int l=(i<<1)+1,r=(i+1)<<1;
	int max;
	if(l<length&&a[i]<a[l])
		max=l;
	else max=i;
	if(r<length&&a[max]<a[r])
		max=r;
	if(max!=i){
		swap(a,max,i);
		MAX_HEAPIFY(a,max,length);
	}
}

void BUILD_MAX_HEAP(int a[]){
	int i;
	for(i=(LENGTH-1)/2;i>=0;i--)
		MAX_HEAPIFY(a,i,LENGTH);
}

void HEAPSORT(int a[]){
	BUILD_MAX_HEAP(a);
	int i;
	int length=LENGTH;
	for(i=LENGTH-1;i>=1;i--){
		swap(a,0,i);
		length--;
		MAX_HEAPIFY(a,0,length);
	}
}

int main(){
	int i;
	int a[LENGTH];
	input(a,LENGTH);
	HEAPSORT(a);
	printf("\nheapsort result: ");
	for(i=0;i<LENGTH;i++)
		printf("%d ",a[i]);
	return 0;
}


