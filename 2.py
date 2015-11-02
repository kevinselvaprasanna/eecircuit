from pylab import *
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad

def f(t):
	return 1.0/(1.0+t*t)
print f(2)
f=np.vectorize(f)

x=np.arange(0,5.1,0.1)
plt.plot(x,f(x),"ro")
plt.title(r"Plot of $1/(1+t^{2})$") # Setting the title of the graph
plt.xlabel(r"$t$") # Setting the X-label 
plt.ylabel(r"$1/(1+t^{2})$") # Setting the Y-label
show()
intvalue = []
interr=[]
qerror = []
arctan =[]
y=[]
quadv=np.vectorize(quad)
intvalue,qerror = quadv(f,0,x)
arctan = np.arctan(x)
plt.plot(x,intvalue)
plt.plot(x,arctan,"ro")
plt.title(r"Plot of $arctan(x)$ v/s $x$") # Setting the title of the plot
plt.xlabel(r"$x$") # Setting the X-label
plt.ylabel(r"$\int du/(1+x{2})$") # Setting the Y-label
plt.legend(("quad f",r"$arctan(x)$")) # Setting the Legend for the plot
show()
interr = abs(intvalue-arctan)
plt.semilogy(x,interr,"ro")
plt.title(r"Error in $\int dx/(1+x^{2})$") # Setting the title of the plot
plt.xlabel(r"$x$") # Setting the X - label
plt.ylabel("Error") # Setting the Y-label
show()

def ftrap(x):
	h = (max(x)-min(x))/(2*(len(x)-1))
	x = np.arange(min(x),max(x),h)
	y = (np.cumsum(f(x),dtype=float) - ((1.0/2.0)*(f(0)+f(x))))*h
	return (x,y)


eser=[]
h=0.1
hval =[]
hval.append(h)
trueer=[]
yprev = (np.cumsum(f(x),dtype=float)-((1.0/2.0)*(f(0)+f(x))))*h
trueer.append(max(abs(yprev-np.arctan(x))))
eser.append(1.0)
er=[1]
while(max(er)>1e-8):
	er=[]
	trueer.append(max(abs(yprev-np.arctan(x))))
	x,y = ftrap(x)
	h=h/2
	hval.append(h)
	for k in range((len(x)-1)/2):
		er.append(y[2*k] - yprev[k])
	eser.append(max(er))
	yprev=y
	print max(er)
	
plt.loglog(hval,eser,"ro")
plt.loglog(hval,trueer,"bo")
plt.xlabel(r"$log$ $h$") # Setting the X-label
plt.ylabel(r"Error ($log$ $err$)") # Setting the Y-label
plt.title(r"$log$ - $log$ plot of $Error$ v/s $h$") # Setting the title of the plot
plt.legend(("Estimated Error","Exact Error"))
show()
	
	
