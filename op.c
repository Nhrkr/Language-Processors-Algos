#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
int i=0;
int len=0;
 char s[100]; 
int f0() 
 {
int flag=1,j;
char comp[100]="";
for(j=0;j<1 && i+j<len;j++)
{ 
 if(comp[j]!=s[i+j]) 
 { 
 flag=0; 
 } 
 } 
if(flag==1 && i+j<=len) 
 { 
 i+=1; 
 return 1;
 } else 
 { 
 return 0;
}  
} 
 int main()
{
gets(s); 
 len=strlen(s);
 f0();
if(i==len) 
{ 
 printf("YES "); 
 } 
 else
{ 
 printf("NO  "); 
 } 
 
return 0; 
 }