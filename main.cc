#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "textdisplay.h"
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  bool black = true;
  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      if (n >= 4 && n % 2 == 0) {
        black = true;
        g.init(n);
        std::cout << g;
      }
      // Add code here
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      if (black) {
        if (g.setPiece(r,c, Colour::Black)) {
          black = false;
          cout << g;
        }
      } else {
        if (g.setPiece(r,c, Colour::White)) {
          black = true;
          cout << g;
        }
      }
      if (g.isFull()) {
        g.whoWon();
        return 0;
      }
      // Add code here
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
