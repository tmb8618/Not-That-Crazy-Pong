#pragma once
#include "Vect.h"

#define padWidthHalf 10
#define padHeightHalf 35

enum {RIGHT_TENS, RIGHT_ONES, LEFT_TENS, LEFT_ONES, TIMER_TENS, TIMER_ONES};

class Pong
{
public:
	
	struct GameObj
	{
		Vect pos;				//Absoulte position of obj. Only uses XY, and is located in the center of the paddle
		Vect velocity;			//Velocity of obj. Also only uses XY. 
		bool collideRightLast;	//for ball only. Cant collide with the same paddle twice.
								  //doing so leads to some awkward 'double switchback' situations.
		bool isActive;			//for ball only. If this ball is active, then perform collision checks.
									//less checks = faster code, or so i think.

		void operator = (const GameObj& original)
		{
			this->pos = original.pos;
			this->velocity = original.velocity;
			this->collideRightLast = original.collideRightLast;
		}
	};

	Pong();

	
	int leftScore;
	int rightScore;
	GameObj left;		//paddle on the left (AI controlled)
	GameObj right;		//paddle on the right (player controlled)
	GameObj ball[20];	//Ball array. up to 20 can be onscreen. Every time a ball is bounced off a paddle,
							//a new ball is created. 

	void move(float dt);					//updates the position of the objects in the scene.

	void drawPaddles();						//Draws both paddles.

	void drawBall(int i);					//Draws the current position of the specified ball.

	void drawNet();							//Pong's gotta have a net. cant collide with the ball. drawn down the center.

	void drawScore(int right, int left);	//Draw the score onscreen. Looks like classic pong!!

	void drawTimer(int time);				//Draws the time till the end of the game in the middle of the screen.

	void ballPaddleCollide(int i);			//If the ball hits a paddle, a new ball is made and the velocites of both balls are 
												//altered slightly, after the x velocity is reversed.

	void ballWallCollide(int i);			//If a ball hits a wall, the y velocity is simply reversed. no physics nonsense needed.

	void goalCheck(int i);					//If the ball passes past the bounds of the screen, then one side gets a point

	void act();		//AI for the left paddle. 
	
	~Pong();

private:

	void drawNumber(int num, int place);	//for drawScore. draws the number in the position left or right.

	void newBall(const GameObj& origin);	//After a ball hits a paddle, another ball is added to the game at the same point
												//with a slightly different velocity than the first ball. This new ball
												//is sent back at the opposing paddle with the old one

	Vect alterDirection(bool lastHitRight);	//After a ball hits a paddle, the direction is altered slightly. It is influenced by the
												//way the paddle is moving, but is more or less random.

};

