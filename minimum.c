#include<stdio.h>
int main(){
int arr[100],n,i,mini=999999;
printf("Enter the size of array:");
scanf("%d",&n);
printf("Enter the elements:");
for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
}
mini=arr[0];
for(int i=0;i<n;i++){
    if(arr[i]<mini){
        mini=arr[i];
    }
}
printf("The minimum element is:%d",mini);
return 0;
}


