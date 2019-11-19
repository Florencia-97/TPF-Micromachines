#include "VideoWriter.h"
#include "../../../config/constants.h"

extern "C" {
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

const std::string videoFileName = "micromachinesVideo.mp4";

VideoWriter::VideoWriter(SafeQueue<std::vector<char>>* vq)
    : context(), videoOutput(context, videoFileName) {
    videoQueue = vq;
    ctx = sws_getContext(BUFFER_WIDTH, BUFFER_HEIGHT,
                         AV_PIX_FMT_RGB24, BUFFER_WIDTH, BUFFER_HEIGHT,
                         AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
}

void VideoWriter::_run() {
    while (this->isAlive()){
        std::vector<char> dataBuffer = videoQueue->pop();
        if (dataBuffer.empty()){
            this->close();
            return;
        }
        videoOutput.writeFrame(dataBuffer.data(), ctx);
    }
}

VideoWriter::~VideoWriter(){
    videoOutput.close();
    sws_freeContext(ctx);
    BaseThread::close();
}