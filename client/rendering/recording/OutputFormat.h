#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H
#include <string>

class AVCodec;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVStream;
class AVCodecContext;
class FormatContext;
class SwsContext;

class OutputFormat {
public:
    // Ctor
    OutputFormat(FormatContext& context, const std::string& filename, int w, int h);
    // Dtor
    ~OutputFormat();
    // Escribe un frame a disco. Utiliza `swsContext` para convertir
    // de RGB24 a YUV420p
    void writeFrame(const char* data, SwsContext* swsContext);
    // Cierra el stream de video
    void close();
private:
    // Inicializa frame
    void initFrame();
    // Inicializa contexto de codec
    void codecContextInit(AVCodec* codec);
    FormatContext& context;
    AVOutputFormat* avOutputFormat;
    AVStream* video_avstream;
    AVCodecContext* codecContext;
    int currentPts;
    FILE* outputFile;
    AVFrame* frame;
    AVPacket* pkt;
    int video_width;
    int video_height;
};
#endif
