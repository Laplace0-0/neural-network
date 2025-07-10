// include/log.hpp
#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

// ANSI color codes
#define COLOR_RESET    "\033[0m"
#define COLOR_RED      "\033[1;31m"
#define COLOR_GREEN    "\033[1;32m"
#define COLOR_YELLOW   "\033[1;33m"
#define COLOR_BLUE     "\033[1;34m"
#define COLOR_CYAN     "\033[1;36m"
#define COLOR_BOLD     "\033[1m"

inline void log_error(const std::string& message) {
    std::cerr << COLOR_RED << "[Error] " << message << COLOR_RESET << std::endl;
}

inline void log_warn(const std::string& message) {
    std::cerr << COLOR_YELLOW << "[Warning] " << message << COLOR_RESET << std::endl;
}

inline void log_info(const std::string& message) {
    std::cout << COLOR_BLUE << "[Info] " << message << COLOR_RESET << std::endl;
}

inline void log_success(const std::string& message) {
    std::cout << COLOR_GREEN << "[Success] " << message << COLOR_RESET << std::endl;
}

#endif // LOG_HPP
