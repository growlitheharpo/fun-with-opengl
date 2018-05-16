#pragma once
#include <iostream>

#define LOG_ERR(x) std::cerr << x << std::endl
#define LOG(x) std::cout << x << std::endl

#ifndef NDEBUG

#define DEBUG_IF(x, y) { if (x) { y; } }
#define DEBUG_IF_ELSE(x, y, z) { if (x) { y; } else { z; } }

#define DLOG_ERR(x) LOG_ERR(x)
#define DLOG(x) LOG(x)

#else

#define DEBUG_IF(x, y) {;}
#define DEBUG_IF_ELSE(x, y, z) {;}

#define DLOG_ERR(x) {;}
#define DLOG(x) {;}

#endif
