#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct point {
	int x, y;
	struct point next;
} point_t;


point_t *add(point_t *tail, int x, int y) {
	point_t newPoint = malloc(sizeof(point_t));
	newPoint->x = x;
	newPoint->y = y;
	if(tail)
		tail->next = newPoint;
	return newPoint;
}

bool pointInRect(point_t point, point_t *rects) {
	int lastX = 0;

	while(rects) {
		if (point.x >= lastX && point.x <= rects->x && point.y <= rects->y)
			return true;
		lastX = rects->x;
		rects = rects->next;
	}
	return false;
}
