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

VideoRecorder::VideoRecorder() : rec(false) {}

void VideoRecorder::init(SDL_Renderer* render){
    // TODO: see if i can use the class texture loader here
    videoTexture = SDL_CreateTexture(render,
                                     SDL_PIXELFORMAT_RGB24,
                                     SDL_TEXTUREACCESS_TARGET, BUFFER_WIDTH, BUFFER_HEIGHT);
    videoWriter = new VideoWriter(&videoQueue, BUFFER_WIDTH, BUFFER_HEIGHT);
    videoWriter->run();
    std::cout << "All created correctly\n";
}

void VideoRecorder::setTarget(SDL_Renderer* render){
    SDL_SetRenderTarget(render, videoTexture);
}

void VideoRecorder::record(SDL_Renderer* render){
    std::vector<char> dataBuffer(BUFFER_WIDTH * BUFFER_HEIGHT * 3);
    int r = SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_RGB24, dataBuffer.data(), BUFFER_WIDTH * 3);
    if (r){
        std::cout << r << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RendererReadPixels error", SDL_GetError(), NULL);
        std::cout << "Error when rendering read pixels\n";
        return;
    }
    videoQueue.push(dataBuffer);
}

VideoRecorder::~VideoRecorder(){
    if (!rec) return;
    std::vector<char> pill;
    videoQueue.push(pill);
    if (videoTexture != nullptr) {
        SDL_DestroyTexture(videoTexture);
    }
    videoWriter->close();
    videoWriter->join();
    delete(videoWriter);
}
bool VideoRecorder::get_rec_value() {
  return rec;
}
void VideoRecorder::set_rec_value(bool valueForRec) {
  this->rec = valueForRec;

}

