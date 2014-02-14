/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CCAPI_H
#define CCAPI_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Core Connectivity API (Experimental)
 *
 * These interfaces for deploying to Windows Phone devices are available as
 * registered DLLs if the Windows Phone tools have been installed.
 * As the IDL is not part of the Windows SDK, these interfaces were crafted by
 * hand via the MSDN documentation and the information gathered by OLEView.
 * As a consequence, not all interfaces have been stubbed out, and not all
 * methods have been tested. This means that some methods may end up in the
 * wrong position in the vtable, causing unexpected behavior or crashes.
 * You have been warned!
 *
 * CoreConnectivity documentation:
 *    http://msdn.microsoft.com/en-us/library/ee481381.aspx
 * SmartDevice Connectivity documentation:
 *    http://msdn.microsoft.com/en-us/library/microsoft.smartdevice.connectivity.aspx
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <windows.h>

// Undefined
struct ICcFormFactorContainer;
struct ICcOSImage;
struct ICcOSImageContainer;
struct ICcPackageContainer;
struct ICcProjectContainer;
struct ICcServiceCategoryContainer;
struct ICcServiceCB;
struct ICcServiceInfo;
struct ICcTransportStream;
struct ICcTypeToArchitectureMap;

// Defined
struct ICcConnection;
struct ICcCollection;
struct ICcConnection3;
struct ICcDatastore;
struct ICcDevice;
struct ICcDeviceContainer;
struct ICcObject;
struct ICcObjectContainer;
struct ICcPlatform;
struct ICcPlatformContainer;
struct ICcProperty;
struct ICcPropertyContainer;
struct ICcServer;

static const CLSID CLSID_ConMan = { 0x349AB2E8, 0x71B6, 0x4069, 0xAD, 0x9C, 0x11, 0x70, 0x84, 0x9D, 0xA6, 0x4C };

typedef struct tagFileInfo{
  LONG m_FileAttribues;
  LONGLONG m_FileSize;
  FILETIME m_CreationTime;
  FILETIME m_LastAccessTime;
  FILETIME m_LastWriteTime;
} FileInfo;

typedef struct tagFileVerifyVersion{
  DWORD m_Major;
  DWORD m_Minor;
  DWORD m_Build;
  DWORD m_Revision;
} FileVerifyVersion;

typedef struct tagFileVerifyInfo{
  FileVerifyVersion m_AssemblyVersion;
  FileVerifyVersion m_Win32Version;
  BSTR m_Culture;
  BYTE m_PublicKeyToken[12 + 3/*PUBLIC_KEY_TOKEN_LENGTH*/]; //### What is the key length?
  DWORD m_Flags;
} FileVerifyInfo;

typedef struct tagFileVerifyReference{
  BSTR m_Name;
  BSTR m_SourcePath;
  FileVerifyInfo m_Info;
} FileVerifyReference;

typedef struct tagFileVerifyResult{
  DWORD m_Version;
  FileVerifyInfo _Info;
} FileVerifyResult;

typedef struct tagPlatformInfo{
  DWORD m_OSMajor;
  DWORD m_OSMinor;
  DWORD m_BuildNo;
  DWORD m_ProcessorArchitecture;
  DWORD m_InstructionSet;
} SystemInfo;

struct __declspec(uuid("{7A4AA9D3-0F9E-4CD4-8D52-62B6C0653752}")) ICcCollection : public IDispatch
{
    virtual HRESULT __stdcall get_Count(long *count) = 0;
    virtual HRESULT __stdcall get_Item(long index, ICcObject **object) = 0;
    virtual HRESULT __stdcall get_NewEnum(IUnknown **val) = 0;
};

struct __declspec(uuid("{CEF4C928-326F-49A9-B7E7-8FE7588B74B5}")) ICcConnection : public IDispatch
{
    virtual HRESULT __stdcall DeviceId(BSTR *deviceId) = 0;
    virtual HRESULT __stdcall GetSystemInfo(SystemInfo *systemInfo) = 0;
    virtual HRESULT __stdcall SendFile(BSTR desktopFile, BSTR deviceFile, DWORD fileAction, DWORD creationFlags, BSTR customFileAction) = 0;
    virtual HRESULT __stdcall ReceiveFile(BSTR deviceFile, BSTR desktopFile, DWORD fileAction) = 0;
    virtual HRESULT __stdcall RemoveFile(BSTR deviceFile) = 0;
    virtual HRESULT __stdcall GetFileInfo(BSTR deviceFile, FileInfo *fileInfo) = 0;
    virtual HRESULT __stdcall SetFileInfo(BSTR deviceFile, FileInfo *fileInfo) = 0;
    virtual HRESULT __stdcall DeleteDirectory(BSTR deviceDirectory, VARIANT_BOOL removeAll) = 0;
    virtual HRESULT __stdcall MakeDirectory(BSTR deviceDirectory) = 0;
    virtual HRESULT __stdcall DownloadPackage(BSTR packageId) = 0;
    virtual HRESULT __stdcall LaunchProcess(BSTR executable, BSTR arguments, DWORD creationFlags, DWORD *processId, DWORD *processHandle) = 0;
    virtual HRESULT __stdcall TerminateProcess(DWORD processId) = 0;
    virtual HRESULT __stdcall GetProcessExitCode(DWORD processId, VARIANT_BOOL *processExited, DWORD *exitCode) = 0;
    virtual HRESULT __stdcall RegistryCreateKey(LONG key, BSTR subKey) = 0;
    virtual HRESULT __stdcall RegistryDeleteKey(LONG key, BSTR subKey) = 0;
    virtual HRESULT __stdcall RegistrySetValue(LONG key, BSTR subKey, BSTR valueName, DWORD type, BSTR data, DWORD length) = 0;
    virtual HRESULT __stdcall RegistryQueryValue(LONG key, BSTR subKey, BSTR valueName, DWORD type, WCHAR *value, LONG *length) = 0;
    virtual HRESULT __stdcall RegistryDeleteValue(LONG key, BSTR subKey, BSTR valueName) = 0;
    virtual HRESULT __stdcall IsConnected(VARIANT_BOOL *connected) = 0;
    virtual HRESULT __stdcall VerifyFilesInstalled(DWORD arraySize, FileVerifyReference *infoArray, FileVerifyResult *existenceArray) = 0;
    virtual HRESULT __stdcall ConnectDevice() = 0;
    virtual HRESULT __stdcall DisconnectDevice() = 0;
    virtual HRESULT __stdcall SearchFileSystem(BSTR criteria, BSTR startingDirectory, SAFEARRAY/*<BSTR>*/ *results) = 0;
    virtual HRESULT __stdcall CreateStream(BSTR streamId, DWORD timeout, ICcServiceCB *callback, DWORD *cookieId, ICcTransportStream **stream) = 0;
    virtual HRESULT __stdcall EnumerateProcesses(SAFEARRAY/*<BSTR>*/ **processes, SAFEARRAY/*<DWORD>*/ **processIds) = 0;
    virtual HRESULT __stdcall CloseProcessHandle(DWORD processHandle) = 0;
};

struct __declspec(uuid("{F4B43EA3-3106-4D3D-94E3-084D4136C40C}")) ICcConnection3 : public IUnknown
{
    virtual HRESULT __stdcall GetInstalledApplicationCount(int *count) = 0; // E_NOTIMPL
    virtual HRESULT __stdcall GetInstalledApplicationIDs(SAFEARRAY/*<BSTR>*/ **productIds, SAFEARRAY/*<BSTR>*/ **instanceIds) = 0;
    virtual HRESULT __stdcall IsApplicationInstalled(BSTR productId, VARIANT_BOOL *installed) = 0;
    virtual HRESULT __stdcall InstallApplication(BSTR productId, BSTR instanceId, BSTR genre, BSTR iconPath, BSTR xapPath) = 0;
    virtual HRESULT __stdcall UpdateApplication(BSTR productId, BSTR instanceId, BSTR genre, BSTR applicationPath, BSTR xapPath) = 0;
    virtual HRESULT __stdcall GetInstalledFileInfo(BSTR productId, BSTR fileName, FileInfo *fileInfo) = 0; // E_NOTIMPL
    virtual HRESULT __stdcall IsApplicationRunning(BSTR productId, VARIANT_BOOL *isRunning) = 0; // E_NOTIMPL
    virtual HRESULT __stdcall UninstallApplication(BSTR productId) = 0;
    virtual HRESULT __stdcall LaunchApplicationWithService(BSTR productId, BSTR serviceInfo) = 0; // E_NOTIMPL
    virtual HRESULT __stdcall TerminateRunningApplicationInstances(BSTR productId) = 0;
    virtual HRESULT __stdcall LaunchApplication(BSTR productId, DWORD *processId) = 0;

// Untested
    virtual HRESULT __stdcall UpdateInstalledFile(BSTR productId, BSTR fileRelativePath, BSTR sourceFilePath, VARIANT_BOOL updateFileInfo) = 0;
    virtual HRESULT __stdcall UpdateInstalledFilesInfo(BSTR productId, SAFEARRAY/*<BSTR>*/ *fileNames, SAFEARRAY/*<BSTR>*/ *xapRelativePaths) = 0;
    virtual HRESULT __stdcall UpdateInstalledFiles(BSTR productId, SAFEARRAY/*<BSTR>*/ *fileNames, SAFEARRAY/*<BSTR>*/ *xapRelativePaths) = 0;
    virtual HRESULT __stdcall ActivateDevice() = 0;
};

struct __declspec(uuid("{5F25394E-D9B6-4F8E-A0DF-325610A35BFA}")) ICcConnection4 : public IUnknown
{
    virtual HRESULT __stdcall GetDirectoryListing(BSTR deviceDirPath, SAFEARRAY/*<BSTR>*/ **listing) = 0;
    virtual HRESULT __stdcall GetApplicationType(BSTR productId, DWORD *type) = 0;
    virtual HRESULT __stdcall GetEndPoints(int localPort, BSTR localIp, BSTR remoteIp, int remotePort) = 0;
};

struct __declspec(uuid("{EDB0A0CA-F0F8-4EBF-9D31-43E182569A5A}")) ICcDatastore : public IDispatch
{
    virtual HRESULT __stdcall Save() = 0;
    virtual HRESULT __stdcall RegisterRefreshEvent(BSTR eventName) = 0;
    virtual HRESULT __stdcall UnregisterRefreshEvent() = 0;
    virtual HRESULT __stdcall get_DeviceContainer(ICcDeviceContainer **dc) = 0;
    virtual HRESULT __stdcall get_OSImageContainer(ICcOSImageContainer **oc) = 0;
    virtual HRESULT __stdcall get_PackageContainer(ICcPackageContainer **pc) = 0;
    virtual HRESULT __stdcall get_PlatformContainer(ICcPlatformContainer **pc) = 0;
    virtual HRESULT __stdcall get_PropertyContainer(ICcPropertyContainer **pc) = 0;
    virtual HRESULT __stdcall get_ServiceCategoryContainer(ICcServiceCategoryContainer **scc) = 0;
    virtual HRESULT __stdcall get_Version(BSTR *version) = 0;
};

struct __declspec(uuid("{971BF639-8C53-4057-B635-375D7BCDFF3E}")) ICcDevice : public IDispatch
{
    virtual HRESULT __stdcall ClearOSImage() = 0;
    virtual HRESULT __stdcall ClearServiceMap(BSTR serviceCatetoryId) = 0;
    virtual HRESULT __stdcall GetOSImage(ICcOSImage **image) = 0;
    virtual HRESULT __stdcall GetServiceMap(BSTR serviceCategoryId, ICcServiceInfo **serviceInfo) = 0;
    virtual HRESULT __stdcall SetOSImage(BSTR osImage) = 0;
    virtual HRESULT __stdcall SetServiceMap(BSTR serviceCategoryId, BSTR serviceInfoId) = 0;
};

struct __declspec(uuid("{88152DD3-5ECB-47A2-8F15-610C4C390122}")) ICcDeviceContainer : public IDispatch
{
};

struct __declspec(uuid("{B669EC21-E8FC-42E4-AEC5-8F0EF3673AB8}")) ICcObject : public IDispatch
{
    virtual HRESULT __stdcall get_Name(BSTR *name) = 0;
    virtual HRESULT __stdcall put_Name(BSTR name) = 0;
    virtual HRESULT __stdcall get_ID(BSTR *id) = 0;
    virtual HRESULT __stdcall get_IsProtected(VARIANT_BOOL *isProtected) = 0;
    virtual HRESULT __stdcall get_PropertyContainer(ICcPropertyContainer **pc) = 0;
};

struct __declspec(uuid("{1C0048A9-A73F-41B3-BD75-467D615CB9E5}")) ICcObjectContainer : public IDispatch
{
    virtual HRESULT __stdcall FindObject(BSTR nameOrId, ICcObject **object) = 0;
    virtual HRESULT __stdcall EnumerateObjects(ICcCollection **collection) = 0;
    virtual HRESULT __stdcall AddObject(BSTR name, BSTR id, ICcObject **object) = 0;
    virtual HRESULT __stdcall DeleteObject(BSTR nameOrId) = 0;
};

struct __declspec(uuid("{2E12E75A-1625-44B6-B527-7A1E7ED61577}")) ICcPlatform : public IDispatch
{
    virtual HRESULT __stdcall get_ProjectContainer(ICcProjectContainer **container) = 0;
    virtual HRESULT __stdcall get_DeviceContainer(ICcDeviceContainer **container) = 0;
    virtual HRESULT __stdcall get_FormFactorContainer(ICcFormFactorContainer **container) = 0;
    virtual HRESULT __stdcall get_TypeToArchitectureMap(ICcTypeToArchitectureMap **map) = 0;
};

struct __declspec(uuid("{C434B7DA-ABAA-428A-944A-3AF1A7419A92}")) ICcPlatformContainer : public IDispatch
{
};

struct __declspec(uuid("{A918FF41-F287-488D-BE16-99DBF54E331D}")) ICcProperty : public IDispatch
{
    virtual HRESULT __stdcall get_Value(BSTR *val) = 0;
    virtual HRESULT __stdcall set_Value(BSTR val) = 0;
    virtual HRESULT __stdcall AddPropertyContainer() = 0;
};

struct __declspec(uuid("{9636B4A4-633C-4542-A809-9E96ABF01FA5}")) ICcPropertyContainer : public IDispatch
{
};

struct __declspec(uuid("{F19FF2DB-0A4E-4148-ABE3-47EE7E31194F}")) ICcServer : public IDispatch
{
    virtual HRESULT __stdcall get_Locale(DWORD *locale) = 0;
    virtual HRESULT __stdcall put_Locale(DWORD *locale) = 0;
    virtual HRESULT __stdcall GetDatastore(DWORD locale, ICcDatastore **datastore) = 0;
    virtual HRESULT __stdcall GetConnection(ICcDevice *device, DWORD timeout, ICcServiceCB *callback, BSTR *connectionId, ICcConnection **connection) = 0;
    virtual HRESULT __stdcall EnumerateConnections(DWORD sizeActual, DWORD *sizeReturned, BSTR *connections, VARIANT_BOOL *moreEntries) = 0;
    virtual HRESULT __stdcall GetConnectionFromId(BSTR connectionId, ICcConnection **connection) = 0;
};

#endif