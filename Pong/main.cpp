//TYLER BROGNA

#include <iostream>
#include <GL\freeglut.h>
#include "Pong.h"
#include "keys.h"
#include <iostream>

using namespace std;

Pong game;
float oldTime = 0;
float dt;
bool gameEnd = false;

void drawScene()
{
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	dt = currentTime - oldTime;
	oldTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT);

	if (!gameEnd)
	{
		game.drawPaddles();
		game.drawNet();
		game.drawScore(game.leftScore, game.rightScore);
		game.drawTimer(glutGet(GLUT_ELAPSED_TIME) / 1000);

		for (int i = 0; i < 20; i++) //Active ball game loop. Go through all the balls in the game
		{								//and do all the checks needed
			if (game.ball[i].isActive)
			{
				game.drawBall(i);			//Draw active balls
				game.ballPaddleCollide(i);	//check ball collision with paddles
				game.ballWallCollide(i);	//check ball collision with walls
				game.goalCheck(i);			//see if the balls went past the edge of the screen.
			}
		}

		game.act(); //Ai pattern for the left paddle
	}
	else
	{
		game.drawNet();
		game.drawScore(game.leftScore, game.rightScore);
	}
	if (glutGet(GLUT_ELAPSED_TIME) > 45000)
	{
		gameEnd = true;
	}
	
	
	glFlush();
}

void idle(int wait)
{
	bool moveUp = IsKeyPressed(KEY_UP);			//check if the up key is pressed
	bool moveDown = IsKeyPressed(KEY_DOWN);		//same thing, but for the down key

	if (moveUp) //if up is pressed, then the pad moves up by getting a bit of y velocity
	{
		game.right.velocity.y = .07;
	}
	
	if (moveDown) //same with move down, same velocity but in the opposite direction
	{
		game.right.velocity.y = -.07;
	}

	if (!moveUp && !moveDown) // stop moving if neither key is pressed
	{
		game.right.velocity.y = 0;
	}

	if (!gameEnd) // movement loop.
	{
		game.move((dt + 1) / 1000);
	}
	glutPostRedisplay();

	glutTimerFunc(10, idle, 0);
}

void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1280, 0, 720, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char **argPtr)
{ 	
	glutInit(&argc, argPtr);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(200, 200);

	glutInitWindowSize(1280, 720);

	glutCreateWindow("PONG");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	InitKeyboard();

	glutDisplayFunc(drawScene);

	glutReshapeFunc(resize);

	glutTimerFunc(10, idle, 0);

	glutMainLoop();
}