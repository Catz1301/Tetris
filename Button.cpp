#include "Button.h"

using namespace sf;




Button::Button()
{

	buttonHeight = NULL;
	buttonWidth = NULL;
	buttonText = "";
	buttonColor = Color(0, 0, 255);
	btnCoord.x1 = posX;
	btnCoord.y1 = posY;
	btnCoord.x2 = m_Posx + buttonWidth;
	btnCoord.y2 = posY + buttonHeight;
}

Button::Button(int x1, int y1, int x2, int y2, sf::Color c, char* buttonLabel) {
	btnCoord.y1 = x1;
	btnCoord.x1 = y1;
	btnCoord.x2 = x2;
	btnCoord.y2 = y2;
	buttonText = buttonLabel;
	buttonColor = c;
}
void Button::setWidth(int val)
{
	buttonWidth = val;
	btnCoord.x2 = posX + buttonWidth;
}

void Button::setHeight(int val)
{
	buttonHeight = val;
	btnCoord.y2 = posY + buttonHeight;
}

int Button::getWidth()
{
	return buttonWidth;
}

int Button::getHeight()
{
	return buttonHeight;
}

float Button::getPosx()
{
	return posX;
}

float Button::getPosy()
{
	return posY;
}

void Button::setText(const sf::String& str, const sf::Font& fnt)
{

	buttonText = str;
	btnFont = fnt;
	//String str = m_Text;
	txt.setString(str);
	int len = str.getSize();
	int chrSize = (buttonHeight - 2);
	txt.setCharacterSize(chrSize);
	txt.setFont(fnt);
	txt.move(posX + ((buttonWidth/2) - (len/2)*chrSize), (posY - 2));
}

bool Button::onClickListener(sf::RenderWindow& RwWin)
{
	Event btnEvnt;
	while (RwWin.pollEvent(btnEvnt)) {
		if (btnEvnt.type == Event::MouseButtonPressed) {
			//if ((btnEvnt.mouseButton.x >= m_Posx && btnEvnt.mouseButton.x <= m_Posx+m_Width) && (btnEvnt.mouseButton.y >= m_Posy && btnEvnt.mouseButton.y <= m_Posy + m_Height)) {
				if (btnEvnt.mouseButton.button == Mouse::Left) {
					return true;
				}
			//}
		}

	}
	return false;
}

void Button::move(float x, float y)
{
	posX = posX + x;
	posY = posY + y;
	btnCoord.x1 = posX;
	btnCoord.y1 = posY;
	btnSprite.move(x,y);
}

void Button::draw(sf::RenderWindow& RwWin)
{
	if (buttonHeight == NULL)
		buttonHeight = 100;
	if (buttonWidth == NULL)
		buttonWidth = 100;
	if (buttonHeight < 5)
			buttonHeight = 5;
	if (buttonWidth < 5)
		buttonWidth = 5;
	if (buttonColor == Color(0,0,255))
		btnImg.create(buttonWidth, buttonHeight, buttonColor);

	bool longitude;
	for (int ery = 0; ery < buttonHeight; ery++) {
		for (int erx = 0; erx < buttonWidth; erx++) {
			if (((ery == 0 || ery == 1) || (ery == buttonHeight-2 || ery == buttonHeight - 1))) {
				longitude = true;
			}
			else {
				longitude = false;
			}

			if (longitude == true) {
				btnImg.setPixel(erx, ery, Color(0,0,0));
			}
			else {
				if (longitude == false) {
					if ((erx == 0 || erx == 1) || (erx == buttonWidth-2 || erx == buttonWidth-1)){
						btnImg.setPixel(erx, ery, Color(0,0,0));
					}
				}
			}
		}
	}
	btnTex.loadFromImage(btnImg);

	btnSprite.setTexture(btnTex);


	RwWin.draw(btnSprite);
	RwWin.draw(txt);


}

Button::~Button()
{
	//dtor
}
