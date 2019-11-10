#include <SDL2/SDL.h>
#include <iostream>

#include "UserInput.h"
#include "../../config/constants.h"
#include "../common/SafeQueue.h"

UserInput::UserInput(SafeQueue<InfoBlock> *safeQueueServer,
                     SafeQueue<InfoBlock> *safeQueueClient,
                     std::queue<SDL_Event> *mouse_queue,
                     std::queue<SDL_Event> *text_queue,
                     std::queue<std::string> *sound_queue) {
    // TODO assign to class safeQueue a way of being past without pointer
    this->keyboard_input = safeQueueServer;
    this->mouse_input = safeQueueClient;
    this->mouse_queue = mouse_queue;
    this->writing_queue = text_queue;
    this->sound_queue = sound_queue;
    key_pressings[UP] = false;
    key_pressings[DOWN] = false;
    key_pressings[LEFT] = false;
    key_pressings[RIGHT] = false;
}

void UserInput::_run(){
  SDL_StartTextInput();
    SDL_Event e;
    std::cout << "Starting to read input keys from client\n";
    while (this->isAlive()){
        while( SDL_WaitEvent(&e)!= 0 && this->isAlive()) {
            _rcvKeyInput(e);
        }
    }
  SDL_StopTextInput();
}

void UserInput::_rcvKeyInput(SDL_Event &e){

  if (e.type == SDL_QUIT) {
        InfoBlock ib;
        ib[ACTION_TYPE] = QUIT;
        this->mouse_input->push(ib);
        this->keyboard_input->push(ib);
        this->close();
        return;
    }
    char eventType = '\n';
    std::string actionType = "\n";
    bool event_value = false;
  switch (e.type){
    case SDL_MOUSEBUTTONDOWN:mouse_queue->push(e);
            eventType = MOUSE_BUTTON_DOWN;
            break;
    case SDL_MOUSEBUTTONUP:mouse_queue->push(e);
            eventType = MOUSE_BUTTON_UP;
            break;
    case SDL_TEXTINPUT:;
      writing_queue->push(e);
      break;
    case SDL_KEYDOWN:actionType = ACTION_TYPE;
            event_value = true;
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    eventType = UP;
                    sound_queue->push(SOUND_CAR_RUN);
                    break;
                case SDLK_DOWN:
                    eventType = DOWN;
                    sound_queue->push(SOUND_CAR_STOP);
                    break;
                case SDLK_LEFT:
                    eventType = LEFT;
                    break;
                case SDLK_RIGHT:
                    eventType = RIGHT;
                    break;
              default:writing_queue->push(e);
                    return;
            }
            break;
        case SDL_KEYUP:
            actionType = ACTION_TYPE_DOWN;
            event_value = false;
            switch (e.key.keysym.sym) {
                case SDLK_0: // we can change the key later on!
                    sound_queue->push(SOUND_ON_OFF);
                    return;
                case SDLK_UP:
                    if (e.key.state == SDL_RELEASED) {
                        eventType = UP;
                        sound_queue->push(SOUND_STOP_CAR_RUN);
                    }
                    break;
                case SDLK_DOWN:
                    if (e.key.state == SDL_RELEASED){
                        eventType = DOWN;
                        sound_queue->push(SOUND_CAR_STOP_NO);
                    }
                    break;
                case SDLK_LEFT:
                    if (e.key.state == SDL_RELEASED) eventType = LEFT;
                    break;
                case SDLK_RIGHT:
                    if (e.key.state == SDL_RELEASED) eventType = RIGHT;
                    break;
                default:
                    return;
            }
        default:
            break;
    }

    if( actionType == "\n") return;
    if (key_pressings[eventType] == event_value) return;
    key_pressings[eventType] = event_value;

    // For keys to send to server
    //Creating infoblock to mouse_queue in EventsQueue
    InfoBlock ib;
    ib[actionType] = eventType;
    keyboard_input->push(ib);
}

void UserInput::close() {
    this->keyboard_input->setOpen(false);
    this->mouse_input->setOpen(false);
    BaseThread::close();
}