#include <stdio.h>
#include <unistd.h>
int main(){
    int n;
    printf("Enter the size: ");
    scanf("%d",&n);
    int a[100];
    for(int i=0;i<n;i++){
        a[i]=i+1;
    }
    int evensum=0;
    int oddsum=0;
    int x;
    int i;
    x=fork();
    if(x>0){
        for(i=0;i<n;i++){
            if(a[i]%2==0){
                evensum=evensum+a[i];
            }
        }
        printf("Parent Process\n");
        printf("Even sum is %d\n",evensum);   
    }
    else{
        for(i=0;i<n;i++){
            if(a[i]%2!=0){
                oddsum=oddsum+a[i];
            }
        }
        printf("Child Process\n");	
        printf("Odd sum is %d\n",oddsum);
    }
    return 0;
}