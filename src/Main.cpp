/*
 * main.cpp
 * Blaze Game Engine v0.11
 *
 * Created by Ned Bingham on October 20, 2011.
 * Modified by Ned Bingham on October 20, 2011.
 * Copyright 2011 Sol Union. All rights reserved.
 *
 * Blaze Game Engine v0.11 is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Blaze Game Engine v0.11 is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Blaze Game Engine v0.11.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "core.h"
#include <time.h>

canvashdl core;
keyboardhdl *keys;
mousehdl *mouse;
/*objecthdl obj;
camerahdl cam;*/

bool windowed = false;
int mouse_x = -1;
int mouse_dx = -1;
int mouse_y = -1;
int mouse_dy = -1;

void init()
{
	srand(time(0));
	core.initialize();
	/*cam.init(0.0, 1.0, 1.0, 0.0, vec4f(1.0, 1.0, 1.0, 1.0), vec4f(), vec4f(), 0.0);
	cam.frustum = frustum4f(-.16, .16, -.1, .1, .2, 1.0E10);
	user.cam = &cam;

	core.add_child(&cam);
	core.add_user(&user);*/
	mouse = core.devices.new_mouse();
	keys = core.devices.new_keyboard();

	mouse->hide();

	core.player.map_analog(&mouse->pointer[0], &lookv);
	core.player.map_analog(&mouse->pointer[1], &lookh);
	core.player.map_digital(&(((button8hdl*)&keys->keystates)[12]), NULL, &left, NULL, NULL,      &right, &up,  NULL, NULL);
	core.player.map_digital(&(((button8hdl*)&keys->keystates)[14]), NULL, &down, NULL, &backward, NULL,   NULL, NULL, &forward);
}

void displayfunc()
{
	core.render();
}

void reshape(int w, int h)
{
	core.reshape(w, h);
}

void pmotionfunc(int x, int y)
{
	int dx = mouse_x != -1 ? x - mouse_x : 0;
	int dy = mouse_y != -1 ? y - mouse_y : 0;
	mouse_x = x;
	mouse_y = y;
	int d2x = mouse_dx != -1 ? dx - mouse_dx : 0;
	int d2y = mouse_dy != -1 ? dy - mouse_dy : 0;
	mouse_dx = dx;
	mouse_dy = dy;

	mousehdl *currm = NULL;
	for (list_node<controllerhdl> *i = core.devices.begin(); i != core.devices.end(); i = i->next)
	{
		if (i->type == CNTRL_MOUSE)
		{
			currm = (mousehdl*)i;
			currm->pointer[0] = vec3f((float)mouse_y, (float)mouse_dy, (float)d2y);
			currm->pointer[1] = vec3f((float)mouse_x, (float)mouse_dx, (float)d2x);
		}
	}
}

void mousefunc(int button, int state, int x, int y)
{
	int dx = mouse_x != -1 ? x - mouse_x : 0;
	int dy = mouse_y != -1 ? y - mouse_y : 0;
	mouse_x = x;
	mouse_y = y;
	int d2x = mouse_dx != -1 ? dx - mouse_dx : 0;
	int d2y = mouse_dy != -1 ? dy - mouse_dy : 0;
	mouse_dx = dx;
	mouse_dy = dy;

	mousehdl *currm = NULL;
	for (list_node<controllerhdl> *i = core.devices.begin(); i != core.devices.end(); i = i->next)
	{
		if (i->type == CNTRL_MOUSE)
		{
			currm = (mousehdl*)i;
			currm->pointer[0] = vec3f((float)mouse_y, (float)mouse_dy, (float)d2y);
			currm->pointer[1] = vec3f((float)mouse_x, (float)mouse_dx, (float)d2x);

			if (state == GLUT_DOWN)
				currm->press(button - GLUT_LEFT_BUTTON);
			else if (state == GLUT_UP)
				currm->release(button - GLUT_LEFT_BUTTON);
		}
	}
}

void motionfunc(int x, int y)
{
	int dx = mouse_x != -1 ? x - mouse_x : 0;
	int dy = mouse_y != -1 ? y - mouse_y : 0;
	mouse_x = x;
	mouse_y = y;
	int d2x = mouse_dx != -1 ? dx - mouse_dx : 0;
	int d2y = mouse_dy != -1 ? dy - mouse_dy : 0;
	mouse_dx = dx;
	mouse_dy = dy;

	mousehdl *currm = NULL;
	for (list_node<controllerhdl> *i = core.devices.begin(); i != core.devices.end(); i = i->next)
	{
		if (i->type == CNTRL_MOUSE)
		{
			currm = (mousehdl*)i;
			currm->pointer[0] = vec3f((float)mouse_y, (float)mouse_dy, (float)d2y);
			currm->pointer[1] = vec3f((float)mouse_x, (float)mouse_dx, (float)d2x);
		}
	}
}

void keydownfunc(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);

	keyboardhdl *currm = NULL;
	for (list_node<controllerhdl> *i = core.devices.begin(); i != core.devices.end(); i = i->next)
	{
		if (i->type == CNTRL_KEYBOARD)
		{
			currm = (keyboardhdl*)i;
			currm->press(key);
		}
	}
}

void keyupfunc(unsigned char key, int x, int y)
{
	keyboardhdl *currm = NULL;
	for (list_node<controllerhdl> *i = core.devices.begin(); i != core.devices.end(); i = i->next)
	{
		if (i->type == CNTRL_KEYBOARD)
		{
			currm = (keyboardhdl*)i;
			currm->release(key);
		}
	}
}

void release()
{
	core.release();
}

struct test_node : ilist_node<test_node>
{
	test_node() {}
	test_node(int x)
	{
		i = x;
	}
	~test_node(){}
	int i;
};

struct test_list : ilist<test_node>
{

};

int main(int argc, char **argv)
{
	/*glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	atexit(release);

	if (windowed)
	{
		glutInitWindowSize(1600, 900);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("BGE");
	}
	else
	{
		glutGameModeString("1600x900:32@60");
		glutEnterGameMode();
	}

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error %s\n", glewGetErrorString(err));
		exit(1);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "Status: Using GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glutReshapeFunc(reshape);
	glutDisplayFunc(displayfunc);
	glutIdleFunc(displayfunc);

	glutPassiveMotionFunc(pmotionfunc);
	glutMotionFunc(motionfunc);
	glutMouseFunc(mousefunc);
	glutKeyboardFunc(keydownfunc);
	glutKeyboardUpFunc(keyupfunc);

	init();
	glutMainLoop();
	if (!windowed)
		glutLeaveGameMode();*/

	test_list x;
	x.push_back(test_node(10));
	x.push_back(test_node(7));
	x.push_back(test_node(2));

	for (test_node *n = x.begin(); n != x.end(); n = n->next)
		cout << n->i << endl;
}
