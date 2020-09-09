import java.lang.*;

class arr{
	static void swap(int a[]){
		int temp=0;
		for(int i=0;i<10;i+=2){
			temp=a[i];
			a[i]=a[i+1];
			a[i+1]=temp;
		}
	}
	public static void main(String []argv){
		int a[]={1,2,3,4,5,6,7,8,9,0};
		swap(a);
		for(int i=0;i<10;i++)
			System.out.print(a[i]+",");
	}
}