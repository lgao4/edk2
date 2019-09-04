# EDK II Project

CLANG7WIN tool chain supports cross host machines. It depends on LLVM9
LLVM9 rc3 release is ready https://prereleases.llvm.org/9.0.0/#rc3

CLANG7WIN tool chain is added to generate PE image
On Windows OS, set CLANG_HOST_BIN=n, set CLANG9_BIN=LLVM installed directory
CLANG_HOST_BIN is used CLANG_HOST_PREFIX. Prefix n is for nmake.
For example:
*  set CLANG_HOST_BIN=n
*  set CLANG7WIN_BIN=C:\Program Files\LLVM\bin\
*  set IASL_PREFIX=C:\Asl\

On Linux/Mac, export CLANG9_BIN=LLVM installed directory, CLANG_HOST_BIN is 
not required, because there is no prefix for make.
For example:
*  export CLANG7WIN_BIN=/home/clang9/bin/
