#include "GraphicsDisplay.h"
#include <iostream>

GraphicsDisplay::GraphicsDisplay(int length): length{length} {
    win.fillRectangle(0, 0, 500, 500, win.Blue);
}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified){
    State s = whoNotified.getState();
    Info i = whoNotified.getInfo();
    if (s.type == StateType::NewPiece) {
        if (i.colour == Colour::Black) {
            win.fillRectangle(length * i.col, length * i.row, length, length, win.Black);
        } else if (i.colour == Colour::White) {
            win.fillRectangle(length * i.col, length * i.row, length, length, win.White);
        }
    }
    if (s.type == StateType::Reply) {
        if (s.colour == Colour::Black) {
            win.fillRectangle(length * i.col, length * i.row, length, length, win.Black);
        } else if (s.colour == Colour::White) {
            win.fillRectangle(length * i.col, length * i.row, length, length, win.White);
        }
    }
}

void GraphicsDisplay::whoWon(Colour colour){
    
    if (colour == Colour::Black) {
        win.drawString(220,220,"Black wins!");
    } else if (colour == Colour::White) {
        win.drawString(220,220,"White wins!");
    } else if (colour == Colour::NoColour) {
        win.drawString(240,240,"Tie!");
    }
}




