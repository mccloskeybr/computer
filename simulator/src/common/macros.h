#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#define KILOBYTES(val) ((val)*1024LL)
#define MEGABYTES(val) (KILOBYTES(val)*1024LL)
#define GIGABYTES(val) (MEGABYTES(val)*1024LL)
#define TERABYTES(val) (GIGABYTES(val)*1024LL)

#define BIT(val) 1 << (val)

#define STATIC_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#define FILE_AND_LINE__(A, B) A "|" #B
#define FILE_AND_LINE_(A, B) FILE_AND_LINE__(A, B)
#define FILE_AND_LINE FILE_AND_LINE_(__FILE__, __LINE__)

#ifdef DEBUG
#define ASSERT(exp) if (!(exp)) { *(int*)0 = 0; }
#else
#define ASSERT(exp) (exp)
#endif

#ifdef DEBUG
#define STATIC_ASSERT(exp, msg) static_assert((exp), msg)
#else
#define STATIC_ASSERT(exp)
#endif

#define UNIMPLEMENTED() ASSERT(false)
#define UNREACHABLE() ASSERT(false)
#define TODO() ASSERT(false)

#endif
