#ifndef ZLOG_CPP_H
#define ZLOG_CPP_H

#include <zlog.h>
#include <sstream>

class ZlogCPP
{
public:
    ZlogCPP(const char* cat, const char* file_name, int sizeof_file_name, const char* func_name, int sizeof_func_name, int line,  zlog_level level)
        :_cat(zlog_get_category(cat)),_file_name(file_name),_sizeof_file_name(sizeof_file_name),_func_name(func_name),_sizeof_func_name(sizeof_func_name),_line(line),_level(level)
    {

    }
    ~ZlogCPP()
    {
        zlog(_cat, _file_name, _sizeof_file_name, _func_name, _sizeof_func_name,_line,_level,"%s", ss.str().data());
    }


    std::stringstream ss;

private:
    zlog_category_t* _cat = nullptr;
    const char* _file_name;
    int _sizeof_file_name;
    const char* _func_name;
    int _sizeof_func_name;
    int _line;
    zlog_level _level;

};

#define ZLOGD(TAG)  ZlogCPP(TAG, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__,ZLOG_LEVEL_DEBUG).ss
#define ZLOGI(TAG)  ZlogCPP(TAG, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__,ZLOG_LEVEL_INFO).ss
#define ZLOGW(TAG)  ZlogCPP(TAG, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__,ZLOG_LEVEL_WARN).ss
#define ZLOGE(TAG)  ZlogCPP(TAG, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__,ZLOG_LEVEL_ERROR).ss


#endif // ZLOG_CPP_H
