## New Cross OS tool chain CLANG9

CLANG9 tool chain is added to directly generate PE/COFF image (EFI image).
This tool chain uses LLVM clang C compiler and lld linker, generates PE/COFF
image and PDB compatible debug symbol format. Now, it supports IA32/X64 Archs.
It must use LLVM 9 or above release. LLVM 9 is ready on 
http://releases.llvm.org/download.html#9.0.0.

CLANG9 is the cross OS tool chain. It can work on Windows/Linux/Mac. 
For the same source code, with the same version LLVM tool chain, 
CLANG9 can generate the same binary image. So, the developer can 
choose the different development environment and work on the same 
code base. Besides, EDKII project build also requires third party 
tools: nasm and iasl. They both keep the same version. If so, the same 
binary image can be generated on this different OS.

LLVM tool chain provides the compiler and linker. To build EDK2 project, 
some other tools are still required. On Windows OS, nmake and Visual Studio 
are required to call Makefile and compile BaseTools C tools. 
On Linux/Mac, binutils and gcc are required to make and compile BaseTools 
C tools. Because VS or GCC are mainly used to compile BaseTools and provide 
nmake/make tool, they can keep on the stable version without update.

To build source code, CLANG9 tool chain (-t CLANG9) can be specified
on Windows OS, set CLANG_HOST_BIN=n, set CLANG9_BIN=LLVM installed directory
CLANG_HOST_BIN is used CLANG_HOST_PREFIX. Prefix n is for nmake.
For example:
*  set CLANG_HOST_BIN=n
*  set CLANG9_BIN=C:\Program Files\LLVM\bin\
*  set IASL_PREFIX=C:\Asl\

On Linux/Mac, export CLANG9_BIN=LLVM installed directory, CLANG_HOST_BIN is
not required, because there is no prefix for make.
For example:
*  export CLANG9_BIN=/home/clang9/bin/

Now, CLANG9 tool chain has been verified in Edk2 packages and Ovmf/Emulator
with LLVM 9.0.0 on Windows and Linux OS. 
OVMF IA32/X64/IA32X64 all boots to Shell on Windows and Linux OS. 
Emulator can boot to Shell on Windows only with CLANG9.
OVMF Ia32X64 RELEASE build generates the same BIOS images on Windows and Linux OS.

## Cross OS/Host Reproducible Build
We enabled the reporducible build (https://reproducible-builds.org/) recently
for edk2 MSVC and GCC/CLANG toolchains. And now we go further, CLANG9 is the first
Uefi toolchain to support "Cross OS/Host Reproducible Build", which is to generate
exactly same firmware release binary across different operating systems.
e.g. Linux, Windows. The magic behind it is the across OS llvm linker (lld).
CLANG9 is a perfect candidate for the Uefi defaut build toolchain in the future.

The "Cross OS/Host Reproducible Build" make the firmware binary to be real OS independent,
which has several significant benefits for firmware:
* Cut the validation/testing effort for different OS built bianry.
* Easily to support customer and reproduce their build or runtime failures
* Harden identical build results for firmware in different OS and make the binary 
  security to be OS independent.

To support "cross OS binary reproducible" feature, besides the above same version LLVM 9, 
please make sure to use the same version iasl compiler between different OS. E.g.

Linux:
```
~$ iasl -v
Intel ACPI Component Architecture
ASL+ Optimizing Compiler/Disassembler version 20180105
Copyright (c) 2000 - 2018 Intel Corporation
```

Windows:
```
>c:\ASL\iasl.exe -v
Intel ACPI Component Architecture
ASL+ Optimizing Compiler/Disassembler version 20180105
Copyright (c) 2000 - 2018 Intel Corporation
```

### The verbos build and run steps in Linux:
```
$ wget http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz
$ tar -xvf clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz
$ sudo apt-get install build-essential git uuid-dev iasl nasm
$ git clone https://github.com/lgao4/edk2.git edk2
$ git checkout CLANG9
$ git submodule update --init
$ make -C BaseTools/
$ source edksetup.sh
$ export CLANG9_BIN=~/Your/local/path/to/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/
$ build -p OvmfPkg/OvmfPkgIa32X64.dsc -a IA32 -a X64 -t CLANG9 -b RELEASE
$ qemu-system-x86_64 -m 5120 -smp 1 -bios ~/your/local/path/to/edk2/Build/Ovmf3264/RELEASE_CLANG9/FV/OVMF.fd -global e1000.romfile=""  -machine q35 -serial mon:stdio -display none
```

### The verbos build and run steps in Windows:
```
$ Download http://releases.llvm.org/9.0.0/LLVM-9.0.0-win64.exe and install it
$ Download Visual Studio 2015 or 2017 or 2019 and install it.
$ Download nasm compiler http://www.nasm.us/
$ Download iasl compiler https://acpica.org/downloads
$ git clone https://github.com/lgao4/edk2.git edk2
$ git checkout CLANG9
$ git submodule update --init
$ edksetup.bat Reconfig
$ edksetup.bat Rebuild
$ set CLANG_HOST_BIN=n
$ set CLANG9_BIN=C:\Program Files\LLVM\bin\
$ set IASL_PREFIX=C:\Asl\
$ build -p OvmfPkg\OvmfPkgIa32X64.dsc -a IA32 -a X64 -t CLANG9 -b RELEASE
$ qemu-system-x86_64 -m 5120 -smp 1 -bios RootDirectory\edk2\Build\Ovmf3264\RELEASE_CLANG9\FV\OVMF.fd -global e1000.romfile=""  -machine q35 -serial mon:stdio -display none
```
