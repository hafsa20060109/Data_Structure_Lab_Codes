#include<stdio.h>
int main(){
int arr[100];
int n,i,pos,value;

printf("Enter the size:");
scanf("%d",&n);

printf("Enter the elements:");
for(i=0;i<n;i++){
scanf("%d",&arr[i]);
}

printf("Enter the position to update 1 to %d:",n);
scanf("%d",&pos);

if(pos<1 || pos>n){

    printf("Invalid position");


}

else{

    printf("Enter the  updated or new  value:");
    scanf("%d",&value);
    arr[pos-1]=value;

    printf("Updated array:\n");
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);

    }
}


return 0;

}
