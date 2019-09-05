## New CLANG9PE tool chain

CLANG9PE tool chain is added to directly generate PE/COFF image (EFI image).
This tool chain uses LLVM Clang compiler and lld linker, generates PE/COFF
image and PDB compatible debug symbol format. Now, it supports IA32/X64 Archs.
It must use LLVM 9 or above release. LLVM 9 will be released soon.
Now, LLVM 9.0.0-rc3 is ready on https://prereleases.llvm.org/9.0.0/#rc3.

CLANG9PE is the cross OS tool chain. It can work on Windows/Linux/Mac. 
For the same source code, with the same version LLVM tool chain, 
CLANG9PE can generate the same binary image. So, the developer can 
choose the different development environment and work on the same 
code base. 

LLVM tool chain provides the compiler and linker. To build EDK2 project, 
some other tools are still required. On Windows OS, nmake and Visual Studio 
are required to trig Makefile and compile BaseTools C tools. 
On Linux/Mac, binutils and gcc are required to be installed for make and 
compile BaseTools C tools. Because VS or GCC are mainly used to compile 
BaseTools and provide nmake/make tool, they can keep on the stable version 
without update.

To build source code, CLANG9PE tool chain (-t CLANG9PE) can be specified
on Windows OS, set CLANG_HOST_BIN=n, set CLANG9PE_BIN=LLVM installed directory
CLANG_HOST_BIN is used CLANG_HOST_PREFIX. Prefix n is for nmake.
For example:
*  set CLANG_HOST_BIN=n
*  set CLANG9PE_BIN=C:\Program Files\LLVM\bin\
*  set IASL_PREFIX=C:\Asl\

On Linux/Mac, export CLANG9PE_BIN=LLVM installed directory, CLANG_HOST_BIN is 
not required, because there is no prefix for make.
For example:
*  export CLANG9PE_BIN=/home/clang9/bin/

Now, CLANG9PE tool chain has been verified in Edk2 packages and Ovmf/Emulator
with LLVM 9.0.0-rc3 on Windows and Linux OS. 
OVMF IA32/X64/IA32X64 all boots to Shell on Windows and Linux OS. 
Emulator can boot to Shell on Windows only with CLANG9PE.
