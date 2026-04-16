#include <stdio.h>

// int fib(int n){
//     if(n<=1){
//         return n;
//     }
//     int a = fib(n-1);
//     int b = fib(n-2);
//     return a+b;
// }
typedef struct{
    int n;
    int a;
    int b;
    int ip; //=0/1/2
} frame;

int fib(int n){
    int ret = 0;
    frame stack[128];
    int top = -1;
    stack[++top]=(frame){n,0,0,0};
    while(top!=-1){
        frame *f = &stack[top];
        if(f->n<=1){
            ret = f->n;
            --top;
            continue;
        }
        if(f->ip==0){
            f->ip = 1;
            stack[++top] = (frame){f->n-1,0,0,0};
            continue;
        }
        if(f->ip==1){
            f->a = ret;
            f->ip = 2;
            stack[++top] = (frame){f->n-2,0,0,0};
            continue;
        }
        if(f->ip==2){
            f->b = ret;
            ret = f->a+f->b;
            --top;
        }
    }
    return ret;
}

int main(){
    int n;
    scanf("%d",&n);
    int ans = fib(n);
    printf("%d",ans);
}