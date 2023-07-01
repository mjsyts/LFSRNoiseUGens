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

struct LFSRNoise1 : public Unit {
    uint32 mState; //lfsr state
    uint32 mCounter; //sample counter
    uint32 mSeed; //different seeds for original and 1 ugen
    float mLevel; //output
};

struct LFSRNoiseF : public Unit {
    uint32 mState; //lfsr state
    uint32 mCounter; //sample counter
    uint32 mSeed = 0b11;
    float mLevel; //output
};

void LFSRNoise_Ctor(LFSRNoise *unit);
void LFSRNoise_next(LFSRNoise *unit, int inNumSamples);

void LFSRNoise1_Ctor(LFSRNoise1 *unit);
void LFSRNoise1_next(LFSRNoise1 *unit, int inNumSamples);

void LFSRNoiseF_Ctor(LFSRNoiseF *unit);
void LFSRNoiseF_next(LFSRNoiseF *unit, int inNumSamples);

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

void LFSRNoise1_Ctor(LFSRNoise1 *unit) {
    //set calc function
    SETCALC(LFSRNoise_next);
    
    //initialize member variables
    unit->mState = 1u;
    unit->mSeed = 1u;
    unit->mCounter = 0;
    unit->mLevel = 0.f;
    
    //calculate one sample
    LFSRNoise1_next(unit, 1);
}

void LFSRNoiseF_Ctor(LFSRNoiseF *unit) {
    //set calc function
    SETCALC(LFSRNoiseF_next);
    
    //initialize member variables
    unit->mState = 0x1;
    unit->mCounter = 0;
    unit->mLevel = 0.f;
    
    //calculate one sample
    LFSRNoiseF_next(unit, 1);
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

void LFSRNoise1_next(LFSRNoise1 *unit, int inNumSamples) {
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
                state = seed;
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

void LFSRNoiseF_next(LFSRNoiseF *unit, int inNumSamples) {
    float* out = ZOUT(0);
    float freq = IN0(0);
    int numBits = static_cast<int>(IN0(1));
    uint32 state = unit->mState;
    uint32 counter = unit->mCounter;
    float level = unit->mLevel;
    
    numBits = sc_clip(numBits, 2, 31);
    
    int remain = inNumSamples;
    do {
        if (counter <= 0) {
            counter = (int)(SAMPLERATE / sc_max(freq, .001f));
            counter = sc_max(1, counter);
            
            //reset LFSR if all bits are 0. most stable solution
            if (state == 0) {
                state = unit->mSeed;
            }
            
            uint32_t mask = (1 << numBits) - 1;
            
            uint32_t feedback = ((state >> (numBits - 2)) & 0x1) ^ ((state >> (numBits - 1)) & 0x1);
            state = (state << 1) | feedback;
            state &= mask;
            
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
    DefineSimpleUnit(LFSRNoise1);
    DefineSimpleUnit(LFSRNoiseF);
}
