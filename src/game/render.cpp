#include "game/render.h"
#include "game/sbWindow.h"
#include "area/area.h"


//data
float sb::Render::areaVertices[8]{};
float sb::Render::squareVertices[8]{};
//Bottom left corner of the output area
sb::Vec2d<int> sb::Render::areaBottomLeft = sb::Vec2d<int>();
//Top right corner of the output area
sb::Vec2d<int> sb::Render::areaTopRight = sb::Vec2d<int>();

//managing this class
void sb::Render::init() {
	int areaWidth = sb::Area::getWidth();
	int areaHeight = sb::Area::getHeight();

	areaVertices[0] = 0;			areaVertices[1] = 0;
	areaVertices[2] = areaWidth;	areaVertices[3] = 0;
	areaVertices[4] = areaWidth;	areaVertices[5] = areaHeight;
	areaVertices[6] = 0;			areaVertices[7] = areaHeight;

	squareVertices[0] = 0;			squareVertices[1] = 0;
	squareVertices[2] = 0;			squareVertices[3] = 1;
	squareVertices[4] = 1;			squareVertices[5] = 1;
	squareVertices[6] = 1;			squareVertices[7] = 0;
}
void sb::Render::terminate() {

}
void sb::Render::update() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);

	drawArea();
	drawTiles();

	glDisableClientState(GL_VERTEX_ARRAY);
	glfwSwapBuffers(sb::SBWindow::getGLFWwindow());
}

//drawing
void sb::Render::drawTiles() {
	int areaWidth = sb::Area::getWidth();
	int areaHeight = sb::Area::getHeight();
	glVertexPointer(2, GL_FLOAT, 0, &squareVertices);
	for (int y = 0; y < areaHeight; y++) {
		for (int x = 0; x < areaWidth; x++) {
			sb::Tile& tile = sb::Area::getTile(x, y);
			if (tile.isEmpty())
				continue;
			glPushMatrix();
			sb::Render::setColor(tile.color);

			glTranslatef(x, y, 0);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			glPopMatrix();
		}
	}
}
void sb::Render::drawArea() {
	glLineWidth(3);
	glColor3ub(150, 150, 150);
	glVertexPointer(2, GL_FLOAT, 0, &areaVertices);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}
void sb::Render::setColor(sb::RGB color) {
	glColor3ub(color.r, color.g, color.b);
}

sb::Vec2d<int> sb::Render::getAreaBottomLeft() {
	return areaBottomLeft;
}
sb::Vec2d<int> sb::Render::getAreaTopRight() {
	return areaTopRight;
}

void sb::Render::changeOutputArea() {
	//getting data
	float numberTilesWidth = sb::Area::getWidth();
	float numberTilesHeight = sb::Area::getHeight();
	float windowWidth = static_cast<float>(sb::SBWindow::getWidth());
	float windowHeight = static_cast<float>(sb::SBWindow::getHeight());

	//calculating the tile size
	float tileWidth = windowWidth / numberTilesWidth;
	float tileHeight = windowHeight / numberTilesHeight;

	float tileSize;
	float renderWidth;
	float renderHeight;

	if (tileWidth < tileHeight) {
		//if the width is less, then it becomes the size
		tileSize = tileWidth;

		//since now "tileSize * numberTilesWidth == windowWidth". 
		//the area will be drawn according to "numberTilesWidth". 
		renderWidth = numberTilesWidth;

		//finding the rendering height by ratio of windowHeight/tileSize
		renderHeight = windowHeight / tileSize;
	}
	else {
		//if the height is less, then it becomes the size
		tileSize = tileHeight;

		//since now "tileSize * numberTilesHeight == windowHeight". 
		//the area will be drawn according to "numberTilesHeight".
		renderHeight = numberTilesHeight;

		//finding the rendering width by ratio of windowWidth/tileSize
		renderWidth = windowWidth / tileSize;
	}

	//the boundaries of the rendering game area
	areaBottomLeft.x = sb::SBWindow::getWidth() / 2 - tileSize * numberTilesWidth / 2;
	areaBottomLeft.y = 0;
	areaTopRight.x = sb::SBWindow::getWidth() / 2 + tileSize * numberTilesWidth / 2;
	areaTopRight.y = tileSize * numberTilesHeight;

	//moving the world coordinates to the center and
	//changing the image output according to the size of the game area
	glLoadIdentity();
	glViewport(areaBottomLeft.x, areaBottomLeft.y, sb::SBWindow::getWidth(), sb::SBWindow::getHeight());
	glOrtho(0, renderWidth, 0, renderHeight, -1, 1);
}