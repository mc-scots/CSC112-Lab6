//////////////////////////////////////////////////////////////////////
// This class is a widget which plays the insanity peg puzzle.
// $Revision: 1.1 $
//   $Log: insanity.h,v $
//   Revision 1.1  2017/03/29 13:47:31  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
//////////////////////////////////////////////////////////////////////
#ifndef INSANITY_H
#define INSANITY_H
#include <vector>
#include <string>
#include "widget.h"
#include "peg.h"

class Insanity : public Widget
{
public:
    //constructor
    Insanity();
    
    //destructor
    ~Insanity();

    //widget functions
    virtual void handleEvent(Event *e);
    virtual void display();

    //insanity functions
    virtual void selectPeg(int cursor);
    virtual bool move(int p1, int p2);
    virtual void solve();

private:
    std::vector<Peg *> pegs;
    int cursor;  //the peg where the cursor is
    int toMove;  //the peg selected to move
    std::string message;  //the message to display below the board
};
#endif
