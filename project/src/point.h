#define TILE_SIZE 20

typedef struct {
	unsigned int x;
	unsigned int y;
} Point;

Point* getPoint(unsigned int x, unsigned int y);

int comparePoints(Point* a, Point* b);
