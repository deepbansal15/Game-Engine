/*
 * Message.cpp
 *
 *  Created on: Jan 17, 2013
 *      Author: nathan
 */

#include "Message.h"

namespace TileEngine
{


Message::Message(std::string message, std::string fontFile, int fontSize, float x, float y)
{
	this->fontSize = fontSize;
	fileName = fontFile;
	this->message = message;
	this->x = x;
	this->y = y;

	font = ResourceMgr->acquireFont(fontFile, fontSize);
	textColor = {255,255,255};
	dx = dy = 0;

	image = TTF_RenderText_Solid(font, message.c_str(), textColor);
}

void Message::update()
{
	x += dx;
	y += dy;
}

void Message::setFont(std::string fontFile, int size)
{
	ResourceMgr->releaseFont(fileName, fontSize);
	font = ResourceMgr->acquireFont(fontFile, size);
	setMessage(message);
}

void Message::setMessage(std::string message)
{
	SDL_FreeSurface(image);
	image = TTF_RenderText_Solid(font, message.c_str(), textColor);
}

void Message::scrollSpeed( float dx, float dy )
{
	this->dx = dx;
	this->dy = dy;
}

void Message::setTextColor(SDL_Color color)
{
	textColor = color;
	setMessage(message);
}

Message::~Message()
{
	SDL_FreeSurface(image);
	ResourceMgr->releaseFont(fileName, fontSize);
}
}
