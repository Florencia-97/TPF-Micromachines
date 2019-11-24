#include "SoundSystem.h"
#include <iostream>
#include "../../config/constants.h"
#include "../../common/infostream/InfoBlock.h"

SoundSystem::SoundSystem(std::queue<std::string> *queue)
	: playSounds(true) {
  this->sound_queue = queue;
  this->lastSound = "";
}

void SoundSystem::init() {
  YAML::Node sounds = YAML::LoadFile("config/sound_configuration.yaml");
  Mix_Music *backgroundMusic = Mix_LoadMUS("client/sound_sys/sounds/background_song.mp3");
  if (backgroundMusic == nullptr) {
	printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());

  }
  // Starting to play music!
  Mix_PlayMusic(backgroundMusic, -1);
  Mix_VolumeMusic(MAX_VOLUME_BACKGROUND_SOUND);
  this->backgroundEffects.insert({SOUND_BACKGROUND, backgroundMusic});
  for (auto it = sounds.begin(); it != sounds.end(); ++it) {
	Mix_Chunk *soundN = Mix_LoadWAV(it->second.as<std::string>().c_str());
	if (soundN == nullptr) {
	  printf("Failed to load car wav sound sound effect! SDL_mixer Error: %s\n",
			 Mix_GetError());
	}
	Mix_VolumeChunk(soundN, MAX_VOLUME_EFFECTS_SOUND);
	this->musicEffects.insert({it->first.as<std::string>(), soundN});
  }
  std::cout << "Finished loading sounds\n";
}

void SoundSystem::play(bool inRace) {
  if (this->sound_queue->empty()) return;
  std::string event = this->sound_queue->front();
  this->sound_queue->pop();
  if (_controlSound(event)) return;
  if (Mix_PausedMusic() == 1) return;
  if (inRace && _controlCarSound(event)) return;
  if (event == SOUND_CAR_GEAR || event == VIDEO_RECORDING_ON_OFF
	  || (inRace && event != SOUND_ON_OFF && event != this->lastSound)) {
	if (event == SOUND_CAR_GEAR) {
	  Mix_PlayChannelTimed(1, this->musicEffects[event], 0, 580);
	  return;
	}
	Mix_PlayChannel(1, this->musicEffects[event], 0);
    this->lastSound = event;
  }
}

bool SoundSystem::_controlSound(std::string &event) {
  if (event != SOUND_ON_OFF) return false;
  if (Mix_PausedMusic() == 1) {
	Mix_ResumeMusic();
  } else {
	Mix_PauseMusic();
  }
  return true;
}

bool SoundSystem::_controlCarSound(std::string &event) {
  if (event == SOUND_CAR_RUN || event == SOUND_CAR_STOP) {
	Mix_PlayChannel(1, this->musicEffects[event], -1);
  } else if (event == SOUND_STOP_CAR_RUN || event == SOUND_CAR_STOP_NO) {
	Mix_HaltChannel(1);
  } else {
	return false;
  }
  this->lastSound = event;
  return true;
}

SoundSystem::~SoundSystem() {
  for (auto &backgroundEffect : this->backgroundEffects) {
	Mix_FreeMusic(backgroundEffect.second);
	backgroundEffect.second = nullptr;
  }
  for (auto &musicEffect : this->musicEffects) {
	Mix_FreeChunk(musicEffect.second);
	musicEffect.second = nullptr;
  }
}