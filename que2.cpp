#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("i1.txt");
	fout.open("generated1.c");
	char lhs,t;
	int i;
	fin>>t;
	fin.close();
	fin.open("i1.txt");
	string rhs,text,text1,text2,line,term;
	fout<<"#include<stdio.h>\nint i=0,ans;\nchar a[100];\n";
	while(getline(fin,line))
	{
		//clearing error flags
		rhs.clear();
		text1.clear();
		text.clear();
		term.clear();
		
		lhs=line[0];
		rhs=line.substr(2,line.length()-1);
		i=0;
		while(rhs[i]!='\0')
		{
            text.append("if( ");
			while(rhs[i]!='|' && rhs[i]!='\0')
			{
				//non terminal--call that function
				if(isupper(rhs[i]))
				{
					text.append(string(1,rhs[i]) +"() && ");
				}
				//terminal--append
				else if(islower(rhs[i]))
				{
					term = term + string(1,rhs[i]);
					text.append("(a[i++]=='" + string(1,rhs[i]) + "') && ");
				}
				i++;
			}
			text.append("1)\nreturn 1;\ni=k;\n");
			if(rhs[i]=='|')
                i++;
		}
		if(rhs.find("~")!=string::npos)
		{
			text1="if(a[i]!='" + string(1,term[0]) + "'){ return 1; } else { " + text + "return 0;\n }";
			fout<<line[0]<<"()\n{\nint k=i;\n"+ text1 +" \n}\n";
		}
		else
		{
			fout<<line[0]<<"(){ \nint k=i;\n "<< text <<" return 0;\n}\n";
		}
	}
	fin.close();
	fout<<"\nmain()\n{\ngets(a);\nans = "<<string(1,t)<<"();\nif(ans)\nprintf("<<"\"Success\""<<");\nelse\nprintf("<<"\"Failed\""<<");\n}";
	fout.close();

}
