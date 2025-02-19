entry
    ALLOC     x1 144
    WRITE64ii x1 0   12
    WRITE64ii x1 16 34
    WRITE64ii x1 17 34
    XOR       x2 x2 x2
    READ64    x3 x1 x2
    DUMP      x3
    ADDi      x2 x2 16
    READ64    x3 x1 x2
    DUMP      x3
    ADDi      x2 x2 1
    READ64    x3 x1 x2
    DUMP      x3
exit
    EXIT