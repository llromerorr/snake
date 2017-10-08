::To compile with g++ of mingw32/64
::By Luis Romero https://www.instagram.com/CreyTuning

::create icon resource
windres Resource/icon.rc Resource/icon.o

::compile the game
cls && g++ -Wall Source/main.cpp Source/Levels.cpp Resource/icon.o -static -o Build/Debug.exe && start Build/Debug.exe