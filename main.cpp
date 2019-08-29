#include "glTexture.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include<math.h>
#include<stdlib.h>

using namespace std;
float x,y,radius,x1=335.0,x2=817.0,scale1=2.0,scale2=0.0;
float l=380.0;
float y2=674.0;
float m;
float PI=3.14159;
int triangleAmount = 50;
GLfloat twicePi = 2.0f * PI;
glTexture hTexture;
float dx,dx2,dy2,xInc,yInc,x01,h1,x02,h2;
bool l1,l2,l3,l4;
bool scene1,scene2,scene3;
GLfloat position = 0.0f;
GLfloat position1 = 0.0f;
int count=0;
GLfloat speed = 5.0f;
GLfloat angle = 50.0f;
GLfloat sizex = 1.0f;
int arr[3]={0,1,2};
void DDA1()
{
    dx2=x2-x1;
    dy2=y2-l;
    float Steps;
    if (abs(dx2) > abs(dy2))
        Steps = abs(dx2);
    else
        Steps = abs(dy2);
    xInc=dx2/Steps;
    yInc=dy2/Steps;
}
void DDA2()
{
    dx2=x1-x2;
    dy2=l-y2;
    float Steps;
    if (abs(dx2) > abs(dy2))
        Steps = abs(dx2);
    else
        Steps = abs(dy2);
    xInc=dx2/Steps;
    yInc=dy2/Steps;
}
void Init()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0,1024,674,0,0.1,-1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glClearColor(0.0,0.0,0.0,1.0);
}
void Scene1T(int value)
{
    if(dx>=1024)
    {
        dx=-1024;
    }
    dx+=5;
    glutPostRedisplay();
    glutTimerFunc(10,Scene1T,0);
}
void update(int value)
{

    if(position > 500)
        position = 0.0f;

    position += speed;

	glutPostRedisplay();
	glutTimerFunc(50, update, 0);

}
void update1(int value)
{

    if(position1 > 130)
        position1 = 0.0f;

    position1 += speed;

	glutPostRedisplay();
	glutTimerFunc(50, update1, 0);

}
void l2T(int value)
{
    if(l2==false)
    {
        l2=true;
    }
    else
    {
        l2=false;
    }
    glutPostRedisplay();
    glutTimerFunc(500,l2T,0);
}
void Scene2T1(int value)
{
    if(x01>=0&&y>=0)
    {
        DDA1();
        x01+=xInc;
        h1+=yInc;
    }
    else
    {
        x01=0;
        h1=0;
    }
    if(scale1<=0)
    {
        scale1=2.0;
    }
    else
    {
        scale1-=0.05;
    }
    glutPostRedisplay();
    glutTimerFunc(100,Scene2T1,0);
}
void Scene2T2(int value)
{
    if(x02>=0&&y>=0)
    {
        DDA1();
        x02+=xInc;
        h2+=yInc;
    }
    else
    {
        x02=0;
        h2=0;
    }
    if(scale2>=2.0)
    {
        scale2=0.0;
    }
    else
    {
        scale2+=0.05;
    }
    glutPostRedisplay();
    glutTimerFunc(100,Scene2T2,0);
}
void DrawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    if(scene1!=true&&scene2!=true&&scene3!=true)
    {
        hTexture.SetActive(4);
        glEnable( GL_TEXTURE_2D );
        glPushMatrix();
        glBegin(GL_QUADS);
            glTexCoord2d(0.0f, 1.0f);glVertex3f(0, 0, -1.0f);
            glTexCoord2d(0.0f, 0.0f);glVertex3f(0, 674, -1.0f);
            glTexCoord2d(1.0f, 0.0f);glVertex3f(1024, 674, -1.0f);
            glTexCoord2d(1.0f, 1.0f);glVertex3f(1024, 0, -1.0f);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    if(scene1==true)
    {
        //BG
        hTexture.SetActive(1);
        glEnable( GL_TEXTURE_2D );
        glPushMatrix();
        glBegin(GL_QUADS);
            glTexCoord2d(0.0f, 1.0f);glVertex3f(0, 0, -1.0f);
            glTexCoord2d(0.0f, 0.0f);glVertex3f(0, 674, -1.0f);
            glTexCoord2d(1.0f, 0.0f);glVertex3f(1024, 674, -1.0f);
            glTexCoord2d(1.0f, 1.0f);glVertex3f(1024, 0, -1.0f);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        //Light1

        x=50,y=180,radius=200;
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f,1.0f,0.0f,0.2f);
            glVertex3f(x, y,-0.99f); // center of circle
            for(int i = 0; i <= triangleAmount;i++) {
                glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.99f);
                }
        glEnd();
        //Light 2
        glPushMatrix();
         if(l2==true)
        {
        x=412,y=180,radius=200;
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f,1.0f,0.0f,0.2f);
            glVertex3f(x, y,-0.99f); // center of circle
            for(int i = 0; i <= triangleAmount;i++) {
                glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.99f);
            }
        glEnd();
        }
        glPopMatrix();
        //Light 3
        x=748,y=180,radius=200;
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f,1.0f,0.0f,0.2f);
            glVertex3f(x, y,-0.99f); // center of circle
            for(int i = 0; i <= triangleAmount;i++) {
                glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.99f);
            }
        glEnd();

        //Light 4
        x=1100,y=180,radius=200;
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f,1.0f,0.0f,0.2f);
            glVertex3f(x, y,-0.99f); // center of circle
            for(int i = 0; i <= triangleAmount;i++) {
                glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.99f);
            }
        glEnd();
        glPushMatrix();
        glTranslatef(dx,0,0);
        //Carroof
        glBegin(GL_POLYGON);
        glColor3ub(201, 112, 229);
            glVertex3f(209,425,-0.9);
            glVertex3f(152,465,-0.9);
            glVertex3f(386,465,-0.9);
            glVertex3f(429,425,-0.9);
        glEnd();
        //sidewindow
        glBegin(GL_POLYGON);
        glColor3ub(124, 55, 153);
            glVertex3f(152,465,-0.9);
            glVertex3f(110,503,-0.9);
            glVertex3f(458,503,-0.9);
            glVertex3f(386,465,-0.9);
        glEnd();
        //frontwidnow
        glBegin(GL_POLYGON);
        glColor3ub(124, 35, 153);
            glVertex3f(386,465,-0.9);
            glVertex3f(458,503,-0.9);
            glVertex3f(497,462,-0.9);
            glVertex3f(429,425,-0.9);
        glEnd();
        //hood
        glBegin(GL_POLYGON);
        glColor3ub(201, 112, 229);
            glVertex3f(458,503,-0.9);
            glVertex3f(573,505,-0.9);
            glVertex3f(600,462,-0.9);
            glVertex3f(497,462,-0.9);
        glEnd();
        //front
        glBegin(GL_POLYGON);
        glColor3ub(152, 69, 179);
            glVertex3f(600,520,-0.9);
            glVertex3f(600,571,-0.9);
            glVertex3f(632,536,-0.9);
            glVertex3f(629,478,-0.9);
            glVertex3f(600,462,-0.9);
            glVertex3f(573,505,-0.9);
        glEnd();
        //tire
        x=493,y=560,radius=50;
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.2f,0.2f,0.2f);
            glVertex3f(x, y,-0.91f); // center of circle
            for(int i = 0; i <= triangleAmount;i++) {
                glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.91f);
            }
        glEnd();
        //tire2
        x=155,y=560,radius=50;
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.2f,0.2f,0.2f);
            glVertex3f(x, y,-0.91f); // center of circle
            for(int i = 0; i <= triangleAmount;i++) {
                glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.91f);
            }
        glEnd();
        //side
        glBegin(GL_POLYGON);
        glColor3ub(72, 19, 89);
            glVertex3f(35,503,-0.9);
            glVertex3f(16,532,-0.9);
            glVertex3f(49,571,-0.9);
            glVertex3f(600,571,-0.9);
            glVertex3f(600,520,-0.9);
            glVertex3f(573,505,-0.9);
            glVertex3f(458,503,-0.9);
        glEnd();
        //bunker
        glBegin(GL_POLYGON);
        glColor3ub(201, 112, 229);
            glVertex3f(35,503,-0.9);
            glVertex3f(110,503,-0.9);
            glVertex3f(133,481,-0.9);
            glVertex3f(70,481,-0.9);
        glEnd();
        //shadow
        glBegin(GL_POLYGON);
        glColor4ub(5,5,5,30);
            glVertex3f(600,571,-0.9);
            glVertex3f(49,571,-0.9);
            glVertex3f(0,674,-0.9);
            glVertex3f(573,674,-0.9);
            glVertex3f(632,536,-0.9);
        glEnd();
        glPopMatrix();
        glColor3f(1.0,1.0,1.0);
    }
    else if(scene2==true)
    {
        hTexture.SetActive(2);
        glEnable( GL_TEXTURE_2D );
        glPushMatrix();
        glBegin(GL_QUADS);
            glTexCoord2d(0.0f, 1.0f);glVertex3f(0, 0, -1.0f);
            glTexCoord2d(0.0f, 0.0f);glVertex3f(0, 674, -1.0f);
            glTexCoord2d(1.0f, 0.0f);glVertex3f(1024, 674, -1.0f);
            glTexCoord2d(1.0f, 1.0f);glVertex3f(1024, 0, -1.0f);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glScalef(0.3,0.3,1.0);
        //roof
        glPushMatrix();
        glTranslatef(1200,950,0);
        glTranslatef(x01,h1,0);
        glScalef(scale1,scale1,1);
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(585+50,436,-0.9);
            glVertex3f(613+50,454,-0.9);
            glVertex3f(632+50,448,-0.9);
            glVertex3f(604+50,432,-0.9);
        glEnd();
        //side
        glBegin(GL_POLYGON);
        glColor3ub(182, 74, 131);
            glVertex3f(585+50,436,-0.9);
            glVertex3f(585+50,445,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(613+50,454,-0.9);
        glEnd();
        //sidedoor
        glBegin(GL_POLYGON);
        glColor3ub(25,2,80);
            glVertex3f(579+50,441,-0.9);
            glVertex3f(579+50,446,-0.9);
            glVertex3f(622+50,480,-0.9);
            glVertex3f(622+50,474,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(585+50,445,-0.9);
        glEnd();
        //frontwindow
        glBegin(GL_POLYGON);
        glColor3ub(182, 74, 131);
            glVertex3f(632+50,448,-0.9);
            glVertex3f(613+50,454,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(632+50,458,-0.9);
        glEnd();
        //hood
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(642+50,465,-0.9);
            glVertex3f(632+50,458,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(622+50,474,-0.9);
        glEnd();
        //front
        glBegin(GL_POLYGON);
        glColor3ub(30,100,60);
            glVertex3f(622+50,480,-0.9);
            glVertex3f(642+50,472,-0.9);
            glVertex3f(642+50,465,-0.9);
            glVertex3f(622+50,474,-0.9);
        glEnd();
        //back
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(585+50,439,-0.9);
            glVertex3f(579+50,441,-0.9);
            glVertex3f(585+50,445,-0.9);
        glEnd();
        glPopMatrix();

        //2nd car
        glPushMatrix();
        glTranslatef(1200,950,0);
        glTranslatef(x02,h2,0);
        glScalef(scale2,scale2,1);
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(585-50,436,-0.9);
            glVertex3f(613-50,454,-0.9);
            glVertex3f(632-50,448,-0.9);
            glVertex3f(604-50,432,-0.9);
        glEnd();
        //side
        glBegin(GL_POLYGON);
        glColor3ub(182, 74, 131);
            glVertex3f(585-50,436,-0.9);
            glVertex3f(585-50,445,-0.9);
            glVertex3f(613-50,464,-0.9);
            glVertex3f(613-50,454,-0.9);
        glEnd();
        //sidedoor
        glBegin(GL_POLYGON);
        glColor3ub(25,2,80);
            glVertex3f(579-50,441,-0.9);
            glVertex3f(579-50,446,-0.9);
            glVertex3f(622-50,480,-0.9);
            glVertex3f(622-50,474,-0.9);
            glVertex3f(613-50,464,-0.9);
            glVertex3f(585-50,445,-0.9);
        glEnd();
        //frontwindow
        glBegin(GL_POLYGON);
        glColor3ub(182, 74, 131);
            glVertex3f(632-50,448,-0.9);
            glVertex3f(613-50,454,-0.9);
            glVertex3f(613-50,464,-0.9);
            glVertex3f(632-50,458,-0.9);
        glEnd();
        //hood
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(642-50,465,-0.9);
            glVertex3f(632-50,458,-0.9);
            glVertex3f(613-50,464,-0.9);
            glVertex3f(622-50,474,-0.9);
        glEnd();
        //front
        glBegin(GL_POLYGON);
        glColor3ub(30,100,60);
            glVertex3f(622-50,480,-0.9);
            glVertex3f(642-50,472,-0.9);
            glVertex3f(642-50,465,-0.9);
            glVertex3f(622-50,474,-0.9);
        glEnd();
        //back
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(585-50,439,-0.9);
            glVertex3f(579-50,441,-0.9);
            glVertex3f(585-50,445,-0.9);
        glEnd();
        //3rdcar
        glPushMatrix();
        glTranslatef(-260,-60,0);
        glTranslatef(x01,h1,0);
        glScalef(scale2,scale2,1);
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(585+50,436,-0.9);
            glVertex3f(613+50,454,-0.9);
            glVertex3f(632+50,448,-0.9);
            glVertex3f(604+50,432,-0.9);
        glEnd();
        //side
        glBegin(GL_POLYGON);
        glColor3ub(182, 74, 131);
            glVertex3f(585+50,436,-0.9);
            glVertex3f(585+50,445,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(613+50,454,-0.9);
        glEnd();
        //sidedoor
        glBegin(GL_POLYGON);
        glColor3ub(25,2,80);
            glVertex3f(579+50,441,-0.9);
            glVertex3f(579+50,446,-0.9);
            glVertex3f(622+50,480,-0.9);
            glVertex3f(622+50,474,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(585+50,445,-0.9);
        glEnd();
        //frontwindow
        glBegin(GL_POLYGON);
        glColor3ub(182, 74, 131);
            glVertex3f(632+50,448,-0.9);
            glVertex3f(613+50,454,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(632+50,458,-0.9);
        glEnd();
        //hood
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(642+50,465,-0.9);
            glVertex3f(632+50,458,-0.9);
            glVertex3f(613+50,464,-0.9);
            glVertex3f(622+50,474,-0.9);
        glEnd();
        //front
        glBegin(GL_POLYGON);
        glColor3ub(30,100,60);
            glVertex3f(622+50,480,-0.9);
            glVertex3f(642+50,472,-0.9);
            glVertex3f(642+50,465,-0.9);
            glVertex3f(622+50,474,-0.9);
        glEnd();
        //back
        glBegin(GL_POLYGON);
        glColor3ub(234, 85, 164);
            glVertex3f(585+50,439,-0.9);
            glVertex3f(579+50,441,-0.9);
            glVertex3f(585+50,445,-0.9);
        glEnd();
        glPopMatrix();
        glPopMatrix();
        glColor3f(1.0,1.0,1.0);
    }
    else if(scene3==true)
    {
    hTexture.SetActive(3);
        glEnable( GL_TEXTURE_2D );
    glPushMatrix();
    glBegin(GL_QUADS);
        glTexCoord2d(0.0f, 1.0f);glVertex3f(0.0f, 0.0f, -1.0f);
        glTexCoord2d(0.0f, 0.0f);glVertex3f(0.0f, 576.0f, -1.0f);
        glTexCoord2d(1.0f, 0.0f);glVertex3f(1024.0f, 576.0f, -1.0f);
        glTexCoord2d(1.0f, 1.0f);glVertex3f(1024.0f, 0.0f, -1.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


     glPushMatrix();
     glRotatef(-5.0,0.0f,0.0f,1.0f);
    glTranslatef(-position,position,0.0f);


    GLfloat x=434,y=415,radius=11;
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(0.0f,0.0f,0.0f,1.0f);
		glVertex3f(x, y,-0.999f);
		for(int i = 0; i <= triangleAmount;i++) {
			glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.99f);
		}
    glEnd();

          x=460,y=390,radius=10;
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(0.0f,0.0f,0.0f,1.0f);
		glVertex3f(x, y,-0.999f);
		for(int i = 0; i <= triangleAmount;i++) {
			glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)),y + (radius * sin(i * twicePi / triangleAmount)),-0.99f);
		}
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(153, 0, 153);
        glVertex3f(444.0f,349.0f,-0.999f);
        glVertex3f(474.0f,349.0f,-0.999f);
        glVertex3f(432.0f,391.0f,-0.999f);
        glVertex3f(403.0f,390.0f,-0.999f);
    glEnd();


       glBegin(GL_POLYGON);
        glColor3ub(153, 0, 153);
        glVertex3f(395.0f,415.0f,-0.999f);
        glVertex3f(423.0f,415.0f,-0.999f);
        glVertex3f(423.0f,430.0f,-0.999f);
        glVertex3f(395.0f,430.0f,-0.999f);

    glEnd();

       glBegin(GL_QUADS);
        glColor3ub(153, 0, 153);
        glVertex3f(403.0f,390.0f,-0.999f);
        glVertex3f(433.0f,390.0f,-0.999f);
        glVertex3f(422.0f,414.0f,-0.999f);
        glVertex3f(394.0f,414.0f,-0.999f);
    glEnd();

           glBegin(GL_POLYGON);
        glColor3ub(153, 0, 153);
        glVertex3f(474.0f,349.0f,-0.999f);
        glVertex3f(474.0f,382.0f,-0.999f);
        glVertex3f(423.0f,429.0f,-0.999f);
        glVertex3f(424.0f,414.0f,-0.999f);
        glVertex3f(434.0f,391.0f,-0.999f);
    glEnd();
    glPopMatrix();



    glPushMatrix();
     glRotatef(3.0,0.0f,0.0f,1.0f);
     glTranslatef(0,-position1,0.0f);

               glBegin(GL_POLYGON);
        glColor3ub(153, 0, 153);
        glVertex3f(527.0f,416.0f,-0.999f);
        glVertex3f(554.0f,416.0f,-0.999f);
        glVertex3f(580.0f,502.0f,-0.999f);
        glVertex3f(523.0f,502.0f,-0.999f);
    glEnd();

                  glBegin(GL_POLYGON);
        glColor3ub(153, 0, 153);
        glVertex3f(580.0f,502.0f,-0.999f);
        glVertex3f(523.0f,502.0f,-0.999f);
        glVertex3f(523.0f,533.0f,-0.999f);
        glVertex3f(579.0f,533.0f,-0.999f);
    glEnd();

                glBegin(GL_POLYGON);
        glColor3ub(153, 0, 153);
        glVertex3f(524.0f,534.0f,-0.999f);
        glVertex3f(524.0f,547.0f,-0.999f);
        glVertex3f(576.0f,547.0f,-0.999f);
        glVertex3f(577.0f,534.0f,-0.999f);
    glEnd();
    glPopMatrix();

   glColor3f(1.0,1.0,1.0);
    }
    glPopMatrix();
    glutSwapBuffers();

}
void Reshape(int w, int h)
{
    if (w <= 0)
    {
        w = 1;
    }
    if (h <= 0)
    {
        h = 1;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float ratio = 1 * w / h;
    gluPerspective(90, ratio, 0.1, -1.0f);
    glViewport(0.0f, 0.0f, w, h);
}
void handleKeypress(unsigned char key, int x, int y)
{
    if(key==32)
    {
        if(arr[count]==0)
        {
            scene2=false;
            scene1=true;
            scene3=false;
        }
        else if(arr[count]==1)
        {
            scene1=false;
            scene2=true;
            scene3=false;
        }
        else if (arr[count]==2)
        {
            scene1=false;
            scene2=false;
            scene3=true;
        }
        if(count>=3)
            count=0;
        else
            count++;
    }
    else if (key==27)
    {
        exit(0);
    }
	glutPostRedisplay();

}
int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(1024, 674);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("ScreenSaver");
    glutFullScreen();
    glutDisplayFunc(DrawScene);
    glutTimerFunc(10,Scene1T,0);
    glutTimerFunc(500,l2T,0);
    glutTimerFunc(100,Scene2T1,0);
    glutTimerFunc(100,Scene2T2,0);
    glutTimerFunc(50, update, 0);
    glutTimerFunc(50, update1, 0);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(Reshape);
    hTexture.loadTextureInfo("bin/Debug/Scene1.bmp", 1);
    hTexture.loadTextureInfo("bin/Debug/Scene2.bmp", 2);
    hTexture.loadTextureInfo("bin/Debug/Scene3.bmp", 3);
    hTexture.loadTextureInfo("bin/Debug/start.bmp", 4);
    Init();
    glutMainLoop();
    return 0;
}

