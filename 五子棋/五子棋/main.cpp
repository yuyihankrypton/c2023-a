/*
˵����
C++
OpenGL
��֦�㷨
������
�û���
*/

#include "openGL.h"
#include "chess.h"

GLuint locxsize;
GLuint locysize;

GLuint vaoIDs[3];
GLuint vboIDs[6];
// ���ڴ�С
int xsize = 780;
int ysize = 780;
// ���ƴ��ڵ���ɫ����
vec4 yellow = vec4(1.0, 0.89, 0.77, 1.0);
vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
const int ELLIPSE_NUM_POINTS = 100;

int mainWindowSubmenu;
int mainWindowSubmenu1;
int mainWindow;
int mainWindowMenu;
int subWindow;
int subWindowMenu;
int subWindow1;
int subWindowMenu1;
const int MENU_CHOICE_BOOT = 0;
const int MENU_CHOICE_HUMAN = 1;
const int MENU_CHOICE_ROLLBACK = 2;
const int MENU_CHOICE_EXIT = 5;
bool isOk = false;
bool isMusic = true;
// ��Ϸ��OpenGL��ʼ��
vec4 gridpoints[60 + 255 * ELLIPSE_NUM_POINTS];
vec4 gridcolours[60 + 255 * ELLIPSE_NUM_POINTS];
Gobang gobang;
// ���Բ�ϵĵ�
vec2 getEllipseVertex(vec2 center, double scale, double verticalScale, double angle)
{
	vec2 vertex(sin(angle), cos(angle));
	vertex *= scale;
	vertex += center;

	vertex.y *= verticalScale;
	return vertex;
}
void  init()
{
	//�������̱���ɫ
	glClearColor(0.80f, 0.52f, 0.25f, 0.0f);
	// ��ʼ�����̸񣬰���60���������꣨�ܹ�30���ߣ�������ÿ������һ����ɫֵ3

	// ������
	int i = 0;
	for (int i = 0; i < 15; i++)
	{
		gridpoints[2 * i] = vec4((-150 + (50.0 * i)), 10.0, 0, 1);
		gridpoints[2 * i + 1] = vec4((-150 + (50.0 * i)), 710.0, 0, 1);
	}

	// ˮƽ��
	for (int i = 0; i < 15; i++)
	{
		gridpoints[30 + 2 * i] = vec4(-150.0, (10 + (50.0 * i)), 0, 1);
		gridpoints[30 + 2 * i + 1] = vec4(550.0, (10 + (50.0 * i)), 0, 1);
	}

	// �������߸��ɺ�ɫ
	for (int i = 0; i < 60; i++)
		gridcolours[i] = black;
	// ������ɫ��
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	locxsize = glGetUniformLocation(program, "xsize");
	locysize = glGetUniformLocation(program, "ysize");

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	GLuint vColor = glGetAttribLocation(program, "vColor");

	glGenVertexArrays(3, &vaoIDs[0]);

	// ���̸񶥵�
	glBindVertexArray(vaoIDs[0]);
	glGenBuffers(2, vboIDs);

	// ���̸񶥵�λ��
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[0]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridpoints, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	// ���̸񶥵���ɫ
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridcolours, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vColor);

}
/** \brief ����Բ������*/
void generateEllipsePoints(bool currentState, int startVertexIndex, int numPoints,
	vec2 center, double scale, double verticalScale)
{
	double angleIncrement = (2 * M_PI) / numPoints;
	double currentAngle = M_PI / 2;

	for (int i = startVertexIndex; i < startVertexIndex + numPoints; ++i) {
		gridpoints[i] = vec4(getEllipseVertex(center, scale, verticalScale, currentAngle), 0, 1);
		if (currentState == 0) {
			gridcolours[i] = white;

		}
		else {
			gridcolours[i] = black;

		}
		currentAngle += angleIncrement;
	}

}
// ����������ϵĵ�,������λ��������
void updateSquarePoints(float x, float y)
{
	gridpoints[60] = vec4(x - 25, y - 25, 0, 1);
	gridpoints[61] = vec4(x + 25, y - 25, 0, 1);
	gridpoints[62] = vec4(x + 25, y - 25, 0, 1);
	gridpoints[63] = vec4(x + 25, y + 25, 0, 1);
	gridpoints[64] = vec4(x + 25, y + 25, 0, 1);
	gridpoints[65] = vec4(x - 25, y + 25, 0, 1);
	gridpoints[66] = vec4(x - 25, y + 25, 0, 1);
	gridpoints[67] = vec4(x - 25, y - 25, 0, 1);
	for (int i = 60; i<68; ++i)
		gridcolours[i] = green;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);


	// ���̸񶥵�λ��
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[0]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridpoints, GL_DYNAMIC_DRAW);

	// ���̸񶥵���ɫ
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridcolours, GL_DYNAMIC_DRAW);

	glUniform1i(locxsize, xsize);
	glUniform1i(locysize, ysize);

	glBindVertexArray(vaoIDs[0]);
	// �������̸����
	glDrawArrays(GL_LINES, 0, 60);
	if (gobang.piecesCnt>0)
		glDrawArrays(GL_LINES, 60, 68);
	// ��������
	int startOffset = 68;
	for (int i = 0; i<gobang.piecesCnt; ++i, startOffset += ELLIPSE_NUM_POINTS)
		glDrawArrays(GL_TRIANGLE_FAN, startOffset, ELLIPSE_NUM_POINTS);
	//glFlush();
	glutSwapBuffers();
	int x, y;
	if (isOk)
	{
		gobang.getBestPos(x, y);
		cout << "hit:" << gobang.hit << endl;
		gobang.hit = 0;
		cout << "boot:" << x << ' ' << y << endl;
		isOk = false;
		if (gobang.placePiece(x, y))
		{

			gobang.isGameOver(x, y);
			if (gobang.gameOver)
			{
				switch (gobang.gameOver)
				{
				case 1:
					MessageBox(NULL, ("�׷�Ӯ"), ("������ʾ"), MB_OK);
					break;
				case 2:
					MessageBox(NULL, ("�ڷ�Ӯ"), ("������ʾ"), MB_OK);
					break;
				case 3:
					MessageBox(NULL, ("�;�"), ("������ʾ"), MB_OK);
					break;
				}
			}
		}


	}
}


void mainWindowMouse(int button, int state, int x, int y)
{
	if (gobang.gameOver == 0 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << x << ' ' << y << endl;
		int a[15];
		int i;
		for (i = 0; i < 15; ++i)
		{
			a[i] = 40 + 50 * i;
		}
		if (x - a[x / 50] >= -25 && x - a[x / 50] < 25)
			x = a[x / 50];
		else
			x = a[x / 50 - 1];

		if (y - a[y / 50] >= -25 && y - a[y / 50] < 25)
			y = a[y / 50];
		else
			y = a[y / 50 - 1];
		if (!gobang.placePiece((y - 40) / 50, (x - 40) / 50))
			MessageBox(NULL, ("���λ�ò��Ϸ�"), ("������ʾ"), MB_YESNO | MB_ICONQUESTION);
		else
		{
			gobang.isGameOver((y - 40) / 50, (x - 40) / 50);
			if (gobang.gameOver == 0)
			{
				isOk = true;

			}
			else
			{
				switch (gobang.gameOver)
				{
				case 1:
					MessageBox(NULL, ("�׷�Ӯ"), ("������ʾ"), MB_OK);
					break;
				case 2:
					MessageBox(NULL, ("�ڷ�Ӯ"), ("������ʾ"), MB_OK);
					break;
				case 3:
					MessageBox(NULL, ("�;�"), ("������ʾ"), MB_OK);
					break;
				}
			}

		}
	}
}
//////////////////////////////////////////////////////////////////////////
// �ڴ��ڱ������ʱ�򣬿������̸�Ĵ�С��ʹ֮���̶ֹ��ı�����
void reshape(GLsizei w, GLsizei h)
{
	xsize = w;
	ysize = h;
	glViewport(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////
// ������Ӧʱ���е���ͨ������Ӧ
void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 033: // ESC�˳���Ϸ
		exit(EXIT_SUCCESS);
		break;

	}
	glutPostRedisplay();
}
//////////////////////////////////////////////////////////////////////////
void idle(void)
{
	glutPostRedisplay();
}
//////////////////////////////////////////////////////////////////////////
void mainWindowMenuEvents(int menuChoice)
{
	switch (menuChoice) {
	case MENU_CHOICE_BOOT:
		gobang.restart();
		int x, y;
		gobang.getBestPos(x, y);
		if (gobang.placePiece(x, y))
		{
			gobang.isGameOver((y - 40) / 50, (x - 40) / 50);
			if (gobang.gameOver)
			{
				switch (gobang.gameOver)
				{
				case 1:
					MessageBox(NULL, ("�׷�Ӯ"), ("������ʾ"), MB_YESNO | MB_ICONQUESTION);
					break;
				case 2:
					MessageBox(NULL, ("�ڷ�Ӯ"), ("������ʾ"), MB_YESNO | MB_ICONQUESTION);
					break;
				case 3:
					MessageBox(NULL, ("�;�"), ("������ʾ"), MB_YESNO | MB_ICONQUESTION);
					break;
				}
			}
		}
		break;
	case MENU_CHOICE_HUMAN:
		gobang.restart();
		break;
	case MENU_CHOICE_ROLLBACK:
		if (gobang.piecesCnt)
			gobang.removePiece(gobang.steps[gobang.steps.size() - 1].x, gobang.steps[gobang.steps.size() - 1].y);
		if (gobang.piecesCnt)
			gobang.removePiece(gobang.steps[gobang.steps.size() - 1].x, gobang.steps[gobang.steps.size() - 1].y);
		break;		
	case MENU_CHOICE_EXIT:
		exit(EXIT_SUCCESS);
		break;

	}
	glutPostRedisplay();
}
//�Ҽ��˵�
void mainWindowSetupMenu()
{
	mainWindowMenu = glutCreateMenu(mainWindowMenuEvents);
	glutAddMenuEntry("Rollback", MENU_CHOICE_ROLLBACK);
	glutAddMenuEntry("AI first", MENU_CHOICE_BOOT);
	glutAddMenuEntry("Player first", MENU_CHOICE_HUMAN);
	glutAddMenuEntry("Exit", MENU_CHOICE_EXIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(xsize, ysize);
	glutInitWindowPosition(680, 178);
	glutCreateWindow("Gobang");
	glewInit();
	init();
	mainWindowSetupMenu();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mainWindowMouse);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

