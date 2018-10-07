#pragma once
#include <iostream>

#define LOG_ERR(x) std::cerr << x << std::endl
#define LOG(x) std::cout << x << std::endl

#ifndef NDEBUG

#define DEBUG_IF(x, y) do { if (x) { y; } } while (false)
#define DEBUG_IF_ELSE(x, y, z) do { if (x) { y; } else { z; } } while (false)

#define DLOG_ERR(x) LOG_ERR(x)
#define DLOG(x) LOG(x)

#define DEBUG_STATEMENT(x) do { x } while(false)

#else

#define DEBUG_IF(x, y) {;}
#define DEBUG_IF_ELSE(x, y, z) {;}

#define DLOG_ERR(x) {;}
#define DLOG(x) {;}

#define DEBUG_STATEMENT(x) do {} while(false)

#endif
