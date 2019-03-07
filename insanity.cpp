//////////////////////////////////////////////////////////////////////
// This class is a widget which plays the insanity peg puzzle.
// $Revision: 1.1 $
//   $Log: insanity.cpp,v $
//   Revision 1.1  2017/03/29 13:47:31  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Widget.H>
#include "insanity.h"

using namespace std;
static string defaultMessage = "INSANITY! -- GOOD LUCK";

//a call back for peg clicking
static void peg_callback(Peg *peg, Insanity *puzzle)
{
    puzzle->peg_click(peg);
}

//constructor
Insanity::Insanity(int x, int y, int w, int h) : Fl_Group(x,y,w,h)
{
    int sx, sy; //screen position of the pegs
    int size;   //size of the pegs

    //compute the size
    size=w/10;

    sx = this->x();
    sy = this->y() + h/2 - size/2;

    //set up the peg board
    for(int i=0; i<10; i++) {
        pegs.push_back(new Peg(sx, sy, size));        
        sx += size;

        //red pegs on the left, green pegs on the right
        if(i<4) {
            pegs[i]->color(RED);
            pegs[i]->present(true);
        } else if(i>5) {
            pegs[i]->color(GREEN);
            pegs[i]->present(true);
        }
        pegs[i]->user_data((void *) i);
        pegs[i]->callback((Fl_Callback*) peg_callback, this);
    }
    
    //set up initial selection
    to_move = -1;
    
    //set up initial message
    message = new Fl_Output(this->x()+5, this->y() + h - size - 5, w-10, size, defaultMessage.c_str());
    message->labelsize(size);

    end();  //the group is built
}


//destructor
Insanity::~Insanity() 
{
    //delete all the pegs
    for(int i=0; i<pegs.size(); i++) {
        delete pegs[i];
    }
}



//insanity functions
void 
Insanity::peg_click(Peg *peg)
{
    message->value("");

    //find the peg
    int cursor;
    for(cursor=0; cursor < pegs.size(); cursor++) {
        if(peg == pegs[cursor]) { break; }
    }

    //either mark the peg or move the peg
    if(to_move == -1) {
        //if the peg is present, select it for moving!
        if(pegs[cursor]->present()) {
            to_move = cursor;
            pegs[cursor]->selected(true);
        }
     } else {
        if(not move(to_move, cursor)) {
            message->value("Invalid Move!");
        }
        pegs[to_move]->selected(false);
        to_move = -1;
    }
}

//move the cursor to a peg
void 
Insanity::select_peg(int cursor)
{
    //first, we deselect the current peg
    pegs[this->to_move]->selected(false);
    
    //next, we select our peg
    pegs[cursor]->selected(true);
}


//attempt a move, returns false if the move is invalid true otherwise
bool
Insanity::move(int p1, int p2)
{
    //filled to empty check
    if(not pegs[p1]->present() or pegs[p2]->present()) { return false; }
    
    //red direction check
    if(pegs[p1]->color() == RED and p2 < p1) { return false; } 
    
    //green direction check
    if(pegs[p1]->color() == GREEN and p2 > p1) { return false; } 
    
    //distance check
    if(abs(p1-p2) > 2) { return false; }
    
    //jump check
    if(abs(p1-p2) == 2 and not pegs[min(p1+1, p2+1)]->present()) { return false; }
    
    //make the move
    pegs[p2]->present(true);
    pegs[p2]->color(pegs[p1]->color());
    pegs[p1]->present(false);
    pegs[p1]->color(DEFAULT);
    
    return true;
}


//solve the puzzle using backtracking (this is where your efforts come in!)
void 
Insanity::solve()
{
    message->value("Thinking...");
    sleep(2);
    message->value("Oh wait, you haven't taught me how to solve yet!");
}


