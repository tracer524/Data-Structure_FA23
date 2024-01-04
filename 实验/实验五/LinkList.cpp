#ifndef LINKLIST_CPP
#define LINKLIST_CPP
#include "LinkList.hpp"
#include <iostream>

Status LNode::MakeNode(ElemType e){
    //分配由 p 指向的值为 e 的结点，并返回 OK；若分配失败，则返回 ERROR
    data = e;
    next = NULL;
    return OK;
}//MakeNode

Status LNode::SetCurElem(ElemType e){
    //已知 p 指向线性链表中的一个结点，用 e 更新 p 所指结点中数据元素的值
    data = e;
    return OK;
}//SetCurElem

ElemType LNode::GetCurElem(){
    //已知 p 指向线性链表中的一个结点，返回 p 所指结点中数据元素的值
    return data;
}//GetCurElem

Status LinkList::InitList(){
    //初始化一个空的线性链表 L
    head = tail = (Link)malloc(sizeof(Link));
    if(!head) exit(OVERFLOW);
    head->next = NULL;
    len = 0;
    return OK;
}//InitList

Status LinkList::DestroyList(){
    //销毁一个线性链表 L，L不再存在
    Link q;
    while(head){
        q = head->next;
        free(head);
        head = q;
    }
    len = 0;
    return OK;
}//DestroyList

Status LinkList::ClearList(){
    //将线性链表 L 重置为空表，并释放原链表的结点空间
    Link p = head, q=p->next;
    while(q){
        p = q->next;
        free(q);
        q=p;
    }
    head->next = NULL;
    tail = head;
    len = 0;
    return OK;
}//ClearList

Status LinkList::InsFirst(Link s){
    //已知 h 指向线性链表的头结点，将 s 所指结点插入在第一个结点之前
    s->next = head->next;
    head->next = s;
    return OK;
}//InsFirst

Status LinkList::DelFirst(Link &q){
    //已知 h 指向线性链表的头结点，删除链表中的第一个结点并以 q 返回
    q = head->next;
    head->next = q->next;
    return OK;
}//DelFirst

Status LinkList::Append(Link s){
    //将指针 s 所指(彼此以指针相链)的一串结点链接在线性链表 L 的最后一个结点之后，
    //  并改变链表 L 的尾指针指向新的尾结点
    s->next = NULL;
    if(!tail) tail = s;
    else tail->next = s;
    tail = s;
    len++;
    return OK;
}//Append

Status LinkList::Remove(Link &q){
    //删除线性链表 L 中的尾结点并以 q 返回，改变链表 L 的尾指针指向新的尾结点
    q = tail;
    tail = q->next;
    delete q;
    len--;
    return OK;
}//Remove

Status LinkList::InsBefore(Link &p, Link s){
    //已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之前，
    //  并修改指针 p 指向新插入的结点
    Link q = PriorPos(p);
    if(!q) return ERROR;
    s->next = p;
    q->next = s;
    p = s;
    len++;
    return OK;
}//InsBefore

Status LinkList::InsAfter(Link &p, Link s){
    //已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之后，
    //  并修改指针 p 指向新插入的结点
    s->next = p->next;
    p->next = s;
    len++;
    return OK;
}//InsAfter


Status LinkList::ListEmpty(){
    //若线性链表 L 为空表，则返回 TRUE，否则返回 FALSE
    if(head == NULL) return TRUE;
    else return FALSE;
}//ListEmpty

int LinkList::ListLength(){
    //返回线性链表 L 中元素个数
    int i=0; Link p = head;
    while(p->next){
        i++;
        p = p->next;
    }
    return i;
}//ListLength

Position LinkList::GetHead(){
    //返回线性链表 L 中头结点的位置
    return head;
}//GetHead

Position LinkList::GetLast(){
    //返回线性链表 L 中最后一个结点的位置
    return tail;
}//GetLast

Position LinkList::PriorPos(Link p){
    //  已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接前驱的位置，
    //  若无前驱，则返回 NULL
    Link q = head;
    if(q == p) return NULL;
    while(q && q->next != p) q = q->next;
    return q;
}//PriorPos

Position LinkList::NextPos(Link p){
    //已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接后继的位置，
    //  若无后继，则返回 NULL
    if(!p->next) return NULL;
    return p->next;
}//NextPos

Status LinkList::LocatePos(int i, Link &p){
    //返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK，i 值不合法时返回 ERROR
    int j;
    if(i < 1 || i > len) return ERROR;
    p = head;
    for(j = 1; j < i; j++) p = p->next;
    return OK;
}//LocatePos

Status LinkList::LocateElem(ElemType e, Position &q, Status(*compare)(ElemType, ElemType)){
    //  若有序链表 L 中存在与 e 满足判定函数 compare() 取值为0的元素，则 q 指示
    //  L 中第一个值为 e 的结点的位置，并返回 TRUE；否则 q 指示第一个与 e 满足判定函数
    //  compare() 取值>0 的元素的前驱的位置。并返回 FALSE
    Link p = head->next;
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

Status LinkList::ListTraverse(Status (*visit)(ElemType)){
    //依次对 L 的每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
    //  若 visit() 成功，则操作成功
    Link p = head;
    while(p){
        if(!visit(p->data)) return ERROR;
        p = p->next;
    }
    return OK;
}//ListTraverse

Status PrintElem(ElemType elem){
    std::cout << elem << " ";
    return OK;
}

#endif