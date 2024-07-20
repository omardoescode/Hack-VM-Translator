  @LCL
  D=M
  @R13 // endFrame
  M=D

  @R13
  D=M
  @5
  D=D-A
  
  A=D
  D=M

  @R14 // retAddr
  M=D
  
  // Push return value to argument 0
  @SP
  A=M-1 
  D=M

  @ARG
  A=M
  M=D

  // SP = ARG + 1
  @ARG
  D=M+1

  @SP
  M=D
  
  // THAT=*(end_frame - 1)
  @R13
  A=M-1
  D=M

  @THAT
  M=D


  // THIS=*(end_frame - 2)
  @R13
  D=M
  @2
  D=D-A
  A=D
  D=M
  @THIS
  M=D

  // ARG=*(end_frame - 3)
  @R13
  D=M
  @3
  D=D-A
  A=D
  D=M
  @ARG
  M=D


  // LCL=*(end_frame - 4)
  @R13
  D=M
  @4
  D=D-A
  A=D
  D=M
  @LCL
  M=D

  @R14
  0;JMP

