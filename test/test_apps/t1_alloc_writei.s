entry
    ALLOC  x1 144
    WRITEi x1 0   12
    WRITEi x1 128 34
    WRITEi x1 136 34
    XOR    x2 x2 x2
    READ   x3 x1 x2
    DUMP   x3
    ADDi   x2 x2 16
    READ   x3 x1 x2
    DUMP   x3
    ADDi   x2 x2 1
    READ   x3 x1 x2
    DUMP   x3
exit
    EXIT