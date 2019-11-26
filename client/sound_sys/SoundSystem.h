#ifndef MICROMACHINES_SOUNDSYSTEM_H
#define MICROMACHINES_SOUNDSYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <queue>
#include <common/ThreadQueue.h>

class SoundSystem {
  bool playSounds;
  std::string lastSound;
  std::map<std::string, Mix_Chunk *> musicEffects;
  std::map<std::string, Mix_Music *> backgroundEffects;
  ThreadQueue *sound_queue;
  static bool _controlSound(std::string &event);
  bool _controlCarSound(std::string &event);
 public:

  /*Builder of the class SoundSystem*/
  explicit SoundSystem(ThreadQueue *queue);

  /*Initializes all the components of the object for later use. It is necessary
   * to execute this function first of all for the correct operation of the
   * object*/
  void init();

  /*Plays the music if inRace is true*/
  void play(bool inRace);

  /*Destroyer of the class*/
  ~SoundSystem();
};

#endif //MICROMACHINES_SOUNDSYSTEM_H
