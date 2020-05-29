
#ifndef __SUTILS_DISABLE_COPYMOVE_H_
#define __SUTILS_DISABLE_COPYMOVE_H_

#define S_DISABLE_COPYMOVE(Class)             \
    Class(const Class& ) = delete;            \
	Class(const Class&&) = delete;            \
	Class& operator=(const Class& ) = delete; \
    Class& operator=(const Class&&) = delete;

#endif // __SUTILS_DISABLE_COPYMOVE_H_
