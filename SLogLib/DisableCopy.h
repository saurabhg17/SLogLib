
#ifndef __SUTILS_DISABLE_COPY_H_
#define __SUTILS_DISABLE_COPY_H_

#define S_DISABLE_COPY(Class)      \
    Class(const Class& ) = delete; \
	Class(const Class&&) = delete;

#endif // __SUTILS_DISABLE_COPY_H_
