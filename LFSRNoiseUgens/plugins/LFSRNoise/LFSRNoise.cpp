// PluginLFSRNoise.cpp
// JS (email)

#include "SC_PlugIn.h"

static InterfaceTable *ft;

struct LFSRNoise : public Unit {
    uint32 mState; //lfsr state
    uint32 mCounter; //sample counter
    uint32 mSeed; //different seeds for original and 1 ugen
    float mLevel; //output
};

void LFSRNoise_Ctor(LFSRNoise *unit);
void LFSRNoise_next(LFSRNoise *unit, int inNumSamples);

void LFSRNoise_Ctor(LFSRNoise *unit) {
    //set calc function
    SETCALC(LFSRNoise_next);
    
    //initialize member variables
    unit->mSeed = UINT32_MAX;
    unit->mState = UINT32_MAX;
    unit->mCounter = 0;
    unit->mLevel = 0.f;
    
    //calculate one sample
    LFSRNoise_next(unit, 1);
}

void LFSRNoise_next(LFSRNoise *unit, int inNumSamples) {
    float* out = ZOUT(0);
    float freq = IN0(0);
    int fbPos = static_cast<int>(IN0(1));
    uint32 state = unit->mState;
    uint32 seed = unit->mSeed;
    uint32 counter = unit->mCounter;
    float level = unit->mLevel;
    
    fbPos = sc_clip(fbPos, 1, 31);
    
    int remain = inNumSamples;
    do {
        if (counter <= 0) {
            counter = (int)(SAMPLERATE / sc_max(freq, .001f));
            counter = sc_max(1, counter);
            
            //reset LFSR if all bits are 0. most stable solution
            if (state == 0) {
                state = UINT32_MAX;
            }
            
            //step LFSR
            int newbit = state & 1;
            state >>= 1;
            newbit ^= state & 1;
            
            int mask = (1 << fbPos);
            state = ((state & ~mask) | (newbit << fbPos));
            
            //level value
            level = (state & 1) ? 1.0f : -1.0f;
        }
        int nsmps = sc_min(remain, counter);
        remain -= nsmps;
        counter -= nsmps;
        for (int i = 0; i < nsmps; i++) {
            ZXP(out) = level;
        }
    } while (remain);
    
    //update member variables
    unit->mState = state;
    unit->mLevel = level;
    unit->mCounter = counter;
}

PluginLoad(InterfaceTable *inTable) {
    ft = inTable;
    DefineSimpleUnit(LFSRNoise);
}
