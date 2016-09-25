//从文件输入
void input(int a[],int length){
	int i;
	FILE *fp=fopen("input.txt","r");
	if(fp==NULL){
		printf(" Open file failed!!");
	}
	printf("input numbers:");
	for(i=0;i<length;i++){
		fscanf(fp,"%d",&a[i]);
		printf("%d ",a[i]);
	}
	fclose(fp);
}
//交换数组中两个元素
void swap(int a[],int i,int j){
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}
