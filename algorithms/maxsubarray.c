#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN -65536
typedef struct haha{
	int low;
	int high;
	int sum;
}H,suba;

suba FIND_MAX_CROSSING_SUBARRAY(int a[],int low,int mid,int high, suba maxsuba){	//寻找跨越中点的最大子数组	
	
	int leftsum = MIN;
	int sum = 0;
	int i,lmaxnum,rmaxnum;
	for(i=mid;i>=low;i--){							//由中点向左寻找
		sum = sum + a[i];
		if(leftsum < sum){
			leftsum = sum;
			lmaxnum = i;
		}
	}
	int rightsum = MIN;								//由中点后一个元素向右寻找	
	sum = 0;
	for(i=mid+1;i<=high;i++){
		sum = sum + a[i];
		if(rightsum < sum){
			rightsum = sum;
			rmaxnum = i;
		}
	}
	maxsuba.low=lmaxnum;
	maxsuba.high=rmaxnum;
	maxsuba.sum=leftsum+rightsum;					//合并左右最大子数组之和
	return maxsuba;
}

suba FIND_MAXIMUM_SUBARRAY(int a[],int low,int high,suba maxsuba){	//递归调用
	suba left,right,cross;
	int mid;
	if(low == high){
		maxsuba.low=low;
		maxsuba.high=high;
		maxsuba.sum=a[low];
		return maxsuba;
	}
	else{
		mid = (low+high)/2;
		left = FIND_MAXIMUM_SUBARRAY(a,low,mid,maxsuba);			//分治法，将一个数组分为左，中，右三部分，其中中间部分也是合并操作
		right = FIND_MAXIMUM_SUBARRAY(a,mid+1,high,maxsuba);
		cross =FING_MAX_CROSSING_SUBARRAY(a,low,mid,high,maxsuba);
		if ((left.sum >= right.sum)&&(left.sum>=cross.sum)){		//比较左中右三部分最大子数组之和
			maxsuba=left;
		}
		else if((right.sum >= left.sum)&&(right.sum>=cross.sum)){
			maxsuba=right;
		}
		else{
			maxsuba=cross;

		}
	}
	
			return maxsuba;
}


int main(){
	int a[10];
	memset(a,0,10*sizeof(int));
	int i;
	printf("input the number: ");
	for(i=0;i < 10;i++)
		scanf("%d",&a[i]);
	suba maxsuba,msuba;
	msuba=FIND_MAXIMUM_SUBARRAY(a,0,9,maxsuba);
	printf("%d\n",msuba.sum);
	for(i=msuba.low;i <= msuba.high;i++)
		printf("%d ",a[i]);
	return 0;
}
