def gcd(int a,int b):
	if b==0:
		return a
	else:
		return gcd(b,a%b)

t=input()
for tt in range(0,t):
	a=input()
	b=input()
	c=input()
	d=input()
	a*=b,
	c*=d
	g=gcd(a,c)
	print("1/"+a*c//g+" "+"1/"+g)

