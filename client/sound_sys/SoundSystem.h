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
    void _loadSounds();
public:
    SoundSystem(std::queue<std::string> *sq);
    void play();
    ~SoundSystem();
};


#endif //MICROMACHINES_SOUNDSYSTEM_H
