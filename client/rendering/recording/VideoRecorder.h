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
    // Return whether recording is on or not
    bool get_rec_value();
    // Starts recorder
    void init(SDL_Renderer *render);
    // Sets render target to video Texture
    void setTarget(SDL_Renderer *render);
    // Records what is rendered in buffer, and pushes it in queue
    void record(SDL_Renderer *render);
    // Changes state of  recorder
    void set_rec_value(bool valueForRec);
    ~VideoRecorder();
};

#endif //MICROMACHINES_VIDEORECORDER_H
