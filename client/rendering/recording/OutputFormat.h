#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H
#include <string>

class AVCodec;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVCodecContext;
class FormatContext;
class SwsContext;

class OutputFormat {
private:
    void initFrame();
    // Starts codec context
    void codecContextInit(AVCodec* codec);
    FormatContext& context;
    AVOutputFormat* avOutputFormat;
    AVCodecContext* codecContext;
    int currentPts;
    FILE* outputFile;
    AVFrame* frame;
    AVPacket* pkt;
    int video_width;
    int video_height;
public:
    OutputFormat(FormatContext& cxt, const std::string& fn, int w, int h);

    // Writes frame to disk, Uses swsContext to convert from RGB24 to YUV420p
    void writeFrame(const char* data, SwsContext* swsContext);

    // Closes video stream
    void close();

    ~OutputFormat();
};
#endif
