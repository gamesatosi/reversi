#include "textdisplay.h"
#include "subject.h"


TextDisplay::TextDisplay(int n) : gridSize{n} {
    for (int i = 0; i < n; ++i) {
        std::vector<char> v;
        for (int j = 0; j < n; ++j) {
            v.emplace_back('-');
        }
        this->theDisplay.emplace_back(v);
    }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    State s = whoNotified.getState();
    Info i = whoNotified.getInfo();
    if (s.type == StateType::NewPiece) {
        if (i.colour == Colour::Black) {
            this->theDisplay[i.row][i.col] = 'B';
        } else if (i.colour == Colour::White) {
            this->theDisplay[i.row][i.col] = 'W';
        }
    }
    if (s.type == StateType::Reply) {
        if (s.colour == Colour::Black) {
            this->theDisplay[i.row][i.col] = 'B';
        } else if (s.colour == Colour::White) {
            this->theDisplay[i.row][i.col] = 'W';
        }
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 0; i < td.gridSize; ++i) {
        for (int j = 0; j < td.gridSize; ++j) {
            out << td.theDisplay[i][j];
        }  
        out << std::endl;
    }
    return out;
}











