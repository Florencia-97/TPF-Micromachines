#ifndef MICROMACHINES_VIDEOWRITER_H
#define MICROMACHINES_VIDEOWRITER_H

#include "../common/conc/BaseThread.h"
#include <vector>
#include "../common/SafeQueue.h"
#include "OutputFormat.h"
#include "FormatContext.h"

class VideoWriter : public BaseThread{
    FormatContext context;
    SafeQueue<std::vector<char>>* videoQueue;
    OutputFormat videoOutput;
    SwsContext* ctx = nullptr;
    void _run() override;
public:
    VideoWriter(SafeQueue<std::vector<char>>* vq, int w, int h);
    ~VideoWriter();
};


#endif //MICROMACHINES_VIDEOWRITER_H
