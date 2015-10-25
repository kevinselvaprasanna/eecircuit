.circuit
v1 n1 GND 5k
r1 n1 n2 1meg
r2 n2 GND 1meg
.end

Two node problem (removing gnd)
kcl at n1: I1+(v[n1]-v[n2])/1000=0
kcl at n2: (v[n2]-v[n1]/1000 + (v[n2]-0)/1000=0

.command
dc v1 10m 100000m 3
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
