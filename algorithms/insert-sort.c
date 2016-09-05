#include <stdio.h>
#include <string.h>
int main(){
	int a[10];
	memset(a,0,10*sizeof(int));
	int n,m;
	printf("input the numbers:\n");
	for(n=0;n<10;n++){
	scanf("%d",&a[n]);
	}	
	int i=0;
	int j=0;
	for(j=1;j<10;j++){
		int key;
		key = a[j];
		i=j-1;
		while(i>=0&&a[i]>key){
			a[i+1]=a[i];
			i=i-1;	
		}
		a[i+1]=key;
	}
	for(m=0;m<10;m++)
	printf("%d ",a[m]);
return 0;
}
