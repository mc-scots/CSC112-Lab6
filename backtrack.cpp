// A generic OOP implementation of the backtracking algorithm
// $Revision: 1.1 $
//   $Log: backtrack.cpp,v $
//   Revision 1.1  2017/03/29 13:50:23  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
#include "backtrack.h"

//constructor
Candidate::Candidate()
{
    _nextStep = nullptr;
}


bool Candidate::backtrack()
{
    //return an empty vector if we reject
    if(reject()) { return false; }
    
    //if we are solved, then this is the last step
    //in a solution chain
    if(solved()) { return true; }
    
    _nextStep = next();        //get the next candidate
    while(_nextStep != nullptr) {
        //backtrack from the next solution
        if(_nextStep->backtrack()) { return true; }
        
        //try again
        _nextStep = next();
    }
    
    return false;
}


Candidate *
Candidate::nextStep()
{
    return _nextStep;
}
