# GbaFletchlingGame
A little game made for the Gameboy Advance using C++

## Instalation
This repository uses submodules for the math library (gcem). so clone this with the option --recurse-submodules
```
git clone --recurse-submodules https://github.com/FireFlyForLife/GbaFletchlingGame.git
```

Then open the project visual studio "Fletchling.sln"

In Visual Studio open the "Property Manager". Rightclick GBA -> Properties -> User Macros -> Set NOCASHGBA to the location of your NO$GBA emulator executable.

Open the Makefile in the root of the repository -> At the top change DEVKITPRO to the instalation path of DEVKITPRO and DEVKITARM to the instalation path of where the ARM toolchain is installed

Now build and run in Visual Studio and the NO$GBA emulator should start running your game!
