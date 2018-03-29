## Introduction

Everyone loves a good golf tee/peg puzzle\! Many a patron of certain
southern cooking restaurants have stared at wooden boards in sweet
consternation while awaiting the arrival of their 2500 calorie
breakfast. In this lab, we are going to write a program that does the
impossible. That's right, we are going to solve one of these puzzles\!
The code you write in this lab will be reused in your next programming
assignment, so you'll want to do a good job of it.

## Insanity

The game we are going to solve in this lab is the insanity puzzle.
Insanity is a puzzle consisting of 10 holes and 8 pegs. In our version,
4 red pegs will start on the left, and 4 green pegs will start on the
right. The object of the puzzle is to swap all the pegs. That is, when
it is solved, the red pegs will all be on the left and the green pegs
will all be on the right. There are a few rules constraining the moves
though\!

1.  Pegs can move only forward. Red pegs always move right and green
    pegs always move left.
2.  A peg can be moved onto an adjacent empty space.
3.  A peg can jump a single occupied space.

The starter file contains a fully implemented and playable version of
this puzzle. Go ahead and build it by running "make", and play with the
puzzle for a few minutes to get a feel for how it works. It seems like
it should be an easy task, but this puzzle can be delightfully
frustrating\!

When you are done playing with the puzzle, press ESC to exit the
program. Now go and explore the code until you understand how it all
works. The insanity.h, insanity.cpp, peg.h, and peg.cpp files are where
all the key action is so look at those closely\!

## Writing the Solver

Ok, so I'm sure you tried pressing the "s" key at some point during your
explorations. Clearly, we have not yet implemented the solving part of
this thing. That is the subject of this lab. You'll want to read these
instructions carefully because in them I will tell you how to do this,
but I am not going to give you all of the code. Think of it as a guided
application of backtracking, which shouldn't be too much of a stretch
because that is exactly what this is\!

### The InsanitySolver Class

We have a lot of options when it comes to designing the solver. We could
use the Insanity widget as candidate solutions, but that wouldn't be a
good idea. Widgets are big heavyweight classes, and so we don't want to
put them in a position where we'll create a bunch of them. Instead, we
are going to create another class which looks something like this:

``` cpp
class InsanitySolver : public Candidate
{
public: 
    InsanitySolver(const std::vector<Peg*> &board);
    InsanitySolver(const std::vector<int> &board);
    ~InsanitySolver();

    virtual bool reject();
    virtual bool solved();
    virtual Candidate *next();
    virtual int validMove(int i);
    virtual int from();
    virtual int to();

private:
    std::vector<int> board;
    int p1;
    int p2;
    int nextToTry;
};
```

I put the class definition in my insanity.h file and the class
implementation in insanity.cpp file.

So now, what's the deal with the board in this one? It's not a peg
vector, it's an int vector\! Well, the answer is these will be a lot
easier to work with. Remember, pegs are big heavy widgets. Integers
are nice, small, and easily compared. So we need an encoding
scheme. The one I used was this:

` 0 - Empty`  
` 1 - Red`  
` 2 - Green`

Let's go ahead and write the constructors together. We want to scan the
board we are given, and populate the one we have with the proper
encodings:

``` cpp
InsanitySolver::InsanitySolver(const std::vector<Peg*> &board)
{
    for(int i=0; i<board.size(); i++) {
        if(board[i]->present() == false) {
            this->board.push_back(0);
        } else if(board[i]->color() == RED) {
            this->board.push_back(1);
        } else if(board[i]->color() == GREEN) {
            this->board.push_back(2);
        }
    }
    nextToTry=0;
}


InsanitySolver::InsanitySolver(const std::vector<int> &board) : board(board)
{
    nextToTry=0;
}
```

While I'm still in the mode of handing out freebies, here is my
destructor:

``` cpp
InsanitySolver::~InsanitySolver()
{
    if(nextStep() != nullptr) {
        delete nextStep();
    }
}
```

That wasn't much of a gift though as that is the same destructor from
all of our classroom examples.

### reject()

The reject function will return true if there are no more available
moves and the puzzle is not yet solved. Think of how you would do that.
One hint is that if you look at each peg, there are only 2 potential
landing spots for it. It's a fairly simple matter to loop over all of
them and check to see if they have anywhere to go. If none do, then
there is no way to solve the puzzle\!

### solved()

A solved puzzle is one with 4 green pegs on the left and 4 red pegs on
the right. Think about what the indexes of these positions are. All you
have to do is loop over the ending holes and see if they all have the
correct color in them\!

Return true if everything is where it should be, false otherwise.

### next()

For the next function, you'll need to make the class remember which peg
it has tried. Also, remember what move you are going to try. The basic
idea is to try each peg in turn. The fields p1 and p2 remember the
source and destination of each move. from() and to() simply return p1
and p2 respectively. nextToTry stores the next peg for us to try moving.

Putting it all toegether for the next function, we arrive at:

``` cpp
Candidate *
InsanitySolver::next()
{
    InsanitySolver *ns;
    int p1;
    int p2;
    
    while(nextToTry < board.size()) {
        //try the next next peg
        p1 = nextToTry++;
        p2 = validMove(p1);
        
        if(p2 != -1) {
            //reuse the allocated next step(if there is one)
            ns = (InsanitySolver*) nextStep();
            if(ns == nullptr) {
                ns = new InsanitySolver(board);
            } else {
                ns->board = board;
                ns->nextToTry = 0;
            }
            ns->p1=p1;
            ns->p2=p2;
            swap(ns->board[ns->p1], ns->board[ns->p2]);
            return ns;
        }
    }
    
    
    //if we make it here, we are out of moves!
    return nullptr;
}
```

Of course, there is one other missing detail. The validMove function
looks at the peg passed in as a parameter and returns that peg's one
valid move. If the peg cannot move, it returns -1. You will need to
supply this function.

## Insanity::solve()

The Insanity widget's solve function uses the backtracking algorithm and
then animates the solution. It's not terribly complicated, but I am in a
giving mood so here is mine:

``` cpp
void 
Insanity::solve()
{
    InsanitySolver *solution = new InsanitySolver(pegs);
    
    //show our thinking
    message = "Thinking...";
    display();
    if(solution->backtrack()) {
        message = "Got it!  Here it is.";
    } else {
        message = "Unsolvable fromt his position!";
    }
    display();
    
    //animate the solution
    for(InsanitySolver *ptr = (InsanitySolver*) solution->nextStep();
        ptr != nullptr;  ptr=(InsanitySolver*) ptr->nextStep())
    {
        move(ptr->from(), ptr->to());
        display();
        usleep(500000); 
    }
}
```

## Conclusion

Be sure to test your program and make sure it works. Also, study it
until you understand it because your next programming assignment will
make use of this\!
