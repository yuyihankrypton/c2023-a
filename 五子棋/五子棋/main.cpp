/*
说明：
C++
OpenGL
剪枝算法
博弈树
置换表
*/

#include "openGL.h"
#include "chess.h"

GLuint locxsize;
GLuint locysize;

GLuint vaoIDs[3];
GLuint vboIDs[6];
// 窗口大小
int xsize = 780;
int ysize = 780;
// 绘制窗口的颜色变量
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
// 游戏和OpenGL初始化
vec4 gridpoints[60 + 255 * ELLIPSE_NUM_POINTS];
vec4 gridcolours[60 + 255 * ELLIPSE_NUM_POINTS];
Gobang gobang;
// 获得圆上的点
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
	//设置棋盘背景色
	glClearColor(0.80f, 0.52f, 0.25f, 0.0f);
	// 初始化棋盘格，包含60个顶点坐标（总共30条线），并且每个顶点一个颜色值3

	// 纵向线
	int i = 0;
	for (int i = 0; i < 15; i++)
	{
		gridpoints[2 * i] = vec4((-150 + (50.0 * i)), 10.0, 0, 1);
		gridpoints[2 * i + 1] = vec4((-150 + (50.0 * i)), 710.0, 0, 1);
	}

	// 水平线
	for (int i = 0; i < 15; i++)
	{
		gridpoints[30 + 2 * i] = vec4(-150.0, (10 + (50.0 * i)), 0, 1);
		gridpoints[30 + 2 * i + 1] = vec4(550.0, (10 + (50.0 * i)), 0, 1);
	}

	// 将所有线赋成黑色
	for (int i = 0; i < 60; i++)
		gridcolours[i] = black;
	// 载入着色器
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	locxsize = glGetUniformLocation(program, "xsize");
	locysize = glGetUniformLocation(program, "ysize");

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	GLuint vColor = glGetAttribLocation(program, "vColor");

	glGenVertexArrays(3, &vaoIDs[0]);

	// 棋盘格顶点
	glBindVertexArray(vaoIDs[0]);
	glGenBuffers(2, vboIDs);

	// 棋盘格顶点位置
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[0]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridpoints, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	// 棋盘格顶点颜色
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridcolours, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vColor);

}
/** \brief 生成圆的坐标*/
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
// 获得正方形上的点,用来定位最后落棋点
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


	// 棋盘格顶点位置
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[0]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridpoints, GL_DYNAMIC_DRAW);

	// 棋盘格顶点颜色
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
	glBufferData(GL_ARRAY_BUFFER, (68 + 225 * ELLIPSE_NUM_POINTS) * sizeof(vec4), gridcolours, GL_DYNAMIC_DRAW);

	glUniform1i(locxsize, xsize);
	glUniform1i(locysize, ysize);

	glBindVertexArray(vaoIDs[0]);
	// 绘制棋盘格的线
	glDrawArrays(GL_LINES, 0, 60);
	if (gobang.piecesCnt>0)
		glDrawArrays(GL_LINES, 60, 68);
	// 绘制棋子
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
					MessageBox(NULL, ("白方赢"), ("操作提示"), MB_OK);
					break;
				case 2:
					MessageBox(NULL, ("黑方赢"), ("操作提示"), MB_OK);
					break;
				case 3:
					MessageBox(NULL, ("和局"), ("操作提示"), MB_OK);
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
			MessageBox(NULL, ("点击位置不合法"), ("操作提示"), MB_YESNO | MB_ICONQUESTION);
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
					MessageBox(NULL, ("白方赢"), ("操作提示"), MB_OK);
					break;
				case 2:
					MessageBox(NULL, ("黑方赢"), ("操作提示"), MB_OK);
					break;
				case 3:
					MessageBox(NULL, ("和局"), ("操作提示"), MB_OK);
					break;
				}
			}

		}
	}
}
//////////////////////////////////////////////////////////////////////////
// 在窗口被拉伸的时候，控制棋盘格的大小，使之保持固定的比例。
void reshape(GLsizei w, GLsizei h)
{
	xsize = w;
	ysize = h;
	glViewport(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////
// 键盘响应时间中的普通按键响应
void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 033: // ESC退出游戏
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
					MessageBox(NULL, ("白方赢"), ("操作提示"), MB_YESNO | MB_ICONQUESTION);
					break;
				case 2:
					MessageBox(NULL, ("黑方赢"), ("操作提示"), MB_YESNO | MB_ICONQUESTION);
					break;
				case 3:
					MessageBox(NULL, ("和局"), ("操作提示"), MB_YESNO | MB_ICONQUESTION);
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
//右键菜单
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

