#ifndef _CAR_
#define _CAR_


class Car{
    public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Initializes the variables
    Dot();

    //Centers the camera over the dot
    void setCamera( SDL_Rect& camera );

    //Shows the dot on the screen
    void render( SDL_Rect& camera );

    private:
    //Collision box of the dot
    SDL_Rect mBox;
};

#endif