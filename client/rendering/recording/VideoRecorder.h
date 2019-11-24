#ifndef MICROMACHINES_VIDEORECORDER_H
#define MICROMACHINES_VIDEORECORDER_H

#include <SDL_render.h>
#include "../common/SafeQueue.h"
#include "FormatContext.h"
#include "OutputFormat.h"
#include "VideoWriter.h"

class VideoRecorder {
    SDL_Texture *videoTexture = nullptr;
    SafeQueue<std::vector<char>> videoQueue;
    VideoWriter *videoWriter;
    bool rec;
    std::vector<char> dataBuffer;
    SDL_Rect mBox;

public:
    VideoRecorder();
    bool get_rec_value();
    void init(SDL_Renderer *render);
    void setTarget(SDL_Renderer *render);
    void record(SDL_Renderer *render);
    ~VideoRecorder();
    void set_rec_value(bool valueForRec);
};

#endif //MICROMACHINES_VIDEORECORDER_H
