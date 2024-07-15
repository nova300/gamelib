#pragma once
#include <stdio.h>

#define PRINT_LOGS

#ifdef PRINT_LOGS

#define LOG_PRINT(fmt, args...) fprintf(stderr, "LOG: %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##args)

#define LOG_ASSERT(condition,fmt, args...) if(condition) fprintf(stderr, "LOG_ASSERT: %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##args)

#define LOG_ASSERT_RETURN(condition,fmt, args...) if(condition) {fprintf(stderr, "LOG_ASSERT_RETURN: %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##args); return;}

#define LOG_RETURN(fmt, args...) {fprintf(stderr, "LOG_RETURN: %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##args); return;}

#else

#define PRINTERROR(fmt, args...)
#define LOG_ASSERT(condition,fmt, args...)
#define LOG_ASSERT_RETURN(condition,fmt, args...)

#endif