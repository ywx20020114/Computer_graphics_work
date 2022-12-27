#include "stdlib.h"
#include <GL/glut.h>
#include<iostream>
#include <math.h>
using namespace std;
GLfloat w = 1100;
GLfloat h = 1100;
double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_z = 0.0;

# define  white  1.0 ,  1.0  ,  1.0   // ����ɫ�ĺ궨��
# define  green  0.0 ,  0.502,  0.0
# define  red    0.8 ,  0.0  ,  0.0
# define  gray   0.502, 0.502,0.502
# define  hgray  0.117, 0.180,0.227
# define  blue   0.0  , 0.0  ,  1.0
# define  pi  3.14159265
# define  gold   1.0,215.0/255.0,0.0
# define  hgreen 0.0,100.0/255.0,0.0
# define  brown  210.0/255.0, 105.0/255.0,  30.0/255.0
# define  nbrown 128.0/255.0, 64.0/255.0, 64.0/255.0
# define  men   244.0/255.0 ,164.0/255.0 , 96.0/255.0
# define  menba   139.0/255.0 ,69.0/255.0,19.0/255.0
# define water 141.0/255.0, 193.0/255.0, 241.0/255.0
# define orange 255.0/255.0, 128.0/255.0, 0.0/255.0
# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0

double fang[8][3];             // ���峤�����8������
// ����constract����  �������������������ĵ�ʱ��
// ���������7������ ����ֵ��fang

double san[8][3];              // �������Ϊ���εĳ�����

//�����������������
GLuint texGround;
GLuint texPoor;
GLuint texFloor;
GLuint texRoof;
GLuint texwall;

#define BMP_Header_Length 54  
static GLfloat angle = 0.0f;  
//���ʲ���
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };  //���ʲ��������淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ��
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };  //���ʱ����΢΢�����ⷢ�����
const GLfloat matiral_shininess = 11.00;
//���ò���


GLfloat sca[3] = { 1.5, 1.5, 1.5 };
GLfloat tra[3] = { -300, 0, -470 };


GLfloat AngleX;
GLfloat AngleY;


GLfloat bx = 0; //Ӿ����������ƶ�����
GLfloat by = 0;
GLfloat bz = 0;

void setMetiral(GLfloat matiral_diffuse_ambient[4])
{
	//������ɫ
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient); //������ֵͬ������
	//���ò���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);  //���淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ��
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);  //���ʱ����΢΢�����ⷢ����ߣ��������۾��о���������������ɫ 
	glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 0);   //������ָ������0~128�� ��ֵԽС������Խ�ֲڣ����Դ����Ĺ������䵽���棬Ҳ���Բ����ϴ�����㡣��ֵԽ�󣬱�ʾ����Խ�����ھ��棬��Դ���䵽����󣬲�����С�����㡣

}



void cons(double x, double y, double z, double x1, double y1, double z1) {  //����
	san[0][0] = x;
	san[0][1] = y;
	san[0][2] = z;     //  ��0����

	san[1][0] = x;
	san[1][1] = y;
	san[1][2] = z + z1;   //  ��1����

	san[4][0] = x;
	san[4][1] = y + y1;
	san[4][2] = z;     //  ��4����

	san[5][0] = x;
	san[5][1] = y + y1;
	san[5][2] = z + z1 / 2;      //  ��5����
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			san[3][i] = san[0][i] + x1;
			san[2][i] = san[1][i] + x1;
			san[6][i] = san[4][i] + x1;
			san[7][i] = san[5][i] + x1;
		}
		else {
			san[3][i] = san[0][i];
			san[2][i] = san[1][i];
			san[6][i] = san[4][i];
			san[7][i] = san[5][i];
		}
	}
}

void constract(double x, double y, double z, double x1, double y1, double z1) { //������
	fang[0][0] = x;
	fang[0][1] = y;
	fang[0][2] = z;        //  ��0����

	fang[1][0] = x;
	fang[1][1] = y;
	fang[1][2] = z + z1;     //  ��һ����

	fang[2][0] = x + x1;
	fang[2][1] = y;
	fang[2][2] = z + z1;     //  �ڶ�����

	fang[3][0] = x + x1;
	fang[3][1] = y;
	fang[3][2] = z;        //  ��������
	for (int i = 0; i < 4; i++) {  // for()ѭ�������������ĸ���
		for (int j = 0; j < 3; j++) {
			if (j == 1)
				fang[i + 4][j] = fang[i][j] + y1;
			else
				fang[i + 4][j] = fang[i][j];
		}
	}
}

void build2() {
	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glEnd();   //     �µ�

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glEnd();   //     ǰ��

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     ����
}

void build() {
	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     �µ�

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
	glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
	glEnd();   //     ǰ��

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
	glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glEnd();   //     ����

	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
	glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
	glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
	glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
	glEnd();   //     ����
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();          //����M����
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	//glScalef(1.5, 1.5, 1.5);
	//glTranslatef(-470, 0, -470);


	glScalef(sca[0], sca[1], sca[2]);
	glTranslatef(tra[0], tra[1], tra[2]);


	////****************************���ӵ���װ壨��ɫΪ ��ɫ��********
	glBegin(GL_POLYGON);
	constract(-200, 0, -200, 1100, 1, 800);
	glColor3f(green);
	build();

	////****************************���Ӵ�ز�********
	glBegin(GL_POLYGON);
	constract(-200, -5, -200, 1100, 1, 800);
	glColor3f(nbrown);
	build();

	

	
	GLfloat matiral_diffused[4] = { 0.20, 0.32, 0.80, 1.00 };
	setMetiral(matiral_diffused);

	glEnable(GL_TEXTURE_2D);    //�ݵ�����
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 11, -200);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-200, 11, 600);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(900, 11, 600);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(900, 11, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	

	//****************************����դ����������ɫΪ ��ɫ��********
	glBegin(GL_POLYGON);
	constract(10, 10, 10, 20, 40, 480);
	glColor3f(white);
	build();       //    ��Ӧ��A��
	constract(30, 10, 10, 650, 40, 20);
	glColor3f(white);
	build();       //    ��Ӧ��B��
	constract(680, 10, 10, 20, 40, 480);
	glColor3f(white);
	build();       //    ��Ӧ��C��
	constract(30, 10, 470, 100, 40, 20);
	glColor3f(white);
	build();       //    ��Ӧ��D��
	//constract(230, 10, 470, 450, 40, 20);
	glColor3f(white);
	build();       //    ��Ӧ��F��
	//****************************����դ�����ӣ���ɫΪ ��ɫ��********
	glBegin(GL_POLYGON);
	constract(10, 10, 10, 20, 50, 20);
	glColor3f(white);
	build();       //    ��Ӧ��A��
	glBegin(GL_POLYGON);
	constract(680, 10, 10, 20, 50, 20);
	glColor3f(white);
	build();       //    ��Ӧ��C��
	glBegin(GL_POLYGON);
	constract(230, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    ��Ӧ��F��
	glBegin(GL_POLYGON);
	constract(10, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    ��Ӧ��E��
	glBegin(GL_POLYGON);
	constract(680, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    ��Ӧ��G��
	glBegin(GL_POLYGON);
	//constract(310, 10, 470, 20, 50, 20);
	//glColor3f(white);
	//build();       //    ��Ӧ��H��
	glBegin(GL_POLYGON);
	constract(110, 10, 470, 20, 50, 20);
	glColor3f(white);
	build();       //    ��Ӧ��I��
	

	//****************************����Ӿ��********
	glColor3f(water);
	constract(490, 10, 75, 150, 5, 350);
	build();

	glColor3f(white);
	constract(490, 10, 75, 8, 12, 350);
	build();     //��ǽ��
	glColor3f(white);
	constract(632, 10, 75, 8, 12, 350);
	build();     //��ǽ��
	glColor3f(white);
	constract(498, 10, 75, 134, 12, 8);
	build();     //��ǽ��
	glColor3f(white);
	constract(498, 10, 417, 134, 12, 8);
	build();     //��ǽ��1

	glEnable(GL_TEXTURE_2D);   //Ӿ������
	glBindTexture(GL_TEXTURE_2D, texPoor);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(490, 16, 75);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(490, 16, 425);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(640, 16, 425);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(640, 16, 75);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//****************************���ӳ���ǽ����ɫΪ ��ɫ��********
	glColor3f(white);
	constract(320, 10, 250, 10, 100, 220);
	build();
	constract(460, 10, 250, 10, 100, 220);
	build();
	//****************************���ӳ��ⶥ���ɫΪ ���ɫ��********
	glColor3f(hgray);
	constract(320, 110, 250, 150, 10, 220);
	build();
	//****************************�������ҺͿ�����ǽ�ڣ���ɫΪ ��ɫ��********
	
	glColor3f(white);
	constract(438, 10, 50, 12, 150, 197);
	build();     //��ǽ��
	glColor3f(white);
	constract(62, 10, 50, 376, 150, 12);
	build();     //��ǽ��

	glColor3f(white);
	constract(62, 10, 235, 376, 35, 12);
	build();     //��ǽ��1
	glColor3f(white);
	constract(62, 45, 235, 50, 65, 12);
	build();     //��ǽ��2
	glColor3f(white);
	constract(200, 45, 235, 238, 65, 12);
	build();     //��ǽ��3
	glColor3f(white);
	constract(62, 110, 235, 376, 50, 12);
	build();     //��ǽ��4



	//****************************���ӷ��ڵذ�********
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texFloor);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(62, 15, 62);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(62, 15, 235);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(438, 15, 235);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(438, 15, 62);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//****************************�������ҺͿ����Ĳ�������ɫΪ ��ɫ��********
	glColor4f(blue, 0.35);
	constract(62 + 50, 45, 235, 88, 65, 12);
	build();

	////****************************���ӷ��� ����ɫ ��************
	
	glColor3f(115.0/255.0, 37.0/255.0, 32.0/255.0);
	cons(50, 160, 148.5, 400, 27, 110);
	build2();
	cons(50, 187, 148.5, 400, 27, 90);
	//cons(50, 187, 140, 400, 27, 90);
	build2();
	cons(50, 214, 148.5, 400, 27, 70);
	build2();
	cons(50, 241, 148.5, 400, 15, 50);
	build2();
	glColor3f(115.0 / 255.0, 37.0 / 255.0, 32.0 / 255.0);
	cons(50, 160, 148.5, 400, 27, -110);
	build2();
	cons(50, 187, 148.5, 400, 27, -90);
	build2();
	cons(50, 214, 148.5, 400, 27, -70);
	build2();
	cons(50, 241, 148.5, 400, 15, -50);
	build2();

	//************************************* ��*************
	glColor3f(men);
	constract(230, 10, 250, 50, 100, 5);
	build();              //����
	glColor3f(menba);
	constract(235, 60, 255, 5, 5, 5);
	build();              //�Ű���
	//**************************************С·*************
	for (int i = 0; i < 6; i++)
	{
		glColor3f(brown);
		constract(235 - i * 15, 10, 250 + i * 40, 40, 2, 20);
		build();
	}
	

	//**************************************����*************
	glColor3f(brown);
	constract(60, 10, 390, 15, 70, 15);
	build();
	//**************************************��Ҷ*************
	glColor3f(hgreen);
	glTranslatef(60, 70, 400);
	glutSolidSphere(25.0, 20, 20);  //��1

	glTranslatef(20, 0, 0);
	glutSolidSphere(25.0, 20, 20);  //��2

	glTranslatef(-10, 0, -10);
	glutSolidSphere(25.0, 20, 20);  //��3

	glTranslatef(0, 0, 20);
	glutSolidSphere(25.0, 20, 20);  //��4

	glTranslatef(0, 10, -10);
	glutSolidSphere(25.0, 20, 20);  //��4
	glTranslatef(-70, -80, -400);




	glFlush();  // ˢ��
	glutSwapBuffers();//��Ҫ����swapbuffer����
}

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
//GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.5 };;//��Դλ��
GLfloat light_position[] = { 1.0,1.0,0,0 };;//��Դλ��
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };

void init(void)
{
	

	GLfloat sun_direction[] = { 700.0, 400.0, 100.0, 1.0 };
	GLfloat sun_intensity[] = { sunshine, 1.0 };
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };

	glEnable(GL_LIGHTING);              // ������
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	


	glEnable(GL_LIGHT0);                // ������
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	glEnable(GL_COLOR_MATERIAL);        
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glLineWidth(5);
	glClearColor(white, 0.0);      //���屳����ɫ-->  white

	glEnable(GL_BLEND); // �򿪻��
	glDisable(GL_DEPTH_TEST); // �ر���Ȳ���
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // ����Դ����alphaͨ��ֵ�İ�͸����Ϻ���
	glEnable(GL_DEPTH_TEST); //����Ȳ���

	glMatrixMode(GL_PROJECTION);     // ò�ƺ��ӽ��йصĶ��� places the camera at (0,0,0) and faces it along(0,0,-1).
	glOrtho(-w, w, -h, h, -w, w); // specify clipping volume
}


int flag = 1;
void timerFunction(int value)
{
	if (flag == 1) {
		by = by + 4;
		flag++;
	}
	else if (flag == 2) {
		by = by - 4;
		flag--;
	}
	else {
		cout << "Wrong!\n";
	}
	glutPostRedisplay();
	glutTimerFunc(1000, timerFunction, 1);
}

void specialkeys(int key, int x, int y) {   //������Ӧ����

	
	//��ת
	if (key == GLUT_KEY_RIGHT)
		rotate_y -= 1;
	else if (key == GLUT_KEY_LEFT)
		rotate_y += 1;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 1;
	else if (key == GLUT_KEY_UP)
		rotate_x += 1;

	glutPostRedisplay();
}

// ����power_of_two�����ж�һ�������ǲ���2����������
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* ����load_texture
* ��ȡһ��BMP�ļ���Ϊ����
* ���ʧ�ܣ�����0������ɹ�������������
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;
	FILE* pFile;
	errno_t err;

	// ���ļ������ʧ�ܣ�����
	if ((err = fopen_s(&pFile, file_name, "rb")) != 0)
	{
		printf("�޷��򿪴��ļ�\n");            //����򲻿���������򲻿�
		exit(0);                               //��ֹ����
	}

	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// �����������ֽ��������ڴ�
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// ��ȡ��������
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// �Ծ;ɰ汾�ļ��ݣ����ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
	// ��ͼ���߳�����OpenGL�涨�����ֵ��Ҳ����
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// ����ÿ����Ҫ���ֽ��������ֽ���
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// �����ڴ�
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// ������������
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// ����һ���µ�������
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}


	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //�ָ�֮ǰ�������
	free(pixels);
	return texture_ID;
}

int main(int argc, char** argv)    //  main���� ���Ӽ����¼�
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The House");
	init();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);    // ��������
	
	texGround = load_texture("grass4.bmp");  //��������
	texPoor = load_texture("swimmingpoor3.bmp");
	texFloor = load_texture("floor.bmp");

	texRoof = load_texture("roof.bmp"); 
	texwall = load_texture("wall.bmp");
	glutDisplayFunc(display);
	
	glutSpecialFunc(specialkeys);  //���ü��̿��ƺ���	
	glutTimerFunc(1000, timerFunction, 1);    //ע�ᶨʱ��
	glutMainLoop();
	system("pause");
	return 0;
}

