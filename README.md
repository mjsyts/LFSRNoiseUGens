# LFSRNoiseUGens
SuperCollider LFSR noise generator plugin.

## Installation
Download the zip file from GitHub or in the terminal: 
```git clone https://github.com/mjsyts/LFSRNoiseUGens```

In terminal, from the project root directory:
```
cd LFSRNoiseUGens
mkdir build
cmake .. -DCMAKE_BUILD_TYPE=Release -DSC_PATH=<Path to SC Source>
cmake --build . --config Release
```

Then drag the built files into your Extensions folder and recompile your class library in SC.
