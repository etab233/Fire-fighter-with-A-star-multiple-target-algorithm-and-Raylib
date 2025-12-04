#ifndef B421B8BE_1361_4E7E_9561_B7E41C5DAC74
#define B421B8BE_1361_4E7E_9561_B7E41C5DAC74

#include "fireState.h"

class Action{
public:
    FireState burn_cell(FireState state, position cell, fire f);
    void extinguish_cell(FireState& state,position cell ,fire f);
};

#endif /* B421B8BE_1361_4E7E_9561_B7E41C5DAC74 */
