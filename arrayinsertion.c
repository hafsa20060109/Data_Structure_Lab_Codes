#include<stdio.h>
int main(){
int arr[100],n,i,valu,pos;
printf("Enter the size of array:");
scanf("%d",&n);
printf("Enter the elements of the array:");
for(i=0;i<n;i++){
    scanf("%d",&arr[i]);
}
printf("The position is:");
scanf("%d",&pos);
printf("The value is:");
scanf("%d",&valu);
for(i=n;i>=pos;i--){

        arr[i]=arr[i-1];
        }
arr[pos-1]=valu;
 n++;
printf("New array is(after insertion):");
for(i=0;i<n;i++){
    printf(" %d",arr[i]);
}
return 0;

}
