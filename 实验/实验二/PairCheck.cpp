# define TRUE       1
# define FALSE      0
# define OK         1
# define ERROR      0
# define INFEASIBLE -1
# define OVERFLOW   -2
# define STACK_INIT_SIZE 100
# define STACKINCREMENT  10
# define N 10000

#include <iostream>
#include <fstream>


using namespace std;

typedef int Status;

typedef char SElemType;

typedef struct {
    char *base;
    char *top;
    int stacksize;
} SqStack;

// 栈操作函数声明
Status InitStack(SqStack &S);
    // 构造一个空栈S
Status DestroyStack(SqStack &S);
    // 销毁栈S，S不再存在
Status ClearStack(SqStack &S);
    // 把S置为空栈
Status StackEmpty(SqStack S);
    // 若栈S为空栈，则返回TRUE，否则返回FALSE
int StackLength(SqStack S);
    // 返回S的元素个数，即栈的长度
Status GetTop(SqStack S, SElemType &e);
    // 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
Status Push(SqStack &S, SElemType e);
    // 插入元素e为新的栈顶元素
Status Pop(SqStack &S, SElemType &e);
    // 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status StackTraverse(SqStack S, Status (*visit)(SElemType &e));
    // 从栈底到栈顶依次对栈中每个元素调用函数visit()。一旦visit()失败，则操作失败

int main(){
    string output[N];
    string data;
    SqStack S;
    SElemType top;
    InitStack(S);
    int i, j=1, check;     // i:行数，j:字符数

    // 读取文件
    ifstream infile;
    infile.open("2.txt");

    getline(infile, data);  // 行数
    cout << data << endl;
    int LineNum = atoi(data.c_str());

    for(i=0; i<=LineNum; i++){
        check = 1;
        getline(infile, data);
        cout << data << endl;
        ClearStack(S);
        for(j=0; data[j] != '@'; j++){
            if(data[j] == '('){
                if(!StackEmpty(S)){
                    GetTop(S, top);
                    if(top == '{'){
                        check = 0;
                        break;
                    }
                }
                Push(S, data[j]);
            }
            else if(data[j] == '['){
                if(!StackEmpty(S)){
                    GetTop(S, top);
                    if(top == '('){
                        check = 0;
                        break;
                    }
                }
                Push(S, data[j]);
            }
            else if(data[j] == '{'){
                if(!StackEmpty(S)){
                    GetTop(S, top);
                    if(top != '{'){
                        check = 0;
                        break;
                    }
                }
                Push(S, data[j]);
            }
            else if(data[j] == ')'){
                GetTop(S, top);
                if(top == '('){
                    Pop(S, top);
                }
                else{
                    check = 0;
                    break;
                }
            }
            else if(data[j] == ']'){
                GetTop(S, top);
                if(top == '['){
                    Pop(S, top);
                }
                else{
                    check = 0;
                    break;
                }
            }
            else if(data[j] == '}'){
                GetTop(S, top);
                if(top == '{'){
                    Pop(S, top);
                }
                else{
                    check = 0;
                    break;
                }
            }
        }// for
        if(StackEmpty(S) && check){
            output[i] = "Yes";
        }
        else{
            output[i] = "No";
        }
    }
   
    infile.close();
    
    ofstream outfile;
    outfile.open("2.txt", ios::app);
    for(i=0; i<LineNum; i++){
        outfile << output[i] << endl;
    }
    return 0;
}

Status InitStack(SqStack &S){
    // 构造一个空栈S
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base) exit(OVERFLOW);     // 存储分配失败
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack &S){
    // 销毁栈S，S不再存在
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return OK;
}

Status ClearStack(SqStack &S){
    // 把S置为空栈
    S.top = S.base;
    return OK;
}

Status StackEmpty(SqStack S){
    // 若栈S为空栈，则返回TRUE，否则返回FALSE
    if(S.top == S.base) return TRUE;
    else return FALSE;
}

int StackLength(SqStack S){
    // 返回S的元素个数，即栈的长度
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType &e){
    // 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if(S.top == S.base) return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status Push(SqStack &S, SElemType e){
    // 插入元素e为新的栈顶元素
    if(S.top - S.base >= S.stacksize){  // 栈满，追加存储空间
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S.base) exit(OVERFLOW);     // 存储分配失败
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, SElemType &e){
    // 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
    if(S.top == S.base) return ERROR;
    e = *S.top;
    S.top--;
    return OK;
}

Status StackTraverse(SqStack S, Status (*visit)(SElemType &e)){
    // 从栈底到栈顶依次对栈中每个元素调用函数visit()。一旦visit()失败，则操作失败
    while(S.top > S.base){
        visit(*S.base++);
    }
    return OK;
}
