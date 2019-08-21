#include "Button.h"

using namespace sf;

Image btnImg;
Texture btnTex;
Sprite btnSprite;
Text txt;
Font btnFont;


Button::Button()
{

	m_Height = NULL;
	m_Width = NULL;
	m_Text = "";
	m_Color = Color(0, 0, 255);
	btnCoord.x1 = m_Posx;
	btnCoord.y1 = m_Posy;
	btnCoord.x2 = m_Posx + m_Width;
	btnCoord.y2 = m_Posy + m_Height;
}

void Button::setWidth(int val)
{
	m_Width = val;
	btnCoord.x2 = m_Posx + m_Width;
}

void Button::setHeight(int val)
{
	m_Height = val;
	btnCoord.y2 = m_Posy + m_Height;
}

int Button::getWidth()
{
	return m_Width;
}

int Button::getHeight()
{
	return m_Height;
}

float Button::getPosx()
{
	return m_Posx;
}

float Button::getPosy()
{
	return m_Posy;
}

void Button::setText(const sf::String& str, const sf::Font& fnt)
{

	m_Text = str;
	btnFont = fnt;
	//String str = m_Text;
	txt.setString(str);
	int len = str.getSize();
	int chrSize = (m_Height - 2);
	txt.setCharacterSize(chrSize);
	txt.setFont(fnt);
	txt.move(m_Posx + ((m_Width/2) - (len/2)*chrSize), (m_Posy - 2));
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
	m_Posx = m_Posx + x;
	m_Posy = m_Posy + y;
	btnCoord.x1 = m_Posx;
	btnCoord.y1 = m_Posy;
	btnSprite.move(x,y);
}

void Button::draw(sf::RenderWindow& RwWin)
{
	if (m_Height == NULL)
		m_Height = 100;
	if (m_Width == NULL)
		m_Width = 100;
	if (m_Height < 5)
			m_Height = 5;
	if (m_Width < 5)
		m_Width = 5;
	if (m_Color == Color(0,0,255))
		btnImg.create(m_Width, m_Height, m_Color);

	bool longitude;
	for (int ery = 0; ery < m_Height; ery++) {
		for (int erx = 0; erx < m_Width; erx++) {
			if (((ery == 0 || ery == 1) || (ery == m_Height-2 || ery == m_Height - 1))) {
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
					if ((erx == 0 || erx == 1) || (erx == m_Width-2 || erx == m_Width-1)){
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
