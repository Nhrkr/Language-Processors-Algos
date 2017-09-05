#include<stdio.h>
int main()
{
	int p,q,r,s;
	p=0;
L1: q=p+1;
	r=r+q;
	
	s=1;
	if(p<9) goto L1;
	return r;
}
