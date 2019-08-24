// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_TYPES_H_
#define _SLOGLIB_TYPES_H_

namespace SLogLib {
;

// Levels indicating severity of message.
enum MessageLevel
{
	eLevelInfo,
	eLevelWarn,
	eLevelError,
	eLevelDebug,
	eLevelDetail,
};

enum NewLineFlag
{
	DoNotAppendNewLine = 0,
	AppendNewLine      = 1
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_TYPES_H_
