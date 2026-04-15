#include <stdio.h> 

int total;

typedef struct {
    int src;
    int tmp;
    int dst;
    int n;
    int stage; // =0/1/2/3 未进入递归点 进入第一个递归点 结束第一个未进入第二个 进入第二个 结束第二个
} Frame;

int hanoi(int src, int tmp, int dst, int n){
    if(n==0){
        return 0;
    }
    static int step = 0;
    hanoi(src,dst,tmp,n-1);
    printf("%d->%d, step %d, plate #%d\n",src, dst, ++step, n);
    hanoi(tmp, src, dst, n - 1);
    return step;
}

int hanoi_stack(int src, int tmp, int dst, int n) {
    if (n == 0) {
        return 0;
    }
    Frame stack[128];
    int top = 0;
    int step = 0;

    stack[top++] = (Frame){src, tmp, dst, n, 0};

    while (top > 0) {
        Frame *cur = &stack[top - 1];
        if (cur->n == 0) {
            --top;
            continue;
        }
        if (cur->stage == 0) {
            cur->stage = 1;
            stack[top++] = (Frame){cur->src, cur->dst, cur->tmp, cur->n - 1, 0};
            continue;
        }
        if (cur->stage == 1) {
            printf("%d->%d, step %d, plate #%d\n", cur->src, cur->dst, ++step, cur->n);
            cur->stage = 2;
            stack[top++] = (Frame){cur->tmp, cur->src, cur->dst, cur->n - 1, 0};
            continue;
        }
        --top;
    }

    return step;
}

typedef struct{
    struct node * left;
    struct node * right;
    int val;
}node;

typedef node* tree;



int main(){
    scanf("%d",&total);
    hanoi_stack(1, 2, 3, total);
}