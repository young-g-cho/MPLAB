#include <stdint.h>               

#define FILTER_DEPTH 100

//declare the filter structure that will be used to
//implement the moving average filter
typedef struct Filter
{
	uint16_t num_elements;
	uint16_t max_elements;
	uint16_t cur;
	uint16_t last;
	int32_t sum;
	int32_t average;
	int32_t butffer[FILTER_DEPTH];

}MovingAverageFilter;

void initFilter (MovingAverageFilter *filter);
void filterAdd(MovingAverageFilter *filter, int32_t new_Value);
