#include <iostream>
using namespace std;

int GetFrequency(char *chars, int *freq, char *charList, int &n);

int main(){
    int *freq = new int[100000];
    char *charList = new char[100000];
    char *chars = new char[500000];
    int n = 0;
    int m = 0;
    int i;
    char *buf = new char;
    FILE *f = fopen("2_4.mp4", "rb");
    while(fread(buf, sizeof(char), 1, f)){
        n++;
        chars[n] = *buf;
    }
    m = GetFrequency(chars, freq, charList, n);
    for(i=1; i<=m; i++){
        cout << charList[i] << freq[i] << endl;
    }
    return 0;
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