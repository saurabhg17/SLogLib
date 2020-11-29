// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "Types.h"

namespace SLogLib {
;

static const std::string _messageLevelStr[] = {"None", "Fatal", "Error", "Warn", "Info", "Debug", "Detail", "All"};

std::string toString(const MessageLevel& messageLevel)
{
	return _messageLevelStr[static_cast<size_t>(messageLevel)];
}

};
