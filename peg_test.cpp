///////////////////////////////////////////////////////////////////////////
// File: peg_test.cpp
// Purpose: This is a test driver for the peg class
///////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "peg.h"

using namespace std;

void toggle_peg(Peg *peg, void*user)
{
    if(not peg->selected()) {
        peg->selected(true);
        peg->present(true);
    } else {
        if(peg->color() == DEFAULT) {
            peg->color(RED);
        } else if(peg->color() == RED) {
            peg->color(GREEN);
        } else if(peg->color() == GREEN) {
            peg->color(BLUE);
        } else if(peg->color() == BLUE) {
            peg->color(YELLOW);
        } else {
            peg->color(DEFAULT);
            peg->present(false);
            peg->selected(false);
        }
    }
}

int main(int argc, char **argv)
{
    int size;

    //Get the size the user wants to test
    cout << "Size? ";
    cin >> size;

    Fl_Window *window = new Fl_Window(size, size);
    Peg *peg = new Peg(0, 0, size);
    peg->callback((Fl_Callback*) toggle_peg);

    //display the window
    window->show(argc, argv);
    return Fl::run();
}
