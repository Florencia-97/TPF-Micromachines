#ifndef FORMATCONTEXT_H
#define FORMATCONTEXT_H
#include <string>

class AVFormatContext;

class FormatContext {
    AVFormatContext *pFormatCtx;
public:
    FormatContext();
    ~FormatContext();
    AVFormatContext* getContext() const;
};
#endif
