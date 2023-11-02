#include <LinkList.hpp>
#include <iostream>



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
