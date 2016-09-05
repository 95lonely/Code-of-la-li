#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAX 65536			//监视哨设为65536	

void merge(int a[],int p,int q,int r){//merge_sort的归并过程：将两个有序的子序列合并
	int n1 = q-p+1;
	int n2 = r-q;
	int *L;					//借助两个动态数组完成原数组元素的暂时存储
	int *R;
	int i,j;
	L=(int *)calloc(n1,sizeof(int));
//	memset(L,0,n1*sizeof(L));
	R=(int *)calloc(n2,sizeof(int));
//	memset(R,0,n2*sizeof(R));
	for(i=0;i<=n1-1;i++)	//将原数组a[p]~a[q]元素存入动态数组
		L[i]=a[p+i];
	for(j=0;j<=n2-1;j++)	//将原数组a[q+1]~a[r]元素存入动态数组
		R[j]=a[q+1+j];
	L[n1]=MAX;				//监视哨MAX：一个远大于所有原数组元素的数，用来减少比较次数（不然还需要一个while循环来保证两个动态数组没有越界）
	R[n2]=MAX;
	i=0;
	j=0;
	int k;
	for(k=p;k<=r;k++){		//将两个动态数组中已经从小到大有序排列的元素做比较，小的放入a[k]，并用小元素所属的动态数组的下一个元素与另一个动态数组的元素比较
		if(L[i]<=R[j]){
			a[k]=L[i];
			i++;
		}
		else {
			a[k]=R[j];
			j++;
		}
	}
	free(L);
	free(R);
}
void merge_sort(int a[],int p,int r){	//递归调用
	int q;
	if(p<r){
		q=(p+r)/2;
		merge_sort(a,p,q);	//此处体现了分治的思想，将一个数组拆成两半a[p~q]和[q+1,r],递归调用后，最终会从两个元素排序后返回
		merge_sort(a,q+1,r);
		merge(a,p,q,r);		//此处体现了合并的思想，将已经排好序的两个子序列合并
	}
}

int main(){					//主函数
	int n;
	int a[10];
	printf("input the number: ");
	for(n=0;n<10;n++)
		scanf("%d",&a[n]);
	merge_sort(a,0,9);
	for(n=0;n<10;n++)
		printf("%d ",a[n]);
	return 0;
}





