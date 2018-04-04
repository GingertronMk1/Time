#include "MyScene.h"
//#include <cmath>

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}


void MyScene::Initialise()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1);
    /*
    // Set lighting effect colours and positional parameter
    float ambient[]  = { .2f, .2f, .2f, 1.f };      // ambient light (20% white)
    float diffuse[]  = { .5f, .5f, .5f, 1.f };      // diffuse light (50% white)
    float specular[] = { 1.f, 1.f, 1.f, 1.f };      // specular light (100% white)
    float position[] = { 1.f, .5f, 1.f, 0.f };      // directional light (w = 0)
    // Attach properties to single light source (GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
    glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
    // Enable this lighting effects
    glEnable(GL_LIGHTING);  // enable scene lighting (required to enable a light source)
    glEnable(GL_LIGHT0);    // enable light source with attached parameters (GL_LIGHT0) 
*/
    
    //Setting the Stage
    Stage* stage = new Stage();
    GLuint* skybox = new GLuint[6];
    skybox[0] = Scene::GetTexture("./Textures/Skybox/left.bmp");
    skybox[1] = Scene::GetTexture("./Textures/Skybox/right.bmp");
    skybox[2] = Scene::GetTexture("./Textures/Skybox/front.bmp");
    skybox[3] = Scene::GetTexture("./Textures/Skybox/back.bmp");
    skybox[4] = Scene::GetTexture("./Textures/Skybox/down.bmp");
    skybox[5] = Scene::GetTexture("./Textures/Skybox/up.bmp");
    stage->setTextures(skybox);
    stage->position(0.0f, 0.0f, 0.0f);
    //objects["stage"] = stage;
    
    
    //Creating the turf
    Turf *t = new Turf("./Textures/Turf.bmp");
    t->position(0,0,0);
    
    //Creating posts at one end
    Posts *p1 = new Posts();
    p1->position(0,0,500);
    
    //Creating other posts
    Posts *p2 = new Posts();
    p2->position(0,0,-500);
    
    //Creating ball
    Ball *b = new Ball();
    b->position(0,20,20);
    b->Bangle(-30.0f, 0.0f, 0.0f);
    
    //Putting a tee under the ball
    Tee *tee = new Tee("./Textures/Tee.bmp");
    tee->position(0,0,20);
    
    Sun *s = new Sun();
    s->position(0,500,0);

    //Adding everything to the scene, drawing
    AddObjectToScene(t);
    AddObjectToScene(p1);
    AddObjectToScene(p2);
    AddObjectToScene(b);
    AddObjectToScene(tee);
    AddObjectToScene(s);
    AddObjectToScene(stage);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 10000.0);        // Bumped FoV to 100, far draw distance to 10000
}
