// PluginLFSRNoise.hpp
// M. Josiah Sytsma (sytsma.music@icloud.com)

#pragma once

#include "SC_PlugIn.hpp"

class LFSRNoise : public SCUnit {
    enum Inputs {
        FREQ_IN,
        FB_IN,
        TRIG_IN,
        SEED_IN,
        NUMINPUTS
    };
    
    uint32_t    mState; //lfsr state
    uint32_t    mCounter; //sample counter
    uint32_t    mSeed; //seed 1 or UINT32_MAX
    float       mPrevTrig;
    float       mPhase;  // Phase accumulator - float precision is fine
    const float minPhase = 0.0;
    const float maxPhase = 1.0;  // Normalized phase range
    float       mLevel; //output
    bool        triggered(float inTrig);
    void        next(int inNumSamples);
    
public:
    LFSRNoise();
    //~LFSRNoise(); //default destructor
};

inline bool LFSRNoise::triggered(float trigIn) {
    return trigIn > 0.f && mPrevTrig <= 0.f;
}
