LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

tetris:
	mkdir -p output
	$(CXX) -o tetris $(LIBS) main.cpp
	mv tetris output/tetris
	mv -t output share
	wget -o output/share/sounds/bgm.wav http://projects.catz.gq/linux%20Projects/tetris-extra/Astral.wav;
	wget -o output/share/sounds/Ronin.wav http://projects.catz.gq/linux%20Projects/tetris-extra/Onyx%20-%20Sunlight.wav
	
