#ifndef MICROMACHINES_SOUNDSYSTEM_H
#define MICROMACHINES_SOUNDSYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <queue>

class SoundSystem {
    bool playSounds;
    std::map<std::string, Mix_Chunk *> musicEffects;
    Mix_Music* backgroundMusic;
    std::queue<std::string>* sound_queue;
    bool _controlSound(std::string& event);
public:
    SoundSystem(std::queue<std::string> *sq);
    void play();
    void init();
    ~SoundSystem();
};


#endif //MICROMACHINES_SOUNDSYSTEM_H
