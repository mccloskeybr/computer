#ifndef COMMON_LOG_H
#define COMMON_LOG_H

#define LOG_FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG(Callback, fmt, ...) Callback(SDL_LOG_CATEGORY_APPLICATION, "%s:%d: -- "fmt, LOG_FILENAME, __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG(SDL_LogDebug, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG(SDL_LogInfo, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG(SDL_LogWarn, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG(SDL_LogError, fmt, ##__VA_ARGS__)

#endif
