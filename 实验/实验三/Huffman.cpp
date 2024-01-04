#define MAX_FILE_LENGTH 150000
#define MAX_FILENAME_LENGTH 1024
#define MAX_CHAR_NUMBER 100000

#include <iostream>
#include <string>

using namespace std;

typedef struct {
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

void Select(HuffmanTree HT, int n, int &s1, int &s2);
    // 在HT[1..n]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *weight, int n);
    // 用n个字符的权值weight构造Huffman树HT,并求出n个字符的Huffman编码HC

int ReadFile(char *filename, char *chars);
    // 从文件中逐个字节读取信息

int GetFrequency(char *chars, int *freq, char *charList, int &n);
    // 获取待处理文本字符的频率信息

void WriteCodedString(char *CodedChar, char *chars, HuffmanCode HC, char *CharList, int FLength, int CharNum);
    // 将比特流写入文件

void Decode(char *CodedChar, HuffmanCode HC, char *CharList, char *DecodedChar);
    // 根据比特流还原文件

int main(){
    int i;
    char *filename = new char[MAX_FILENAME_LENGTH];
    char *CodedChar = new char[MAX_FILE_LENGTH];
    char *DecodedChar = new char[MAX_FILE_LENGTH];
    filename = "2_2.txt";
    char *chars = new char[MAX_FILE_LENGTH];
    int FileLength = ReadFile(filename, chars);
    cout << "原始字符" << endl;%
    for(i = 1; i <= FileLength; i++){
        cout << chars[i];
    }
    cout << endl;
    int *freq = new int[MAX_CHAR_NUMBER];
    char *charList = new char[MAX_CHAR_NUMBER];
    int charNum = GetFrequency(chars, freq, charList, FileLength);
    cout << "频率信息" << endl;
    for(i=1; i <= charNum; i++){
        cout << charList[i] << '\t' << freq[i] << '\n';
    }
    HuffmanTree HT;
    HuffmanCode HC;
    HuffmanCoding(HT, HC, freq, charNum);
    WriteCodedString(CodedChar, chars, HC, charList, FileLength, charNum);
    cout << "编码后字符" << endl << CodedChar << endl;
    Decode(CodedChar, HC, charList, DecodedChar);
    cout << "编码信息" << endl;
    for(i=1; i <= charNum; i++){
        cout << charList[i] << '\t' << HC[i] << '\n';
    }
    cout << DecodedChar << '\n';
    return 0;
}

void Select(HuffmanTree HT, int n, int &s1, int &s2) {
    s1 = 0;
    s2 = 0; 
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0) {
            if (s1 == 0 || HT[i].weight < HT[s1].weight) {
                s1 = i;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0 && i != s1) {
            if (s2 == 0 || HT[i].weight < HT[s2].weight) {
                s2 = i;
            }
        }
    }
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *weight, int n){
   int i;
    HuffmanTree p;
    if (n <= 1) return;
    int m = 2 * n - 1;
    HT = new HTNode[m + 1];
    for (p=HT, i=1; i<=n; ++i, ++p, ++weight) {   // 初始化前n个结点
        p->weight = *weight;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }
    for ( ; i <= m; ++i, ++p) {
        p->weight = 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }
    for(i=n+1; i<=m; ++i) { // 建赫夫曼树
        int s1, s2;
        Select(HT, i-1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    HC = new char*[n + 2]; // 分配n个字符编码的头指针向量
    char *cd = new char[n]; // 分配求编码的工作空间
    cd[n - 1] = '\0'; // 编码结束符
    for(i=1; i<=n; i++){
        int start = n - 1;
        for(int c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent){
            if(HT[f].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';
        }
        HC[i] = new char[n - start];
        strcpy(HC[i], &cd[start]);
    }
    HC[n+1] = new char[1];
    *HC[n+1] = '\0'; 
    free(cd);
}

int ReadFile(char *filename, char *chars){
    int n = 0;
    char *buf = new char;
    FILE *f = fopen(filename, "r");
    while((*buf = fgetc(f)) != EOF){
        n++;
        chars[n] = *buf;
    }
    chars[n+1] = '\0';
    return n;
}

int GetFrequency(char *chars, int *freq, char *charList, int &n){
    int i, j, charNum=0, check=0;
    for(i=1; i<=n; i++){
        check = 0;
        for(j=1; j<=charNum; j++){
            if(chars[i]==charList[j]){
                freq[j] += 1;
                check = 1;
                break;
            }
        }
        if(!check){
            charList[j] = chars[i];
            freq[j] = 1;
            charNum++;
        }
    }
    return charNum;
}

void WriteCodedString(char *CodedChar, char *chars, HuffmanCode HC, char *CharList, int FLength, int CharNum){
    int i, j;
    for(i=1; i<=FLength; i++){
        for(j=1; j<=CharNum; j++){
            if(chars[i] == CharList[j]){
                strcat(CodedChar, HC[j]);
            }
        }
    }
    CodedChar[strlen(CodedChar)] = '\0';
}

void Decode(char *CodedChar, HuffmanCode HC, char *CharList, char *DecodedChar){
    int i, j, k=0;
    char *target = new char[2];
    target[1] = '\0';
    char *buf1 = new char[20];
    char *buf2 = new char[2];
    buf2[1] = '\0';
    for(i=0; i<strlen(CodedChar); i++){
        buf2[0] = CodedChar[i];
        strcat(buf1, buf2);
        for(j=1; j<=strlen(CharList+1); j++){
            if(!strcmp(buf1, HC[j])){
                target[0] = CharList[j];
                strcat(DecodedChar, target);
                buf1[0] = '\0';
            }
        }
    }

}
