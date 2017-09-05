import re
inn={}                         
out={}
fin={}                         
fout={}
kill={}
gen={}
use={}
deff={}
label={}                        
pre={}                         
succ={}                         
fwd={}                         
var={}                          
fold={}                        
with open("que.c",'r') as filee :
    i=1
    none=[]
    for line in filee :
        if ';' in line and 'int ' not in line :
            l=line
                
            if i==1 :
                pre[i]=[]
            else :
                if not('goto' in prev and 'if' not in prev) :
                    pre[i]=[str(i-1)]

            if ':' in l :                          
                temp_label=(l.split(':'))[0]
                label[temp_label]=i
                if temp_label in fwd.keys() :      
                    if i in pre.keys() :
                        pre[i]=pre[i]+fwd[temp_label]
                    else :
                        pre[i]=fwd[temp_label]

                    temp=fwd[temp_label][0]
                    if temp in succ.keys() :
                        succ[temp]=succ[temp]+[str(i)]
                    else :
                        succ[temp]=[str(i)]
                        
                    del fwd[temp_label]             

            if not('goto' in l and 'if' not in l):
                succ[i]=[str(i+1)]
                    
            if 'goto ' in l :                  
                temp_label=((l.split('goto '))[1]).split(';')[0]
                if temp_label not in label.keys() :          
                    if temp_label in fwd.keys() :
                        fwd[temp_label]=fwd[temp_label]+[str(i)]
                    else :
                        fwd[temp_label]=[str(i)]
                else :                                        
                    jmp_i=label[temp_label]
                    if pre[jmp_i]==[] :
                        pre[jmp_i]=[str(i)]
                    else :
                        pre[jmp_i]=pre[jmp_i]+[str(i)]

                    if i in succ.keys():
                        succ[i]=succ[i]+[str(jmp_i)]
                    else :
                        succ[i]=[str(jmp_i)]

            if i not in pre.keys() :                       
                pre[i]=[]

            inn[i]=[]
            out[i]=[]
            fin[i]=[]
            fout[i]=[]

            if '=' in line :
                #temp=re.split(r'[^A-Za-z]' , line.lstrip())
                #temp=filter(None,temp)
                temp_line=line
                if ':' in line :
                    temp_line=line.split(':')[1]
                temp=re.findall('[_a-z][_a-z0-9]*',temp_line, re.I)     
                temp_def=re.search('([_a-z]*)=',temp_line)              
                deff[i]=[temp_def.group(1)]
                temp.remove(temp_def.group(1))                          
                var[deff[i][0]]='null'
                if not temp :
                    use[i]=[]
                    var[deff[i][0]]=(temp_line.split('=')[1]).split(';')[0]
                else :
                    use[i]=temp
                kill[i]=[]
                gen[i]=[i]
            elif 'if' in line :
                temp_line=line
                if ':' in line :
                    temp_line=line.split(':')[1]
                deff[i]=[]
                temp=re.search('[a-z][a-z]\(([a-z0-9])[<>=]*([a-z0-9])\)',temp_line)
                use[i]=[]
                if not temp.group(1).isdigit() :
                    use[i]=[temp.group(1)]
                if not temp.group(2).isdigit() :
                    use[i]=use[i]+[temp.group(2)]
                kill[i]=[]
                gen[i]=[]
            elif 'return' in line :
                temp_line=line
                if ':' in line :
                    temp_line=line.split(':')[1]
                temp=re.search('return\s([a-z]);',temp_line)
                if temp:
                    use[i]=[temp.group(1)]
                else :
                    use[i]=[]
                deff[i]=[]
                gen[i]=[]
                kill[i]=[]
            #print(var)
            fold[i+1]=dict(var)
            i=i+1
            
        elif ';' in line and 'int' in line :                                  
            temp=line.split('int ')
            temp=temp[1].split(';')[0]
            temp=temp.split(',')
            for x in temp :
                var[x]='null'
            fold[1]=var
        prev=line
    succ[i-1]=none
#print(label)
#print(fold)
print('pre and succ')
print(pre)
print(succ)
print('use and def')
print(use)
print(deff)
print('in and out for live variable')
for k in range(1,3):                                                            
    for j in range(i-1,0,-1) :
        p=succ[j]
        for x in p :
            out[j]=list(set(out[j]+inn[int(x)]))
        inn[j]=list(set(out[j])-set(deff[j]))
        inn[j]=list(set(inn[j]+use[j]))

print(inn)
print(out)

for j in range(1,i) :                                                          
    if gen[j] :
        v=deff[j][0]
        for k in range(1,i) :
            if v in deff[k] :
                kill[j]=kill[j]+[k]
        kill[j].remove(j)
print('gen and kill')
print(gen)
print(kill)
print('in and out for constant folding')
for k in range(1,5):                                                            # data flow analysis
    for j in range(1,i) :
        p=pre[j]
        for x in p :
            fin[j]=list(set(fin[j]+fout[int(x)]))
        fout[j]=list(set(fin[j])-set(kill[j]))
        fout[j]=list(set(fout[j]+gen[j]))
    print('iteration')
    print(fin)
    print(fout)

output1=open("ans1.c",'w')                                                      # output to file by replacing constant
with open("que.c",'r') as filee :
    j=1;
    for line in filee :
        if ';' in line and 'int ' not in line and j<i :
            temp_line=line   
            for x in use[j] :
                for k in fin[j]:
                    if fold[k][x]!='null' :
                        temp_line=temp_line.replace(x,fold[k][x])

            output1.write(temp_line)
            j=j+1
        else :
            output1.write(line)

output1.close()
output2=open("ans2.c",'w')
with open("ans1.c",'r') as filee :                                        # output to file removing dead variables
    j=1;
    for line in filee :
        if ';' in line and 'int ' not in line and j<i :
            temp=deff[j]
            if temp:
                if temp[0] in out[j]:
                    output2.write(line)
            else :
                output2.write(line)
            j=j+1
        else :
            output2.write(line)
                
output2.close()

