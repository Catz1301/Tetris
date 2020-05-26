#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Button
{
	public:
		/** Default constructor */
		//Button(sf::Window winPrm);
		Button();
		Button(int x1, int y1, int x2, int y2);
		/** Default destructor */
		~Button();

		/** Access m_Width
		 * \return The current value of m_Width
		 */
		int getWidth();

		/** Set m_Width
		 * \param val New value to set
		 */
		void setWidth(int val);

		/** Access m_Height
		 * \return The current value of m_Height
		 */
		int getHeight();

		/** Set m_Height
		 * \param val New value to set
		 */
		void setHeight(int val);

		/** Access m_Text
		 * \return The current value of m_Text
		 */
		//std::string getText();

		/** Set m_Text
		 * \param val New value to set
		 */
		void setText(const sf::String& str, const sf::Font& fnt);

		float getPosx();
		float getPosy();

		void move(float x, float y);

		void draw(sf::RenderWindow& RwWin);

		bool onClickListener(sf::RenderWindow& RwWin);

	protected:

		struct coord
		{
			int x1,y1,x2,y2;
		} btnCoord;

	private:
		int buttonWidth; //!< Member variable "m_Width"
		int buttonHeight; //!< Member variable "m_Height"
		sf::Color buttonColor;
		std::string buttonText; //!< Member variable "m_Text"
		float posX, posY;
		void *ptr;
		sf::Image btnImg;
		sf::Texture btnTex;
		sf::Sprite btnSprite;
		sf::Text txt;
		sf::Font btnFont;
};

#endif // BUTTON_H
