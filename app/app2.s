entry
  ALLOC x1 144
  ALLOC x2 524288
  XOR x0 x0 x0
  ADDi x0 x0 1
  XOR x14 x14 x14
  ADDi x14 x14 256
  XOR x15 x15 x15
  ADDi x15 x15 512
entry_fill_framebuffer
  WRITEi x1 0   4278650631
  WRITEi x1 4   4280223495
  WRITEi x1 8   4281274119
  WRITEi x1 12  4282846983
  WRITEi x1 16  4283897607
  WRITEi x1 20  4284948231
  WRITEi x1 24  4285996807
  WRITEi x1 28  4287571719
  WRITEi x1 32  4288622343
  WRITEi x1 36  4289675015
  WRITEi x1 40  4290725639
  WRITEi x1 44  4291249927
  WRITEi x1 48  4292824839
  WRITEi x1 52  4292826887
  WRITEi x1 56  4292826887
  WRITEi x1 60  4292304647
  WRITEi x1 64  4292304647
  WRITEi x1 68  4292306703
  WRITEi x1 72  4291784463
  WRITEi x1 76  4291786511
  WRITEi x1 80  4291788559
  WRITEi x1 84  4291790615
  WRITEi x1 88  4291266327
  WRITEi x1 92  4291268375
  WRITEi x1 96  4291270431
  WRITEi x1 100 4290748191
  WRITEi x1 104 4290748191
  WRITEi x1 108 4290750247
  WRITEi x1 112 4290750247
  WRITEi x1 116 4290752303
  WRITEi x1 120 4290228015
  WRITEi x1 124 4290230063
  WRITEi x1 128 4290230071
  WRITEi x1 132 4291809135
  WRITEi x1 136 4292861855
  WRITEi x1 140 4293914567
init_fire_pixels
  XOR x3 x3 x3
init_fire_first_loop
  ADDi x5 x3 130560
  WRITEri x2 x5 35 
  XOR x4 x4 x4
init_fire_second_loop
  MUL x6 x4 x15
  ADD x6 x6 x3
  WRITEri x2 x6 0
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
  WRITE x2 x7 x9
  BR_COND x0 after_eq
color_from_eq_zero
  WRITEri x2 x7 0
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
