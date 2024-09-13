#zvezdochka
num=[]
s=0
u=1
v=0
a=open('input.txt')
c=a.readline(-1)
num=c.split()
z=a.readline(1)
if z=="+":
    for i in range(len(num)):
        s+=int(num[i-1])
    print(s)
if z=="-":
    v+=int(num[0])
    for i in range(len(num)-1):
        v-=int(num[i+1])
        
    print(v)
if z=="*":
    for i in range(len(num)):
        u*=int(num[i])
    print(u)
a.close()
