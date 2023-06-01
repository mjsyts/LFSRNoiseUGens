// PluginLFSRNoise.cpp
// JS (email)

#include "SC_PlugIn.h"

static InterfaceTable *ft;

struct LFSRNoise : public Unit {
    uint32 mState; //lfsr state
    uint32 mCounter; //sample counter
    uint16 mLevel; //output
};

struct LFSRMaxNoise : public Unit {
    uint32 mState; //lfsr state
    uint32 mCounter; //sample counter
    int16 mLevel; //output
};

struct LFSRMaxNoise2 : public Unit {
    uint32 mState; //lfsr state
    uint32 mCounter; //sample counter
    int16 mLevel; //output
};

void LFSRNoise_Ctor(LFSRNoise *unit);
void LFSRNoise_next(LFSRNoise *unit, int inNumSamples);

void LFSRNoise_Ctor(LFSRNoise *unit) {
    //set calc function
    SETCALC(LFSRNoise_next);
    
    //initialize member variables
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
    uint32 counter = unit->mCounter;
    int16 level = unit->mLevel;
    
    int lsb0;
    int lsb1;
    int newbit;
    int mask;
    
    fbPos = sc_clip(fbPos, 1, 31);
    
    int remain = inNumSamples;
    do {
        if (counter <= 0) {
            counter = (int)(SAMPLERATE / sc_max(freq, .001f));
            counter = sc_max(1, counter);
            
            //reset LFSR if state is 0
            if(state == 0) {
                state = UINT32_MAX;
            };
            
            //step LFSR
            lsb0 = state % 2;
            state >>= 1;
            lsb1 = state % 2;
            newbit = lsb0^lsb1;
            
            mask = 1 << fbPos;
            state = ((state & ~mask) | (newbit << fbPos));
            
            //level value
            level = (state % 2);
            if (level == 0)
            {
                level = -1;
            };
        }
        int nsmps = sc_min(remain, counter);
        remain -= nsmps;
        counter -= nsmps;
        LOOP(nsmps, ZXP(out) = level;);
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

