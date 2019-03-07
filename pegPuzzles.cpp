// Play peg puzzles!
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include "insanity.h"

using namespace std;

int main(int argc, char **argv)
{
    Fl_Window *window = new Fl_Window(400,200, "INSANITY!");
    Insanity *puzzle = new Insanity(0,0,400,200);
    window->end();

    //show the window and enter the event loop
    window->show(argc, argv);
    return Fl::run();
}
