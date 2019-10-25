
#include "Car.h"

Car::Car(){
    //Initialize the collision box
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = DOT_WIDTH;
    mBox.h = DOT_HEIGHT;

}

void Car::setCamera( SDL_Rect& camera ){
    //Center the camera over the dot
    camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 ) camera.x = 0;
    if( camera.y < 0 ) camera.y = 0;
    if( camera.x > LEVEL_WIDTH - camera.w ) camera.x = LEVEL_WIDTH - camera.w;
    if( camera.y > LEVEL_HEIGHT - camera.h ) camera.y = LEVEL_HEIGHT - camera.h;
}

void Car::render( SDL_Rect& camera ){
    gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );
}