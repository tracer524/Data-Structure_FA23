# define TRUE       1
# define FALSE      0
# define OK         1
# define ERROR      0
# define INFEASIBLE -1
# define OVERFLOW   -2
# define N          10

#include <iostream>
#include <cmath>

using namespace std;

typedef int Status;

typedef struct term{   // 多项式的项
    float   coef;     // 系数
    int     exp;      // 指数
}term, ElemType;

typedef struct LNode{  // 结点类型
    ElemType        data;
    struct LNode    *next;
}*Link, *Position;

typedef  struct LinkList{             // 链表类型
    Link    head, tail;     // 分别指向线性链表的头结点和最后一个结点
    int     len;            // 指示线性链表中数据元素的个数
}LinkList;

typedef  LinkList polynomial;   //用带表头结点的有序链表表示多项式

        //-----链表操作-----
Status MakeNode( Link &p, ElemType e);
    //  分配由 p 指向的值为 e 的结点，并返回 OK；若分配失败，则返回 ERROR
void FreeNode( Link &p );
    //  释放 p 所指结点
Status InitList( LinkList &L);
    //  初始化一个空的线性链表 L
Status DestroyList( LinkList &L );
    //  销毁一个线性链表 L，L不再存在
Status ClearList( LinkList &L );
    //  将线性链表 L 重置为空表，并释放原链表的结点空间
Status InsFirst( Link h, Link s );
    //  已知 h 指向线性链表的头结点，将 s 所指结点插入在第一个结点之前
Status DelFirst( Link h, Link &q );
    //  已知 h 指向线性链表的头结点，删除链表中的第一个结点并以 q 返回
Status Append( LinkList &L, Link s );
    //  将指针 s 所指(彼此以指针相链)的一串结点链接在线性链表 L 的最后一个结点之后，
    //  并改变链表 L 的尾指针指向新的尾结点
Status Remove( LinkList &L, Link &q );
    //  删除线性链表 L 中的尾结点并以 q 返回，改变链表 L 的尾指针指向新的尾结点
Status InsBefore( LinkList &L, Link &p, Link s );
    //  已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之前，
    //  并修改指针 p 指向新插入的结点
Status InsAfter( LinkList &L, Link &p, Link s );
    //  已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之后，
    //  并修改指针 p 指向新插入的结点
Status SetCurElem( Link &p, ElemType e );
    //  已知 p 指向线性链表中的一个结点，用 e 更新 p 所指结点中数据元素的值
ElemType GetCurElem( Link p );
    //  已知 p 指向线性链表中的一个结点，返回 p 所指结点中数据元素的值
Status ListEmpty( LinkList L );
    //  若线性链表 L 为空表，则返回 TRUE，否则返回 FALSE
int ListLength( LinkList L );
    //  返回线性链表 L 中元素个数
Position GetHead( LinkList L );
    //  返回线性链表 L 中头结点的位置
Position GetLast( LinkList L );
    //  返回线性链表 L 中最后一个结点的位置
Position PriorPos( LinkList L, Link p );
    //  已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接前驱的位置，
    //  若无前驱，则返回 NULL
Position NextPos( LinkList L, Link p );
    //  已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接后继的位置，
    //  若无后继，则返回 NULL
Status LocatePos( LinkList L, int i, Link &p );
    //  返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK，i 值不合法时返回 ERROR
Status LocateElem( LinkList L, ElemType e, Position &q, int(*compare)(ElemType, ElemType) );
    //  若有序链表 L 中存在与 e 满足判定函数 compare() 取值为0的元素，则 q 指示
    //  L 中第一个值为 e 的结点的位置，并返回 TRUE；否则 q 指示第一个与 e 满足判定函数
    //  compare() 取值>0 的元素的前驱的位置。并返回 FALSE
Status ListTraverse( LinkList L, Status(*visit)() );
    //  依次对 L 的每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
    //  若 visit() 成功，则操作成功
Status OrderInsert( LinkList &L, ElemType e, int (*compare)(ElemType, ElemType) );
    //  按有序判定函数 compare() 的约定，将新结点插入到有序链表 L 的适当位置上
int cmp(ElemType e1, ElemType e2);
    //  比较两项指数大小, e1>e2 返回1, e1=e2 返回0, e1<e2 返回-1


        //-----基本操作的函数原型说明-----
void CreatePolyn(polynomial &P, int m );
    //  输入m项的系数和指数，建立表示一元多项式的有序链表P
void DestroyPolyn(polynomial &P);
    //  销毁一元多项式P
void PrintPolyn(polynomial P);
    //  打印输出一元多项式P
void ClearPolyn(polynomial p);
    //  将一元多项式P置空
int PolynLength(polynomial P);
    //  返回一元多项式P中的项数
void AddPolyn(polynomial &Pa, polynomial &Pb);
    //  完成多项式相加运算，即: Pa=Pa+Pb, 并销毁一元多项式Pb
void SubstractPolyn(polynomial &Pa, polynomial &Pb);
    //  完成多项式相减运算，即: Pa=Pa-Pb, 并销毁一元多项式Pb
float EvaluatePolyn(polynomial P, float f);
    //  算出一元多项式P(x)在x=f处的值
void DiffPolyn(polynomial &P);
    //  求一元多项式P的1阶导数
void Integral(polynomial &p);
    //  求一元多项式P的不定积分
void IntPrintPolyn(polynomial P);
    //  打印输出P的不定积分
float IntEvalPolyn(polynomial P, float f);
    //  算出一元多项式P的不定积分在x=f处的值
float DefIntegral(polynomial P, float a, float b);
    //  求一元多项式P在[a, b]上的定积分

int main(){
    int choice=1;
    Link PList[N];             // 多项式链表的头指针
    polynomial PolynList[N];   // 多项式数组
    int m;                     // 项数
    int n;
    int count = 0;             // 目前多项式最靠前空位
    int i;
    int a,b,c;
    float alpha, beta;         // 定积分中的上下限
    float f;                   // 求值时的自变量
    Link p;
    Link Ins;                  // 用于插入新结点
    term ins;
    ins.coef = 0.0; ins.exp = 0;
    MakeNode(Ins, ins);
    Link Mod;                  // 用于修改结点
    int mod_exp = 0;    float mod_coef = 0.0;
    int flag[N];               // 标记多项式是否存在
    int check;                 // 用于检查输入是否合法
    for(i=0; i<N; i++) flag[i]=0;
    while(choice != 0){
        cout << "--------------------" << endl << "1 创建多项式" << endl 
        << "2 输出多项式" << endl << "3 求和" << endl << "4 求差" << endl 
        << "5 求值" << endl << "6 销毁" << endl << "7 清空" << endl 
        << "8 修改" << endl << "9 微分" << endl << "10 不定积分" << endl 
        << "11 定积分" << endl << "0 退出" << endl << "--------------------" 
        << endl << "请输入选项:";
        cin >> choice;
        switch (choice)
        {
        case 1:                                             // 创建多项式
            count = 0;
            while(flag[count] && count<=N) count++;
            if(count==N){
                cout << "多项式已满" << endl;
                break;
            }
            cout << "请输入项数，输入0退出:";
            cin >> m;
            if(m==0) break;
            CreatePolyn(PolynList[count], m);
            PList[count]=PolynList[count].head;
            flag[count]=1;
            break;
        case 2:                                             // 输出多项式
            cout << "希望输出的多项式序号，输入0退出：";
            cin >> n;
            if(n==0) break;
            if(n<0 || n>=N){
                cout << "序号超出范围" << endl;
                break;
            }
            if(flag[n-1])    PrintPolyn(PolynList[n-1]);
            else cout << "多项式不存在" << endl;
            break;
        case 3:                                             // 求和
            cout << "请输入第一个要相加的多项式序号，输入0退出：";
            cin >> a;
            if(!flag[a-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            cout << "请输入第二个要相加的多项式序号，输入0退出：";
            cin >> b;
            if(!flag[b-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            AddPolyn(PolynList[a-1], PolynList[b-1]);
            flag[b-1] = 0;
            break;
        case 4:                                             // 求差
            cout << "请输入第一个要相减的多项式序号，输入0退出：";
            cin >> a;
            if(!flag[a-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            cout << "请输入第二个要相减的多项式序号，输入0退出：";
            cin >> b;
            if(!PolynList[b-1].head){
                cout << "多项式不存在" << endl;
                break;
            }
            SubstractPolyn(PolynList[a-1], PolynList[b-1]);
            flag[b-1] = 0;
            PList[b-1] = NULL;
            break;
        case 5:                                             // 求值
            cout << "请输入要求值的多项式序号，输入0退出：";
            cin >> a;
            if(!PolynList[a-1].head){
                cout << "多项式不存在" << endl;
                break;
            }
            cout << "请输入自变量x：";
            cin >> f;
            cout << "结果为：" << EvaluatePolyn(PolynList[a-1], f) << endl;
            break;
        case 6:                                             // 销毁
            cout << "请输入要销毁的多项式序号，输入0退出：";
            cin >> a;
            if(!PolynList[a-1].head){
                cout << "多项式不存在" << endl;
                break;
            }
            DestroyPolyn(PolynList[a-1]);
            flag[a-1] = 0;
            PList[a-1] = NULL;
            break;
        case 7:                                             // 清空
            cout << "请输入要清空的多项式序号，输入0退出：";
            cin >> a;
            if(!flag[a-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            ClearPolyn(PolynList[a-1]);
            break;
        case 8:                                             // 修改,操作包括：1 插入新的结点、2 删除已有结点、3 修改已有结点的系数和指数
            cout << "请输入要修改的多项式序号，输入0退出：";
            cin >> a;
            if(!flag[a-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            cout << "--------------------" << endl << "1 插入新的结点" << endl <<
            "2 删除已有结点" << endl << "3 修改已有结点的系数和指数" << endl <<
            "0 退出" << endl << "--------------------" << endl << "请输入选项：";
            cin >> b;
            switch (b){
            case 1:                              // 插入新的结点
                cout << "请输入要插入的系数：";
                cin >> Ins->data.coef;
                cout << "请输入要插入的指数：";
                cin >> Ins->data.exp;
                OrderInsert(PolynList[a-1], Ins->data, cmp);
                break;
            case 2:                              // 删除已有结点
                cout << "请输入要删除的位置：";
                cin >> c;
                if(c<1 || c>PolynLength(PolynList[a-1])){
                    cout << "位置不合法" << endl;
                    break;
                }
                LocatePos(PolynList[a-1], c, PList[a-1]);
                DelFirst(PList[a-1], PolynList[a-1].tail);
                FreeNode(PolynList[a-1].tail);
                break;
            case 3:                              // 修改已有结点的系数和指数
                cout << "请输入要修改的位置：";
                cin >> c;
                if(c<1 || c>PolynLength(PolynList[a-1])){
                    cout << "位置不合法" << endl;
                    break;
                }
                LocatePos(PolynList[a-1], c+1, Mod);
                do{
                    check = 1;
                    cout << "请输入要修改的系数：";
                    cin >> mod_coef;
                    cout << "请输入要修改的指数：";
                    cin >> mod_exp;
                    p=PolynList[a-1].head->next;
                    for(i=0; i<ListLength(PolynList[a-1]); i++){
                        if(mod_exp == p->data.exp && i!=c){
                            cout << "请勿输入重复指数" << endl;
                            check = 0;
                            break;
                        }
                        p=p->next;
                    }// for
                }while(!check);
                Mod->data.coef = mod_coef;  
                Mod->data.exp = mod_exp;
                break;
            }
            break;
        case 9:                                             // 微分(n阶)
            cout << "请输入要微分的多项式序号，输入0退出：";
            cin >> a;
            if(!flag[a-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            do
            {
                cout << "请输入要微分的阶数：";
                cin >> n;
                if(n <= 0){
                    cout << "请输入正整数" << endl;
                    check = 0;
                }
                else check = 1;
            } while (!check);
            for(i=0; i<n; i++)  DiffPolyn(PolynList[a-1]);
            cout << "结果为:" << endl;
            PrintPolyn(PolynList[a-1]);
            break;
        case 10:                                            // 不定积分
            cout << "请输入要不定积分的多项式序号，输入0退出：";
            cin >> a;
            if(!flag[a-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            Integral(PolynList[a-1]);
            cout << "结果为:" << endl;
            IntPrintPolyn(PolynList[a-1]);
            break;
        case 11:                                            // 定积分
            cout << "请输入要定积分的多项式序号，输入0退出：";
            cin >> a;
            if(!flag[a-1]){
                cout << "多项式不存在" << endl;
                break;
            }
            cout << "请输入积分下限：";
            cin >> alpha;
            cout << "请输入积分上限：";
            cin >> beta;
            cout << "结果为：" << DefIntegral(PolynList[a-1], alpha, beta) << endl;
            break;
        case 0: break;
        default:
            cout << "输入错误，请重新输入" << endl;
            break;
        }//switch
    }//while
    return 0;
}

        //-----链表操作的算法描述-----
Status MakeNode( Link &p, ElemType e){
    //分配由 p 指向的值为 e 的结点，并返回 OK；若分配失败，则返回 ERROR
    p = (Link)malloc(sizeof(LNode));
    if(!p) return ERROR;
    p->data = e;
    p->next = NULL;
    return OK;
}//MakeNode

void FreeNode(Link &p){
    //释放 p 所指结点
    free(p);
}//FreeNode

Status InitList( LinkList &L){
    //初始化一个空的线性链表 L
    L.head = L.tail = (Link)malloc(sizeof(Link));
    if(!L.head) exit(OVERFLOW);
    L.head->next = NULL;
    L.len = 0;
    return OK;
}//InitList

Status DestroyList( LinkList &L){
    //销毁一个线性链表 L，L不再存在
    Link q;
    while(L.head){
        q = L.head->next;
        free(L.head);
        L.head = q;
    }
    L.len = 0;
    return OK;
}//DestroyList

Status ClearList( LinkList &L){
    //将线性链表 L 重置为空表，并释放原链表的结点空间
    Link p = L.head, q=p->next;
    while(q){
        p = q->next;
        free(q);
        q=p;
    }
    L.head->next = NULL;
    L.tail = L.head;
    L.len = 0;
    return OK;
}//ClearList

Status InsFirst( Link h, Link s){
    //已知 h 指向线性链表的头结点，将 s 所指结点插入在第一个结点之前
    s->next = h->next;
    h->next = s;
    return OK;
}//InsFirst

Status DelFirst( Link h, Link &q){
    //已知 h 指向线性链表的头结点，删除链表中的第一个结点并以 q 返回
    q = h->next;
    h->next = q->next;
    return OK;
}//DelFirst

Status Append( LinkList &L, Link s){
    //将指针 s 所指(彼此以指针相链)的一串结点链接在线性链表 L 的最后一个结点之后，
    //  并改变链表 L 的尾指针指向新的尾结点
    s->next = NULL;
    if(!L.tail) L.tail = s;
    else L.tail->next = s;
    L.tail = s;
    L.len++;
    return OK;
}//Append

Status Remove( LinkList &L, Link &q){
    //删除线性链表 L 中的尾结点并以 q 返回，改变链表 L 的尾指针指向新的尾结点
    q = L.tail;
    L.tail = q->next;
    delete q;
    L.len--;
    return OK;
}//Remove

Status InsBefore( LinkList &L, Link &p, Link s){
    //已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之前，
    //  并修改指针 p 指向新插入的结点
    Link q = PriorPos(L, p);
    if(!q) return ERROR;
    s->next = p;
    q->next = s;
    p = s;
    L.len++;
    return OK;
}//InsBefore

Status InsAfter( LinkList &L, Link &p, Link s){
    //已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之后，
    //  并修改指针 p 指向新插入的结点
    s->next = p->next;
    p->next = s;
    L.len++;
    return OK;
}//InsAfter

Status SetCurElem( Link &p, ElemType e){
    //已知 p 指向线性链表中的一个结点，用 e 更新 p 所指结点中数据元素的值
    p->data = e;
    return OK;
}//SetCurElem

ElemType GetCurElem( Link p){
    //已知 p 指向线性链表中的一个结点，返回 p 所指结点中数据元素的值
    return p->data;
}//GetCurElem

Status ListEmpty( LinkList L){
    //若线性链表 L 为空表，则返回 TRUE，否则返回 FALSE
    if(L.head == NULL) return TRUE;
    else return FALSE;
}//ListEmpty

int ListLength( LinkList L){
    //返回线性链表 L 中元素个数
    int i=0; Link p = L.head;
    while(p->next){
        i++;
        p = p->next;
    }
    return i;
}//ListLength

Position GetHead( LinkList L){
    //返回线性链表 L 中头结点的位置
    return L.head;
}//GetHead

Position GetLast( LinkList L){
    //返回线性链表 L 中最后一个结点的位置
    return L.tail;
}//GetLast

Position PriorPos( LinkList L, Link p){
    //  已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接前驱的位置，
    //  若无前驱，则返回 NULL
    Link q = L.head;
    if(q == p) return NULL;
    while(q && q->next != p) q = q->next;
    return q;
}//PriorPos

Position NextPos( LinkList L, Link p){
    //已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接后继的位置，
    //  若无后继，则返回 NULL
    if(!p->next) return NULL;
    return p->next;
}//NextPos

Status LocatePos( LinkList L, int i, Link &p){
    //返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK，i 值不合法时返回 ERROR
    int j;
    if(i < 1 || i > L.len) return ERROR;
    p = L.head;
    for(j = 1; j < i; j++) p = p->next;
    return OK;
}//LocatePos

Status LocateElem( LinkList L, ElemType e, Position &q, Status(*compare)(ElemType, ElemType)){
    //  若有序链表 L 中存在与 e 满足判定函数 compare() 取值为0的元素，则 q 指示
    //  L 中第一个值为 e 的结点的位置，并返回 TRUE；否则 q 指示第一个与 e 满足判定函数
    //  compare() 取值>0 的元素的前驱的位置。并返回 FALSE
    Link p = L.head->next;
    while(p && compare(p->data, e) < 0){
        q = p;
        p = p->next;
    }
    if(p && compare(p->data, e) == 0){
        q = p;
        return TRUE;
    }
    else return FALSE;
}//LocateElem

Status ListTraverse( LinkList L, Status(*visit(ElemType)) ){
    //依次对 L 的每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
    //  若 visit() 成功，则操作成功
    Link p = L.head;
    while(p){
        if(!visit(p->data)) return ERROR;
        p = p->next;
    }
    return OK;
}//ListTraverse

Status OrderInsert( LinkList &L, ElemType e, int (*compare)(ElemType, ElemType)){
    //按有序判定函数 compare() 的约定，将新结点插入到有序链表 L 的适当位置上
    Link p = L.head->next, q = L.head;
    while(p && (compare(p->data, e) > 0)){
        q = p;
        p = p->next;
    }
    Link s;
    if(MakeNode(s, e)){
        if(!InsAfter(L, q, s)) return ERROR;
        return OK;
    }
    else return ERROR;
}//OrderInsert

Status equal(ElemType e1, ElemType e2){
    //判断两项指数是否相等
    return e1.exp == e2.exp;
}//equal

int cmp(ElemType e1, ElemType e2){
    //比较两项指数大小, e1>e2 返回1, e1=e2 返回0, e1<e2 返回-1
    if (e1.exp == e2.exp) return 0;
    else if(e1.exp < e2.exp) return -1;
    else return 1;
}//cmp

        //-----多项式基本操作的实现-----
void CreatePolyn( polynomial &P, int m){
    //输入m项的系数和指数，建立表示一元多项式的有序链表P
    Link h, s; term e; Position q; int exp[m]; 
    int i, j;       //用于循环
    int cor;
    InitList(P);   h=GetHead(P);
    e.coef = 0.0; e.exp = m; SetCurElem(h, e);
    for(i = 1; i <= m; i++){
        do{
            cor=0;
            cout << "请输入第" << i << "项系数：";
            cin >> e.coef;
            cout << "请输入第" << i << "项指数：";
            cin >> e.exp;
            exp[i-1] = e.exp;
            for(j=0; j<i-1; j++){
                if(e.exp == exp[j]){
                    cor=1;              //若有重复指数，cor赋为1
                    cout << "请勿输入重复指数" << endl;
                }
            }   
        }while(cor);
        if(!LocateElem(P, e, q, cmp))
            OrderInsert(P, e, cmp);
    }//for
}//CreatePolyn

void DestroyPolyn(polynomial &P){
    //销毁一元多项式P
    DestroyList(P);
}

void PrintPolyn(polynomial P){
    //打印输出一元多项式P
    Link p;
    p=GetHead(P);
    cout << "项数：" << p->data.exp << endl;
    p=p->next;
    while(p){
        if(p != GetHead(P)->next) cout << "+";
        cout << p->data.coef << "x^" << p->data.exp;
        p = p->next;
    }
    if(!P.head->data.exp) cout << "0";
    cout << endl;
}

void ClearPolyn(polynomial p){
    //将一元多项式P置空
    ClearList(p);
    p.head->data.exp = 0;
    p.head->data.coef = 0.0;
}

int PolynLength(polynomial P){
    //返回一元多项式P中的项数
    return ListLength(P);
}

void AddPolyn(polynomial &Pa, polynomial &Pb){
    //完成多项式相加运算，即: Pa=Pa+Pb, 并销毁一元多项式Pb
    Link qa, qb, pa, pb;
    pa = GetHead(Pa); pb = GetHead(Pb);
    qa = NextPos(Pa, GetHead(Pa)); qb = NextPos(Pb, GetHead(Pb));
    while(qa && qb){
        if(qa->data.exp == qb->data.exp){
            // a当前指数等于b
            qa->data.coef += qb->data.coef;
            if(qa->data.coef == 0){
                // 若系数为0，删除该项
                pa->next = qa->next;
                FreeNode(qa);
                qa = pa->next;
            }
            else{
                pa = pa->next;
                qa = qa->next;
            }
            pb->next = qb->next;
            FreeNode(qb);
            qb = pb->next;
        }
        else if(qa->data.exp < qb->data.exp){
            // a当前指数小于b
            DelFirst(pb, qb);
            InsFirst(pa, qb);
            pa = qb;
            qb = pb->next;
        }
        else{
            // a当前指数大于b
            pa = pa->next;
            qa = qa->next;
        }
    }//while
    if(qb){
        // b还有剩余项
        pa->next = qb;
        Pa.tail = Pb.tail;
    }
    DestroyList(Pb);
    Pa.len = PolynLength(Pa);
    Pa.head->data.exp = Pa.len;
    cout << "结果为：" << endl;
    PrintPolyn(Pa);
}//AddPolyn

void SubstractPolyn(polynomial &Pa, polynomial &Pb){
    //完成多项式相减运算，即: Pa=Pa-Pb, 并销毁一元多项式Pb
    Link qb;
    qb = NextPos(Pb, GetHead(Pb)); 
    while(qb){
        qb->data.coef*=(-1);
        qb=NextPos(Pb, qb);
    }
    AddPolyn(Pa, Pb);
}//SubtractPolyn

float EvaluatePolyn(polynomial P, float f){
    //算出一元多项式P(x)在x=f处的值
    float sum = 0;
    Link p = NextPos(P, GetHead(P));
    while(p){
        sum += p->data.coef * pow(f, p->data.exp);
        p = NextPos(P, p);
    }
    return sum;
}//EvaluatePolyn

void DiffPolyn(polynomial &P){
    //求一元多项式P的1阶导数，若某一项求导后为0则删去该项
    Link p = NextPos(P, GetHead(P)), q;
    while(p){
        p->data.coef *= p->data.exp;
        p->data.exp -= 1;
        if(p->data.exp == -1){
            q = p;
            p = PriorPos(P, q);
            p->next = q->next;
            FreeNode(q);
        }
        p = p->next;
    }
}//DiffPolyn

void Integral(polynomial &P){
    //求一元多项式P的不定积分
    Link p = NextPos(P, GetHead(P));
    while(p){
        if(p->data.exp == -1){
            p->data.exp += 1;
            p = NextPos(P, p);
        }
        else{
            p->data.coef /= (p->data.exp + 1);
            p->data.exp += 1;
            p = NextPos(P, p);
        }
    }
}//Integral

void IntPrintPolyn(polynomial P){
    // 不定积分结果中常数项实际上应为对数
    Link p;
    p=GetHead(P);
    cout << "项数：" << p->data.exp << endl;
    p=p->next;
    while(p){
        if(p->data.exp == 0){
            if(p != GetHead(P)->next) cout << "+";
            cout << "ln" << p->data.coef;
            p = p->next;
        }
        else{
            if(p != GetHead(P)->next) cout << "+";
            cout << p->data.coef << "x^" << p->data.exp;
            p = p->next;
        }
    }
    cout << endl;
}

float IntEvalPolyn(polynomial P, float f){
    // 不定积分结果中常数项实际上应为对数
    float sum = 0;
    Link p = NextPos(P, GetHead(P));
    while(p){
        if(p->data.exp == 0){
            sum += p->data.coef * log(f);
        }
        else{
            sum += p->data.coef * pow(f, p->data.exp);
            p = NextPos(P, p);
        }
        
    }
    return sum;
}

float DefIntegral(polynomial P, float a, float b){
    //求一元多项式P在[a, b]上的定积分
    polynomial Q=P;
    Integral(Q);
    return (IntEvalPolyn(Q, b) - IntEvalPolyn(Q, a));
}//DefIntegral
