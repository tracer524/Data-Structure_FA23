#ifndef LINKLIST_HPP
#define LINKLIST_HPP

# define TRUE       1
# define FALSE      0
# define OK         1
# define ERROR      0
# define INFEASIBLE -1
# define OVERFLOW   -2
# define N          10

typedef int Status;

typedef int ElemType;

typedef struct LNode{  // 结点类型
    ElemType        data;
    struct LNode    *next;
}*Link, *Position;

typedef  struct LinkList{             // 链表类型
    Link    head, tail;     // 分别指向线性链表的头结点和最后一个结点
    int     len;            // 指示线性链表中数据元素的个数
}LinkList;

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

#endif