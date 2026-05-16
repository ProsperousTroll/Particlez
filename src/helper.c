#include "../inc/helper.h"
#include <stdlib.h>
#include <time.h>

float getRandom(float min, float max){
	static int seeded = 0;
	if(!seeded){
		srand((unsigned int)time(NULL));
		seeded = 1;
	}
	int x = (int)(min*100);
	int y = (int)(max*100);
	int res = x + rand() % (y+100 - x);
	return (float)res / 100;
}
