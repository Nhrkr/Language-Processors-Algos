import re


fo = open("foo.txt", "r")
start=0
end=0
dict1 = {}
dict2 = {}
loops=()
definitions=[]
define=()
loops_list=[]
invariants=[]
stmt_no=0
op1=()
op2=()
operator=[]

for line in fo:
	stmt_no=stmt_no+1
	matchObj = re.match( r'(.*):(.*)', line)
	if matchObj:
		dict1[matchObj.group(1)]=stmt_no
		dict2[stmt_no]= matchObj.group(2)
	else:
 		dict2[stmt_no]=line
fo.close()
fo=open("foo.txt","r")
stmt_no=0
for line in fo:
	stmt_no=stmt_no+1
	matchObj = re.match( r'(.*)goto (.*)', line)
	if matchObj:
		loops=(stmt_no,dict1[matchObj.group(2)])
		loops_list.append(loops)

fo.close
fo=open("foo.txt","r")
i=0
for line in fo:
	i=i+1
	matchObj=re.match(r'(.*)=(.*?)',dict2[i])
	if matchObj:
		define=(matchObj.group(1),i)
		definitions.append(define)
for item in loops_list:
	start=item[1]
	end=item[0]
	init_start=start
	while(start<=end):
		matchObj=re.match(r'^([a-zA-Z0-9_]+) *= *([a-zA-Z0-9_]+) *[+-/*]? *([a-zA-Z0-9_]*)',dict2[start])
		if matchObj:
			op1=(matchObj.group(2),i)
			op2=(matchObj.group(3),i)
			operator.append(op1)
			operator.append(op2)
			if matchObj.group(2).isdigit() and matchObj.group(3).isdigit():
				print(matchObj.group(2),",",matchObj.group(3))
				invariants.append(dict2[start])
			if matchObj.group(2).isalpha() and matchObj.group(3).isdigit():
			    flag=0
			    for item1 in definitions:
			    	if(item1[0]==matchObj.group(2)):
			    		if(item1[1]<end and item1[1]>init_start):
			    			flag=1
			    if flag==0:
			    	invariants.append(dict2[start])
			if matchObj.group(3).isalpha() and matchObj.group(2).isdigit():
			    flag=0
			    for item1 in definitions:
			    	if(item1[0]==matchObj.group(3)):
			    		if(item1[1]<end and item1[1]>init_start):
			    			flag=1
			    if flag==0:
			    	invariants.append(dict2[start])
			if matchObj.group(3).isalpha() and matchObj.group(2).isalpha():
			    flag=0
			    for item1 in definitions:
			    	if(item1[0]==matchObj.group(3)):
			    		if(item1[1]<end and item1[1]>init_start):
			    			flag=1
			    	if(item1[0]==matchObj.group(2)):
			    		if(item1[1]<end and item1[1]>init_start):
			    			flag=1
			    if flag==0:
			    	invariants.append(dict2[start])

		start=start+1
print("The loop invariants are:",invariants)


