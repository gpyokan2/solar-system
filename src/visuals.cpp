#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <time.h>

#include "GL/glut.h"
#include "visuals.h"

Model md;
static bool animate = true;
static bool grow = true;
static float shineSize = 50.0;
static float rotx1 = 0.0, rotx2 = 0.0, rotx3 = 0.0, rotx4 = 0.0;
static float angle1 = 0.0, angle2 = 0.0, angle3 = 0.0, angle4 = 0.0;
static float anglex = 0.0, angley = 0.0;

Stars starSystem;
Planets planetSystem;

using namespace std;

void createLightSource(float planetSize, float shineInitSize, Point position, Point colour, Light_t l) {
	glPushMatrix();
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(position.x, position.y, position.z);
		glColor4f(colour.x, colour.y, colour.z, 0.8);
		glutSolidSphere(planetSize, 40, 40);
		if (l == SUN) {
	  		glColor4f(colour.x, colour.y+0.2, colour.z, 0.4);
	  		glutSolidSphere(shineInitSize, 40, 40);

	  		glColor4f(colour.x, colour.y+0.2, colour.z, 0.3);
	  		glutSolidSphere(shineInitSize+2, 40, 40);

			glColor4f(colour.x, colour.y+0.2, colour.z, 0.25);
	  		glutSolidSphere(shineInitSize+4, 40, 40);
		
			glColor4f(colour.x, colour.y+0.2, colour.z, 0.3);
	  		glutSolidSphere(shineInitSize+6, 40, 40);
		} else if (l == STAR) {
			glColor4f(colour.x, colour.y+0.2, colour.z, 0.2);
	  		glutSolidSphere(shineInitSize, 40, 40);
		}
	glDisable(GL_BLEND);
	glPopMatrix();
}

void createStars(void) {
	srand((unsigned) time(NULL));
	starSystem.colour.x = 1; starSystem.colour.y = 1; starSystem.colour.z = 1;
	for (int i = 0 ; i < STARS ; i++) {
		starSystem.starsgrow[i] = true;
		starSystem.starsSize[i] = rand()%2+0.2;
		starSystem.starsShineSize[i] = starSystem.starsSize[i];
		starSystem.starsPosition[i].x = rand()%800-400;
		starSystem.starsPosition[i].y = rand()%800-400;	/* [-400, 400] */
		starSystem.starsPosition[i].z = rand()%600-800; /* [-800, -200] */
	}
}

void drawStars(void) {
	for (int i = 0 ; i < STARS ; i++) {
		createLightSource(starSystem.starsSize[i], starSystem.starsShineSize[i], starSystem.starsPosition[i], starSystem.colour, STAR);	
	}
}

void Render(void) {    
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window and the depth buffer
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	glTranslatef(0, 0, -515);
	glRotatef(anglex, 1, 0, 0);
	glRotatef(angley, 0, 1, 0);
	glTranslatef(0, 0, 515);

	Point pos, col;
	pos.x = 0.0; pos.y = 0.0; pos.z = -515;
	col.x = 1.0; col.y = 0.8; col.z = 0.0;
	createLightSource(50, shineSize, pos, col, SUN);
	drawStars();

	/* Red planet */
	glPushMatrix();
		Point p1;
		p1.x = 100; p1.y = 0; p1.z = -500;
		glTranslatef(0, 0, -500); 
		glRotatef(angle1, 0, 1, 0);
		glTranslatef(0, 0, 400);

		glTranslatef(p1.x, p1.y, p1.z);
		glScalef(0.04, 0.04, 0.04);
		
		glRotatef(rotx1, 0, 1, 0);
		glColor3f(0.9, 0.1, 0.1);
		DisplayModel(md);
	glPopMatrix();

	/* Green planet */
	glPushMatrix();
		Point p2;
		p2.x = 0; p2.y = -20; p2.z = -500;
		glTranslatef(0, 0, -500); 
		glRotatef(angle2, 1, 0, 0);
		glTranslatef(0, 0, 600);

		glTranslatef(p2.x, p2.y, p2.z);
		glScalef(0.02, 0.02, 0.02);
		
		glRotatef(rotx2, 0, 1, 0);
		glColor3f(0.2, 0.8, 0.2);
		DisplayModel(md);
	glPopMatrix();

	/* Light Blue planet */
	glPushMatrix();
		Point p3;
		p3.x = -120; p3.y = 0; p3.z = -500;
		glTranslatef(0, 0, -500); 
		glRotatef(angle3, 0, 1, 0);
		glTranslatef(0, 0, 400);

		glTranslatef(p3.x, p3.y, p3.z);
		glScalef(0.06, 0.06, 0.06);
		
		glRotatef(rotx3, 0, 1, 0);
		glColor3f(0.3, 0.6, 0.7);
		DisplayModel(md);
	glPopMatrix();

	/* Blue planet */
	glPushMatrix();
		Point p4;
		p4.x = 0; p4.y = 50; p4.z = -500;
		glTranslatef(0, 0, -500); 
		glRotatef(angle4, 1, 0, 0);
		glTranslatef(0, 0, 600);

		glTranslatef(p4.x, p4.y, p4.z);
		glScalef(0.01, 0.01, 0.01);
		
		glRotatef(rotx4, 0, 1, 0);
		glColor3f(0.2, 0.2, 0.6);
		DisplayModel(md);
	glPopMatrix();

	glutSwapBuffers();	// All drawing commands applied to the hidden buffer, so now, bring forward the hidden buffer and hide the visible one
}

void Resize(int w, int h) { 
	// define the visible area of the window ( in pixels )
	if (h == 0) {
		h = 1;
	}
	// Setup viewing volume
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	glViewport( 0, 0, w, h);
	gluPerspective(45, (float)w/(float)h, 1, CAM_FAR);

    glMatrixMode(GL_MODELVIEW);
}

void shine(float &shine, bool &g, float upbound, float lowbound, float dt) {
	if (g) {
		shine += dt;
	} else {
		shine -= dt;
	}
	if (shine > upbound){
		g = false;
	} else if (shine < lowbound){
		g = true;
	}
}

void planetMovement(void) {
	rotx1 += 2;
	angle1 += 0.3;

	rotx2 += 5;
	angle2 += 0.7;
	
	rotx3 += 3;
	angle3 += 0.3;
	
	rotx4 += 4;
	angle4 += 0.7;
}

void Idle(void) {
	if (animate) {
		shine(shineSize, grow, 54, 51, 0.03);
		for (int i = 0 ; i < STARS ; i++) {
			shine(starSystem.starsShineSize[i], starSystem.starsgrow[i], starSystem.starsSize[i]+1.5, starSystem.starsSize[i], 0.2);
		}
		planetMovement();
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'A':
		case 'a':
			angley += 0.5f;
			break;
		case 'D':
		case 'd':
			angley -= 0.5f;
			break;
		case 'W':
		case 'w':
			anglex += 0.5f;
			break;
		case 'S':
		case 's':
			anglex -= 0.5f;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		animate = !animate;
		glutPostRedisplay();
	}
}

void Setup(char *path) { 
	ReadFile(path);
	createStars();

	//Parameter handling
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 0.0, 50.0, 0.0 };
	  // GLfloat light_position[] = { 1000,1000,-3000, 10.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	   
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	if (NORMAL_PLANETS) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_BLEND); 

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	}

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	//glEnable(GL_NORMALIZE);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ReadFile(char *path) {
	md.vertices = POINTS; 
	md.faces = FACES;    
	char first[80];
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}
	int i = 0, j = 0, m = 0;
	while (!feof(file)) {
		if (fscanf(file, "%s  ", first) != 1) {
			fprintf(stderr, "error reading line header\n");
			exit(EXIT_FAILURE);
		}
		if (!strcmp(first, "v")) {
			if (fscanf(file,"%f %f %f ", &md.obj_points[i].x, &md.obj_points[i].y, &md.obj_points[i].z) != 3) {
				fprintf(stderr, "error reading objpoints\n");
				exit(EXIT_FAILURE);
			}
			i++;
		} else if (!strcmp(first, "vn")) {
			if (fscanf(file,"%f %f %f ", &md.obj_normals[m].x, &md.obj_normals[m].y, &md.obj_normals[m].z) != 3) {
				fprintf(stderr, "error reading objnormals\n");
				exit(EXIT_FAILURE);
			}
			m++;
		} else if (!strcmp( first, "f")) {
			if (fscanf(file,"%d//%d %d//%d %d//%d ", &md.obj_faces[j].vtx[0], &md.obj_norm[j].vtx[0], &md.obj_faces[j].vtx[1], &md.obj_norm[j].vtx[1], &md.obj_faces[j].vtx[2], &md.obj_norm[j].vtx[2]) != 6) {
				fprintf(stderr, "error reading faces\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
	}
	fclose(file);
}

void DisplayModel(Model md) {
	glPushMatrix();
		glBegin(GL_TRIANGLES);
			for (int i = 0; i < md.faces; i++) {
				if (NORMAL_PLANETS) {
					glNormal3f(md.obj_normals[md.obj_norm[i].vtx[0]-1].x, md.obj_normals[md.obj_norm[i].vtx[0]-1].y, md.obj_normals[md.obj_norm[i].vtx[0]-1].z);
					glNormal3f(md.obj_normals[md.obj_norm[i].vtx[1]-1].x, md.obj_normals[md.obj_norm[i].vtx[1]-1].y, md.obj_normals[md.obj_norm[i].vtx[1]-1].z);
					glNormal3f(md.obj_normals[md.obj_norm[i].vtx[2]-1].x, md.obj_normals[md.obj_norm[i].vtx[2]-1].y, md.obj_normals[md.obj_norm[i].vtx[2]-1].z);
				}
				glVertex3f(md.obj_points[md.obj_faces[i].vtx[0]-1].x, md.obj_points[md.obj_faces[i].vtx[0]-1].y, md.obj_points[md.obj_faces[i].vtx[0]-1].z);
				glVertex3f(md.obj_points[md.obj_faces[i].vtx[1]-1].x, md.obj_points[md.obj_faces[i].vtx[1]-1].y, md.obj_points[md.obj_faces[i].vtx[1]-1].z);
				glVertex3f(md.obj_points[md.obj_faces[i].vtx[2]-1].x, md.obj_points[md.obj_faces[i].vtx[2]-1].y, md.obj_points[md.obj_faces[i].vtx[2]-1].z);
			}
		glEnd();
	glPopMatrix();
}
