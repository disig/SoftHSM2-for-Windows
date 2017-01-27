# SoftHSM2 installer for MS Windows

This project provides binary builds and MSI installers of [SoftHSM2](https://github.com/opendnssec/SoftHSMv2) for MS Windows platform.

## Overview

[SoftHSM](https://www.opendnssec.org/softhsm/) is an implementation of a cryptographic store accessible through a PKCS#11 interface. You can use it to explore PKCS#11 without having a Hardware Security Module. It is being  developed as a part of the [OpenDNSSEC](https://www.opendnssec.org/) project.

## Download

[SoftHSM 2.2.0 "portable" ZIP archive](https://github.com/disig/SoftHSM2-for-Windows/releases/download/v2.2.0/SoftHSM2-2.2.0-portable.zip)  
Requires user to set/modify `SOFTHSM2_CONF` and `PATH` environment variables manually.

[SoftHSM 2.2.0 MSI installer](https://github.com/disig/SoftHSM2-for-Windows/releases/download/v2.2.0/SoftHSM2-2.2.0.msi)  
Does everything automatically.

These packages include both 32-bit and 64-bit versions of PKCS#11 library and require both 32-bit and 64-bit version of [Visual C++ Redistributable for Visual Studio 2015](http://www.microsoft.com/en-us/download/details.aspx?id=48145
) to be installed on the target system.

## Building the source

See our [Building SoftHSM2 for Windows](BUILDING.md) guide for more details about how these packages were built.

## About

SoftHSM2 installer for MS Windows is provided by [Disig a.s.](https://www.disig.sk)
