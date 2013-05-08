//TYLER BROGNA
//PHOENIX RODDEN

#include "Pong.h"
#include <GL\freeglut.h>;
#include <iostream>;

Pong::Pong()
{
	leftScore = 0;
	rightScore = 0;

	left.pos.x += 80;
	left.pos.y += 350;

	right.pos.x += 1200;
	right.pos.y += 350;

	ball[0].pos.x += 500;
	ball[0].pos.y += 360;

	ball[0].velocity.x = .04;
	ball[0].velocity.y = -.01;
	ball[0].isActive = true;
	ball[0].collideRightLast = false;
}

void Pong::move(float dt) //euler integration for movement. woohoo
{
	for (int i = 0; i < 20; i++)
	{
		ball[i].pos.x += ball[i].velocity.x / dt;
		ball[i].pos.y += ball[i].velocity.y / dt;
	}
	left.pos.x += left.velocity.x / dt;
	left.pos.y += left.velocity.y / dt;

	right.pos.x += right.velocity.x / dt;
	right.pos.y += right.velocity.y / dt;

}

#pragma region Drawing

void Pong::drawPaddles() //draws the paddles at their locations. each paddle is 20x70.
{
	glBegin(GL_QUADS);
		glVertex3f(left.pos.x - padWidthHalf, left.pos.y - padHeightHalf, 0); //left paddle
		glVertex3f(left.pos.x + padWidthHalf, left.pos.y - padHeightHalf, 0);
		glVertex3f(left.pos.x + padWidthHalf, left.pos.y + padHeightHalf, 0);
		glVertex3f(left.pos.x - padWidthHalf, left.pos.y + padHeightHalf, 0);

		glVertex3f(right.pos.x - padWidthHalf, right.pos.y - padHeightHalf, 0); //right paddle
		glVertex3f(right.pos.x + padWidthHalf, right.pos.y - padHeightHalf, 0);
		glVertex3f(right.pos.x + padWidthHalf, right.pos.y + padHeightHalf, 0);
		glVertex3f(right.pos.x - padWidthHalf, right.pos.y + padHeightHalf, 0);
	glEnd();
}

void Pong::drawBall(int i) //draws the balls at their positions. each ball is 10x10.
{
	glBegin(GL_POLYGON);
		glVertex3f(ball[i].pos.x - 5, ball[i].pos.y - 5, 0);
		glVertex3f(ball[i].pos.x + 5, ball[i].pos.y - 5, 0);
		glVertex3f(ball[i].pos.x + 5, ball[i].pos.y + 5, 0);
		glVertex3f(ball[i].pos.x - 5, ball[i].pos.y + 5, 0);
	glEnd();
}

void Pong::drawNet() //Draws the net. The non collidable white dashed lines in the center of the screen
{
	glBegin(GL_QUADS);
		glVertex3f(638, 0, 0);
		glVertex3f(642, 0, 0);
		glVertex3f(642, 60, 0);
		glVertex3f(638, 60, 0);

		glVertex3f(638, 84, 0);
		glVertex3f(642, 84, 0);
		glVertex3f(642, 144, 0);
		glVertex3f(638, 144, 0);

		glVertex3f(638, 168, 0);
		glVertex3f(642, 168, 0);
		glVertex3f(642, 228, 0);
		glVertex3f(638, 228, 0);

		glVertex3f(638, 252, 0);
		glVertex3f(642, 252, 0);
		glVertex3f(642, 312, 0);
		glVertex3f(638, 312, 0);

		glVertex3f(638, 336, 0);
		glVertex3f(642, 336, 0);
		glVertex3f(642, 396, 0);
		glVertex3f(638, 396, 0);		

		glVertex3f(638, 420, 0);
		glVertex3f(642, 420, 0);
		glVertex3f(642, 480, 0);
		glVertex3f(638, 480, 0);
		
		glVertex3f(638, 504, 0);
		glVertex3f(642, 504, 0);
		glVertex3f(642, 564, 0);
		glVertex3f(638, 564, 0);

		glVertex3f(638, 588, 0);
		glVertex3f(642, 588, 0);
		glVertex3f(642, 648, 0);
		glVertex3f(638, 648, 0);

		glVertex3f(638, 672, 0);
		glVertex3f(642, 672, 0);
		glVertex3f(642, 732, 0);
		glVertex3f(638, 732, 0);
	glEnd();
}

void Pong::drawScore(int right, int left) // draws the score of each paddle in their respective field halves
{
	div_t rightDiv = div(right, 10);
	div_t leftDiv = div(left, 10);

	if (rightDiv.quot > 0)
	{
		drawNumber((int)rightDiv.quot, RIGHT_TENS);
	}

	drawNumber((int)rightDiv.rem, RIGHT_ONES);

	if (leftDiv.quot > 0)
	{
		drawNumber((int)leftDiv.quot, LEFT_TENS);
	}

	drawNumber((int)leftDiv.rem, LEFT_ONES);
}

void Pong::drawNumber(int num, int place)
{
	Vect loc; //Each number can be contained in a 40x70 box
	switch(place)
	{
	case RIGHT_TENS:
		loc.x = 320;
		loc.y = 520;
		break;
	case RIGHT_ONES:
		loc.x = 370;
		loc.y = 520;
		break;
	case LEFT_TENS:
		loc.x = 910;
		loc.y = 520;
		break;
	case LEFT_ONES:
		loc.x = 960;
		loc.y = 520;
		break;
	case TIMER_TENS:
		loc.x = 595;
		loc.y = 350;
		break;
	case TIMER_ONES:
		loc.x = 645;
		loc.y = 350;
		break;
	}

	glBegin(GL_QUADS);


		switch(num)
		{
		case 0:	//DRAWING NUMBER 0
			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x + 10, loc.y + 10, 0);
			glVertex3f(loc.x + 10, loc.y + 60, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y + 70, 0);
			glVertex3f(loc.x + 10, loc.y + 60, 0);
			glVertex3f(loc.x + 30, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);

			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x + 30, loc.y + 60, 0);
			glVertex3f(loc.x + 30, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y, 0);

			glVertex3f(loc.x + 40, loc.y, 0);
			glVertex3f(loc.x + 30, loc.y + 10, 0);
			glVertex3f(loc.x + 10, loc.y + 10, 0);
			glVertex3f(loc.x, loc.y, 0);

			break;
		case 1:		//DRAWING NUMBER 1
			glVertex3f(loc.x + 30, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x + 30, loc.y + 70, 0);

			break;
		case 2:		//DRAWING NUMBER 2
			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y, 0);

			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x + 10, loc.y, 0);
			glVertex3f(loc.x + 10, loc.y + 30, 0);
			glVertex3f(loc.x, loc.y + 30, 0);

			glVertex3f(loc.x, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x, loc.y + 40, 0);

			glVertex3f(loc.x + 30, loc.y + 40, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 30, loc.y + 60, 0);

			glVertex3f(loc.x, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);
			break;
		case 3:		//DRAWING NUMBER 3
			glVertex3f(loc.x + 30, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x + 30, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y, 0);

			glVertex3f(loc.x, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x, loc.y + 40, 0);

			glVertex3f(loc.x, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);
			break;
		case 4:			//DRAWING NUMBER 4
			glVertex3f(loc.x + 30, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x + 30, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x, loc.y + 40, 0);

			glVertex3f(loc.x, loc.y + 40, 0);
			glVertex3f(loc.x + 10, loc.y + 40, 0);
			glVertex3f(loc.x + 10, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			break;
		case 5:		//DRAWING NUMBER 5

			glVertex3f(loc.x, loc.y + 40, 0);
			glVertex3f(loc.x + 10, loc.y + 40, 0);
			glVertex3f(loc.x + 10, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y, 0);

			glVertex3f(loc.x, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x, loc.y + 40, 0);

			glVertex3f(loc.x, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x + 30, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 30, loc.y + 30, 0);

			break;
		case 6:		//DRAWING NUMBER 6
			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x + 10, loc.y, 0);
			glVertex3f(loc.x + 10, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y, 0);

			glVertex3f(loc.x, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x, loc.y + 40, 0);

			glVertex3f(loc.x, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x + 30, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 30, loc.y + 30, 0);

			break;
		case 7:		//DRAWING NUMBER 7
			glVertex3f(loc.x + 30, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x + 30, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			break;
		case 8:		//DRAWING NUMBER 8
			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x + 10, loc.y, 0);
			glVertex3f(loc.x + 10, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y, 0);

			glVertex3f(loc.x, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x, loc.y + 40, 0);

			glVertex3f(loc.x, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x + 30, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x + 30, loc.y + 70, 0);
			break;
		case 9:		//DRAWING NUMBER 9
			glVertex3f(loc.x + 30, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x + 30, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y, 0);
			glVertex3f(loc.x, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y + 10, 0);
			glVertex3f(loc.x + 40, loc.y, 0);

			glVertex3f(loc.x, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 30, 0);
			glVertex3f(loc.x + 40, loc.y + 40, 0);
			glVertex3f(loc.x, loc.y + 40, 0);

			glVertex3f(loc.x, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 60, 0);
			glVertex3f(loc.x + 40, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			glVertex3f(loc.x, loc.y + 40, 0);
			glVertex3f(loc.x + 10, loc.y + 40, 0);
			glVertex3f(loc.x + 10, loc.y + 70, 0);
			glVertex3f(loc.x, loc.y + 70, 0);

			break;
		}
	glEnd();
}


void Pong::drawTimer(int time)
{
	time = (time - 45) * -1; // the time sent is starting at 0. this makes it look like a countdown, 
								//rather than it counting up
	div_t timeSplit = div(time, 10);

	if (timeSplit.quot > 0)
	{
		drawNumber(timeSplit.quot, TIMER_TENS);
	}

	drawNumber(timeSplit.rem, TIMER_ONES);
}

#pragma endregion

#pragma region Collision

void Pong::ballPaddleCollide(int i)
{
	if (ball[i].collideRightLast) //dont collide again with the same paddle. sometimes balls collide 
	{								//with the same paddle the next frame that they did previously. do not want.
		if (ball[i].pos.x + 5 > left.pos.x - padWidthHalf &&
			ball[i].pos.x - 5 < left.pos.x + padWidthHalf) //close enough, x-wise?
		{
			if (ball[i].pos.y - 5 < left.pos.y + padHeightHalf && 
				ball[i].pos.y + 5 > left.pos.y - padHeightHalf) //close close enough, y-wise?
			{
				ball[i].velocity.x = ball[i].velocity.x * -1; //reverse  direction
				ball[i].collideRightLast = false;			//switch the last collided paddle
				newBall(ball[i]);							//make a new ball
			}
		}
	}
	else if (!ball[i].collideRightLast)
	{
		if (ball[i].pos.x + 5 > right.pos.x - padWidthHalf &&
			ball[i].pos.x - 5 < right.pos.x + padWidthHalf)
		{
			if (ball[i].pos.y - 5 < right.pos.y + padHeightHalf &&
				ball[i].pos.y + 5 > right.pos.y - padHeightHalf)
			{
				ball[i].velocity.x = ball[i].velocity.x * -1;
				ball[i].collideRightLast = true;
				newBall(ball[i]);
			}
		}
	}
}

void Pong::ballWallCollide(int i)
{
	if (ball[i].pos.y - 5 < 0 ||
		ball[i].pos.y + 5 > 720) //if the ball is gonna go off the screen in the y direction,
	{								//reverse y velocity.
		ball[i].velocity.y = ball[i].velocity.y * -1;
	}
}

Vect Pong::alterDirection(bool lastHitRight) //this give a new ball a new random velocity
{
	Vect newVel;
	newVel.x = (float) (rand() % 5 + 2) / 100; //x velocity between .04 and .06
	if (lastHitRight)
	{
		newVel.x = newVel.x * -1; //this makes sure the balls go the right direction, toward the opponent
	}

	newVel.y = (float) (rand() % 5 + 2) / 100; //new y velocity between .02 and .07
	if (rand() % 2 == 0)
	{
		newVel.y = newVel.y * -1; //random 'up' or 'down' velocity
	}
	return newVel;
}

void Pong::goalCheck(int i)
{
	if (ball[i].pos.x < 0) // if the ball touches the edge of the screen, the the opposite side scorea point
	{
		ball[i].isActive = false;
		rightScore++;
	}
	else if (ball[i].pos.x > 1280)
	{
		ball[i].isActive = false;
		leftScore++;
	}
}

#pragma endregion

void Pong::newBall(const GameObj& origin) //activates a new ball at the same place as the collided ball, but
{											//has a new velocity.
	for (int i = 0; i < 20; i++)
	{
		if (!ball[i].isActive)
		{
			ball[i].isActive = true;
			ball[i].velocity = alterDirection(origin.collideRightLast);
			ball[i].pos = origin.pos;
			ball[i].collideRightLast = origin.collideRightLast;
			break;
		}
	}
}

void Pong::act()
{
	int closestDist = 1280;
	int closestNum = 0;

	for (int i = 0; i < 20; i++)	//go through the ball array
	{
		if (ball[i].isActive)		//which ones are active?
		{
			if (ball[i].pos.x < 640 && //Which ball is closest?
				ball[i].pos.x < closestDist)
			{
				closestDist = ball[i].pos.x;
				closestNum = i;
			}
		}
	}

	if (ball[closestNum].pos.y > left.pos.y) //when the closest is found, follow that ball.
	{
		left.velocity.y = .05;
	}
	else
	{
		left.velocity.y = -.05; //*The comp move slower than the human player because the comp is brutal
									//and unforgiving.
	}
}

Pong::~Pong()
{

}