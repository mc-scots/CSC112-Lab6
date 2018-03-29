// A generic OOP implementation of the backtracking algorithm
// $Revision: 1.1 $
//   $Log: backtrack.h,v $
//   Revision 1.1  2017/03/29 13:50:23  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
#ifndef BACKTRACK_H
#define BACKTRACK_H
#include <vector>
class Candidate
{
public:
    //constructor
    Candidate();

    //returns true if this candidate is invalid or otherwise unworkable.
    virtual bool reject() = 0;
    
    //returns true if this candidate is a solved puzzle
    virtual bool solved() = 0;
    
    //returns the next extension of this candidate solution 
    //(nullptr if there is none)
    virtual Candidate *next() = 0;
   
    //carry out the backtracking algorithm and return a list of candidates
    //leading from this one to the finished solution
    virtual bool backtrack();


    //return the next step in the solution chain (if there is one)
    virtual Candidate *nextStep();

private:
    Candidate *_nextStep;
};
#endif
