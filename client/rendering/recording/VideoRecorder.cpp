#include <vector>
#include <iostream>
#include <SDL_messagebox.h>
#include "VideoRecorder.h"
#include <SDL_pixels.h>
#include "../../../config/constants.h"

extern "C" {
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}
const std::string videoFileName = "micromachinesVideo.mp4";

VideoRecorder::VideoRecorder() {}

void VideoRecorder::init(SDL_Renderer* render){
    // TODO: see if i can use the class texture loader here
    videoOutput = new OutputFormat(context, videoFileName);
    ctx = sws_getContext(BUFFER_WIDTH, BUFFER_HEIGHT,
                         AV_PIX_FMT_RGB24, BUFFER_WIDTH, BUFFER_HEIGHT,
                         AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
    videoTexture = SDL_CreateTexture(render,
                                     SDL_PIXELFORMAT_RGB24,
                                     SDL_TEXTUREACCESS_TARGET, BUFFER_WIDTH, BUFFER_HEIGHT);
    std::cout << "All created correctly\n";
}

void VideoRecorder::record(SDL_Renderer* render){
    // TODO: stop button!
    SDL_SetRenderTarget(render, videoTexture);
    std::vector<char> dataBuffer(BUFFER_WIDTH * BUFFER_HEIGHT * 3);
    std::cout << "Hello\n";
    int r = SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_RGB24, dataBuffer.data(), BUFFER_WIDTH * 3);
    if (r){
        std::cout << r << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RendererReadPixels error", SDL_GetError(), NULL);
        std::cout << "Error when rendering read pixels\n"; // I dont wanna throw an error, at least for now
        return;
    }
    std::cout << "good\n";
    videoOutput->writeFrame(dataBuffer.data(), ctx);
    std::cout << "bye\n";
}

VideoRecorder::~VideoRecorder(){
    std::cout << "lalala\n";
    videoOutput->close();
    if (videoTexture != nullptr) {
        SDL_DestroyTexture(videoTexture);
    }
    sws_freeContext(ctx);
    delete(videoOutput);
}

