// PluginLFSRNoise.cpp
// M. Josiah Sytsma (sytsma.music@icloud.com)

#include "SC_PlugIn.hpp"
#include "LFSRNoise.hpp"

static InterfaceTable* ft;

LFSRNoise::LFSRNoise() {
    //set calc function
    mCalcFunc = make_calc_function<LFSRNoise, &LFSRNoise::next>();
    
    //initialize member variables
    mSeed = UINT32_MAX;
    mState = UINT32_MAX;
    mCounter = 0;
    mLevel = 0.f;
    mPhase = 0.0;
    
    //calculate one sample
    next(1);
}

void LFSRNoise::next(int inNumSamples) {
    float *outbuf = out(0);
    float freq = in0(0); // Frequency input
    int fbPos = sc_clip(static_cast<int>(in0(1)), 1, 31); // Feedback position input
    float curTrig = in0(2); // Trigger input
    float seedType = in0(3); // Seed type input
    
    float phase = mPhase;
    float phaseInc = freq / sampleRate(); // Phase increment per sample

    uint32 seed = mSeed;
    uint32 state = mState;
    float level = mLevel;
    
    // Reset seed based on type
    if (seedType < 0) {
        seed = UINT32_MAX;  // All 1's
    } else if (seedType == 0) {
        seed = ~(~0u << fbPos);  // Up to fbIndex 1's
    } else {
        seed = 1;  // Single bit
    }
    
    for (int i = 0; i < inNumSamples; ++i) {
        phase += phaseInc;
        if (phase >= maxPhase) {
            phase -= maxPhase; // Wrap phase

            // Check reset trigger
            if (state == 0 || triggered(curTrig)) {
                state = seed;
            }
            mPrevTrig = curTrig;
            
            // Step LFSR
            int newbit = state & 1;
            state >>= 1;
            newbit ^= state & 1;
            
            int mask = (1 << fbPos);
            state = ((state & ~mask) | (newbit << fbPos));
            
            // Update level based on LFSR state
            level = (state & 1) ? 1.0f : -1.0f;
        }
        outbuf[i] = level;
    }

    // Store local variables back to member variables
    mSeed = seed;
    mState = state;
    mLevel = level;
    mPhase = phase; // Save the updated phase
}

PluginLoad(LFSRNoiseUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<LFSRNoise>(ft, "LFSRNoise", false);
}


