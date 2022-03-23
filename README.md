# SoftHSM2 installer for MS Windows

This project provides binary builds and MSI installers of [SoftHSM2](https://github.com/opendnssec/SoftHSMv2) for MS Windows platform.

## Overview

[SoftHSM](https://www.opendnssec.org/softhsm/) is an implementation of a cryptographic store accessible through a PKCS#11 interface. You can use it to explore PKCS#11 without having a Hardware Security Module. It is being  developed as a part of the [OpenDNSSEC](https://www.opendnssec.org/) project.

## Download

These packages include both 32-bit and 64-bit versions of PKCS#11 library:

[SoftHSM 2.6.1 "portable" ZIP archive](https://github.com/disig/SoftHSM2-for-Windows/releases/download/v2.6.1/SoftHSM2-2.6.1-portable.zip)  
Requires user to set/modify `SOFTHSM2_CONF` and `PATH` environment variables manually.

[SoftHSM 2.6.1 MSI installer](https://github.com/disig/SoftHSM2-for-Windows/releases/download/v2.6.1/SoftHSM2-2.6.1.msi)  
Does everything automatically.

## Building the source

See our [Building SoftHSM2 for Windows](BUILDING.md) guide for more details about how these packages were built.

## About

SoftHSM2 installer for MS Windows is provided by [Disig a.s.](https://www.disig.sk)
