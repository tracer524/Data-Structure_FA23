#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define N          10

#include <iostream>

using namespace std;

class Customer
{
    public:
        int money;
        int arrivalTime;
        int waitTime;
        int leaveTime;
        int order;
};

typedef Customer QElemType;

typedef int Status;

typedef struct QNode{
    QElemType       data;
    struct QNode    *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr    front;      // 队头指针
    QueuePtr    rear;       // 队尾指针
}LinkQueue;

//-----队列操作-----
Status InitQueue( LinkQueue &Q );
    // 构造一个空队列 Q
Status DestroyQueue( LinkQueue &Q );
    // 销毁队列 Q，Q不再存在
Status ClearQueue( LinkQueue &Q );
    // 把 Q 置为空队列
Status QueueEmpty( LinkQueue Q );
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
int QueueLength( LinkQueue Q );
    // 返回 S 的元素个数，即队列的长度
Status GetHead( LinkQueue Q, QElemType &e );
    // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
Status EnQueue( LinkQueue &Q, QElemType e );
    // 插入元素 e 为 Q 的新的队尾元素
Status DeQueue( LinkQueue &Q, QElemType &e );
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；否则返回 ERROR
Status QueueTraverse( LinkQueue Q, Status (*visit)(QElemType &e) );
    // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit() 失败，则操作失败

class Bank
{
    public:
        int money;
        int closeTime;
        int serviceTime;
        int waitTimeList[100];
        int pNumber;
        int clock;
        int open;
        int avgWaitTime;
        LinkQueue Queue1, Queue2;
        Status deal(LinkQueue& queue, Customer &customer);    // 处理queue中一位客户customer的业务
        void checkQueue1();                                 // 对Queue1进行一次处理
        void checkQueue2(int benchmark);                    // 对Queue2进行检查
        void close();                                       // 下班吃饭，全部滚蛋
};

Status Bank::deal(LinkQueue &queue, Customer &customer){
    if(clock + serviceTime > closeTime) return ERROR;
    DeQueue(queue, customer);
    money += customer.money;
    clock += serviceTime;
    customer.leaveTime = clock;
    customer.waitTime = clock - customer.arrivalTime - serviceTime;
    waitTimeList[customer.order] = customer.waitTime;
    return OK;
}

void Bank::checkQueue1(){
    Customer customer;
    GetHead(Queue1, customer);
    if(customer.money < (-money)){     
        // 银行钱不够
        DeQueue(Queue1, customer);
        EnQueue(Queue2, customer);
    }
    else{
        if(!deal(Queue1, customer)){
            close();
            return;
        }
    }
    if(customer.money > 0) checkQueue2(money - customer.money);
}

void Bank::checkQueue2(int benchmark){
    int count = 0;
    int max_count = QueueLength(Queue2);
    Customer customer;
    while(money > benchmark && count < max_count){
        GetHead(Queue2, customer);
        if(customer.money >= (-money)){     
            // 银行钱够，进行处理
            if(!deal(Queue2, customer)){
                close();
                return;
            }
        }
        else{       
            // 银行钱不够，顾客出队再入队
            DeQueue(Queue2, customer);
            EnQueue(Queue2, customer);
        }
        count++;
    }
}

void Bank::close(){
    Customer customer;
    while(!QueueEmpty(Queue1)){
        DeQueue(Queue1, customer);
        customer.leaveTime = closeTime;
        customer.waitTime = customer.leaveTime - customer.arrivalTime;
        waitTimeList[customer.order] = customer.waitTime;
    }
    while(!QueueEmpty(Queue2)){
        DeQueue(Queue2, customer);
        customer.leaveTime = closeTime;
        customer.waitTime = customer.leaveTime - customer.arrivalTime;
        waitTimeList[customer.order] = customer.waitTime;
    }
    open = 0;
}

int main(){
    Bank bank;
    bank.clock = 0;
    bank.open = 1;
    bank.avgWaitTime = 0;
    Customer customer[100];
    int i;
    cin >> bank.pNumber >> bank.money >> bank.closeTime >> bank.serviceTime;
    InitQueue(bank.Queue1);
    InitQueue(bank.Queue2);
    for(i=0; i<bank.pNumber; i++){
        cin >> customer[i].money >> customer[i].arrivalTime;
        customer[i].order = i;
    }
    bank.clock = customer[0].arrivalTime;
    i=0;
    while(bank.clock < bank.closeTime){
        if(i < bank.pNumber && bank.clock >= customer[i].arrivalTime){
            EnQueue(bank.Queue1, customer[i]);
            i++;
        }
        if(!QueueEmpty(bank.Queue1)){
            bank.checkQueue1();
            if(!bank.open)  break;
        }
        else if(i < bank.pNumber){
            bank.clock = customer[i].arrivalTime;
        }
        else{
            bank.close();
            break;
        }
    }
    for(i=0; i<bank.pNumber; i++){
        cout << bank.waitTimeList[i] << endl;
        bank.avgWaitTime += bank.waitTimeList[i];
    }
    bank.avgWaitTime /= bank.pNumber;
    cout << bank.avgWaitTime << endl;
}

Status InitQueue( LinkQueue &Q ){
    // 构造一个空队列 Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;
    return OK;
}//InitQueue

Status DestroyQueue( LinkQueue &Q ){
    // 销毁队列 Q，Q不再存在
    ClearQueue(Q);
    free(Q.front);
    Q.front = NULL;
    Q.rear = NULL;
    return OK;
}//DestroyQueue

Status ClearQueue( LinkQueue &Q ){
    // 把 Q 置为空队列
    QueuePtr p = Q.front->next, q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    Q.rear = Q.front;
    Q.front->next = NULL;
    return OK;
}//ClearQueue

Status QueueEmpty( LinkQueue Q ){
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
    if(Q.front == Q.rear) return TRUE;
    else return FALSE;
}//QueueEmpty

int QueueLength( LinkQueue Q ){
    // 返回 S 的元素个数，即队列的长度
    int i = 0;
    QueuePtr p = Q.front->next;
    while(p){
        i++;
        p = p->next;
    }
    return i;
}//QueueLength

Status GetHead( LinkQueue Q, QElemType &e ){
    // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
    if(Q.front == Q.rear) return ERROR;
    e = Q.front->next->data;
    return OK;
}//GetHead

Status EnQueue( LinkQueue &Q, QElemType e ){
    // 插入元素 e 为 Q 的新的队尾元素
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}//EnQueue

Status DeQueue( LinkQueue &Q, QElemType &e ){
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；否则返回 ERROR
    if(Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return OK;
}//DeQueue

Status QueueTraverse( LinkQueue Q, Status (*visit)(QElemType &e) ){
    // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
    QueuePtr p = Q.front->next;
    while(p){
        if(!visit(p->data)) return ERROR;
        p = p->next;
    }
    return OK;
}//QueueTraverse