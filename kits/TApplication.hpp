// Copyright (c) Orange Lee. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#pragma once

#if TKERNEL_WINVER > 0

#include "TStdInclude.hpp"

#include "TSmartObject.hpp"

template <typename AppType>
class TApplication
{
	//public:
	//	TBlock LoadResource(LPCWSTR lpcResourceName, LPCWSTR lpcTypeName)
	//	{
	//		TBlock block;
	//		HRSRC hResInfo = FindResourceW(hInstance, lpcResourceName, lpcTypeName);
	//		if (!hResInfo) return throw std::exception(), block;
	//		HGLOBAL hResource = ::LoadResource(hInstance, hResInfo);
	//		if (!hResource) return throw std::exception(), block;
	//		DWORD dwSize = SizeofResource(hInstance, hResInfo);
	//		if (!dwSize) return throw std::exception(), block;
	//
	//		LPVOID p = LockResource(hResource);
	//		block.realloc(dwSize);
	//		block.assign(0, p, dwSize);
	//		FreeResource(hResource);
	//
	//		return block;
	//	}

private:
	HINSTANCE __hInstance{};
public:
	const HINSTANCE& hInstance{ __hInstance };

public:
	// 将此函数看作应用程序入口。
	virtual int OnExecute() = 0;
	// 访问当前实例地址。
	static PVOID& __access_instance()
	{
		static PVOID _;
		return _;
	}
public:
	static AppType& App()
	{
		return *(reinterpret_cast<AppType*>(__access_instance()));
	}
	static int Execute(HINSTANCE hInstance = GetModuleHandleW(nullptr))
	{
		auto t = std::make_unique<AppType>(hInstance);
		if (__access_instance())
			throw std::runtime_error("Only one Execute() should be running at a time.");
		__access_instance() = t.get();
		int ret = t->OnExecute();
		t.reset(); // 及时调用析构函数
		__access_instance() = nullptr;
		return ret;
	}

	// 命令行。
private:
	std::vector<std::wstring> __CommandLine;
private:
	void __QueryCommandLine()
	{
		LPWSTR lpCmdLine = GetCommandLineW();
		int nCmd;
		LPWSTR* lpCmdLineArray = CommandLineToArgvW(lpCmdLine, &nCmd);
		for (int i = 0; i < nCmd; i++)
			__CommandLine.push_back(lpCmdLineArray[i]);
		LocalFree(reinterpret_cast<HLOCAL>(lpCmdLineArray));
	}
public:
	const std::vector<std::wstring>& GetCmdLine() const { return __CommandLine; }

	// 应用程序版本信息。
private:
	std::array<int, 4> VersionInfo{};
	void __QueryAppVersionInfo()
	{
		VS_FIXEDFILEINFO* pffi;
		// in fact dwHandle is ignored
		DWORD dwHandle = 0;
		// return 0 if failed
		std::vector<WCHAR> strFileName(65536);
		GetModuleFileNameW(hInstance, strFileName.data(), 65536);
		DWORD dwSize = GetFileVersionInfoSizeW(strFileName.data(), &dwHandle);
		if (!dwSize)
			return void(VersionInfo = std::array<int, 4>{1, 0, 0, 0});
		auto pBlock = std::make_unique<BYTE[]>(dwSize);
		GetFileVersionInfoW(strFileName.data(), 0, dwSize, pBlock.get());
		// dwSize is no longer used
		VerQueryValueW(pBlock.get(), L"\\", (LPVOID*)&pffi, (PUINT)&dwSize);

		return void(VersionInfo = std::array<int, 4>{
			HIWORD(pffi->dwProductVersionMS),
				LOWORD(pffi->dwProductVersionMS),
				HIWORD(pffi->dwProductVersionLS),
				LOWORD(pffi->dwProductVersionLS)});
	}
public:
	const auto& GetAppVersion() const
	{
		return VersionInfo;
	}

	// 应用程序单例运行。
private:
	THANDLE __hMutex;
	THANDLE __hMapFile;
private:
	std::string __get_class_identity(unsigned int idx) const
	{
		std::string type{ typeid(*this).name() };
		std::default_random_engine random_engine(static_cast<unsigned int>(std::hash<std::string>()(type)) + idx);
		std::uniform_int_distribution<unsigned int> random_distribution(0u, UINT_MAX);
		char buffer[256]; // class xxx (32-bit random hex)
		sprintf_s(buffer, "%s %x", type.c_str(), random_distribution(random_engine));
		return buffer;
	}
public:
	class SingleInstance
	{
	public:
		SingleInstance()
		{

		}
	};
	// 要求应用程序在用户级单例启动，否则抛出 TApplication::SingleInstance 异常。
	void DemandSingleInstance()
	{
		if (__hMutex)
			throw std::runtime_error("DemandSingleInstance cannot be called twice.");

		__hMutex = CreateMutexA(nullptr, FALSE, __get_class_identity(0).c_str());
		if (!__hMutex)
			throw std::runtime_error("Fail to CreateMutex.");

		DWORD dwLastError = GetLastError();
		if (dwLastError == ERROR_ALREADY_EXISTS)
		{
			__hMutex.reset();
			throw SingleInstance();
		}
	}
private:
	void __CreateSharedMemory()
	{
		if (!__hMapFile)
		{
			__hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, // 内存 
				nullptr, PAGE_READWRITE, 0, sizeof(__int64), __get_class_identity(1).c_str());
			if (!__hMapFile)
				throw std::runtime_error("Fail to CreateFileMappingA.");
		}
	}
public:
	void WriteSharedInt64(INT64 data)
	{
		__CreateSharedMemory();

		INT64* p = reinterpret_cast<INT64*>(
			MapViewOfFile(__hMapFile.get(), FILE_MAP_ALL_ACCESS, 0, 0, sizeof(INT64)));
		if (!p)
			throw std::runtime_error("Fail to MapViewOfFile.");
		*p = data;
		UnmapViewOfFile(p);
	}
	INT64 ReadSharedInt64()
	{
		__CreateSharedMemory();

		INT64* p = reinterpret_cast<__int64*>(
			MapViewOfFile(__hMapFile.get(), FILE_MAP_ALL_ACCESS, 0, 0, sizeof(INT64)));
		if (!p)
			throw std::runtime_error("Fail to MapViewOfFile.");
		INT64 ret = *p;
		UnmapViewOfFile(p);

		return ret;
	}

	// Constructor
public:
	TApplication(HINSTANCE hInstance) : __hInstance(hInstance)
	{
		__QueryCommandLine();
		__QueryAppVersionInfo();

#if TKERNEL_WINVER >= 1703
		SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
#endif
	}
};

#endif // TKERNEL_WINVER > 0