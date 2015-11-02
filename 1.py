import sys
import re
if len(sys.argv)<2:
	print "usage: 1.py filename"
	sys.exit(1)
with open(sys.argv[1],'r') as f:
	lines = f.readlines()
	start = False
name = []
node1 = []
node2 = []
value = []
v = []
node = {'GND': 0}
i=1
c=0
for l in lines:
	words = l.split()
	if (len(words)>0):
		if (words[0]==".circuit"):
			start = True
			continue
	if (len(words)>0):
			if (words[0]==".end"):
				start = False
	if(start):
		 name.append(words[0])
		 node1.append(words[1])
		 node2.append(words[2])
		 value.append(words[3])
		 c=c+1
		 k = re.search("^([+-]?[0-9]*[\.]?[0-9]*)(e[+-]?[0-9]*)?(.*)",words[3])
		 #print k.groups()
		 if(k.groups()[2]=='k'):
		 	v.append(float(k.groups()[0])*1000)
		 else:
		 	 if(k.groups()[2]=='meg'):
		 		v.append(float(k.groups()[0])*1000000)
		 	 else:
		 		if(k.groups()[2]=='m'):
		 				v.append(float(k.groups()[0])*0.001)
		 		else:
		 			if(k.groups()[2]=='u'):
		 					v.append(float(k.groups()[0])*0.000001)
		 			else:
		 					v.append(float(k.groups()[0]))
		 if(words[1] not in node):
		 	node[words[1]]=i
		 	i=i+1
		 if(words[2] not in node):
		 	node[words[2]]=i
		 	i=i+1
# print name
# print node1
# print node2
# print value
# print v
# print node
for a in range(0,c):
	print name[a] + " " + str(node[node1[a]]) + " " + str(node[node2[a]]) + " " + str(v[a])
for a in range(0,i):
	for n in node:
		if(node[n]==a):
			print str(a) + " : " + n;


