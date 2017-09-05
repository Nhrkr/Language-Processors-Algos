#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define LEN 100
int fcount=0;
ofstream fout;

int fun0(char s[LEN],int pos,int len)
{
    int ret=fcount,p1,p2;
    char s1[LEN],s2[LEN];
    fcount++;
    if(s[pos]=='+')
    {
        int len1=0,len2=0;
        pos+=2;
        int c=1;
        while(pos<len && c!=0)
        {
            s1[len1++]=s[pos++];
            if(s[pos]=='(')
            {
                c++;
            }
            else if(s[pos]==')')
            {
                c--;
            }
            if(c==0)
            {
                break;
            }
        }
        s1[len1]='\0';
        p1=fun0(s1,0,len1);

        pos+=2;
        c=1;
        while(pos<len && c!=0)
        {
            s2[len2++]=s[pos++];
            if(s[pos]=='(')
            {
                c++;
            }
            else if(s[pos]==')')
            {
                c--;
            }
            if(c==0)
            {
                break;
            }
        }
        s2[len2]='\0';
        p2=fun0(s2,0,len2);
        printf(
        "int f%d() \n "
        "{ \n "
            "if(f%d()==1 || f%d()==1) \n "
            "{ \n "
             "   return 1; \n "
            "} \n "
            "else \n "
            "{ \n "
             "   return 0; \n "
            "} \n "
        "} \n ",
        ret,p1,p2);
        
        fout<<"int f"<<ret<<"() \n { \n "
            "if(f"<<p1<<"()==1 || f"<<p2<<"()==1) \n "
            "{ \n "
             "   return 1; \n "
            "} \n "
            "else \n "
            "{ \n "
             "   return 0; \n "
            "} \n "
        "} \n ";
    }
    
    else if(s[pos]=='.')
    {
        int len1=0,len2=0;
        pos+=2;
        int c=1;
        while(pos<len && c!=0)
        {
            s1[len1++]=s[pos++];
            if(s[pos]=='(')
            {
                c++;
            }
            else if(s[pos]==')')
            {
                c--;
            }
            if(c==0)
            {
                break;
            }
        }
        s1[len1]='\0';
        p1=fun0(s1,0,len1);

        pos+=2;
        c=1;
        while(pos<len && c!=0)
        {
            s2[len2++]=s[pos++];
            if(s[pos]=='(')
            {
                c++;
            }
            else if(s[pos]==')')
            {
                c--;
            }
            if(c==0)
            {
                break;
            }
        }
        s2[len2]='\0';
        p2=fun0(s2,0,len2);
        printf(
        "int f%d() \n "
        "{ \n "
            "if(f%d()==1 && f%d()==1) \n "
            "{ \n "
             "   return 1; \n "
            "} \n "
            "else \n "
            "{ \n "
             "   return 0; \n "
            "} \n "
        "} \n",
        ret,p1,p2);
        fout<<"int f"<<ret<<"() \n "
        "{ \n "
            "if(f"<<p1<<"()==1 && f"<<p2<<"()==1) \n "
            "{ \n "
             "   return 1; \n "
            "} \n "
            "else \n "
            "{ \n "
             "   return 0; \n "
            "} \n "
        "} \n";
    }
    else if(s[pos]=='*')
    {
        int len1=0;
        pos+=2;
        int c=1;
        while(pos<len && c!=0)
        {
            s1[len1++]=s[pos++];
            if(s[pos]=='(')
            {
                c++;
            }
            else if(s[pos]==')')
            {
                c--;
            }
            if(c==0)
            {
                break;
            }
        }
        s1[len1]='\0';
        p1=fun0(s1,0,len1);

        printf(
        "\nint f%d() \n "
        "{ \n "
            "while(f%d()==1 && i<len) {} \n "
             "   return 1; \n "
        "} \n",
        ret,p1);
        fout<<"\nint f"<<ret<<"() \n "
        "{ \n "
            "while(f"<<p1<<"()==1 && i<len) {} \n "
             "   return 1; \n "
        "} \n";
    }
    else
    {
        //printf("heyyyy= %s\n",s);
       
        
        printf("int f%d() \n {\n"
        "int flag=1,j;\n"
        "char comp[100]=\"%s\";"
        "\nfor(j=0;j<%d && i+j<len;j++)"
        "\n{ \n if(comp[j]!=s[i+j]) \n { \n flag=0; \n } \n } \n"
        "if(flag==1 && i+j<=len) \n { \n i+=%d; \n return 1;\n } else \n { \n return 0;\n}  \n"
        "} \n ",
        ret,s,len,len);
        fout<<"int f"<<ret<<"() \n {\n"
        "int flag=1,j;\n"
        "char comp[100]=\""<<s<<"\";"
        "\nfor(j=0;j<"<<len<<" && i+j<len;j++)"
        "\n{ \n if(comp[j]!=s[i+j]) \n { \n flag=0; \n } \n } \n"
        "if(flag==1 && i+j<=len) \n { \n i+="<<len<<"; \n return 1;\n } else \n { \n return 0;\n}  \n"
        "} \n ";
    }
    return ret;
}
	//ifstream fin;
	
int main()
{
    int len;
    fout.open("output.cpp");
    fout<<"#include<iostream>\n#include<stdio.h>\n#include<string.h>\n#include<vector>\n#include<algorithm>\nusing namespace std;\n";
    printf("#include<iostream>\n#include<stdio.h>\n#include<string.h>\n#include<vector>\n#include<algorithm>\nusing namespace std;\n");
    fout<<"int i=0;\n";
    printf("int i=0;\n");

    char s[LEN];
    scanf("%s",s);
    len=strlen(s);
    fout<<"int len=0;\n char s[100]; \n";
    printf("int len=0;\n char s[100]; \n");
    fun0(s,0,len);
    fout<<"int main()\n{";
    printf("int main()\n{");
    //printf("scanf(\"\%\s\",s); \n len=strlen(s);");
    fout<<"\ngets(s); \n len=strlen(s);\n f0();";
    printf("\ngets(s); \n len=strlen(s);\n f0();");
    fout<<"\nif(i==len) \n";
    printf("\nif(i==len) \n");
    fout<<"{ \n printf(\"YES \"); \n } \n else\n{ \n printf(\"NO  \"); \n } \n ";
    printf("{ \n printf(\"YES \"); \n } \n else\n{ \n printf(\"NO  \"); \n } \n ");
    fout<<"\nreturn 0; \n }";
    printf("\nreturn 0; \n }");
    return 0;
}
