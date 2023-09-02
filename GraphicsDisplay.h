#ifndef __GRAPHICS_DISPLAY_H__
#define __GRAPHICS_DISPLAY_H__


#include "window.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "state.h"



class GraphicsDisplay: public Observer<Info, State> {
    Xwindow win; // store the window
    int length; //length of each chess

  public:
    GraphicsDisplay(int length); // ctor
    void notify(Subject<Info, State> &whoNotified) override; 
    void whoWon(Colour colour);
};

#endif
