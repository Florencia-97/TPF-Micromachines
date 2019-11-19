#ifndef MICROMACHINES_VIDEORECORDER_H
#define MICROMACHINES_VIDEORECORDER_H

#include <SDL_render.h>
#include <common/SafeQueue.h>
#include "FormatContext.h"
#include "OutputFormat.h"
#include "VideoWriter.h"

class VideoRecorder{
    SDL_Texture* videoTexture = nullptr;
    SafeQueue<std::vector<char>> videoQueue;
    VideoWriter* videoWriter;
public:
    VideoRecorder();
    void init(SDL_Renderer* render);
    void record(SDL_Renderer* render);
    ~VideoRecorder();
};


#endif //MICROMACHINES_VIDEORECORDER_H
