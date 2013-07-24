/*
 * Message.h
 *
 *  Created on: Jan 17, 2013
 *      Author: nathan
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "ResourceManager.h"
#include <string>

namespace TileEngine
{

class Message
{
public:
	//Scrolling
	//Image
	//Change Image
	/////Delete old image
	Message(std::string message,
			std::string fontFile,
			int fontSize = 28,
			float x = 0,
			float y = 0);

	void update();

	void setTextColor(SDL_Color color);

	int X() const{ return (int)x; }
	int Y() const{ return (int)y; }

	void setX( int x ){ this->x = x; }
	void setY( int y ){ this->y = y; }

	void setFont(std::string fontFile, int size = 28);
	void setMessage(std::string message);
	void scrollSpeed( float dx, float dy );

	SDL_Surface* getImage() const{ return image; }
	virtual ~Message();

private:
	SDL_Surface* image;
	SDL_Color textColor;
	TTF_Font* font;
	std::string message;

	std::string fileName;
	int fontSize;

	float x;
	float y;
	float dx;
	float dy;
};
}

#endif /* MESSAGE_H_ */
