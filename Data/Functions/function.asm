// {0} -> nArgs
// {1} -> functionName
@{0}
D=A
@R13
M=D


({1}.initialization)
  // check if it's over
  @R13
  D=M
  @{1}
  D;JEQ

  // Push 0 to SP-N
  @SP
  D=M
  @R13
  A=D-M
  M=0

  // n--
  @R13
  M=M-1

  // Jump back to {1}.initailzation
  @{1}.initialization
  0;JMP

({1})

