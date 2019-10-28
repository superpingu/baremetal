#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Génère un fichier gamma.c, directement incluable dans un fichier c,
qui donne une table de correction gamma adaptée aux ColorShield d'ELEC223.
"""


import math

GAMMA = 1.7

def gamma_table(gamma):
    planes = 8
    maxval = (1 << planes) - 1;
    l=[]
    l.append(0)
    for i in range(255):
        v = pow(float(i+1) / 255.0, GAMMA) * (float(maxval) + 0.5)
        v = int(math.ceil(v))
        if v==0x100:
            v = 0xff
        l.append(v)
    return l

def main():
    l = gamma_table(GAMMA)
    fout = open("gamma.js", "wb")
    fout.write("module.exports = [\n\t");
    for i in range(256):
        fout.write("0x%02x"%(l[i]))
        if i < 255:
            if (i&7) == 7:
                fout.write(", \n\t")
            else:
                fout.write(", ")
    fout.write("];\n");
    fout.close()


if __name__ == "__main__":
    main()
