#include "MyScene.h"
//#include <cmath>

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}


void MyScene::Initialise()
{
    // Set background colour
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_CULL_FACE);         // Enable culling of useless polygons
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    
    //Setting the Stage
    Stage* stage = new Stage();
    GLuint* skybox = new GLuint[6];
    skybox[0] = Scene::GetTexture("./Textures/Skybox/Mountains/left.bmp");
    skybox[1] = Scene::GetTexture("./Textures/Skybox/Mountains/right.bmp");
    skybox[2] = Scene::GetTexture("./Textures/Skybox/Mountains/front.bmp");
    skybox[3] = Scene::GetTexture("./Textures/Skybox/Mountains/back.bmp");
    skybox[4] = Scene::GetTexture("./Textures/Skybox/Mountains/down.bmp");
    skybox[5] = Scene::GetTexture("./Textures/Skybox/Mountains/up.bmp");
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
