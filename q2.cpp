#include <iostream>
#include<string.h>
#include<vector>
#include <fstream>
#include <stdio.h>
using namespace std;

int cnt;
ofstream file;
void func_nonterm(string,string,int);
void func_term(string,string,int);
void func_pipe(string,string,int);

//check for terminals
bool terminal(char s){
    if(s>='a' && s<='z'){
        return true;
    }
    else{
        return false;
    }
}

//check for non terminals
bool nonterminal(char s){
    if(s>='A' && s<='Z'){
        return true;
    }
    else{
        return false;
    }
}

void func_term(string s1,string s,int pos){

    cout<<"terminal="<<s[pos]<<" "<<"pos="<<pos<<endl;
    cnt++;
    int l=(int)s.length();
    file<<"\nif(input[k]!='\\0' && input[k]=='"<<s[pos]<<"'){\nk++;";
    if(pos<l-1){
        if(terminal(s[pos+1])){
            func_term(s1,s,pos+1);
        }
        else if(nonterminal(s[pos+1])){
            func_nonterm(s1,s,pos+1);
        }
        else{    //s[pos+1]='|'
            if(s1[0]=='S')
            {
                cout<<"********************************************************";
                 file<<"\n    if(k==l)";
            }

            func_pipe(s1,s,pos+1);
        }
    }
    if(pos==l-1)
    {
        file<<"\nreturn 1;\n";
         while(cnt--){
            file<<"}\n";
        }
        file<<"else{\nreturn 0;\n}";
    }
}

void func_nonterm(string s1,string s,int pos){
    cout<<"non-terminal="<<s[pos]<<" "<<"pos="<<pos<<endl;
    cnt++;
    int l=(int)s.length();
    file<<"if("<<s[pos]<<"()){\n";
    if(pos<l-1){
        if(terminal(s[pos+1])){
            func_term(s1,s,pos+1);
        }
        else if(nonterminal(s[pos+1])){
            func_nonterm(s1,s,pos+1);
        }
        else{
            //s[pos+1]!='|'
            if(s1[0]=='S')
            {
                cout<<"********************************************************";
                 file<<"\n    if(k==l)";
            }

            func_pipe(s1,s,pos+1);
        }
    }
    if(pos==l-1)
    {
        file<<"\nreturn 1;\n";
         while(cnt--){
            file<<"}\n";
        }
        file<<"else{\nreturn 0;\n}";
    }

}

void func_pipe(string s1,string s,int pos){
    file<<"\n      return 1;\n";
    while(cnt--){
        file<<"}\n";
    }
    cnt=0;  //after encountering '|'
    file<<"\nk=ptr;\nptr=k;\n";
    if(terminal(s[pos+1])){
        func_term(s1,s,pos+1);
    }
    else{ //if(nonterminal(str[0])){
        func_nonterm(s1,s,pos+1);
    }
}

void print_func(vector<string> v){
    string str=v[1];
    string str1=v[0];
    cout<<"left:"<<v[0]<<" "<<"right:"<<v[1]<<endl;
    cnt=0;  //count of number of symbols in a single production
    file<<"\n\nint "<<v[0]<<"(){\nint ptr=k;\n";
    if(terminal(str[0])){
        cout<<"its terminal\n";
        func_term(str1,str,0);
    }
    else{ //if(nonterminal(str[0])){
        cout<<"its non terminal\n";
        func_nonterm(str1,str,0);
    }
    file<<"\n}";
}


int main()
{

    int num,j;
    string left,right;
    file.open("output.c");
    file<<"#include<stdio.h>\n#include<string.h>\nint k=0;\nchar input[100];\nint l;";
    cout<<"Enter the number of productions :";
    cin>>num;
    vector<string> vec[num];
    cout<<"Enter the grammar, left side first then right side :"<<endl;
    j=0;
    while(j<num){
        cin>>left>>right;
        vec[j].push_back(left);
        vec[j].push_back(right);
        cout<<vec[j][0]<<" "<<vec[j][1]<<endl;
        j++;

    }
    j=0;
    while(j<num)
    {
        file<<"\nint "<<vec[j][0]<<"();";
        j++;
    }
    for(j=0;j<num;j++){
        print_func(vec[j]);
    }
    file<<"\nint main(){\n";
    file<<"scanf(\"%s\",input);\nl=strlen(input);\n";
    file<<"int val=S();\n";
    file<<"if(k==l && val==1){printf(\"success\");}\nelse{printf(\"failure\");}";
    file<<"\nreturn 0;\n}";
    file.close();
    return 0;
}
