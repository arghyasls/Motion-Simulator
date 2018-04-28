#include <iostream>
#include <cmath>
#include <gl/glut.h>
#include <string.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define PI 3.14159265
//50 0 70 100 550 0 90 80
//
typedef struct {
	double x;
	double y;
	
} Point;
typedef struct {
	double x;
	double y;
	double t;
} Graph;

GLint WindowID2,WindowID3; 
double time1 = 0.0;
double time2 = 0.0;
double x1,y11,theta1,v1,h1;
double x2,y2,theta2,v2,h2;
double v1x,v1y;
double v2x,v2y;

void print(int x, int y,char *string)
{
glRasterPos2f(x,y);
int len = (int) strlen(string);
for (int i = 0; i < len; i++)
{
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
}
};


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(10.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0,1024, 0.0, 480);
}

void init2() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(4.0f);
	gluOrtho2D(0.0, 25, 0, 720);
}



Point p1,p2;

Graph b1[1000],b2[1000]; 

float ans1=INT_MAX,ans2=INT_MAX;
int q=0;
bool check=0;
double times=0,times2=0;

void calc() {
	time1 += 0.1;
	time2 += 0.1;

	

	p1.x=v1x*time1+x1;
	p1.y = v1y*time1+(-0.5*9.8)*(time1*time1)+y11;
	
	b1[q].x=p1.x;
	b1[q].y=p1.y;
	b1[q].t=time1;
	

	p2.x=v2x*time2+x2;
	p2.y=v2y*time2+ (-0.5*9.8)*(time2*time2)+y2;
	
	b2[q].x=p2.x;
	b2[q].y=p2.y;
	b2[q].t=time2;
	
	
	q++;

	
	
	if(p1.y<0)
		ans1=MIN(ans1,time1);
	if(p2.y<0)
		ans2=MIN(ans2,time2);
		
}
char * stringx(double x)
{
	char s1[20];sprintf(s1,"%f",x);char *time2="X= ";char * str3 = (char *) malloc(1 + strlen(time2)+ strlen(s1) );
     strcpy(str3, time2);
     strcat(str3, s1);
	 return str3;
}
char * stringy(double y)
{
	char s1[20];sprintf(s1,"%f", y);char *time2="Y= ";char * str3 = (char *) malloc(1 + strlen(time2)+ strlen(s1) );
     strcpy(str3, time2);
     strcat(str3, s1);
	 return str3;
}
void display() {
	calc();
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat twicePi = 2.0f * 3.14;
	int triangleAmount=20;

	int radius1=10;
	glColor3f(0.498, 1.000, 0.83);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(p1.x, p1.y); // center of circle
		for(int i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            p1.x + (radius1 * cos(i *  twicePi / triangleAmount)), 
			    p1.y + (radius1 * sin(i * twicePi / triangleAmount))
			);
		}
    glEnd();

	int radius2=30;
	glColor3f(0.957, 0.643, 0.376);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(p2.x,p2.y); // center of circle
		for(int i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            p2.x+ (radius2 * cos(i *  twicePi / triangleAmount)), 
			    p2.y + (radius2 * sin(i * twicePi / triangleAmount))
			);
		}
    
		glEnd();
	if(p1.x>=0 && p1.y>=0){
	glColor3f(0.0f, 1.0f, 0.0f);
	print(p1.x+50,p1.y+50,stringx(p1.x));
	print(p1.x+20,p1.y+20,stringy(p1.y));}

	if(p2.x>=0 && p2.y>=0){
	glColor3f(1.000, 0.271, 0.000);
	print(p2.x+60,p2.y+60,stringx(p2.x));
	print(p2.x+20,p2.y+20,stringy(p2.y));}
	

	if(p1.y<0 && p2.y<0){
	char s1[20];sprintf(s1,"%f", ans1);char *time2="Time Body 1(s)= ";char * str3 = (char *) malloc(1 + strlen(time2)+ strlen(s1) );
      strcpy(str3, time2);
      strcat(str3, s1);
	  glColor3f(0.0f, 1.0f, 0.0f);
	  print(120,340,str3);
	
	char s[20];sprintf(s,"%f", ans2);char *time="Time Body 2(s)= ";char * str4 = (char *) malloc(1 + strlen(time)+ strlen(s) );
      strcpy(str4, time);
      strcat(str4, s);
	  glColor3f(1.000, 0.271, 0.000);
	  print(120, 300,str4);
	  for (int i=0;i<q;i++)
      printf("X %lf Y %lf  T %lf\n",b1[i].x,b1[i].y,b1[i].t);
	  for (int i=0;i<q;i++)
      printf("X %lf Y %lf  T %lf\n",b2[i].x,b2[i].y,b2[i].t);
	
	


	
	
	
}
	glFlush();
}
void display2() {
	if(p1.y<=0 && p2.y<=0){

    glBegin(GL_POINTS);
    glColor3f(0.0f,1.0f,0.0f);
	
    for (int i=0;i<q;i++){
	 if(b1[i].y>=0)
	  glVertex2d(b1[i].t,abs(b1[i].y));
	
	  }
     glEnd();

     glBegin(GL_POINTS);
     glColor3f(0.0f,0.0f,1.0f);
	 glPointSize(10.0f);
     for (int i=0;i<q;i++){
       if(b2[i].y>=0)
	  glVertex2d(b2[i].t,abs(b2[i].y));
	  }
      glEnd();
	  glFlush();
	
	}
}

void display3() {
	if(p1.y<=0 && p2.y<=0){

    glBegin(GL_POINTS);
    glColor3f(0.0f,1.0f,0.0f);
	
    for (int i=0;i<q;i++){
	 glVertex2d(b1[i].t,abs(b1[i].x));
	 }
     glEnd();

     glBegin(GL_POINTS);
     glColor3f(0.0f,0.0f,1.0f);
	 glPointSize(10.0f);
     for (int i=0;i<q;i++){
	 glVertex2d(b2[i].t,abs(b2[i].x));
	  }
      glEnd();

	  glFlush();
	
	}
}
void Timer(int value) {
	glutTimerFunc(6000 / 60, Timer, value);
	if(p1.y >0 || p2.y>0)
	glutPostRedisplay();
	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	printf("Axis dimensions (1024 X 480)\n");
	
	printf("Enter x coordinate of first body on the screen\n");
	scanf("%lf",&x1);
	printf("Enter y coordinate of first body on the screen\n");
	scanf("%lf",&y11);
	
	printf("Enter projection angle of first body\n");
	scanf("%lf",&theta1);
	printf("Enter velocity of first body\n");
	scanf("%lf",&v1);
	

	printf("Enter x coordinate of second body on the screen\n");
	scanf("%lf",&x2);
	printf("Enter y coordinate of second body on the screen\n");
	scanf("%lf",&y2);
	
	printf("Enter projection angle of second body\n");
	scanf("%lf",&theta2);
	printf("Enter velocity of second body\n");
	scanf("%lf",&v2);
	
	double val = PI / 180.0;
	v1x=v1*cos(static_cast<double>(theta1*val));
	v1y=v1*sin(static_cast<double>(theta1*val));
	
	v2x=v2*cos(static_cast<double>(theta2*val));
	v2y=v2*sin(static_cast<double>(theta2*val));
	
	p1.x=x1;
	p1.y=y11;

	p2.x=x2;
	p2.y=y2;

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 480);
    glutCreateWindow("Demonstration Of Motion Of Two Bodies Under Gravity");
	init();
	Timer(0);
	glutDisplayFunc(display);
	
	glutInitWindowSize(640.0, 480.0);           // set a window size
    glutInitWindowPosition(800,0);             // set a window position
    WindowID2 = glutCreateWindow("Graph of Vertical Displacement Vs Time for Two Bodies"); 
	init2(); // Create window 2
	glutDisplayFunc(display2);
	glutInitWindowSize(640.0, 480.0);           // set a window size
    glutInitWindowPosition(800,0);             // set a window position
    
	WindowID3 = glutCreateWindow("Graph of Horizontal Displacement Vs Time for Two Bodies"); 
	init2(); // Create window 2
	glutDisplayFunc(display3);
	glutMainLoop();
	return 0;
}