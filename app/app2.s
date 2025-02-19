entry
  ALLOC x1 288
  ALLOC x2 1048576
  XOR x0 x0 x0
  ADDi x0 x0 1
  XOR x14 x14 x14
  ADDi x14 x14 256
  XOR x15 x15 x15
  ADDi x15 x15 512
entry_fill_framebuffer
  WRITE64ii x1 0  4278650631
  WRITE64ii x1 1  4280223495
  WRITE64ii x1 2  4281274119
  WRITE64ii x1 3  4282846983
  WRITE64ii x1 4  4283897607
  WRITE64ii x1 5  4284948231
  WRITE64ii x1 6  4285996807
  WRITE64ii x1 7  4287571719
  WRITE64ii x1 8  4288622343
  WRITE64ii x1 9  4289675015
  WRITE64ii x1 10 4290725639
  WRITE64ii x1 11 4291249927
  WRITE64ii x1 12 4292824839
  WRITE64ii x1 13 4292826887
  WRITE64ii x1 14 4292826887
  WRITE64ii x1 15 4292304647
  WRITE64ii x1 16 4292304647
  WRITE64ii x1 17 4292306703
  WRITE64ii x1 18 4291784463
  WRITE64ii x1 19 4291786511
  WRITE64ii x1 20 4291788559
  WRITE64ii x1 21 4291790615
  WRITE64ii x1 22 4291266327
  WRITE64ii x1 23 4291268375
  WRITE64ii x1 24 4291270431
  WRITE64ii x1 25 4290748191
  WRITE64ii x1 26 4290748191
  WRITE64ii x1 27 4290750247
  WRITE64ii x1 28 4290750247
  WRITE64ii x1 29 4290752303
  WRITE64ii x1 30 4290228015
  WRITE64ii x1 31 4290230063
  WRITE64ii x1 32 4290230071
  WRITE64ii x1 33 4291809135
  WRITE64ii x1 34 4292861855
  WRITE64ii x1 35 4293914567
init_fire_pixels
  XOR x3 x3 x3
init_fire_first_loop
  ADDi x5 x3 130560
  WRITE64ri x2 x5 35 
  XOR x4 x4 x4
init_fire_second_loop
  MUL x6 x4 x15
  ADD x6 x6 x3
  WRITE64ri x2 x6 0
  INC_NEi x5 x4 255
  BR_COND x5 init_fire_second_loop
b1
  INC_NEi x5 x3 512
  BR_COND x5 init_fire_first_loop
main_loop
  XOR x3 x3 x3
inner_main_loop
  XOR x4 x4 x4
  ADDi x4 x4 1
inner_inner_main_loop
  RAND x5 
  MUL  x6 x4 x15
  ADD  x6 x6 x3
  ADDi x7 x6 0
  SUB  x7 x7 x15
  ANDi x8 x5 1
  SUB  x7 x7 x8
  ADDi x7 x7 1
  READ x8 x2 x6
  EQi x9 x8 0
  BR_COND x9 color_from_eq_zero
color_from_neq_zero
  ADDi x9 x8 0
  ADDi x10 x0 1
  DIV x11 x5 x10
  ANDi x11 x11 1
  AND x11 x5 x11
  SUB x9 x9 x11
  WRITE64 x2 x7 x9
  BR_COND x0 after_eq
color_from_eq_zero
  WRITE64ri x2 x7 0
after_eq
  READ x13 x1 x8
  PUT_PIXEL x3 x4 x13
  INC_NEi x12 x4 256
  BR_COND x12 inner_inner_main_loop
b2
  INC_NEi x12 x3 512
  BR_COND x12 inner_main_loop
b3
  FLUSH
  BR_COND x0 main_loop
exit
  EXIT
