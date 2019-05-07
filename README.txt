Mobile version of Tirmat

Engine configurations:
- The game engine can be compiled into a shared library with cmake. This is done with the engine-level CMakeLists.txt

* To compile with windows (MinGW)
1. cd to game_engine/
2. cmake . -G "MinGW MakeFiles"
3. make

- Should be similar with all platforms; just change the cmake configuration to the one used by the platform
