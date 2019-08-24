// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_HTMLFORMATTER_H_
#define _SLOGLIB_HTMLFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include <sstream>
#include <iomanip>

namespace SLogLib {
;

// The HtmlFormatter class formats only all messages as HTML paragraphs.
// Different message levels are formatted in different colors.
class HtmlFormatter : public AbstractFormatter
{
public:

	explicit HtmlFormatter(NewLineFlag newLineFlag = DoNotAppendNewLine)
		: AbstractFormatter(newLineFlag), mInfoColor("black"), mWarnColor("coral"), 
	      mErrorColor("red"), mDebugColor("fuchsia"), mDetailColor("purple"), mBottomMargin(0.4)
	{}
	
	~HtmlFormatter()
	{}
	
	inline std::string infoColor()    const {return mInfoColor;}
	inline std::string warnColor()    const {return mWarnColor;}
	inline std::string errorColor()   const {return mErrorColor;}
	inline std::string debugColor()   const {return mDebugColor;}
	inline std::string detailColor()  const {return mDetailColor;}
	inline double      bottomMargin() const {return mBottomMargin;}

	inline void setInfoColor(const std::string& c)   {mInfoColor    = c;}
	inline void setWarnColor(const std::string& c)   {mWarnColor    = c;}
	inline void setErrorColor(const std::string& c)  {mErrorColor   = c;}
	inline void setDebugColor(const std::string& c)  {mDebugColor   = c;}
	inline void setDetailColor(const std::string& c) {mDetailColor  = c;}
	inline void setBottomMargin(double m)            {mBottomMargin = m;}
	

public:
	
	inline std::string FormatMessage(const Message& msg) const override
	{
		std::ostringstream _stream;
		
		if(msg.mUserMessage == "\n")
		{
			_stream << "<br/>";
		}
		else
		{
			_stream << "<p style=\"color:" << _getColor(msg.mLevel) << "; "
			        << "margin-left:1em; "
					<< "margin-right:1em; "
					<< "margin-top:0em; "
					<< "margin-bottom:" << mBottomMargin << "em;"
					<< "\">";
			_stream << msg.mUserMessage << "</p>";
		}
		return _stream.str();
	}


private:

	std::string _getColor(unsigned int level) const
	{
		if(level == eLevelInfo)
		{
			return mInfoColor;
		}
		else if(level == eLevelWarn)
		{
			return mWarnColor;
		}
		else if(level == eLevelError)
		{
			return mErrorColor;
		}
		else if(level == eLevelDebug)
		{
			return mDebugColor;
		}
		else if(level == eLevelDetail)
		{
			return mDetailColor;
		}
		return mInfoColor;
	}

private:
	
	std::string mInfoColor;
	std::string mWarnColor;
	std::string mErrorColor;
	std::string mDebugColor;
	std::string mDetailColor;
	double      mBottomMargin;
};

};	// End namespace SLogLib.

#endif // _SLOGLIB_HTMLFORMATTER_H_
