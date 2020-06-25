build:
	mkdir build;
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o ./build/game \
	-I"./lib/lua" \
	-llua5.3 \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clear:
	rm -r ./build;

run:
	./build/game;

restart:
	make clear; make; make run;
