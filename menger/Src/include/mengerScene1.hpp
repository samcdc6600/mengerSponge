#ifndef MENGER_SCENE1_HPP__
#define MENGER_SCENE1_HPP__
#include <iostream>
//#include <chrono> // temporary?
#include "mengerScene.hpp"


class mengerScene1 : public mengerScene
{
public:

    virtual void init()
    {
    }


    virtual void render(SDL_Window* sDLWin)
    {
        using namespace geometry;
        glPushMatrix();

        {// Enable lights
            GLfloat global_ambient[] = { 0.1f, 0.05f, 0.3f, 1.0f };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // Set global ambient light model.

            glShadeModel(GL_SMOOTH); // Set shading model.

            // Specify light0.
            GLfloat ambient[] = { 0.025f, 0.15f, 0.015f };
            GLfloat diffuse[] = { 0.25f, 0.45f, 0.1f };
            GLfloat specular[] = { 0.4f, 0.5f, 0.35f , 1.0f };
            GLfloat position[] = { -1.6f, 1.5f, 2.0f, 1.0f };
            glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
            glLightfv(GL_LIGHT0, GL_POSITION, position);
            // Enable light0.
            glEnable(GL_LIGHT0);
        }

        glScalef(0.5, 0.5, 0.5);

        // Define material properties which will be used when calling glColor.
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

        drawSphere(-1.6f, 1.5f, 2.0f, 1.0, 0.1, 8, 8, false, 1.0);

        /*for (size_t iter{};
             iter < mengerSpongePosDataSize;
             iter += cube::faceStride)
        {*/
        for(size_t faceIter: mengerSpongeFaceIndicies)
        {
            glBegin(GL_TRIANGLE_STRIP);

            // Specular reflection for material.
            float specReflection[] = { 0.1f, 0.1f, 0.1f, 0.1f };
            glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
            // Set material for face. LOL.
            glColor3f(mengerSpongeColorData[
                ((faceIter % (cube::faceStride * cube::faces)) / 
                 cube::faceStride) * cube::vertexStride + cube::rPos],
                      mengerSpongeColorData[
                ((faceIter % (cube::faceStride * cube::faces)) /
                 cube::faceStride) * cube::vertexStride + cube::gPos],
                      mengerSpongeColorData[
                ((faceIter % (cube::faceStride * cube::faces)) /
                 cube::faceStride) * cube::vertexStride + cube::bPos]);


            switch((faceIter % (cube::faceStride * cube::faces)) / cube::faceStride)
            { /* We must create different normals based on the face we are
              currently darwing. */
            case 0: // Back.
                glNormal3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glNormal3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glNormal3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glNormal3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                break;
            case 1: // Front.
                glNormal3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glNormal3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glNormal3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glNormal3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                break;
            case 2: // Left.
                glNormal3f(mengerSpongePosData[faceIter + 0] - 1, mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glNormal3f(mengerSpongePosData[faceIter + 3] - 1, mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glNormal3f(mengerSpongePosData[faceIter + 6] - 1, mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glNormal3f(mengerSpongePosData[faceIter + 9] - 1, mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                break;
            case 3: // Right.
                glNormal3f(mengerSpongePosData[faceIter + 0] + 1, mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glNormal3f(mengerSpongePosData[faceIter + 3] + 1, mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glNormal3f(mengerSpongePosData[faceIter + 6] + 1, mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glNormal3f(mengerSpongePosData[faceIter + 9] + 1, mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                break;
            case 4: // Top.
                glNormal3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1] + 1,
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glNormal3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4] + 1,
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glNormal3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7] + 1,
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glNormal3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10] + 1,
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                break;
            case 5: // Bottom.
                glNormal3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1] - 1,
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glNormal3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4] - 1,
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glNormal3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7] - 1,
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glNormal3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10] - 1,
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                break;
            }

            glEnd();




           
/*           switch ((faceIter % (cube::faceStride * cube::faces)) / cube::faceStride)
            { /* We must create different normals based on the face we are
              currently darwing. */ 
            /*case 0: // Back.
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11] - 1);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glEnd();
                break;
            case 1: // Front.
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11] + 1);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glEnd();
                break;
            case 2: // Left.
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 0] - 1, mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 3] - 1, mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 6] - 1, mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 9] - 1, mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glEnd();
                break;
            case 3: // Right.
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 0] + 1, mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 3] + 1, mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 6] + 1, mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 9] + 1, mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glEnd();
                break;
            case 4: // Top.
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1] + 1,
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4] + 1,
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7] + 1,
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10] + 1,
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glEnd();
                break;
            case 5: // Bottom.
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1] - 1,
                           mengerSpongePosData[faceIter + 2]);
                glVertex3f(mengerSpongePosData[faceIter + 0], mengerSpongePosData[faceIter + 1],
                           mengerSpongePosData[faceIter + 2]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4] - 1,
                           mengerSpongePosData[faceIter + 5]);
                glVertex3f(mengerSpongePosData[faceIter + 3], mengerSpongePosData[faceIter + 4],
                           mengerSpongePosData[faceIter + 5]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7] - 1,
                           mengerSpongePosData[faceIter + 8]);
                glVertex3f(mengerSpongePosData[faceIter + 6], mengerSpongePosData[faceIter + 7],
                           mengerSpongePosData[faceIter + 8]);
                glEnd();
                glBegin(GL_LINES);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10] - 1,
                           mengerSpongePosData[faceIter + 11]);
                glVertex3f(mengerSpongePosData[faceIter + 9], mengerSpongePosData[faceIter + 10],
                           mengerSpongePosData[faceIter + 11]);
                glEnd();
                break;
            }*/
        }

        glPopMatrix();
        SDL_GL_SwapWindow(sDLWin);
	}
};


#endif