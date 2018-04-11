# Building SoftHSM2 for Windows

This document describes process of building both 32-bit and 64-bit versions of [SoftHSM2](https://www.opendnssec.org/softhsm/) on 64-bit Windows 10 machine.

## Required software

- [Visual Studio](https://www.visualstudio.com/vs/) (2017 Community - Version 15.5.7)
- [GNU Privacy Guard for Windows](http://www.gpg4win.org/) (3.0.3)
- [7-zip](http://www.7-zip.org/) (18.01)
- [Strawberry Perl](http://strawberryperl.com/) (5.26.1.1)
- [The Netwide Assembler](http://www.nasm.us/) (2.13.03)
- [Python](https://www.python.org/) (3.6.5)
- [Ubuntu WSL](https://www.microsoft.com/en-us/store/p/ubuntu/9nblggh4msv6) (7/10/2017)
- [Git for Windows](https://gitforwindows.org/) (2.16.3)
- [WiX Toolset](http://wixtoolset.org/) (3.11.1.2318)
- [Wix Toolset Visual Studio 2017 Extension](https://marketplace.visualstudio.com/items?itemName=RobMensching.WixToolsetVisualStudio2017Extension) (0.9.21.62588)

## Prepare working directories

    mkdir C:\build\bin\
    mkdir C:\build\src\

## Build OpenSSL 1.1.0h static library

Download [OpenSSL 1.1.0h](https://www.openssl.org/source/openssl-1.1.0h.tar.gz) with [its signature](https://www.openssl.org/source/openssl-1.1.0h.tar.gz.asc) into `C:\build\src\` directory and verify signature of the downloaded archive:

    cd C:\build\src\
    gpg --keyserver pgp.mit.edu --recv-keys 0E604491
    gpg --verify openssl-1.1.0h.tar.gz.asc openssl-1.1.0h.tar.gz

### 32-bit

Extract archive `openssl-1.1.0h.tar.gz` into `C:\build\src\openssl-1.1.0h-x86` directory:

    cd C:\build\src\
    "C:\Program Files\7-Zip\7z" x openssl-1.1.0h.tar.gz
    "C:\Program Files\7-Zip\7z" x openssl-1.1.0h.tar
    rename openssl-1.1.0h openssl-1.1.0h-x86
    del openssl-1.1.0h.tar

In a **new command line window** build OpenSSL and install it into `C:\build\bin\openssl-1.1.0h-x86` directory:

    set PATH=%PATH%;C:\nasm
	"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
    cd C:\build\src\openssl-1.1.0h-x86
	perl Configure VC-WIN32 --prefix=C:\build\bin\openssl-1.1.0h-x86 --openssldir=C:\build\bin\openssl-1.1.0h-x86\ssl no-shared
    nmake
    nmake test
    nmake install

## 64-bit

Extract archive `openssl-1.1.0h.tar.gz` into `C:\build\src\openssl-1.1.0h-x64` directory:

    cd C:\build\src\
    "C:\Program Files\7-Zip\7z" x openssl-1.1.0h.tar.gz
    "C:\Program Files\7-Zip\7z" x openssl-1.1.0h.tar
    rename openssl-1.1.0h openssl-1.1.0h-x64
    del openssl-1.1.0h.tar

In a **new command line window** build OpenSSL and install it into `C:\build\bin\openssl-1.1.0h-x64` directory:

    set PATH=%PATH%;C:\nasm
    "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    cd C:\build\src\openssl-1.1.0h-x64
	perl Configure VC-WIN64A --prefix=C:\build\bin\openssl-1.1.0h-x64 --openssldir=C:\build\bin\openssl-1.1.0h-x64\ssl no-shared
    nmake
    nmake test
    nmake install

## Build CppUnit 1.13.2 unicode library

Download [CppUnit 1.13.2](http://dev-www.libreoffice.org/src/cppunit-1.13.2.tar.gz) into `C:\build\src\` directory.

### 32-bit

Extract archive `cppunit-1.13.2.tar.gz` into `C:\build\src\cppunit-1.13.2-x86` directory:

    cd C:\build\src\
    "C:\Program Files\7-Zip\7z" x cppunit-1.13.2.tar.gz
    "C:\Program Files\7-Zip\7z" x cppunit-1.13.2.tar
    rename cppunit-1.13.2 cppunit-1.13.2-x86
    del cppunit-1.13.2.tar

To build the source code:
- Open solution `C:\build\src\cppunit-1.13.2-x86\src\CppUnitLibraries2010.sln` in Visual Studio.
- If asked to install "MFC and ATL support" choose "Skip".
- Switch solution configuration to `Release Unicode\Win32`.
- Unload all projects instead of `cppunit`.
- Right click `cppunit` project, select "Retarget projects", make sure "10.whatever" is selected as "Windows SDK Version" and "Upgrade to v141" is selected as "Platform Toolset" then confirm by clicking "OK".
- Righ click `cppunit` project, select "Properties", in "Configuration Properties > C/C++ > Code Generation" change "Runtime Library" to "Multi-threaded (/MT)".
- Rebuild the solution.

Copy the results into `C:\build\bin\cppunit-1.13.2-x86` directory:

    mkdir C:\build\bin\cppunit-1.13.2-x86\lib
    xcopy C:\build\src\cppunit-1.13.2-x86\lib C:\build\bin\cppunit-1.13.2-x86\lib /E
    mkdir C:\build\bin\cppunit-1.13.2-x86\include
    xcopy C:\build\src\cppunit-1.13.2-x86\include C:\build\bin\cppunit-1.13.2-x86\include /E

### 64-bit

Extract archive `cppunit-1.13.2.tar.gz` into `C:\build\src\cppunit-1.13.2-x64` directory:

    cd C:\build\src\
    "C:\Program Files\7-Zip\7z" x cppunit-1.13.2.tar.gz
    "C:\Program Files\7-Zip\7z" x cppunit-1.13.2.tar
    rename cppunit-1.13.2 cppunit-1.13.2-x64
    del cppunit-1.13.2.tar

To build the source code:
- Open solution `C:\build\src\cppunit-1.13.2-x64\src\CppUnitLibraries2010.sln` in Visual Studio.
- If asked to install "MFC and ATL support" choose "Skip".
- Switch solution configuration to `Release Unicode\x64`.
- Unload all projects instead of `cppunit`.
- Right click `cppunit` project, select "Retarget projects", make sure "10.whatever" is selected as "Windows SDK Version" and "Upgrade to v141" is selected as "Platform Toolset" then confirm by clicking "OK".
- Righ click `cppunit` project, select "Properties", in "Configuration Properties > C/C++ > Code Generation" change "Runtime Library" to "Multi-threaded (/MT)".
- Rebuild the solution.

Copy the results into `C:\build\bin\cppunit-1.13.2-x64` directory:

    mkdir C:\build\bin\cppunit-1.13.2-x64\lib
    xcopy C:\build\src\cppunit-1.13.2-x64\lib C:\build\bin\cppunit-1.13.2-x64\lib /E
    mkdir C:\build\bin\cppunit-1.13.2-x64\include
    xcopy C:\build\src\cppunit-1.13.2-x64\include C:\build\bin\cppunit-1.13.2-x64\include /E

## Build SoftHSM 2.4.0

Download [SoftHSM 2.4.0](https://dist.opendnssec.org/source/softhsm-2.4.0.tar.gz) with [its signature](https://dist.opendnssec.org/source/softhsm-2.4.0.tar.gz.sig) into `C:\build\src\` directory and verify signature of the downloaded archive:

    cd C:\build\src\
    gpg --keyserver pgp.mit.edu --recv-keys 4FCB0B94
    gpg --verify softhsm-2.4.0.tar.gz.sig softhsm-2.4.0.tar.gz

### 32-bit

Extract archive `softhsm-2.4.0.tar.gz` into `C:\build\src\softhsm-2.4.0-x86` directory:

    cd C:\build\src\
    "C:\Program Files\7-Zip\7z" x softhsm-2.4.0.tar.gz
    "C:\Program Files\7-Zip\7z" x softhsm-2.4.0.tar
    rename softhsm-2.4.0 softhsm-2.4.0-x86
    del softhsm-2.4.0.tar

Configure build process in a **new command line window**:

	"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
    cd C:\build\src\softhsm-2.4.0-x86\win32\
    python Configure.py enable-static-runtime with-toolset=v141 disable-debug disable-gost with-crypto-backend=openssl with-openssl=C:\build\bin\openssl-1.1.0h-x86\ with-cppunit=C:\build\bin\cppunit-1.13.2-x86\

To build the source code:
- Open solution `C:\build\src\softhsm-2.4.0-x86\win32\softhsm2.sln` in Visual Studio.
- Right click solution in "Solution Explorer", select "Retarget solution", make sure "10.whatever" is selected as "Windows SDK Version" and confirm by clicking "OK".
- Rebuild the source with `Release\Win32` solution configuration.

Verify the build by running the test programs:

    cd C:\build\src\softhsm-2.4.0-x86\win32\Release\
    cryptotest.exe
    datamgrtest.exe
    handlemgrtest.exe
    objstoretest.exe
    p11test.exe
    sessionmgrtest.exe
    slotmgrtest.exe

Copy the results into `C:\build\bin\softhsm-2.4.0-x86` directory:

    mkdir C:\build\bin\softhsm-2.4.0-x86
    copy C:\build\src\softhsm-2.4.0-x86\win32\Release\* C:\build\bin\softhsm-2.4.0-x86\

### 64-bit

Extract archive `softhsm-2.4.0.tar.gz` into `C:\build\src\softhsm-2.4.0-x64` directory:

    cd C:\build\src\
    "C:\Program Files\7-Zip\7z" x softhsm-2.4.0.tar.gz
    "C:\Program Files\7-Zip\7z" x softhsm-2.4.0.tar
    rename softhsm-2.4.0 softhsm-2.4.0-x64
    del softhsm-2.4.0.tar

Configure build process in a **new command line window**:

	"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
	cd C:\build\src\softhsm-2.4.0-x64\win32\
    python Configure.py enable-static-runtime with-toolset=v141 enable-64bit disable-debug disable-gost with-crypto-backend=openssl with-openssl=C:\build\bin\openssl-1.1.0h-x64\ with-cppunit=C:\build\bin\cppunit-1.13.2-x64\

To build the source code:
- Open solution `C:\build\src\softhsm-2.4.0-x64\win32\softhsm2.sln` in Visual Studio.
- Right click solution in "Solution Explorer", select "Retarget solution", make sure "10.whatever" is selected as "Windows SDK Version" and confirm by clicking "OK".
- Rebuild the source with `Release\x64` solution configuration.

Verify the build by running the test programs:

    cd C:\build\src\softhsm-2.4.0-x64\win32\x64\Release\
    cryptotest.exe
    datamgrtest.exe
    handlemgrtest.exe
    objstoretest.exe
    p11test.exe
    sessionmgrtest.exe
    slotmgrtest.exe

Copy the results into `C:\build\bin\softhsm-2.4.0-x64` directory:

    mkdir C:\build\bin\softhsm-2.4.0-x64
    copy C:\build\src\softhsm-2.4.0-x64\win32\x64\Release\* C:\build\bin\softhsm-2.4.0-x64\

## Create portable archive

Create directory structure:

    mkdir C:\SoftHSM2\bin\
    mkdir C:\SoftHSM2\etc\
    mkdir C:\SoftHSM2\lib\
    mkdir C:\SoftHSM2\share\doc\openssl\
    mkdir C:\SoftHSM2\share\doc\softhsm2\
    mkdir C:\SoftHSM2\share\man\man1\
    mkdir C:\SoftHSM2\share\man\man5\
    mkdir C:\SoftHSM2\var\softhsm2\tokens\

Copy executables to `C:\SoftHSM2\bin\` directory:

    copy C:\build\bin\softhsm-2.4.0-x86\softhsm2-dump-file.exe C:\SoftHSM2\bin\
    copy C:\build\bin\softhsm-2.4.0-x86\softhsm2-keyconv.exe C:\SoftHSM2\bin\
    copy C:\build\bin\softhsm-2.4.0-x86\softhsm2-util.exe C:\SoftHSM2\bin\

Sign executables in `C:\SoftHSM2\bin\` directory in a **new command line window**:

    "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    signtool.exe sign /sha1 84babdf3ba22669463db1ccfa7b1c917462bee4a /fd sha256 /tr http://time.certum.pl/ /td sha256 /d "SoftHSM2" /du "https://www.opendnssec.org/softhsm/" C:\SoftHSM2\bin\*.exe

Copy configuration file to `C:\SoftHSM2\etc\` directory:

    copy C:\build\bin\softhsm-2.4.0-x86\softhsm2.conf C:\SoftHSM2\etc\
    copy C:\SoftHSM2\etc\softhsm2.conf C:\SoftHSM2\etc\softhsm2.conf.sample

Copy PKCS#11 libraries to `C:\SoftHSM2\lib\` directory:

    copy C:\build\bin\softhsm-2.4.0-x86\softhsm2.dll C:\SoftHSM2\lib\softhsm2.dll
    copy C:\build\bin\softhsm-2.4.0-x64\softhsm2.dll C:\SoftHSM2\lib\softhsm2-x64.dll

Sign PKCS#11 libraries in `C:\SoftHSM2\lib\` directory in a **new command line window**:

    "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    signtool.exe sign /sha1 84babdf3ba22669463db1ccfa7b1c917462bee4a /fd sha256 /tr http://time.certum.pl/ /td sha256 /d "SoftHSM2" /du "https://www.opendnssec.org/softhsm/" C:\SoftHSM2\lib\*.dll

Copy licenses and changelog to `C:\SoftHSM2\share\doc\` directory:

    copy C:\build\src\openssl-1.1.0h-x64\LICENSE C:\SoftHSM2\share\doc\openssl\LICENSE.txt
    copy C:\build\src\softhsm-2.4.0-x64\LICENSE C:\SoftHSM2\share\doc\softhsm2\LICENSE.txt
    copy c:\build\src\softhsm-2.4.0-x64\NEWS C:\SoftHSM2\share\doc\softhsm2\CHANGELOG.txt

Copy manual pages to `C:\SoftHSM2\share\man\` directory:

    copy C:\build\src\softhsm-2.4.0-x64\src\lib\common\softhsm2.conf.5.in C:\SoftHSM2\share\man\man5\
    copy C:\build\src\softhsm-2.4.0-x64\src\bin\dump\softhsm2-dump-file.1 C:\SoftHSM2\share\man\man1\
    copy C:\build\src\softhsm-2.4.0-x64\src\bin\keyconv\softhsm2-keyconv.1 C:\SoftHSM2\share\man\man1\
    copy C:\build\src\softhsm-2.4.0-x64\src\bin\util\softhsm2-util.1 C:\SoftHSM2\share\man\man1\

Convert manual pages to text files in Ubuntu WSL:

    export MANWIDTH=80
	cd /mnt/c/SoftHSM2/share/man/
    man ./man5/softhsm2.conf.5.in | col -b > ./man5/softhsm2.conf.txt
    man ./man1/softhsm2-dump-file.1 | col -b > ./man1/softhsm2-dump-file.txt
    man ./man1/softhsm2-keyconv.1 | col -b > ./man1/softhsm2-keyconv.txt
    man ./man1/softhsm2-util.1 | col -b > ./man1/softhsm2-util.txt
	rm ./man1/*.1
	rm ./man5/*.in

Convert EOL of all files in `C:\SoftHSM2\etc\` and `C:\SoftHSM2\share\` directories to Windows format in Ubuntu WSL:

	find /mnt/c/SoftHSM2/etc -type f -exec perl -pi -e 's/\n/\r\n/' '{}' ';'
	find /mnt/c/SoftHSM2/share -type f -exec perl -pi -e 's/\n/\r\n/' '{}' ';'

Update file `C:\SoftHSM2\share\man\man5\softhsm2.conf.txt` with [Windows specific information](https://github.com/disig/SoftHSM2-for-Windows/commit/dfc9ace3c9e2ed5130add17e8347c63fd7d49b59).

Update file `C:\SoftHSM2\etc\softhsm2.conf` with [Windows specific information](https://github.com/disig/SoftHSM2-for-Windows/commit/da8c1bc8ee2608bd8924cb079592d8db668d9638).

Create file [`C:\SoftHSM2\README.txt`](SoftHSM/misc/README.txt).

Create archive `C:\build\SoftHSM2-2.4.0-portable.zip`:

    cd C:\build
    "C:\Program Files\7-Zip\7z" a SoftHSM2-2.4.0-portable.zip C:\SoftHSM2

## Create MSI installer

Clone `SoftHSM2-for-Windows` repository in Git CMD:

    cd C:\build\src\
    git clone https://github.com/disig/SoftHSM2-for-Windows/

Open solution `C:\build\src\SoftHSM2-for-Windows\WiX\SoftHSM2.sln` in Visual Studio and rebuild the source with `Release\x86` solution configuration.

Copy generated MSI installer to `C:\build\` directory:

    copy C:\build\src\SoftHSM2-for-Windows\WiX\SoftHSM2\bin\Release\SoftHSM2.msi C:\build\SoftHSM2-2.4.0.msi

Sign MSI installer in a **new command line window**:

    "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    signtool.exe sign /sha1 84babdf3ba22669463db1ccfa7b1c917462bee4a /fd sha256 /tr http://time.certum.pl/ /td sha256 /d "SoftHSM2" /du "https://www.opendnssec.org/softhsm/" C:\build\SoftHSM2-2.4.0.msi
