#ifndef MICROMACHINES_SOUNDSYSTEM_H
#define MICROMACHINES_SOUNDSYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <queue>

class SoundSystem {
    bool playSounds;
    std::string lastSound;
    std::map<std::string, Mix_Chunk*> musicEffects;
    std::map<std::string, Mix_Music*> backgroundEffects;
    std::queue<std::string>* sound_queue;
    bool _controlSound(std::string& event);
    bool _controlCarSound(std::string& event);
public:
    explicit SoundSystem(std::queue<std::string> *sq);
    void play(bool inRace);
    void init();
    ~SoundSystem();
};


#endif //MICROMACHINES_SOUNDSYSTEM_H
