#include<stdio.h>
int main(){
int arr[100],n,i,max=-999999;
printf("Enter the size of array:");
scanf("%d",&n);
printf("Enter the elements of array:");
for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
}
max=arr[0];
for(int i=1;i<n;i++){
    if(arr[i]>max){
        max=arr[i];
    }
}
printf("The maximum number is:%d",max);
return 0;

}
