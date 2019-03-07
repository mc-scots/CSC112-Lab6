/////////////////////////////////////////////////////////////////////
// This is a widget for use in peg puzzle games.  It allows a peg to
// be placed or removed from a slot.  The peg can also be set to 
// one of several colors.
/////////////////////////////////////////////////////////////////////
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include "peg.h"

using namespace std;

//constructors
Peg::Peg() : Peg(0, 0, 20)
{
    //this constructor's work is done by the other version
}


Peg::Peg(int x, int y, int s) : Fl_Widget(x, y, s, s)
{
    _color = DEFAULT;
    _present = false;
    _selected = false;
}


//widget functions
int
Peg::handle(int event)
{
    return 0;
}


void 
Peg::draw()
{

    //draw the outer ring
    fl_color(FL_BLACK);
    fl_circle(x()+5, y()+5, w()/2.0 - 5);

    /* //set the color of the peg
    if(color() == RED) {
        cout << red;
    } else if(color() == BLUE) {
        cout << blue;
    } else if(color() == GREEN) {
        cout << green;
    } else if(color() == YELLOW) {
        cout << yellow;
    } */

}


//handle peg color
void 
Peg::color(PegColor _color)
{
    this->_color = _color;
    redraw();
}


PegColor 
Peg::color()
{
    return this->_color;
}


//present is true if there is a peg in this hole
void 
Peg::present(bool _present)
{
    this->_present = _present;
    redraw();
}


bool 
Peg::present()
{
    return this->_present;
}


//pegs can also be selected, this causes them to 
//display in reverse video
void 
Peg::selected(bool _selected)
{
    this->_selected = _selected;
    redraw();
}


bool 
Peg::selected()
{
    return this->_selected;
}
