LFSRNoise : UGen {
    *ar { |freq = 500, fbPos = 14, continue = 1, resetType = 0, mul = 1.0, add = 0.0|
        ^this.multiNew('audio', freq, fbPos, continue, resetType).madd(mul, add);
    }
    *kr { |freq = 500, fbPos = 14, continue = 1, resetType = 0, mul = 1.0, add = 0.0|
        ^this.multiNew('control', freq, fbPos, continue, resetType).madd(mul, add);
    }
}
