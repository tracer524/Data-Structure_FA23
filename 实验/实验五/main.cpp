#include <iostream>
#include <fstream>
#include <string>

# define TRUE       1
# define FALSE      0
# define OK         1
# define ERROR      0
# define INFEASIBLE -1
# define OVERFLOW   -2
# define N          1000

using namespace std;

typedef int Status;

typedef int ElemType;

class LNode{  // 结点类型
    public:
        ElemType        data;
        struct LNode    *next;
        Status MakeNode(ElemType e);
            //  分配由 p 指向的值为 e 的结点，并返回 OK；若分配失败，则返回 ERROR
        Status SetCurElem(ElemType e);
            //  已知 p 指向线性链表中的一个结点，用 e 更新 p 所指结点中数据元素的值
        ElemType GetCurElem();
            //  已知 p 指向线性链表中的一个结点，返回 p 所指结点中数据元素的值
};

typedef LNode *Link, *Position;

class LinkList{             // 链表类型
    public:
        Link    head, tail;     // 分别指向线性链表的头结点和最后一个结点
        int     len;            // 指示线性链表中数据元素的个数
        Status InitList();
            //  初始化一个空的线性链表 L
        Status DestroyList();
            //  销毁一个线性链表 L，L不再存在
        Status ClearList();
            //  将线性链表 L 重置为空表，并释放原链表的结点空间
        Status InsFirst(Link s);
            //  已知 h 指向线性链表的头结点，将 s 所指结点插入在第一个结点之前
        Status DelFirst(Link &q);
            //  已知 h 指向线性链表的头结点，删除链表中的第一个结点并以 q 返回
        Status Append(Link s);
            //  将指针 s 所指(彼此以指针相链)的一串结点链接在线性链表 L 的最后一个结点之后，
            //  并改变链表 L 的尾指针指向新的尾结点
        Status Remove(Link &q);
            //  删除线性链表 L 中的尾结点并以 q 返回，改变链表 L 的尾指针指向新的尾结点
        Status InsBefore(Link &p, Link s);
            //  已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之前，
            //  并修改指针 p 指向新插入的结点
        Status InsAfter(Link &p, Link s);
            //  已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之后，
            //  并修改指针 p 指向新插入的结点
        Status ListEmpty();
            //  若线性链表 L 为空表，则返回 TRUE，否则返回 FALSE
        int ListLength();
            //  返回线性链表 L 中元素个数
        Position GetHead();
            //  返回线性链表 L 中头结点的位置
        Position GetLast();
            //  返回线性链表 L 中最后一个结点的位置
        Position PriorPos(Link p);
            //  已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接前驱的位置，
            //  若无前驱，则返回 NULL
        Position NextPos(Link p);
            //  已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接后继的位置，
            //  若无后继，则返回 NULL
        Status LocatePos(int i, Link &p);
            //  返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK，i 值不合法时返回 ERROR
        Status LocateElem(ElemType e, Position &q, int(*compare)(ElemType, ElemType));
            //  若有序链表 L 中存在与 e 满足判定函数 compare() 取值为0的元素，则 q 指示
            //  L 中第一个值为 e 的结点的位置，并返回 TRUE；否则 q 指示第一个与 e 满足判定函数
            //  compare() 取值>0 的元素的前驱的位置。并返回 FALSE
        Status ListTraverse(Status (*visit)(ElemType));
            //  依次对 L 的每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
            //  若 visit() 成功，则操作成功
};

Status PrintElem(ElemType elem);

class HT_data{
    public:
        char *filename;
        int size;       // number of elements
        int mod;        
        int *key;
        Status ReadFile();
};

class HashTable_Chaining{
    public:
        HT_data data;
        LNode *links;       // list of links storing the keys
        int *func;          // value of hash fuction of keys
        LinkList *Lists;    // list of linklists in the hash table
        int *SearchLength_Succeeded;
        double ASL_Succeeded;
        int *SearchLength_Failed;
        double ASL_Failed;
        void BuildTable(HT_data FileData);
        int Hash_Chaining(int key);
        void GetSearchLength();
        int Search(int key);
        void PrintTable();
};

class HashTable_LinearProbe{
    public:
        HT_data data;
        int *table;
        int *SearchLength_Succeeded;
        double ASL_Succeeded;
        int *SearchLength_Failed;
        double ASL_Failed;
        void BuildTable(HT_data FileData);  // create a table with the given key
        int Hash_LinearProbe(int key);  // initialize HashTable 
        void GetSearchLength();
        int Search(int key);
        void PrintTable();
};

Status HT_data::ReadFile(){
    ifstream f;
    f.open(filename, ios::in);
    if(!f)  return ERROR;
    int buf[1000] = {0};
    int i = 0, j;
    key = new int[1000];
    while(f >> buf[i] && i < 1000){
        i++;
    }
    size = buf[0];
    mod = buf[i-1];
    for(j = 0; j < i-2; j++){
        key[j] = buf[j+1];
    }
    return OK;
}

void HashTable_Chaining::BuildTable(HT_data FileData){
    ASL_Succeeded = 0;
    ASL_Failed = 0;
    data = FileData;
    int i;
    Lists = new LinkList[data.mod];
    for(i=0; i<data.mod; i++){
        Lists[i].InitList();
    }
    func = new int[data.size];
    links = new LNode[data.size];
    for(i=0; i<data.size; i++){
        func[i] = Hash_Chaining(data.key[i]);
        links[i].MakeNode(data.key[i]);
        Lists[func[i]].Append(links+i);
    }
    GetSearchLength();
}

int HashTable_Chaining::Hash_Chaining(int key){
    return key % data.mod;
}

void HashTable_Chaining::GetSearchLength(){
    int i;
    SearchLength_Succeeded = new int[data.size];
    SearchLength_Failed = new int[data.mod];
    for(i=0; i<data.size; i++){
        SearchLength_Succeeded[i] = Search(data.key[i]);
        ASL_Succeeded += (double)SearchLength_Succeeded[i];
    }
    for(i=0; i<data.mod; i++){
        SearchLength_Failed[i] = Lists[i].ListLength()+1;
        ASL_Failed += (double)SearchLength_Failed[i];
    }
    ASL_Succeeded /= (double)data.size;
    ASL_Failed /= (double)data.mod;
}

int HashTable_Chaining::Search(int key){
    int count = 0;
    Link cur = Lists[Hash_Chaining(key)].head;
    while(cur->data != key){
        cur = cur->next;
        count++;
    }
    return count;
}

void HashTable_Chaining::PrintTable(){
    int i;
    cout << "哈希表地址：" << " ";
    for(i=0; i<data.mod; i++){
        cout << i << " ";
    }
    cout << endl;
    cout << "关键字：" << endl;
    for(i=0; i<data.mod; i++){
        Lists[i].ListTraverse(PrintElem);
        cout << endl;
    }
    cout << "成功查找次数：" << " ";
    for(i=0; i<data.size; i++){
        cout << SearchLength_Succeeded[i] << " ";
    }
    cout << endl;
    cout << "失败查找次数：" << " ";
    for(i=0; i<data.mod; i++){
        cout << SearchLength_Failed[i] << " ";
    }
    cout << endl;
    cout << "查找成功的平均查找次数：" << ASL_Succeeded << endl;
    cout << "查找失败的平均查找次数：" << ASL_Failed << endl;
}

void HashTable_LinearProbe::BuildTable(HT_data FileData){
    data = FileData;
    int i;
    ASL_Succeeded = 0;
    ASL_Failed = 0;
    SearchLength_Succeeded = new int[data.mod];
    SearchLength_Failed = new int[data.mod];
    table = new int[data.mod];
    for(i=0; i<data.mod; i++){
        table[i] = -1;
    }
    for(i=0; i<data.size; i++){
        table[Hash_LinearProbe(i)] = data.key[i];
    }
    ASL_Succeeded /= data.size;
    GetSearchLength();
}

int HashTable_LinearProbe::Hash_LinearProbe(int index){
    int i = 0;
    while(table[(data.key[index] + i) % data.mod] != -1){
        i++;
    }
    SearchLength_Succeeded[(data.key[index] + i) % data.mod] = i+1;
    ASL_Succeeded += (i+1);
    return (data.key[index] + i) % data.mod;
}

void HashTable_LinearProbe::GetSearchLength(){
    int i, j=0, length;
    for(i=0; i<data.mod; i++){
        while(table[(i+j) % data.mod] != -1){
            j++;
        }
        SearchLength_Failed[i] = j+1;
        j = 0;
        ASL_Failed += SearchLength_Failed[i];
    }
    ASL_Failed /= (double)data.mod;
}

void HashTable_LinearProbe::PrintTable(){
    int i;
    cout << "哈希表地址：" << " ";
    for(i=0; i<data.mod; i++){
        cout << i << " ";
    }
    cout << endl;
    cout << "关键字：" << " ";
    for(i=0; i<data.mod; i++){
        cout << table[i] << " ";
    }
    cout << endl;
    cout << "成功查找次数：" << " ";
    for(i=0; i<data.mod; i++){
        cout << SearchLength_Succeeded[i] << " ";
    }
    cout << endl;
    cout << "失败查找次数：" << " ";
    for(i=0; i<data.mod; i++){
        cout << SearchLength_Failed[i] << " ";
    }
    cout << endl;
    cout << "查找成功的平均查找次数：" << ASL_Succeeded << endl;
    cout << "查找失败的平均查找次数：" << ASL_Failed << endl;
}

int main(){
    HT_data data;
    data.filename = "hush5.txt";
    if(!data.ReadFile())    cout << "File not found." << endl;
    HashTable_Chaining HT_C;
    HT_C.BuildTable(data);
    HT_C.PrintTable();
    HashTable_LinearProbe HT_LP;
    HT_LP.BuildTable(data);
    HT_LP.PrintTable();
    return 0;
}

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
    Link p = head->next;
    if(!p)  cout << "_" << endl;
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
