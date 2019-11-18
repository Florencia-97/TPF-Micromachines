#ifndef MICROMACHINES_VIDEORECORDER_H
#define MICROMACHINES_VIDEORECORDER_H

#include <SDL_render.h>
#include "FormatContext.h"
#include "OutputFormat.h"

class VideoRecorder{
    FormatContext context;
    OutputFormat* videoOutput;
    SwsContext* ctx = nullptr;
    SDL_Texture* videoTexture = nullptr;
public:
    VideoRecorder();
    void init(SDL_Renderer* render);
    void record(SDL_Renderer* render);
    ~VideoRecorder();
};


#endif //MICROMACHINES_VIDEORECORDER_H
