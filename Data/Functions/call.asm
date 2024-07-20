// {0} -> the return address
// {1} -> nARgs
// {2} -> functionName
// save return address
@{0}
D=A
@SP
AM=M+1
A=A-1
M=D

// save LCL address 
@LCL
D=M
@SP
AM=M+1
A=A-1
M=D


// save ARG address 
@ARG
D=M
@SP
AM=M+1
A=A-1
M=D


// save THIS address 
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D


// save THAT address 
@THAT
D=M
@SP
AM=M+1
A=A-A1
M=D

// Update ARG Value
@SP
D=M
@5
D=D-A
@{1} // n
D=D-A
@ARG
M=D

// Update LCL Value
@SP
D=M
@LCL
M=M

// JUMP to function unconditionally
@{2}
0; JMP

({0}) // A label to come back to later

