//sprite.h

#ifndef _SPRITE_H
#define _SPRITE_H

#include "imageanim.h"
#include <deque>

class Point
{
public:
	Point() : _x(0), _y(0) {}
	Point(int x, int y) : _x(x), _y(y) {}
	int _x, _y;
};

typedef std::deque<Point> tPoints;

class Sprite : public ImageAnim
{
public:
	enum eSprite {	SPR_NONE = 0,		//static, not moving
					SPR_LEFT = 1,
					SPR_RIGHT = 2,
					SPR_UP = 4,
					SPR_DOWN = 8
				};

	Sprite();
	Sprite(std::string fileName, bool bAlpha, Uint32 nFrames);
	virtual ~Sprite() {}

	//start move from A to B then stop or repeat
	void startMoveTo(int xEnd, int yEnd, Uint32 time = 100, Uint32 delay = 0);
	void startMoveTo(int xEnd, int yEnd, 
					Uint32 rate, Uint32 delay,  
					float xVel, float yVel,
					eSprite type = Sprite::SPR_NONE);
	void calcWaypoints(int x1, int y1, int x2, int y2);

	int calcDistance(int x1, int y1, int x2, int y2);
	void calcXYSteps(int frames, int x1, int y1, int x2, int y2, float &deltaX, float &deltaY);
	Uint32 calcXYRate(Uint32 time, int x1, int y1, int x2, int y2, float &deltaX, float &deltaY);

	void setMoveRate(Uint32 rate, Uint32 delay)	{ _waitM.start(_rateM = rate, delay); }
	void setMoveLoop(bool loop)		{ _loopM = loop;}			//keep moving each time?
	void pauseMove(bool b = true)	{ _pauseM = b; }			//stop/start moving
	void toggleMove()				{ _pauseM = !_pauseM; }		//toggle pause state
	bool canMove()		{ return ((_xVel || _yVel) && (_xDir || _yDir)); } 
	bool isMoving()		{ return !(_x == _xEnd && _y == _yEnd); }	//has it reached end point yet

	//overridden functions
	virtual void setPos(float x, float y);
	virtual void work();	//update movement, and call parent anim update

protected:

	int		_xStart;	//save start x pos
	int		_yStart;	//save start y pos
	int		_xEnd;		//ending x position
	int		_yEnd;		//ending y position

	int		_xDir;		//pos=right, neg=left
	int		_yDir;		//pos=down, neg=up
	float	_xVel;		//amount of change in x dir
	float	_yVel;		//amount of change in y dir

	eSprite _type;		//predefined movement etc

	tPoints	_points;
	tPoints::const_iterator	_pointit;

private:
	bool	_pauseM;	//true if not moving (default=false)
	bool	_loopM;		//loop the movement (default=true), or just once through
	Uint32	_rateM;		//rate of auto movement change
	Waiting _waitM;		//movement delay
};


#endif //_SPRITE_H


