g++.exe src/main.cpp src/Window.cpp src/Ball.cpp src/Paddles.cpp src/Score.cpp src/Networking.cpp src/Text.cpp src/Menu.cpp src/Utilities/Helper.cpp src/UI/UI.cpp src/UI/UIElement.cpp -I"C:\dev\SDL\64\include" -L"C:\dev\SDL\64\lib" -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lws2_32 -o bin/main.exe

pause