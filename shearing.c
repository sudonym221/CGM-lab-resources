#include <GL/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Define shearing factors (change these values to see different effects)
  float shx = 0.5; // Shearing factor for x-axis
  float shy = 0.2; // Shearing factor for y-axis

  // Create a shearing matrix
  GLfloat shearMatrix[16] = {
    1.0f, shx, 0.0f, 0.0f,
    0.0f, 1.0f, shy, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  // Apply shearing transformation
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); // Push the current matrix onto the stack
  glMultMatrixf(shearMatrix);

  // Define a simple object (e.g., a square)
  glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
  glEnd();

  glPopMatrix(); // Pop the matrix from the stack (optional, but good practice)
  glutSwapBuffers();
}

void init() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set up orthographic projection
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("OpenGL Shearing");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}


/*

This program defines separate shearing factors (shx and shy) for the x and y axes. 
It then creates a shearing matrix and applies it before drawing a simple square. 
You can modify the shx and shy values to see how they affect the shape of the object.

Explanation:

    1. We include the GL/glut.h header for OpenGL and GLUT library functions.
    2. The display function is called whenever the window needs to be re-drawn.
        It clears the color buffer and defines the shearing factors.
        It creates a shearing matrix using a 4x4 matrix representation. The specific values in the matrix control the shearing along x and y axes.
        glMatrixMode(GL_MODELVIEW) sets the current matrix mode for applying transformations.
        glPushMatrix() saves the current modelview matrix onto a stack (useful for combining multiple transformations).
        glMultMatrixf(shearMatrix) multiplies the current modelview matrix by the shearing matrix, effectively applying the shearing transformation.
        We define a square object using glBegin and glEnd for drawing quadrilaterals.
        glPopMatrix() restores the previous modelview matrix from the stack (optional in this case).
        glutSwapBuffers() swaps the front and back buffers for smooth animation.
    3.The init function sets up the projection matrix (orthographic in this case) and background color.
    4.The main function initializes GLUT, creates a window, sets display callback function, and enters the main loop.

*/