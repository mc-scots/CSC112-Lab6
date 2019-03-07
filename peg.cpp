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
    //process release of mouse buttons
    if(event == FL_RELEASE) {
        do_callback();
        return 1;
    }
    return 0;
}


void 
Peg::draw()
{
    //draw the outer ring
    if(selected()) {
      fl_color(FL_WHITE);
    } else {
      fl_color(FL_BLACK);
    }
    fl_pie(x()+5, y()+5, w()-10, h()-10, 0, 360.0);

    //draw the inner circle
    if(not present()) { 
        fl_color(FL_BACKGROUND_COLOR);
    } else {
        if(color() == RED) {
            fl_color(FL_RED);
        } else if(color() == BLUE) {
            fl_color(FL_BLUE);
        } else if(color() == GREEN) {
            fl_color(FL_GREEN);
        } else if(color() == YELLOW) {
            fl_color(FL_YELLOW);
        } else {
            fl_color(FL_FOREGROUND_COLOR);
        }
    }
    fl_pie(x()+10, y()+10, w()-20, h()-20, 0, 360.0);
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
