#ifndef HILBERTSPACE_H
#define HILBERTSPACE_H

#include "../Ensemble/Ensemble.h"
#include "../Combinadics/Combinadics.h"

// class contains
// - Base State 
// - Ensemble
class HilbertSpace
{
    public: 
        BaseState baseState;
        Ensemble ensemble;
        void InitialBaseState();
        bool NextBaseState();
        statenumber stateIndex = 0;
        int sectorIndex = 0;

    private:
        // saves size of the previous sectors
        bool NextSector();
        statenumber sectorOffset = 0;

};




#endif