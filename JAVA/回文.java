public static int reverse(int number){
		int a=0;
		int b=0;
		int i=0;
		int j;
		if(number/10==0){
			a= number;
		return a;
		}
		else{
			for(j=number;j>0;j=j/10){
				i++;
			}
			for( i-=1;i>=0;i--){
				a= number %10 ;
				b=b+a*(int)Math.pow(10, i);
				number=number/10;
			}
			return b;
		}
		}
public static boolean isPalindrome(int number){
	int num=0;
		num= reverse(number);
		return (num==number);
	}
