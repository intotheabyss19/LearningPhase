import math as m
while True:
    v=int(input("Enter value of Vs: "))
    p0=2*3.14159*v/5
    p=p0/5.545
    l=m.log10(p)
    if v==0:
        break
    print("Po is: ",p0)
    print("P is: ",p)
    print("log10(p) is: ",l)