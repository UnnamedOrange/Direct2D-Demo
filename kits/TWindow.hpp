// Copyright (c) 2018-2019 Orange Software
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#if TKERNEL_WINVER > 0

#include "TStdInclude.hpp"

#include "TWinAug.hpp"

class TWindow : virtual public TAugProcBase
{
	// 窗口句柄
private:
	HWND __hwnd;
public:
	// 获取窗口句柄
	HWND GetHwnd() const { return __hwnd; }


	// 属性字典
private:
	using KeyValPair = std::pair<std::wstring, std::wstring>;
	std::unordered_map<std::wstring, std::wstring> property_dict;
public:
	std::wstring& operator[](const std::wstring& key)
	{
		return property_dict[key];
	}
	const std::wstring& operator[](const std::wstring& key) const
	{
		return property_dict.at(key);
	}


	// property 助手函数
protected:
	std::wstring __class_name__{ L"__class_name__" };				// 窗口类名
	std::wstring __register_classes__{ L"__register_classes__" };	// 是否注册窗口类
	std::wstring __hInstance__{ L"__hInstance__" };					// 应用程序实例句柄
	std::wstring __class_style__{ L"__class_style__" };				// 窗口类样式
	std::wstring __hIcon__{ L"__hIcon__" };							// hIcon 参数
	std::wstring __hIconSm__{ L"__hIconSm__" };						// hIconSm 参数
public:
	void property_int64(const std::wstring& key, __int64 val)
	{
		wchar_t buffer[24];
		swprintf_s(buffer, L"%lld", val);
		operator[](key) = buffer;
	}
	__int64 property_int64(const std::wstring& key) const
	{
		__int64 ret;
		swscanf_s(operator[](key).c_str(), L"%lld", &ret);
		return ret;
	}

	void property__class_name__(const std::wstring& name) // 设置窗口类名
	{
		operator[](__class_name__) = name;
	}
	const std::wstring& property__class_name__() const // 获取窗口类名
	{
		return operator[](__class_name__);
	}
	void property__register_classes__(int whether) // 是否要注册窗口类
	{
		property_int64(__register_classes__, static_cast<__int64>(!!whether));
	}
	int property__register_classes__() const // 获知是否要注册窗口类
	{
		return property_int64(__register_classes__) == 1ll;
	}
	void property__hInstance__(HINSTANCE hInstance) // 设置 hInstance
	{
		property_int64(__hInstance__, reinterpret_cast<__int64>(hInstance));
	}
	HINSTANCE property__hInstance__() const // 获取 hInstance
	{
		return reinterpret_cast<HINSTANCE>(property_int64(__hInstance__));
	}
	void property__class_style__(UINT style) // 设置 class_style
	{
		property_int64(__class_style__, static_cast<__int64>(style));
	}
	UINT property__class_style__() const // 获取 class_style
	{
		return static_cast<UINT>(property_int64(__class_style__));
	}
	void property__hIcon__(HICON hIcon) // 设置 hIcon
	{
		property_int64(__hIcon__, reinterpret_cast<__int64>(hIcon));
	}
	HICON property__hIcon__() const // 获取 hIcon
	{
		return reinterpret_cast<HICON>(property_int64(__hIcon__));
	}
	void property__hIconSm__(HICON hIcon) // 设置 hIconSm
	{
		property_int64(__hIconSm__, reinterpret_cast<__int64>(hIcon));
	}
	HICON property__hIconSm__() const // 获取 hIconSm
	{
		return reinterpret_cast<HICON>(property_int64(__hIconSm__));
	}
private:
	// 初始化。
	void __InitPropertyDict()
	{
		property__class_name__(__GetIdentity().second);
		property__register_classes__(1);

		property__class_style__(CS_HREDRAW | CS_VREDRAW);
		property__hIcon__(nullptr);
		property__hIconSm__(nullptr);
	}

	// 类标识（使用虚函数表）
private:
	/// 返回类标识。first 是虚函数表指针，second 是推荐的默认窗口类名。
	std::pair<PVOID, std::wstring> __GetIdentity() const
	{
		auto vptr = *((PVOID*)this); // 取 this 指向的内容的前 8 个字节，即虚函数表的指针
		WCHAR strIdName[256];
		swprintf(strIdName, 256, L"TWindow::0x%p", vptr);
		return std::make_pair(vptr, std::wstring(strIdName));
	}


	// 创建窗口类
private:
	// 在创建时会尝试自动注册。
	void __RegisterClasses(HINSTANCE hInstance)
	{
		if (property__register_classes__())
		{
			if (property__class_name__().empty())
				throw std::runtime_error("property__class_name__ cannot be empty.");

			static std::set<std::wstring> registered; // 已注册的类名
			if (registered.count(property__class_name__()))
				return;
			registered.insert(property__class_name__());

			WNDCLASSEXW wndclassex = { sizeof(WNDCLASSEXW) };
			wndclassex.style = property__class_style__();
			wndclassex.lpfnWndProc = VirtualWindowProc;
			wndclassex.cbClsExtra = 0;
			wndclassex.cbWndExtra = 0;
			wndclassex.hInstance = hInstance;
			wndclassex.hIcon = property__hIcon__();
			wndclassex.hIconSm = property__hIconSm__();
			wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wndclassex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
			wndclassex.lpszMenuName = NULL;
			wndclassex.lpszClassName = property__class_name__().c_str();
			if (!RegisterClassExW(&wndclassex))
				throw std::runtime_error("Fail to RegisterClassExW.");
		}
	}


	// 回调函数
private:
	static LRESULT CALLBACK VirtualWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		TWindow* p = reinterpret_cast<TWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

		if (message == WM_NCCREATE)
		{
			p = reinterpret_cast<TWindow*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)p);
			p->__hwnd = hwnd;
		}

		LRESULT ret;
		if (p)
		{
			for (auto t : p->__pre_procs)
				t(hwnd, message, wParam, lParam);
			ret = p->Proc(hwnd, message, wParam, lParam);
			for (auto t : p->__post_procs)
				t(hwnd, message, wParam, lParam);
		}
		else
			ret = DefWindowProcW(hwnd, message, wParam, lParam);

		if (p && message == WM_DESTROY)
			p->__hwnd = nullptr;

		return ret;
	}
	static INT_PTR CALLBACK VirtualDialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		TWindow* p = reinterpret_cast<TWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

		if (message == WM_INITDIALOG)
		{
			p = reinterpret_cast<TWindow*>(lParam);
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)p);
			p->__hwnd = hwnd;
		}

		INT_PTR ret{};
		if (p)
		{
			for (auto t : p->__pre_procs)
				t(hwnd, message, wParam, lParam);
			ret = p->Proc(hwnd, message, wParam, lParam);
			for (auto t : p->__post_procs)
				t(hwnd, message, wParam, lParam);
		}

		if (p && message == WM_DESTROY)
			p->__hwnd = nullptr;

		return ret;
	}
public:
	virtual LONG_PTR Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;


	// 键盘加速键
private:
	HACCEL __hAccel = NULL;
public:
	VOID SetCurrentAccelerator(HACCEL handle) { __hAccel = handle; }


	// 消息循环
public:
	int MessageLoop()
	{
		MSG msg;
		while (GetMessageW(&msg, NULL, 0, 0))
		{
			if (!__hAccel || !TranslateAcceleratorW(GetHwnd(), __hAccel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}
		return (int)msg.wParam;
	}


	// 创建窗口
private:
	virtual INT_PTR __Create(HINSTANCE hInstance, HWND hwndParent) = 0;
public:
	INT_PTR Create(HINSTANCE hInstance, HWND hwndParent)
	{
		property__hInstance__(hInstance);
		__RegisterClasses(hInstance);
		INT_PTR ret = __Create(hInstance, hwndParent);
		return ret;
	}


	// Constructor
public:
	TWindow()
	{
		__InitPropertyDict();
	}

	friend class TWindowNormal;
	friend class TWindowDialogBox;
	friend class TWindowCreateDialog;
};

class TWindowNormal : public TWindow
{
	// 回调函数
	virtual LONG_PTR Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override
	{
		return static_cast<LONG_PTR>(WndProc(hwnd, message, wParam, lParam));
	}
	virtual LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;


	// Constructor
public:
	TWindowNormal()
	{
		__InitPropertyDict();
	}


	// 创建窗口
public:
	virtual INT_PTR __Create(HINSTANCE hInstance, HWND hwndParent) override
	{
		CreateWindowExW(property__dwExStyle__(),
			property__class_name__().c_str(),
			property__lpWindowName__().c_str(),
			property__dwStyle__(),
			property__X__(),
			property__Y__(),
			property__nWidth__(),
			property__nHeight__(),
			hwndParent,
			property__hMenu__(),
			hInstance,
			this);
		return reinterpret_cast<INT_PTR>(GetHwnd());
	}


	// property 助手函数
protected:
	std::wstring __dwExStyle__{ L"__dwExStyle__" };	// dwExStyle
	std::wstring __lpWindowName__{ L"__lpWindowName__" }; // lpWindowName
	std::wstring __dwStyle__{ L"__dwStyle__" };	// dwStyle
	std::wstring __X__{ L"__X__" }; // X
	std::wstring __Y__{ L"__Y__" }; // Y
	std::wstring __nWidth__{ L"__nWidth__" }; // nWidth
	std::wstring __nHeight__{ L"__nHeight__" }; // nHeight
	std::wstring __hMenu__{ L"__hMenu__" }; // hMenu
public:
	void property__dwExStyle__(DWORD dwExStyle) // 设置 dwExStyle 参数
	{
		property_int64(__dwExStyle__, static_cast<INT64>(dwExStyle));
	}
	DWORD property__dwExStyle__() const // 获取 dwExStyle 参数
	{
		return static_cast<DWORD>(property_int64(__dwExStyle__));
	}
	void property__lpWindowName__(const std::wstring& name) // 设置 lpWindowName 参数
	{
		operator[](__lpWindowName__) = name;
	}
	const std::wstring& property__lpWindowName__() const // 获取 lpWindowName 参数
	{
		return operator[](__lpWindowName__);
	}
	void property__dwStyle__(DWORD dwStyle) // 设置 dwStyle 参数
	{
		property_int64(__dwStyle__, static_cast<INT64>(dwStyle));
	}
	DWORD property__dwStyle__() const // 获取 dwStyle 参数
	{
		return static_cast<DWORD>(property_int64(__dwStyle__));
	}
	void property__X__(int X) // 设置 X 参数
	{
		property_int64(__X__, static_cast<INT64>(X));
	}
	int property__X__() const // 获取 X 参数
	{
		return static_cast<int>(property_int64(__X__));
	}
	void property__Y__(int Y) // 设置 Y 参数
	{
		property_int64(__Y__, static_cast<INT64>(Y));
	}
	int property__Y__() const // 获取 Y 参数
	{
		return static_cast<int>(property_int64(__Y__));
	}
	void property__nWidth__(int nWidth) // 设置 nWidth 参数
	{
		property_int64(__nWidth__, static_cast<INT64>(nWidth));
	}
	int property__nWidth__() const // 获取 nWidth 参数
	{
		return static_cast<int>(property_int64(__nWidth__));
	}
	void property__nHeight__(int nHeight) // 设置 nHeight 参数
	{
		property_int64(__nHeight__, static_cast<INT64>(nHeight));
	}
	int property__nHeight__() const // 获取 nHeight 参数
	{
		return static_cast<int>(property_int64(__nHeight__));
	}
	void property__hMenu__(HMENU hMenu) // 设置 hMenu 参数
	{
		property_int64(__hMenu__, reinterpret_cast<INT64>(hMenu));
	}
	HMENU property__hMenu__() const // 获取 hMenu 参数
	{
		return reinterpret_cast<HMENU>(property_int64(__hMenu__));
	}
private:
	void __InitPropertyDict()
	{
		property__dwExStyle__(0);
		property__lpWindowName__(L"");
		property__dwStyle__(WS_OVERLAPPEDWINDOW);
		property__X__(CW_USEDEFAULT);
		property__Y__(CW_USEDEFAULT);
		property__nWidth__(CW_USEDEFAULT);
		property__nHeight__(CW_USEDEFAULT);
		property__hMenu__(nullptr);
	}
};

class TWindowDialogBox : public TWindow
{
	// 回调函数
	virtual LONG_PTR Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override
	{
		return static_cast<LONG_PTR>(WndProc(hwnd, message, wParam, lParam));
	}
	virtual INT_PTR WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;


	// Constructor
public:
	TWindowDialogBox()
	{
		__InitPropertyDict();
	}


	// 创建窗口
public:
	virtual INT_PTR __Create(HINSTANCE hInstance, HWND hwndParent) override
	{
		return DialogBoxParamW(hInstance, property__lpTemplateName__(),
			hwndParent, VirtualDialogProc, reinterpret_cast<LPARAM>(this));
	}


	// property 助手函数
protected:
	std::wstring __lpTemplateName__{ L"__lpTemplateName__" };	// lpTemplateName
public:
	void property__lpTemplateName__(LPCWSTR lpTemplateName) // 设置 lpTemplateName 参数
	{
		property_int64(__lpTemplateName__, reinterpret_cast<INT64>(lpTemplateName));
	}
	LPCWSTR property__lpTemplateName__() // 获取 lpTemplateName 参数
	{
		return reinterpret_cast<LPCWSTR>(property_int64(__lpTemplateName__));
	}
private:
	void __InitPropertyDict()
	{
		property__register_classes__(false);
		property__class_name__(L"#32770");
	}
};

class TWindowCreateDialog : public TWindow
{
	// 回调函数
	virtual LONG_PTR Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override
	{
		return static_cast<LONG_PTR>(WndProc(hwnd, message, wParam, lParam));
	}
	virtual INT_PTR WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;


	// Constructor
public:
	TWindowCreateDialog()
	{
		__InitPropertyDict();
	}


	// 创建窗口
public:
	virtual INT_PTR __Create(HINSTANCE hInstance, HWND hwndParent) override
	{
		return reinterpret_cast<INT_PTR>(CreateDialogParamW(hInstance, property__lpTemplateName__(),
			hwndParent, VirtualDialogProc, reinterpret_cast<LPARAM>(this)));
	}


	// property 助手函数
protected:
	std::wstring __lpTemplateName__{ L"__lpTemplateName__" };	// lpTemplateName
public:
	void property__lpTemplateName__(LPCWSTR lpTemplateName) // 设置 lpTemplateName 参数
	{
		property_int64(__lpTemplateName__, reinterpret_cast<INT64>(lpTemplateName));
	}
	LPCWSTR property__lpTemplateName__() // 获取 lpTemplateName 参数
	{
		return reinterpret_cast<LPCWSTR>(property_int64(__lpTemplateName__));
	}
private:
	void __InitPropertyDict()
	{
		property__register_classes__(false);
		property__class_name__(L"#32770");
	}
};

#endif // TKERNEL_WINVER > 0