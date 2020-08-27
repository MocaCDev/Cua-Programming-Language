#ifndef FUNCTION_SHORTCUTS
#define FUNCTION_SHORTCUTS

typedef void(*destory)(void* ptr);

#define CLOSE(err_code) exit(err_code)
#define RAISE_ERROR(msg, err_code, ...) fprintf(stderr,msg, ##__VA_ARGS__), CLOSE(err_code)

#endif