// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SLOGLIB_HTMLFORMATTER_H_
#define _SLOGLIB_HTMLFORMATTER_H_

#include "SLogLib/Formatters/AbstractFormatter.h"
#include "SLogLib/SysUtils.h"
#include <sstream>
#include <iomanip>

namespace SLogLib {
;

// The HtmlFormatter class formats only all messages as HTML paragraphs.
// Different message levels are formatted in different colors.
class HtmlFormatter : public AbstractFormatter
{
public:

	explicit HtmlFormatter(NewLine newLine = NewLine::No) noexcept
		: AbstractFormatter(newLine), mInfoColor("black"), mWarnColor("coral"), 
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
	
	inline std::string formatMessage(const Message& msg) const override
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
			
			// Insert a single non-breaking space for every white space character 
			// in the beginning of the message.
			for(char ch : msg.mUserMessage)
			{
				if(ch == ' ')
				{
					_stream << "&nbsp;";
				}
				else
				{
					break;
				}
			}
			
			_stream << msg.mUserMessage << "</p>";
		}
		return _stream.str();
	}


private:

	std::string _getColor(MessageLevel level) const
	{
		int _level = toInteger(level);
		if(_level == toInteger(MessageLevel::Info))
		{
			return mInfoColor;
		}
		else if(_level == toInteger(MessageLevel::Warn))
		{
			return mWarnColor;
		}
		else if(_level == toInteger(MessageLevel::Error))
		{
			return mErrorColor;
		}
		else if(_level == toInteger(MessageLevel::Debug))
		{
			return mDebugColor;
		}
		else if(_level == toInteger(MessageLevel::Detail))
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
