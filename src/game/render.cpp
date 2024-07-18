#include "game/render.h"
#include "game/sbWindow.h"
#include "area/area.h"


//data
float sb::Render::areaVertices[8]{};

//managing this class
void sb::Render::init() {
	int areaWidth = sb::Area::getWidth();
	int areaHeight = sb::Area::getHeight();

	areaVertices[0] = 0;			areaVertices[1] = 0;
	areaVertices[2] = areaWidth;	areaVertices[3] = 0;
	areaVertices[4] = areaWidth;	areaVertices[5] = areaHeight;
	areaVertices[6] = 0;			areaVertices[7] = areaHeight;
}
void sb::Render::terminate(){

}
void sb::Render::update(){
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	drawTiles();
	drawArea();

	//glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glfwSwapBuffers(sb::SBWindow::getGLFWwindow());
}

//drawing
void sb::Render::drawTiles() {
	int areaWidth = sb::Area::getWidth();
	int areaHeight = sb::Area::getHeight();

	for (int y = 0; y < areaHeight; y++) {
		for (int x = 0; x < areaWidth; x++) {
			sb::Tile& tile = sb::Area::getTile(x, y);
			if (tile.isEmpty())
				continue;

			glBegin(GL_TRIANGLE_FAN);

			sb::Render::setColor(tile.color);
			glVertex2f(1 + x, 1 + y);
			glVertex2f(1 + x, 0 + y);
			glVertex2f(0 + x, 0 + y);
			glVertex2f(0 + x, 1 + y);
			glEnd();
		}
	}
}
void sb::Render::drawArea(){
	glLineWidth(2);
	glColor3ub(150, 150, 150);
	glVertexPointer(2, GL_FLOAT, 0, &areaVertices);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}
void sb::Render::setColor(sb::RGB color) {
	glColor3ub(color.r, color.g, color.b);
}