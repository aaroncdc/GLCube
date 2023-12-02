#include <GL/enigl.h>
#include <GL/glu.h>
#include <math.h>
#include "bitmap.h"

#define GLE_ENABLE_DEPTH 1

/* Global variables */
const char * signature = "By Aaron CdC :3 ((2023)) https://github.com/aaroncdc";
float rot_an = .0f;
static GLfloat aspect = 1.33333333f;
UCHAR * txData = 0L;
GLuint txName = 0;
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { -1.0, -1.0, 1.5, 0.0 };

void getRotationMatrixFromQuaternion(GLfloat *rotm, GLfloat theta, GLfloat x, GLfloat y, GLfloat z) {
   float an = (float)sin((double)theta/2.0f);
   float norm = 1;
   GLfloat q[] = {0,x,y,z};

   norm = sqrtf(powf(q[1],2)+powf(q[2],2)+powf(q[3],2));
   if(norm != 1){
      x *= (float)(1/norm);
      y *= (float)(1/norm);
      z *= (float)(1/norm);
      norm = 1;
   }
   
   q[0] = cos((float)theta/2.0f);
   q[1] = x*an;
   q[2] = y*an;
   q[3] = z*an;

   /* Lots of linear algebra goes into this. Source: 
   * https://danceswithcode.net/engineeringnotes/quaternions/quaternions.html */
   rotm[0] = powf(q[0],2)+powf(q[1],2)-powf(q[2],2)-powf(q[3],2);
   rotm[1] = 2*q[1]*q[2]-2*q[0]*q[3];
   rotm[2] = 2*q[1]*q[3]+2*q[0]*q[2];
   rotm[4] = 2*q[1]*q[2]+2*q[0]*q[3];
   rotm[5] = powf(q[0],2)-powf(q[1],2)+powf(q[2],2)-powf(q[3],2);
   rotm[6] = 2*q[2]*q[3]-2*q[0]*q[1];
   rotm[8] = 2*q[1]*q[3]-2*q[0]*q[2];
   rotm[9] = 2*q[2]*q[3]+2*q[0]*q[1];
   rotm[10] = powf(q[0],2)-powf(q[1],2)-powf(q[2],2)+powf(q[3],2);
   return;
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   if(GLE_ENABLE_DEPTH){
      glClearDepth(1.0f);                   // Set background depth to farthest
      glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
      glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
      glShadeModel(GL_SMOOTH);   // Enable smooth shading
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

      UCHAR * txData = loadbmp();
      glGenTextures(1, &txName);
      glBindTexture(GL_TEXTURE_2D, txName);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, 128, 128, 0,
         GL_RGB, GL_UNSIGNED_BYTE, txData);
   }

   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   return;
}

void drawit()
{
   GLfloat rotm[] = {
      0,0,0,0,
      0,0,0,0,
      0,0,0,0,
      0,0,0,1
   };
   
   getRotationMatrixFromQuaternion(rotm, rot_an*0.75f, 1, 0, 0);

   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -3.5f);
   glMultMatrixf(rotm);

   getRotationMatrixFromQuaternion(rotm, -rot_an, 0, 1, 0);
   glMultMatrixf(rotm);

   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, txName);

   glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads

      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glNormal3d(0, 1, 0);
      glTexCoord2f(0,0);
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glTexCoord2f(0,1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glTexCoord2f(1.0f,0);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glNormal3d(0, -1, 0);
      glTexCoord2f(0,0);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glTexCoord2f(0,1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glTexCoord2f(1.0f,0);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glNormal3d(0, 0, 1);
      glTexCoord2f(0,0);
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glTexCoord2f(0,1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glTexCoord2f(1.0f,0);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glNormal3d(0, 0, -1);
      glTexCoord2f(0,0);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glTexCoord2f(0,1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glTexCoord2f(1.0f,0);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glNormal3d(-1, 0, 0);
      glTexCoord2f(0,0);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glTexCoord2f(0,1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glTexCoord2f(1.0f,0);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glNormal3d(1, 0, 0);
      glTexCoord2f(0,0);
      glVertex3f(1.0f,  1.0f, -1.0f);
      glTexCoord2f(0,1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glTexCoord2f(1.0f,0);
      glVertex3f(1.0f, -1.0f, -1.0f);

   glEnd();

   glDisable(GL_TEXTURE_2D);

   glLoadIdentity();
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glFlush();

   rot_an += 0.02f;
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   if(GLE_ENABLE_DEPTH){
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
      glMatrixMode(GL_MODELVIEW);
      gluPerspective(75.0f, aspect, 0.001f, 10000.0f);
   }else{
      glClear(GL_COLOR_BUFFER_BIT);
   }
 
   if(GLE_ENABLE_DEPTH){
      /* 3D Graphics */
      drawit();
   }else{
      /* 2D Graphics */
   }
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(unsigned int width, unsigned int height) {  // GLsizei for non-negative integer
   if(width > 1920 || height > 1920)
   {
      return;
   }
   
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   if(GLE_ENABLE_DEPTH){
      // Set the aspect ratio of the clipping volume to match the viewport
      glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
      glLoadIdentity();             // Reset
      // Enable perspective projection with fovy, aspect, zNear and zFar
      gluPerspective(75.0f, aspect, 0.001f, 10000.0f);
   }
   return;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance,
                    LPSTR lpCmdLine, int nShowCmd)
{
   GLWINDOW *win;
   CreateGLWindow(NULL);
   SetInitFunction((INITFUNC)initGL);
   SetRenderFunction((RENDERFUNC)display);
   SetIdleFunction((IDLEFUNC)display);
   SetReshapeFunction((RESHAPEFUNC)reshape);
   SetWindowTitleText("Direct3D test but it's OpenGL");
   ShowGLWindow(NULL);

   if(txData != NULL)
   {
      free(txData);
   }
   return 0;
}