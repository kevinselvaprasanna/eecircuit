*SPICE circuit <filter1a> from XCircuit v3.7 rev 55

L1 1 2 80.96u
L2 2 3 80.96u
R1 3 GND 4k
C1 2 GND 2.485p
R2 in 1 4.0meg
V1 in GND 0 ac 37
.end


.command
ac V1 1000000000m 100000000000000m 1
.end
