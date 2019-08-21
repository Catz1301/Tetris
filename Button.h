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
		int m_Width; //!< Member variable "m_Width"
		int m_Height; //!< Member variable "m_Height"
		sf::Color m_Color;
		std::string m_Text; //!< Member variable "m_Text"
		float m_Posx, m_Posy;
		void *ptr;

};

#endif // BUTTON_H
