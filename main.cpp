#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <math.h>
#include "setup.hpp"
#include "Button.h"

using namespace sf;
using namespace startUp;

const int fieldY = 20;
const int fieldX = 10;
double score = 0;

int field[fieldY][fieldX] = {0};

struct Point
{
int x,y;
} pointA[4], pointb[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool tReset=false;
bool bgmReset=false;
bool gOtst;
int pm;
bool sfx = true;
bool bgmOpt = true;
bool gameOverNotif = true;
bool start;
bool dbug;
int blkLeft = 100;
bool addS = false;
bool noBlkLeft = false;
bool win = false;
float bgmPercent = 100;
float sfxPercent = 100;
bool goal = true;


sf::RenderWindow window(VideoMode(320, 480), "The Game of Tetris!");

sf::Music bgm;
sf::Music tick;
sf::Music gameOverm;


static inline std::string double25tr(double x) {
	std::stringstream type;
	type << x;
	return type.str();
}

static inline std::string float25tr(float x) {
	std::stringstream type;
	type << x;
	return type.str();
}

static inline std::string int25tr(int x) {
	std::stringstream type;
	type << x;
	return type.str();
}

bool check()
{
	for (int i=0; i<4; i++) {
		if (pointA[i].x<0 || pointA[i].x>=fieldX || pointA[i].y>=fieldY) {
			addS = true;
			return 0;
		}
		else if (field[pointA[i].y][pointA[i].x]) {
			addS = true;
			return 0;
		}
	}
	if (addS == true) {
		score = score + 0.5;
		addS = false;
	}
	return 1;
};

bool gameOver();
int pause();
std::string checkBool(bool boolInQ);
int toggle(bool btoggle);
void mute(sf::SoundSource sfss);
int Options();

int gameStart() {
	int option;

	//bool chosen = false;
	window.setVisible(false);
	Button tst;
	tst.setHeight(30);
	tst.setWidth(300);
	tst.move(10,20);
	int tx1 = tst.getPosx();
	int ty1 = tst.getPosy();
	int tx2 = tst.getPosx() + tst.getWidth();
	int ty2 = tst.getPosy() + tst.getHeight();
	Font gameFnt;
	gameFnt.loadFromFile("/usr/share/fonts/truetype/tetrisFont/tetrisFont.ttf");
	tst.setText("Without goals", gameFnt);

	RenderWindow gswindow(VideoMode(320, 480),"Tetris - Choose your options!");
	Texture t4;
	t4.loadFromFile("/usr/share/tetris/images/startUp.png");
	Sprite gsbg(t4);
	bool onClick;
	while (gswindow.isOpen()) {
		Event gse;
		while (gswindow.pollEvent(gse)) {
			if (gse.type == Event::Closed) {
				gswindow.close();
				return 8;
			}

			if (gse.type == Event::MouseButtonPressed) {
				if ((gse.mouseButton.x >= tx1 && gse.mouseButton.x <= tx2) && (gse.mouseButton.y >= ty1 && gse.mouseButton.y <= ty2)) {
					if (gse.mouseButton.button == Mouse::Left) {
						if (goal == true) {
							tst.setText("With goals", gameFnt);
							goal = false;
						}
						else {
							tst.setText("Without goals", gameFnt);
							goal = true;
						}
					}
				}
			}


			if (gse.type == Event::KeyPressed)
			{
				if (gse.key.code==Keyboard::Num1)	   {option = setup::Config1; gswindow.close(); window.setVisible(true); return option;}
				else if (gse.key.code==Keyboard::Num2) {option = setup::Config2; gswindow.close(); window.setVisible(true); return option;}
				else if (gse.key.code==Keyboard::Num3) {option = setup::Config3; gswindow.close(); window.setVisible(true); return option;}
			}
		}

		onClick = tst.onClickListener(gswindow);
		if (onClick == true) {
			exit(0);
		}

		gswindow.clear(Color::White);
		gswindow.draw(gsbg);
		tst.draw(gswindow);
		gswindow.display();
	}



	return 0;
}


int main()
{
	int setting = gameStart();
	if (setting == 8)
		return 0;
	start = true;
	srand(time(0));
	int sngChoose=1+rand()%2;
	//if (sngChoose==1)
	if (setting == setup::Config1)
		bgm.openFromFile("/usr/share/tetris/sounds/bgm.wav");
	else
		bgm.openFromFile("/usr/share/tetris/sounds/ronin.wav");
	bgm.play();
	tick.openFromFile("/usr/share/tetris/sounds/tick.ogg");
	sngChoose = 0;



	unsigned int windowIconSize = 144;
	Image tetrisIcon;
	tetrisIcon.loadFromFile("/usr/share/tetris/images/winIcon.png");
	window.setIcon(windowIconSize, windowIconSize, tetrisIcon.getPixelsPtr());


	Texture t1,t2,t3;
	if (setting == setup::Config1) {
		t1.loadFromFile("/usr/share/tetris/images/tiles.png");
		t2.loadFromFile("/usr/share/tetris/images/background.png");
	}
	else if (setting == setup::Config2) {
		t1.loadFromFile("/usr/share/tetris/images/tilesi.png");
		t2.loadFromFile("/usr/share/tetris/images/backgroundi.png");
	}
	else {
		t1.loadFromFile("/usr/share/tetris/images/tilesBlue.png");
		t2.loadFromFile("/usr/share/tetris/images/Blues.png");
	}
	t3.loadFromFile("/usr/share/tetris/images/frame.png");
	Sprite s(t1), background(t2), frame(t3);

	int dx=0;
	bool rotate=0;
	int colorNum=1;
	float timer=0,delay=0.3;

	Clock clock;
	Clock es;
	Text scoreBlkTime;
	Font gameFont;
	gameFont.loadFromFile("/usr/share/fonts/truetype/tetrisFont/tetrisFont.ttf");
	scoreBlkTime.setCharacterSize(30);
	scoreBlkTime.move(10, 385);
	scoreBlkTime.setStyle(sf::Text::Bold);
	scoreBlkTime.setFont(gameFont);
	scoreBlkTime.setFillColor(Color::Black);
	window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		float timec = es.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
			{
				if (e.key.code==Keyboard::Up) rotate=true;
				else if (e.key.code==Keyboard::Left) dx=-1;
				else if (e.key.code==Keyboard::Right) dx=1;
				else if (e.key.code==Keyboard::Space) tReset=true;
				else if (e.key.code==Keyboard::Escape) {
					pm=pause();
					if (pm != 0) {
						if (pm == 1)
							return 0;
						return pm;
					}
				}
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

		//// <- Move -> ///
		for (int i=0; i<4; i++)
		{
			pointb[i]=pointA[i];
			pointA[i].x+=dx;


		}
		if (!check()) for (int i=0; i<4; i++) pointA[i]=pointb[i];

		//////Rotate//////
		if (rotate)
		{
			Point centerRot = pointA[1]; //center of rotation
			for (int i=0; i<4; i++)
			{
				int x = pointA[i].y-centerRot.y;
				int y = pointA[i].x-centerRot.x;
				pointA[i].x = centerRot.x - x;
				pointA[i].y = centerRot.y + y;
			}
			if (!check()) for (int i=0; i<4; i++) pointA[i]=pointb[i];
		}

		std::string sbtScore = double25tr(score);
		std::string sbtTimec = float25tr(timec);
		if (goal == true) {
			std::string sbtBlk = int25tr(blkLeft);
			scoreBlkTime.setString("Score: " + sbtScore + "\nTime: " + sbtTimec + "\nBlocks left: " + sbtBlk);
		}
		else {
			scoreBlkTime.setString("Score: " + sbtScore + "\nTime: " + sbtTimec);
		}
		///////Tick//////
		if (timer>delay)
		{

			tick.play();
			for (int i=0; i<4; i++)
			{
				pointb[i]=pointA[i];
				pointA[i].y+=1;
			}

			if (!check())
			{

				for (int i=0; i<4; i++)
					field[pointb[i].y][pointb[i].x]=colorNum;

				colorNum=1+rand()%7;
				int fieldX=rand()%7;
				if (field[2][1] == 0) {
					blkLeft--;
					for (int i=0; i<4; i++)
					{
						pointA[i].x = figures[fieldX][i] % 2;
						pointA[i].y = figures[fieldX][i] / 2;
					}
				}
				else {
					window.setTitle("Tetris - Game Over! (Press enter to cont.)");
					gOtst = gameOver();
					score = score - 0.5;
				}

			}

			int reslt = system("clear");
			std::cout << "Score: " << score << std::endl;
			std::cout << "Time: " << timec << std::endl;
			std::cout << "Bgm Status: " << bgm.getStatus() << std::endl;
			//std::cout << "scoreBlkTime Position :" << scoreBlkTime.getPosition() << std::endl;
			//std::cout << "scoreBlkTime String: " << scoreBlkTime.getString() << std::endl;
			std::cout << "reslt: " << reslt << std::endl;
			std::cout << "bgmPercent : " << bgmPercent << std::endl;
			std::cout << "Actual bgm Vol: " << bgm.getVolume() << std::endl;
			std::cout << "blocks left: " << blkLeft << std::endl;

			timer=0;
		}

		///////check lines//////////
		int k=fieldY-1;
		for (int i=fieldY-1; i>0; i--)
		{
			int count=0;
			for (int j=0; j<fieldX; j++)
			{
				if (field[i][j]) { count++;}
				field[k][j]=field[i][j];
			}
			if (count<fieldX) k--; else score = score + 10;
		}

		dx=0;
		rotate=0;
		delay=0.3;

		/////////draw//////////
		window.clear(Color::White);
		window.draw(background);

		for (int i=0; i<fieldY; i++)
			for (int j=0; j<fieldX; j++)
			{
				if (field[i][j]==0) continue;
				s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
				s.setPosition(j*18,i*18);
				s.move(28,31); //offset
				window.draw(s);
			}

		for (int i=0; i<4; i++)
		{
			s.setTextureRect(IntRect(colorNum*18,0,18,18));
			s.setPosition(pointA[i].x*18,pointA[i].y*18);
			s.move(28,31); //offset
			window.draw(s);
		}

		if (gOtst == true) {
			tReset = true;
		}

		if (tReset == true) {
			for (int cboardx = 0; cboardx < fieldY; cboardx++) {
				for (int cboardy = 0; cboardy < fieldY; cboardy++) {
					field[cboardy][cboardx] = 0;
				}
			}
			window.setTitle("The Game of Tetris! (Reset)");
			bgmReset = true;
			blkLeft = 100;
			es.restart();
			score = 0;
			tReset = false;
			gOtst = false;
		}

		if (bgmReset == true) {
			bgm.play();
			bgmReset=false;
		}

		if (bgm.getStatus() == bgm.Stopped) {
			sngChoose = 0;
			sngChoose = rand()%2;
			if (sngChoose == 1)
				bgm.openFromFile("/usr/share/tetris/sounds/bgm.wav");
			else
				bgm.openFromFile("/usr/share/tetris/sounds/ronin.wav");
			bgm.play();
		}
		scoreBlkTime.setFont(gameFont);
		window.draw(frame);
		window.draw(scoreBlkTime);
		if (goal == true) {
			if (blkLeft == -1) {
				win = true;
				bool screenFX = false;
				Font winFont;
				winFont.loadFromFile("/usr/share/fonts/truetype/tetrisFont/tetrisFont.ttf");
				Text uWin;
				uWin.move(320/2, 480/2);
				uWin.setFillColor(Color::White);
				uWin.setString("YOU WIN!!!");
				uWin.setStyle(sf::Text::Bold | sf::Text::Italic);
				uWin.setFont(winFont);
				//uWin.setOutlineColor(Color(255,255,255));
				//uWin.setOutlineThickness(4);
				while (win) {
					Event we;
					while (window.pollEvent(we)) {
						if (we.type == Event::Closed) {
							window.close();
							exit(0);
						}
						if (we.type == Event::KeyPressed)
						{
							if (we.key.code==Keyboard::Space) {
								win = false;
								tReset = true;
							}
							else if (we.key.code==Keyboard::Escape) exit(0);
							//else continue;
						}
					}
					if (screenFX == false) {
						for (int i = 0; i < 3; i++) {
							sleep(milliseconds(200));
							window.clear(Color::Red);
							window.display();
							sleep(milliseconds(200));
							window.clear(Color::Green);
							window.draw(uWin);

							window.display();
						}
						screenFX = true;
					}
					window.display();
				}
			}
		}

		if (win == false) {
			window.display();
		}

	}

	return 0;
}


bool gameOver() {
	tick.stop(); // Stop tick sounds
	bgm.stop(); // stop background music
	//gameOverm.openFromFile("/usr/share/tetris/sounds/gameOver.wav"); // Not sure why this line is commented out, or why this and the next line are here. There should only be one.
	gameOverm.openFromFile("/usr/share/tetris/sounds/gameOver.wav"); // Open gameOver sound
	gameOverm.play(); // Play game over sound
	//RenderWindow swindow(VideoMode(900,300),"Game Over!");
	Font fnt; // Create variable 'fnt' as type sf::Font
	fnt.loadFromFile("/usr/share/fonts/truetype/tetrisFont/tetrisFont.ttf"); // Initiate fnt with font provided in file path
// Free space
	Text go; // Create variable 'go' as type sf::Text. (go is short for "GameOver")
	go.setFont(fnt); // Initiate go with font fnt.
	go.setString("GAME OVER!"); // Set go's text as "GAME OVER"
	go.setCharacterSize(80); // This one is self-explainitory
	go.setScale(2,2); // So is this one
	go.setStyle(Text::Bold | Text::Underlined); // And this one
	go.setFillColor(Color::White); // Same here
	window.draw(go);
	if (gameOverNotif == true) {
		int reslt = system("zenity --notification --title=\"Tetris\" --text=\"Game Over! Press enter to continue.\"");
		if (reslt != 0) {
			return reslt;
		}
	}


	while (true) {
		Event goe;
		while (window.pollEvent(goe)) {
			if (goe.type == Event::Closed) {
				window.close();
				exit(1);
			}
			if (goe.type == Event::KeyPressed) {
				if (goe.key.code == Keyboard::Return) {
					exit(0);
				}
				else if (goe.key.code == Keyboard::Space) {
					//tReset=true;
					gameOverm.stop();
					return true;
				}

			}
		}
	}
}

int pause() {
	window.clear(Color(56,56,56));
	window.display();
	bgm.setVolume(bgm.getVolume()/2.0);
	Font extFnt;
	extFnt.loadFromFile("/usr/share/fonts/truetype/takao-gothic/TakaoPGothic.ttf");
	Text ext, rsm, opt;
	ext.setFont(extFnt);
	rsm.setFont(extFnt);
	opt.setFont(extFnt);
	ext.setString("Exit");
	rsm.setString("Resume");
	opt.setString("Options");
	ext.setCharacterSize(26);
	rsm.setCharacterSize(26);
	opt.setCharacterSize(26);
	ext.move(125,428);
	rsm.move(78,48);
	opt.move(65,88);
	Image exitRect;
	exitRect.create(300,30, Color(255,0,255));
	bool longitude;
	for (int ery =0; ery < 30; ery++) {
		for (int erx = 0; erx < 300; erx++) {
			if (((ery == 0 || ery == 1) || (ery == 28 || ery == 29))) {
				longitude = true;
			}
			else {
				longitude = false;
			}

			if (longitude == true) {
				exitRect.setPixel(erx, ery, Color(0,0,0));
			}
			else {
				if (longitude == false) {
					if ((erx == 0 || erx == 1) || (erx == 298 || erx == 299)) {
						exitRect.setPixel(erx, ery, Color(0,0,0));
					}
				}
			}
		}
	}
	Texture exitTexture;
	exitTexture.loadFromImage(exitRect);
	Sprite backSp(exitTexture), resumeSp(exitTexture), optionsSp(exitTexture);
	backSp.move(10, 50);
	resumeSp.move(10, 90);
	optionsSp.move(10, 430);
	window.setMouseCursorVisible(true);


	while (true) {
		Event pmo;
// TODO (whiskersofdeath#7#07/22/19): figure out a way to draw a settings window.
		while (window.pollEvent(pmo)) {
			if (pmo.type == Event::Closed)
				//window.close();
				return 1;
			if (pmo.type == Event::MouseButtonPressed) {
				if ((pmo.mouseButton.x >= 10 && pmo.mouseButton.x <= 310) && (pmo.mouseButton.y >= 50 && pmo.mouseButton.y <= 80)) {
					if (pmo.mouseButton.button == Mouse::Left) {
						/*if (bgmOpt == true) {
							bgmOpt = false;
						}
						else {
							bgmOpt = true;
						}*/
						//exit(0);
						bgm.setVolume(bgm.getVolume()*2.0);
						window.setMouseCursorVisible(false);
						return 0;
					}
				}

				if ((pmo.mouseButton.x >= 10 && pmo.mouseButton.x <= 310) && (pmo.mouseButton.y >= 90 && pmo.mouseButton.y <= 120)) {
					if (pmo.mouseButton.button == Mouse::Left) {
						/*if (bgmOpt == true) {
							bgmOpt = false;
						}
						else {
							bgmOpt = true;
						}*/
						//exit(0);
						int option = Options();
						if (option != 0) {
							return option;
						}
					}
				}

				if ((pmo.mouseButton.x >= 10 && pmo.mouseButton.x <= 310) && (pmo.mouseButton.y >= 430 && pmo.mouseButton.y <= 460)) {
					if (pmo.mouseButton.button == Mouse::Left) {
						/*if (bgmOpt == true) {
							bgmOpt = false;
						}
						else {
							bgmOpt = true;
						}*/
						exit(0);
					}
				}
			}

			if (pmo.type == Event::KeyPressed) {
				if (pmo.key.code == Keyboard::Escape) {
					/*saveSettings(); */
					bgm.setVolume(bgm.getVolume()*2.0);
					window.setMouseCursorVisible(false);
					return 0;
				}
			}
		}
		window.clear(Color(56,56,56));
		window.draw(backSp);
		window.draw(resumeSp);
		window.draw(optionsSp);
		window.draw(ext);
		window.draw(rsm);
		window.draw(opt);
		window.display();
	}
}

int Options() {
	/*Image blank;
	blank.create(320, 480);
	RenderWindow subWindow(VideoMode(320, 480), "Tetris - paused");
	Texture itos;
	itos.loadFromImage(blank);
	Sprite bg(itos);*/
	window.clear(Color(56,56,56));
	window.display();
	//subWindow.draw(bg);
	bool sToggle = false;
	bool mToggle = false;
	Font gameFont;
	gameFont.loadFromFile("/usr/share/fonts/truetype/tetrisFont/tetrisFont.ttf");
	Text pm;
	pm.setFont(gameFont);
	pm.move(10,10);
	pm.setStyle(Text::Bold);
	Font extFnt;
	extFnt.loadFromFile("/usr/share/fonts/truetype/takao-gothic/TakaoPGothic.ttf");
	Text ext;
	ext.setFont(extFnt);
	ext.setString("Back");
	ext.setCharacterSize(26);
	ext.move(130,428);
	Image exitRect;
	exitRect.create(300,30, Color(255,0,255));
	bool longitude;
	for (int ery =0; ery < 30; ery++) {
		for (int erx = 0; erx < 300; erx++) {
			if (((ery == 0 || ery == 1) || (ery == 28 || ery == 29))) {
				longitude = true;
			}
			else {
				longitude = false;
			}

			if (longitude == true) {
				exitRect.setPixel(erx, ery, Color(0,0,0));
			}
			else {
				if (longitude == false) {
					if ((erx == 0 || erx == 1) || (erx == 298 || erx == 299)) {
						exitRect.setPixel(erx, ery, Color(0,0,0));
					}
				}
			}
		}
	}
	Texture exitTexture;
	exitTexture.loadFromImage(exitRect);
	Sprite backSp(exitTexture);
	backSp.move(10, 430);
	//CircleShape shp;
	//shp.setRadius(30);
	//shp.setFillColor(Color::Blue);
	//sf::Event::MouseButtonEvent
	//shp.move(0, 400);

	while (true) {
		Event pmo;
// TODO (whiskersofdeath#7#07/22/19): figure out a way to draw a settings window.
		while (window.pollEvent(pmo)) {
			if (pmo.type == Event::Closed)
				//window.close();
				return 1;
			if (pmo.type == Event::MouseButtonPressed) {
				if ((pmo.mouseButton.x >= 10 && pmo.mouseButton.x <= 310) && (pmo.mouseButton.y >= 430 && pmo.mouseButton.y <= 460)) {
					if (pmo.mouseButton.button == Mouse::Left) {
						/*if (bgmOpt == true) {
							bgmOpt = false;
						}
						else {
							bgmOpt = true;
						}*/
						return 0;
					}
				}
			}
			if (pmo.type == Event::KeyPressed) {
				if (pmo.key.code == Keyboard::Escape) {
					/*saveSettings(); */
					//bgm.setVolume(bgm.getVolume()*2.0);
					//window.setMouseCursorVisible(false);
					return 0;
				}
				if (pmo.key.code == Keyboard::S) {
					if (tick.getVolume() == 100) {
						tick.setVolume(0);
						gameOverm.setVolume(0);
						sfx = false;
					}
					else {
						tick.setVolume(100);
						gameOverm.setVolume(100);
						sfx = true;
					}
					sToggle = true;
					mToggle = false;
				}
				if (pmo.key.code == Keyboard::M) {
					if (bgm.getVolume() == 50)  {
						bgm.setVolume(0);
						bgmOpt = false;
					}
					else {
						bgm.setVolume(50);
						bgmOpt = true;
					}
					sToggle = false;
					mToggle = true;
				}
				if (pmo.key.code == Keyboard::N) {
					if (gameOverNotif == true) {
						gameOverNotif = false;
					}
					else if (gameOverNotif == false) {
						gameOverNotif = true;
					}
					sToggle = false;
					mToggle = false;
				}

				if (pmo.key.code == Keyboard::Down) {
					if (sToggle == true && sfxPercent > 0) {
						sfxPercent = sfxPercent - 1;
						tick.setVolume(sfxPercent);
						gameOverm.setVolume(sfxPercent);
					}

					if (mToggle == true && bgmPercent > 0) {
						bgmPercent = bgmPercent - 1;
						bgm.setVolume(bgmPercent/2);
					}
				}

				if (pmo.key.code == Keyboard::Up) {
					if (sToggle == true && sfxPercent < 100) {
						sfxPercent = sfxPercent + 1;
						tick.setVolume(sfxPercent);
						gameOverm.setVolume(sfxPercent);

					}

					if (mToggle == true && bgmPercent < 100) {
						bgmPercent = bgmPercent + 1;
						bgm.setVolume(bgmPercent/2);
					}
				}
			}
		}
		pm.setString("Music: " + checkBool(bgmOpt) + " (" + float25tr(bgmPercent) + "%)" + "\nSoundFX: " + checkBool(sfx) + " (" + float25tr(sfxPercent) + "%)" + "\nGame Over Notifications:\n\t\t" + checkBool(gameOverNotif));
		window.clear(Color(56,56,56));
		window.draw(pm);
		window.draw(backSp);
		window.draw(ext);
		window.display();
	}
	//return 0;
}

std::string checkBool(bool boolInQ) {
	if (boolInQ == false) return "Off";
	else if (boolInQ == true) return "On";
	else return "Error";
}

int toggle(bool btoggle) {
	if (btoggle == true) {
		btoggle = false;
	}
	else if (btoggle == false) {
		btoggle = true;
	}
	else {
		return 1;
	}
	return 0;
}

void mute(sf::SoundSource sfss) {
	sfss.setVolume(0.0);
}

