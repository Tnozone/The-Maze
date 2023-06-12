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

void drawRays3D()
{
  int r,mx,my,mp,dof; float rx,ry,ra,xo,yo;
  ra=pa;
  for(r=0;r<1;r++)
  {
    //Check Horizontal Lines
    dof=0;
    float aTan=-1/tan(ra);
    if(ra>PI){ ry=(((int)py>>6)<<6)-0.0001; rx(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;} //Looking up
    if(ra<PI){ ry=(((int)py>>6)<<6)+64; rx(py-ry)*aTan+px; yo=64; xo=-yo*aTan;} //Looking down
    if(ra==0 || ra==PI) { rx=px; ry=py; dof=8;} //Looking straight left or right
    while(dof<8)
    {
      mx=(int)(rx)>>6; my(int)(ry)>>6; mp=my*mapX+mx;
      if(mp<mapX*mapY && map[mp]!=0){ dof=8;} //Hit wall
      else{ rx+=xo; ry+=yo; dof+=1;} //next line
    }
    glColor3f(0,1,0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2i(px,py);
    glVertex2i(rx,ry);
    glEnd();
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
