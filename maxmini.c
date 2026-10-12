#include<stdio.h>
int main(){
    int arr[100], n,max,mini;

printf("Enter the size:");
scanf("%d",&n);

printf("Enter the elements of array:");
for(int i=0;i<n;i++){

        scanf("%d",&arr[i]);
}
    max=arr[0];
    mini=arr[0];
for(int i=1;i<n;i++){

    if(arr[i]>max){
        max=arr[i];
    }

   else if(arr[i]<mini){
        mini=arr[i];
    }
}
printf("Maximum element is:%d\n",max);
printf("Minimum element is:%d\n",mini);

return 0;

}
