// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_ADDTOCALLSTACK_H_
#define _SLOGLIB_ADDTOCALLSTACK_H_

#include "SLogLib/Config.h"
#include "SLogLib/DisableCopy.h"
#include <string>

namespace SLogLib {
;

// The AddToCallStack structure is a used to automatically add and remove function calls to 
// the call stack. The constructor adds the function call and destructor removes it.
struct SLOGLIB_DLL_API AddToCallStack
{
	AddToCallStack(const std::string& fileName, const std::string& funcName, unsigned int lineNumber);
	~AddToCallStack();

private:

	S_DISABLE_COPY(AddToCallStack);
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_ADDTOCALLSTACK_H_
