#include<iostream>
using namespace std;

int mynext[100];

int main(){
    string S,T;
    S = "BBC ABCDAB ABCDABCDABDE";
    T = "ABCDABD";
    int k=-1;//前面那个字串的前后缀重合的个数
    int j=0;
    mynext[0]=-1;
    while(j<T.size()){
        if(k==-1||T[k]==T[j]){
            k++;
            j++;
            mynext[j]=k;
        }else{
            k=mynext[k];
        }
    }

    int i=0;
    j=0;
    while(i<=S.size()){
        if(j==-1||S[i]==T[j]){//如果没有判断j和-1会死循环
            i++;
            j++;
            if(j==T.size()){
                cout<<i-j<<endl;
            }
        }
        else{
            j=mynext[j];
        }
    }
}
