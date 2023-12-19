#include<stdio.h>
#include<stdbool.h>
#include<windows.h>
int a[100],sum=2,b=0;
void prime(){
    for(int i=4;i<=100;i++)
    {
        b=0;
        for(int j=1;j<=sum;j++){
            if(i%a[j]==0){
                b=1;
                break;
            }
        }
        if(b==0){
            sum++;
            a[sum]=i;
        }
    }
}
bool IsPrime(int n){
    if(n==1||n==0) return false;
    for(int i=1;i<=sum;i++){
        if(n%a[i]==0&&n!=a[i]){
            return false;
        }
    }
    return true;
}
int main() {
    a[1]=2,a[2]=3;
    int x,y,z;
    prime();
    for(int i=6;i<=100;i++){
        x=0,y=0,z=0;
        if(i%2==0){
            x=2;
            for(int j=sum;j>=1;j--){
                if(a[j]<i-x){
                    z=a[j];
                    y=i-x-z;
                    if(IsPrime(y)){
                        break;
                    }
                }
            }
            printf("%d=%d+%d+%d\n",i,x,y,z);
        }
        else{
            int m=0,k=0;
            while(k==0){
                z=0;
                for(int j=sum;j>=1;j--){
                    if(z==0){
                        if(a[j]<i&&a[j]!=m){
                            m=a[j];
                            z=a[j];
                            j++;
                        }
                    }
                    else{
                        if(a[j]<i-z){
                            y=a[j];
                            x=i-y-z;
                            if(IsPrime(x)){
                                k=1;
                                break;
                            }
                        }
                    }
                }
            }
            printf("%d=%d+%d+%d\n",i,x,y,z);
        }
    }
    return 0;
}