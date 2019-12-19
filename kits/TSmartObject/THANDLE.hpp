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

#include "../TStdInclude.hpp"

template <UINT_PTR invalid_handle = NULL>
class _THANDLE final
{
	HANDLE handle;

public:
	_THANDLE() : handle(reinterpret_cast<HANDLE>(invalid_handle)) {}
	_THANDLE(HANDLE free_handle) : handle(free_handle) {}
	_THANDLE(const _THANDLE&) = delete;
	_THANDLE(_THANDLE&& another)
	{
		handle = another.handle;
		another.handle = invalid_handle;
	}
	~_THANDLE()
	{
		reset();
	}

	_THANDLE& operator=(HANDLE free_handle)
	{
		reset(free_handle);
		return *this;
	}

	// 返回当前句柄是否无效。
	bool invalid() const { return handle == reinterpret_cast<HANDLE>(invalid_handle); }
	// 返回当前句柄是否有效。
	bool valid() const { return !invalid(); }
	// 返回当前句柄是否有效。
	operator bool const() { return valid(); }
	/// 清空当前句柄。
	void reset()
	{
		if (valid())
			CloseHandle(handle);
		handle = reinterpret_cast<HANDLE>(invalid_handle);
	}
	// 将当前句柄设为新的句柄。
	void reset(HANDLE free_handle)
	{
		reset();
		handle = free_handle;
	}
	// 不再使用该智能对象管理当前句柄。
	HANDLE release()
	{
		auto ret = handle;
		handle = reinterpret_cast<HANDLE>(invalid_handle);
		return ret;
	}
	// 返回当前句柄
	HANDLE get()
	{
		return handle;
	}
};

using THANDLE = _THANDLE<>;
using THANDLEX = _THANDLE<reinterpret_cast<UINT_PTR>(INVALID_HANDLE_VALUE)>;

#endif // TKERNEL_WINVER > 0