*SPICE circuit <filter1a> from XCircuit v3.7 rev 55

L1 1 2 80.96u
L2 2 3 80.96u
R1 3 GND 4k
C1 2 GND 2.485p
R2 in 1 4.0k
V1 in GND 0 ac 5
.end

.command
ac V1 1000 100000000 1
.end
