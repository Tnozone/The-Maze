#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>

#define PI 3.1415926535

float px,py,pdx,pdy,pa; //player position

void drawPlayer()
{
  glColor3f(1,1,0);
  glPointSize(8);
  glBegin(GL_POINTS);
  glVertex2i(px,py);
  glEnd();
  
  glLineWidth(3);
  glBegin(GL_LINES);
  glVertex2i(px,py);
  glVertex2i(px+pdx*5, py+pdy*5);
  glEnd();
}

int mapX=24,mapY=24,mapS=576;
int map[]=
{
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
  2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
  2,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
  2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,
  2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,
  2,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,
  2,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,
  2,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,2,
  2,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
  2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
  2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,2,
  2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,2,
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
};

void DrawMap2D()
{
  int x,y,xo,yo;
  for(y=0;y<mapY;y++)
  {
    for(x=0;x<mapX;x++)
    {
      if(map[y*mapX+x]==1) { glColor3f(1,1,1);}
      else if(map[y*mapX+x]==2) { glColor3f(1,0,0);}
      else { glColor3f(0,0,0);}
      xo=x*mapS; yo=y*mapS;
      glBegin(GL_QUADS);
      glVertex2i(xo , yo  );
      glVertex2i(xo , yo+mapS);
      glVertex2i(xo+mapS, yo+mapS);
      glVertex2i(xo+mapS, yo  );
      glEnd();
    }
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  DrawMap2D();
  drawPlayer();
  glutSwapBuffers();
}

void buttons(unsigned char key,int x,int y)
{
  if(key=='a') { pa-=0.1; if(pa<0) { pa+=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
  if(key=='d') { pa+=0.1; if(pa>2*PI) { pa-=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
  if(key=='w') { px+=pdx; py+=pdy;}
  if(key=='s') { px-=pdx; py-=pdy;}
  glutPostRedisplay();
}

void init()
{
  glClearColor(0.3,0.3,0.3,0);
  gluOrtho2D(0,1024,512,0);
  px=300; py=300; pdx=cos(pa)*5; pdy=sin(pa)*5;
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(1024, 512);
  glutCreateWindow("Maze");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(buttons);
  glutMainLoop();
}
