#include "cell.h"
#include <iostream>

Cell::Cell(size_t r, size_t c) : r{r}, c{c} {}

void Cell::setPiece(Colour colour) {
    this->colour = colour;
    this->setState(State{StateType::NewPiece, colour});
}

void Cell::toggle() {
    this->colour = this->getState().colour;
}


Direction reverse(Direction d) {
    if (d == Direction::N) {
        return Direction::S;
    } else if (d == Direction::NE) {
        return Direction::SW;
    } else if (d == Direction::E) {
        return Direction::W;
    } else if (d == Direction::SE) {
        return Direction::NW;
    } else if (d == Direction::S) {
        return Direction::N;
    } else if (d == Direction::SW) {
        return Direction::NE;
    } else if (d == Direction::W) {
        return Direction::E;
    } else if (d == Direction::NW) {
        return Direction::SE;
    }
    return Direction::N;
}



void Cell::notify(Subject<Info, State> &whoFrom) {
    Info n = whoFrom.getInfo();
    Direction d;
    StateType s;
    // find direction from
    if (n.row - this->r == 1 && n.col == this->c) {
        d = Direction::S;
    } else if (n.row - this->r == 1 && n.col - this->c == 1) {
        d = Direction::SE;
    } else if (n.row == this->r && n.col - this->c == 1) {
        d = Direction::E;
    } else if (this->r - n.row == 1 && n.col - this->c == 1) {
        d = Direction::NE;
    } else if (this->r - n.row == 1 && n.col == this->c) {
        d = Direction::N;
    } else if (this->r - n.row == 1 && this->c - n.col == 1) {
        d = Direction::NW;
    } else if (this->r == n.row && this->c - n.col == 1) {
        d = Direction::W;
    } else if (n.row - this->r == 1 && this->c - n.col == 1) {
        d = Direction::SW;
    }

    if (this->colour == whoFrom.getState().colour) {
        s = StateType::Reply;
    } else if (this->colour == Colour::NoColour) {
        return;
    } else {
        s = StateType::Relay;
    }

    if (whoFrom.getState().type == StateType::NewPiece) {
        this->setState(State{s, n.colour, d});
        this->notifyObservers();
    } else if (whoFrom.getState().type == StateType::Relay) {
        if (d == whoFrom.getState().direction) {
            this->setState(State{s, whoFrom.getState().colour, d});
            this->notifyObservers();
        }
    } else if (whoFrom.getState().type == StateType::Reply) {
        if (this->getState().type == StateType::Relay && reverse(d) == whoFrom.getState().direction) { // if it is not seted, it will be nocolour. if it is setted before, direction will not be the same.
                this->toggle();
                this->setState(State{StateType::Reply, n.colour, whoFrom.getState().direction});
                this->notifyObservers();
        }
    }
}

Info Cell::getInfo() const {
    return Info{this->r, this->c, this->colour};
}





