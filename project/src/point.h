#define TILE_SIZE 20

#define BOARD_X 242
#define BOARD_Y 114

typedef struct {
	unsigned int x;
	unsigned int y;
} Point;

Point* getPoint(int x, int y);

int comparePoints(Point* a, Point* b);
