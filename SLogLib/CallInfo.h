
// This file is part of SLogLib; you can redistribute it and/or
// modify it under the terms of the MIT License.
// 
// Copyright (c) 2015 Saurabh Garg
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
// Author(s): Saurabh Garg

#ifndef _SLOGLIB_CALLINFO_H_
#define _SLOGLIB_CALLINFO_H_

#include <string>
#include <vector>

namespace SLogLib {
;

// The CallInfo structure stores the information of a single function call.
struct CallInfo
{
	std::string  mFileName;    // The name of the file containing the function.
	std::string  mFuncName;    // The name of the function.
	unsigned int mLineNumber;  // The line number at which SLOGLIB_ADD_TO_CALLSTACK macro was 
	                           // inserted in the function.
	
	CallInfo()
		: mLineNumber(0)
	{}
	CallInfo(const std::string& fileName, const std::string& funcName, unsigned int lineNumber)
		: mFileName(fileName), mFuncName(funcName), mLineNumber(lineNumber)
	{}
	
	bool operator != (const CallInfo& B)
	{
		return !(B.mFileName==mFileName && B.mFuncName==mFuncName && B.mLineNumber==mLineNumber);
	}
};

// Define a type for storing array of CallInfo's forming a CallStack.
typedef std::vector<CallInfo> CallStack;

};	// End namespace SLogLib.

#endif // _SLOGLIB_CALLINFO_H_
