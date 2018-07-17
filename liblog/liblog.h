
#ifndef __LIB_LOG_H__
#define __LIB_LOG_H__

#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

enum log_lvl
{
	ERROR, WARNING, INFO, VERBOSE, DEBUG, 
};
void set_logfd(int logfd);
void print_log(enum log_lvl lvl, const char *file, const char *func, int line, const char *fmt, ...);

const char *get_time_stamp(char *time_buf, int buf_len, const char *fmt);
time_t get_time_sec();
time_t get_time_msec();
time_t get_time_usec();

void print_stacktrace();

//#ifdef __PRETTY_FUNCTION__
//#define LOG(_lvl_, _fmt_, ...) print_log(_lvl_, __FILE__, __PRETTY_FUNCTION__, __LINE__, _fmt_, ##__VA_ARGS__)
//#else
//#define LOG(_lvl_, _fmt_, ...) print_log(_lvl_, __FILE__, __FUNCTION__, __LINE__, _fmt_, ##__VA_ARGS__)
//#endif
#define LOG(_lvl_, _fmt_, ...) print_log(_lvl_, __FILE__, __PRETTY_FUNCTION__, __LINE__, _fmt_, ##__VA_ARGS__)

#define E(_fmt_, ...) LOG(ERROR, _fmt_, ##__VA_ARGS__)
#define W(_fmt_, ...) LOG(WARNING, _fmt_, ##__VA_ARGS__)
#define I(_fmt_, ...) LOG(INFO, _fmt_, ##__VA_ARGS__)
#define V(_fmt_, ...) LOG(VERBOSE, _fmt_, ##__VA_ARGS__)
#define D(_fmt_, ...) LOG(DEBUG, _fmt_, ##__VA_ARGS__)

#include <string.h>
#include <errno.h>
#define ERRSTR strerror(errno)

#ifdef __cplusplus
}
#endif

#endif

