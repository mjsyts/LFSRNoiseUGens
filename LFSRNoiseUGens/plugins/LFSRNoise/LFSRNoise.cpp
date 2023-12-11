// PluginLFSRNoise.cpp
// JS (email)

#include "SC_PlugIn.h"

static InterfaceTable *ft;

struct LFSRNoise : public Unit {
    uint32 mState; //lfsr state
    uint32 mCounter; //sample counter
    uint32 mSeed; //seed 1 or UINT32_MAX
    int mFbPos;
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
    unit->mFbPos = 0;
    
    //calculate one sample
    LFSRNoise_next(unit, 1);
}

void LFSRNoise_next(LFSRNoise *unit, int inNumSamples) {
    float* out = ZOUT(0);
    float freq = IN0(0);
    int fbPos = sc_clip(static_cast<int>(IN0(1)), 1, 31);
    int cont = sc_clip(static_cast<int>(IN0(2)), 0, 1);
    int reset = sc_clip(static_cast<int>(IN0(3)), 0, 1);
   
    uint32 seed;
    if (reset == 1){
        seed = UINT32_MAX;
    }{
        seed = ~(~0u << fbPos);
    }
    
    uint32 state = unit->mState;
    uint32 counter = unit->mCounter;
    float level = unit->mLevel;
    
    if (cont == 0 && unit->mFbPos != fbPos){
        state = seed;
    }

    int remain = inNumSamples;
    do {
        if (counter <= 0) {
            counter = static_cast<int>(SAMPLERATE / sc_max(freq, .001f));
            counter = sc_max(1, counter);

            //reset
            if (state == 0) {
                state = seed;
            }

            //step
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
    unit->mFbPos = fbPos;
    unit->mSeed = seed;
    unit->mState = state;
    unit->mLevel = level;
    unit->mCounter = counter;
}


PluginLoad(InterfaceTable *inTable) {
    ft = inTable;
    DefineSimpleUnit(LFSRNoise);
}
