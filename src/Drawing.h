#ifndef DRAWING_H
#define DRAWING_H

class Drawing {
	float circle[65][2];
	void initCircleCoords();

public:
	Drawing();
	~Drawing();

	void drawCircle(float x, float y, float radius, unsigned char *colors);

	void drawInfoPanel();

	void drawWindowWin();
	void drawWidnowRepeat();
	void drawFinalBackground();

	void initDisplayList();
};

#endif
