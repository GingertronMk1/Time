#include "MyScene.hpp"

void setup()
{
    width = 640;
    height = 480;
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow("My Scene");
}

void draw()
{
    glClearColor(0, 1.f, 1.f, 1.f);                   // set background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
    glMatrixMode(GL_MODELVIEW);                         // set for model and viewing operations
    glLoadIdentity();                                   // reset drawing

    glTranslatef(0.f, 0.f, -100.f);                     // move drawing further back in the scene
    
    float v = 20.f;                                      // v for vertex
    // TETRAHEDRON
    glColor3f(1.f,0,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(v,v,v);
    glVertex3f(v, -v, -v);
    glVertex3f(-v, v, -v);
    glEnd();
    glColor3f(0,1.f,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(v, -v, -v);
    glVertex3f(-v, v, -v);
    glVertex3f(-v, -v, v);
    glEnd();
    glColor3f(0,0,1.f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-v, v, -v);
    glVertex3f(-v, -v, v);
    glVertex3f(v, v, v);
    glEnd();
    glColor3f(1.f,1.f,1.f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-v,-v,v);
    glVertex3f(v,v,v);
    glVertex3f(v,-v,-v);
    glEnd();
    
    
    
    glColor3f(0,0,0);
    // CUBE:
    // Front Square
    glBegin(GL_LINE_LOOP);
    glVertex3f(-v, -v, -v);
    glVertex3f(v,-v,-v);
    glVertex3f(-v,v,-v);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(v, v, -v);
    glVertex3f(-v,v,-v);
    glVertex3f(v,-v,-v);
    glEnd();
    // Back Square
    glBegin(GL_LINE_LOOP);
    glVertex3f(-v, -v, v);
    glVertex3f(-v, v, v);
    glVertex3f(v, v, v);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-v, -v, v);
    glVertex3f(v, -v, v);
    glVertex3f(v, v, v);
    glEnd();
    // Left Square
    glBegin(GL_LINE_LOOP);
    glVertex3f(-v,v,v);
    glVertex3f(-v,v,-v);
    glVertex3f(-v,-v,v);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-v,-v,v);
    glVertex3f(-v,-v,-v);
    glVertex3f(-v,-v,v);
    glEnd();
    // Right Square
    glBegin(GL_LINE_LOOP);
    glVertex3f(v,v,v);
    glVertex3f(v,-v,-v);
    glVertex3f(v,-v,v);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(v,v,v);
    glVertex3f(v,-v,-v);
    glVertex3f(v,v,-v);
    glEnd();
    // Top Square
    glBegin(GL_LINE_LOOP);
    glVertex3f(v,v,v);
    glVertex3f(v,v,-v);
    glVertex3f(-v,v,-v);
    glEnd();
    // Bottom Square
    glBegin(GL_LINE_LOOP);
    glVertex3f(-v,-v,-v);
    glVertex3f(-v,-v,v);
    glVertex3f(v,-v,-v);
    glEnd();
    
    checkGLError();
    glutSwapBuffers();                                  // execute all commands, swap buffers
}

void reshape(int _width, int _height) {
    width = _width;
    height = _height;
    GLdouble aspect = static_cast<GLdouble>(width) / static_cast<GLdouble>(height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);          // Initialise GL environment
    setup();                        // Call additional initialisation commands
    glutDisplayFunc(draw);          // Register scene to render contents of draw() function
    checkGLError();                 // Check any OpenGL errors in initialisation
    glutReshapeFunc(reshape);
    glutMainLoop();                 // Begin rendering sequence
    return 0;
}

void checkGLError()
{
    int e = 0;                      // Error count
    GLenum error = glGetError();    // Get first glError
    while (GL_NO_ERROR != error)    // Loop until no errors found
    {
        e++;
        printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
        error = glGetError();                                  // Get next glError
    }
}
