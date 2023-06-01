LFSRNoise : UGen {
    *ar { |freq = 500, fbPos = 14, mul = 1.0, add = 0.0|
        ^this.multiNew('audio', freq, fbPos).madd(mul, add);
    }
    *kr { |freq = 500, fbPos = 14, mul = 1.0, add = 0.0|
        ^this.multiNew('control', freq, fbPos).madd(mul, add);
    }
    checkInputs {
        ^this.checkValidInputs;
    }
}
