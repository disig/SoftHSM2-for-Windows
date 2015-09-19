/*
 * Copyright (c) 2015, Disig a.s. <opensource@disig.sk>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "stdafx.h"


// GenerateSoftHSM2Config - Generate the contents of SoftHSM2 cofiguration file
UINT __stdcall GenerateSoftHSM2Config(MSIHANDLE hInstall)
{
	UINT rv = ERROR_INSTALL_FAILURE;

	LPCWSTR propName = L"CustomActionData";
	LPWSTR propValueEmpty = L"";
	LPWSTR propValue = NULL;
	DWORD propValueLen = 0;

	std::wstring configPath;
	std::wstring tokensDirPath;
	std::wofstream configStream;

	HRESULT hr = WcaInitialize(hInstall, "GenerateSoftHSM2Config");
	if (FAILED(hr))
	{
		WcaLogError(hr, "Failed to initialize");
		goto err;
	}

	WcaLog(LOGMSG_STANDARD, "Initialized.");

	if (ERROR_MORE_DATA != MsiGetProperty(hInstall, propName, propValueEmpty, &propValueLen))
	{
		WcaLog(LOGMSG_STANDARD, "Unable to determine size of CustomActionData");
		goto err;
	}

	propValueLen++;

	propValue = new WCHAR[propValueLen]();
	if (NULL == propValue)
	{
		WcaLog(LOGMSG_STANDARD, "Unable to allocate buffer for CustomActionData");
		goto err;
	}
	
	if (ERROR_SUCCESS != MsiGetProperty(hInstall, propName, propValue, &propValueLen))
	{
		WcaLog(LOGMSG_STANDARD, "Unable to read value of CustomActionData");
		goto err;
	}

	WcaLog(LOGMSG_STANDARD, "CustomActionData = \"%S\"", propValue);

	configPath.assign(propValue, propValueLen);
	configPath.append(L"etc\\softhsm2.conf");
	WcaLog(LOGMSG_STANDARD, "configPath = \"%S\"", configPath.c_str());

	tokensDirPath.assign(propValue, propValueLen);
	tokensDirPath.append(L"var\\softhsm2\\tokens\\");
	WcaLog(LOGMSG_STANDARD, "tokensDirPath = \"%S\"", tokensDirPath.c_str());

	configStream.open(configPath, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary, _SH_DENYWR);
	if (!configStream.is_open())
	{
		WcaLog(LOGMSG_STANDARD, "Unable to open file \"%S\" (errno = %d)", configPath.c_str(), errno);
		goto err;
	}

	configStream << "# SoftHSM v2 configuration file" << std::endl;
	configStream << "directories.tokendir = " << tokensDirPath << std::endl;
	configStream << "objectstore.backend = file" << std::endl;
	configStream << "log.level = INFO" << std::endl;

	configStream.close();

	rv = ERROR_SUCCESS;

err:

	return WcaFinalize(rv);
}


// DllMain - Initialize and cleanup WiX custom action utils.
extern "C" BOOL WINAPI DllMain(
	__in HINSTANCE hInst,
	__in ULONG ulReason,
	__in LPVOID
	)
{
	switch(ulReason)
	{
	case DLL_PROCESS_ATTACH:
		WcaGlobalInitialize(hInst);
		break;

	case DLL_PROCESS_DETACH:
		WcaGlobalFinalize();
		break;
	}

	return TRUE;
}
