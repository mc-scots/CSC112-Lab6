/////////////////////////////////////////////////////////////////////
// This is a widget for use in peg puzzle games.  It allows a peg to
// be placed or removed from a slot.  The peg can also be set to 
// one of several colors.
/////////////////////////////////////////////////////////////////////
#ifndef PEG_H
#define PEG_H
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

enum PegColor { DEFAULT, RED, BLUE, GREEN, YELLOW };

class Peg : public Fl_Widget
{
public:
    //constructors
    Peg();
    Peg(int x, int y, int s);

    //widget functions
    virtual int handle(int event);
    virtual void draw();

    //handle peg color
    virtual void color(PegColor _color);
    virtual PegColor color();

    //present is true if there is a peg in this hole
    virtual void present(bool _present);
    virtual bool present();

    //pegs can also be selected, this causes them to 
    //display with a highlighted ring
    virtual void selected(bool _selected);
    virtual bool selected();

private:
    PegColor _color;  //the peg's color
    bool _present;    //whether it is filled or not
    bool _selected;   //whether or not it is selected
};

#endif
