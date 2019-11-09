#include "SoundSystem.h"
#include <iostream>
#include "../../config/constants.h"

SoundSystem::SoundSystem(std::queue<std::string> *sound_queue)
    : playSounds(true) {
    this->sound_queue = sound_queue;
}

void SoundSystem::init(){
    // TODO: yaml file of sounds!
    this->backgroundMusic = Mix_LoadMUS( "client/sound_sys/sounds/background_song.mp3" );
    if (this->backgroundMusic == nullptr){
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        // Should raise an error?
    }
    Mix_PlayMusic(this->backgroundMusic, 1);
    Mix_Chunk* carsStarting = Mix_LoadWAV( "client/sound_sys/sounds/car_start.wav" );
    if( carsStarting == nullptr ) {
        printf( "Failed to load car starting sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        // Again, should i raise error?
    }
    this->musicEffects.insert({SOUND_CAR_RUN, carsStarting});
    std::cout << "Finished loading sounds\n";
}

void SoundSystem::play(){
    if (this->sound_queue->empty()) return; //check this
    std::string event = this->sound_queue->front();
    this->sound_queue->pop();
    if (_controlSound(event)) return;
    if (Mix_PausedMusic() == 1) return;
    Mix_PlayChannel( -1, this->musicEffects[event], 0 );
}

bool SoundSystem::_controlSound(std::string& event){
    if (event != SOUND_ON_OFF) return false;
    if( Mix_PausedMusic() == 1 ){
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
    return true;
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