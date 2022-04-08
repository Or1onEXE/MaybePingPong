// Colors
unsigned int white = 0xffffff;
unsigned int gray  = 0x555555;
unsigned int black = 0x000000;

unsigned int red   = 0xff0000;
unsigned int green = 0x00ff00;
unsigned int blue  = 0x0000ff;

unsigned int cyan   = 0x00ffff;
unsigned int puprle = 0xff00ff;
unsigned int yellow = 0xffff00;


void renderBackground() {
	unsigned int* pixel = (unsigned int*)renderState.memory;
	for (int y = 0; y < renderState.height; y++) {
		for (int x = 0; x < renderState.width; x++) {
			*pixel++ = red;
		}
	}
}

// Fill screen with some color
void fillScreen(unsigned int color) {
	unsigned int* pixel = (unsigned int*)renderState.memory;
	for (int y = 0; y < renderState.height; y++) {
		for (int x = 0; x < renderState.width; x++) {
			*pixel++ = color;
		}
	}
}

// Fill all screen with white
void clearScreen() {
	unsigned int* pixel = (unsigned int*)renderState.memory;
	for (int y = 0; y < renderState.height; y++) {
		for (int x = 0; x < renderState.width; x++) {
			*pixel++ = white;
		}
	}
}

// Draw rectangle
void drawRect(int x0, int y0, int x1, int y1, unsigned int color) {
	for (int y = y0; y < y1; y++) {
		unsigned int* pixel = (unsigned int*)renderState.memory + x0 + y * renderState.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

// Draw Russia's flag
void drawRussia() {
	unsigned int* pixel = (unsigned int*)renderState.memory;
	for (int y = 0; y < renderState.height; y++) {
		if (y < renderState.height / 3 + 1) {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = red;
			}
		}
		else if (y > renderState.height / 3 && y < renderState.height * 2 / 3) {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = blue;
			}
		}
		else {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = white;
			}
		}
	}
}

// Draw Ukraine's flag
void drawUkraine() {
	unsigned int* pixel = (unsigned int*)renderState.memory;
	for (int y = 0; y < renderState.height; y++) {
		if (y < renderState.height / 2 + 1) {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = blue;
			}
		}
		else {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = yellow;
			}
		}
	}
}