#include "Draw.h"

void reshape(int, int)
{
	glViewport(0, 0, const_width, const_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, const_width, 0, const_height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void draw_axis() {
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(const_origin_x, const_height / 2);
	glVertex2i(const_width, const_height / 2);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(const_width / 2, const_origin_y);
	glVertex2i(const_width / 2, const_height);

	glEnd();
}

void draw_frame() {
	glColor3f(0.5, 0.5, 0.5);
	// TODO!!!
	/*glVertex2i(const_frame_left * scale + const_ + shift, cFrameYu * scale + h + shift);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYu * scale + h + shift);

	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * scale + w + shift, cFrameYd * scale + h + shift);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYd * scale + h + shift);

	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXl * scale + w + shift, cFrameYu * scale + h + shift);
	glVertex2i(cFrameXl * scale + w + shift, cFrameYd * scale + h + shift);

	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYu * scale + h + shift);
	glVertex2i(cFrameXr * scale + w + shift, cFrameYd * scale + h + shift);
	*/
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	draw_axis();
	draw_frame();
	glBegin(GL_QUADS);
	
	for (auto point = points.begin(); point != points.end(); ++point) {
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i((*point).x * scale + const_width / 2 + 0.01, (*point).y * scale + const_height / 2 + 0.01);
		glVertex2i((*point).x * scale + const_width / 2 + 0.01, (*point).y * scale + const_height / 2 - 0.01);
		glVertex2i((*point).x * scale + const_width / 2 - 0.01, (*point).y * scale + const_height / 2 + 0.01);
		glVertex2i((*point).x * scale + const_width / 2 - 0.01, (*point).y * scale + const_height / 2 - 0.01);
	}
	glEnd();
	
	glBegin(GL_LINES);
	
	for (auto point = voronoi_diagram_edges.begin(); point != voronoi_diagram_edges.end(); ++point) {
		glColor3f(0.5, 0.5, 0.5);
		glVertex2i((*point).first.x * scale + const_width / 2, (*point).first.y * scale + const_height / 2);
		glVertex2i((*point).second.x * scale + const_width / 2, (*point).second.y * scale + const_height / 2);
	}

	glEnd();
	glutSwapBuffers();
}


void draw(int argc, char**argv, vector<pair<Point, Point>> vde, vector<Point>  p) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(const_width, const_height);
	glutCreateWindow("");

	voronoi_diagram_edges = vde;
	points = p;

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();
}
