// Play peg puzzles!
// $Revision: 1.1 $
//   $Log: pegPuzzles.cpp,v $
//   Revision 1.1  2017/03/29 13:47:31  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
#include <iostream>
#include "term.h"
#include "insanity.h"
#include "application.h"

using namespace std;

int main()
{
    //make the parts
    Insanity *puzzle = new Insanity();
    Application *app = new Application();
    
    
    //put them together
    app->child(puzzle);
    
    //and go!
    cout << cursorOff;
    cout.flush();
    app->eventLoop();
    cout << cursorOn << normal << clearScreen << endl;
    
    return 0;
}
