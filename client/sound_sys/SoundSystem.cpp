#include "SoundSystem.h"
#include <iostream>
#include "../../config/constants.h"

SoundSystem::SoundSystem(std::queue<std::string> *sound_queue)
    : playSounds(true) {
    this->sound_queue = sound_queue;
    _loadSounds();
}

void SoundSystem::_loadSounds(){
    // TODO: yaml file of sounds!
    std::cout << "Loading sounds\n";
}

void SoundSystem::play(){
    if ( !this->playSounds || this->sound_queue->empty()) return;
    std::string event = this->sound_queue->front();
    this->sound_queue->pop();
    if (_controlSound(event)) return;
    Mix_PlayChannel( -1, this->musicEffects[event], 0 );
}

bool SoundSystem::_controlSound(std::string& event){
    if (event == SOUND_ON_OFF){
        this->playSounds = !this->playSounds;
        return true;
    }
    return false;
}

SoundSystem::~SoundSystem(){
    Mix_FreeMusic(this->backgroundMusic);
    this->backgroundMusic = nullptr;
    for (auto it=this->musicEffects.begin(); it!=this->musicEffects.end(); ++it){
        std::cout << "Releasing sound: " << it->first << std::endl;
        Mix_FreeChunk(it->second);
        it->second = nullptr;
    }
}