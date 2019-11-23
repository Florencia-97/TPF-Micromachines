#ifndef FORMATCONTEXT_H
#define FORMATCONTEXT_H
#include <string>

class AVFormatContext;

class FormatContext {
public:
    FormatContext();
    ~FormatContext();
    AVFormatContext* getContext() const;
private:
    AVFormatContext *pFormatCtx;
};
#endif
