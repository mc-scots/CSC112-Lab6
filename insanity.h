//////////////////////////////////////////////////////////////////////
// This class is a widget which plays the insanity peg puzzle.
//////////////////////////////////////////////////////////////////////
#ifndef INSANITY_H
#define INSANITY_H
#include <vector>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include "peg.h"

class Insanity : public Fl_Group
{
public:
    //constructor
    Insanity(int x, int y, int w, int h);
    
    //destructor
    ~Insanity();

    //insanity functions
    virtual void peg_click(Peg *peg);
    virtual void select_peg(int cursor);
    virtual bool move(int p1, int p2);
    virtual void solve();

private:
    std::vector<Peg *> pegs;
    int to_move;  //the peg selected to move
    Fl_Output *message;  //the message to display below the board  
};
#endif
