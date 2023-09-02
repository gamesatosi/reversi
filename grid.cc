#include "grid.h"

Grid::~Grid() {
    if (td != nullptr) delete td;
    if (ob != nullptr) delete ob;
    if (gd != nullptr) delete gd;
}


void Grid::setObserver(Observer<Info, State> *ob) {
    this->ob = ob;
}

bool Grid::isFull() const {
    int size = this->theGrid.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((theGrid[i][j]).getInfo().colour == Colour::NoColour) {
                return false;
            }
        }
    }
    return true;
}


Colour Grid::whoWon() const {
    int black = 0;
    int white = 0;
    int size = this->theGrid.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ((theGrid[i][j]).getInfo().colour == Colour::Black) {
                ++black;
            } else if ((theGrid[i][j]).getInfo().colour == Colour::White) {
                ++white;
            }
        }
    }
    if (black == white) {
        std::cout << "Tie!" << std::endl;
        gd->whoWon(Colour::NoColour);
        return Colour::NoColour;
    } else if (black > white) {
        std::cout << "Black wins!" << std::endl;
        gd->whoWon(Colour::Black);
        return Colour::Black;
    } else {
        std::cout << "White wins!" << std::endl;
        gd->whoWon(Colour::White);
        return Colour::White;
    }
}

void Grid::init(size_t n) {
    if (n < 4 || n % 2 != 0) { return;}
    if (td != nullptr) delete td;
    if (gd != nullptr) delete gd;
    int a = (int) n;
    this->td = new TextDisplay {a};
    this->gd = new GraphicsDisplay {500 / a};
    this->theGrid.clear();



    for (size_t r = 0; r < n; ++r) {
        std::vector<Cell> new_row;
        for (size_t c = 0; c < n; ++ c) {
            new_row.emplace_back(Cell{r, c});
        }
        this->theGrid.emplace_back(new_row);
    }
    setPiece(n / 2 - 1, n / 2 - 1, Colour::Black);
    setPiece(n / 2 - 1, n / 2, Colour::White);
    setPiece(n / 2, n / 2 - 1, Colour::White);
    setPiece(n / 2, n / 2, Colour::Black);
} 

bool Grid::setPiece(size_t r, size_t c, Colour colour) {
    int ro = (int) r;
    int co = (int) c;
    int size = (int) this->theGrid.size();
    if (ro >= 0 && ro < size && co >= 0 && co < size) {
        if (theGrid[r][c].getInfo().colour == Colour::NoColour) {  
            theGrid[r][c].setPiece(colour);
            theGrid[r][c].attach(td);
            theGrid[r][c].attach(gd);
            for (int row = ro - 1; row < ro + 2; ++row) {
                for (int col = co - 1; col < co + 2; ++col) {
                    if (row >= 0 && row < size && col >= 0 && col < size && !(row == ro && col == co)) {
                        theGrid[row][col].attach(&theGrid[ro][co]);
                    }
                }
            }
            toggle(r,c);
            return true;
        }
    }
    return false;
}

void Grid::toggle(size_t r, size_t c) {
    this->theGrid[r][c].notifyObservers();
}


std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}


