#include<GL/glut.h>
#include<math.h> // for floating-point operations

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Define reflection plane (change these values for different planes)
  float planeNormal[3] = {0.0f, 1.0f, 0.0f}; // Reflect along y-axis plane
  float planeConstant = 0.0f; // Equation of the plane: Ax + By + Cz + D = 0

  // Calculate reflection vector
  GLfloat reflectionMatrix[16];
  float dotProduct = 0.0f;
  for (int i = 0; i < 3; ++i) {
    dotProduct += planeNormal[i] * planeNormal[i];
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      reflectionMatrix[i * 4 + j] = 0.0f;
      if (i == j) {
        reflectionMatrix[i * 4 + j] = 1.0f - 2.0f * planeNormal[i] * planeNormal[j] / dotProduct;
      } else {
        reflectionMatrix[i * 4 + j] = -2.0f * planeNormal[i] * planeNormal[j] / dotProduct;
      }
    }
  }
  reflectionMatrix[3] = (2.0f * planeConstant * dotProduct) / dotProduct;

  // Push current modelview matrix and apply reflection
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(reflectionMatrix);

  // Draw the object to be reflected (e.g., a triangle)
  glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-0.5f, 0.5f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);
  glEnd();

  // Pop the matrix to restore original transformation
  glPopMatrix();

  // Draw the original object without reflection (optional)
  glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(-0.5f, 0.5f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);
  glEnd();

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
  glutCreateWindow("OpenGL Reflection");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}