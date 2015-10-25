.circuit
i1 n1 GND 5
r1 n1 n2 1meg
r2 n2 GND 1meg
v2 n3 n4 5k
v1 n3 gnd 100k 
r3 n4 gnd 5k
.end

Two node problem (removing gnd)
kcl at n1: I1+(v[n1]-v[n2])/1000=0
kcl at n2: (v[n2]-v[n1]/1000 + (v[n2]-0)/1000=0

.command
dc v1 10000 100000 10000
.end
Collect terms:
v[n1]/1000   -v[n2]/1000   + I1 = 0
-v[n1]/1000  +2*v[n2]/1000 +0*I1= 0
v[n1]        +0*v[n2]      +0*I1= 5

nodes are n1(row 0), n2(row 1), gnd(dropped as node 0)
A=
+0.001 -0.001
-0.001 +0.002
 1      0

B=
1
0
0

b=
0
0
5
