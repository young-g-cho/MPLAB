#include "filter.h"

/**
*	@brief initialize the moving average filter
*	@param *filter: address of the starting point of the filter
*/
void initFilter (MovingAverageFilter *filter) {
	
		filter->max_elements = FILTER_DEPTH;
		filter->num_elements = 0;
		filter->cur = 0;
		filter->last = 0;
		filter->sum = 0;
		filter->average = 0;										//average

}


/**
*	@brief Updates the filter
*	@param filter: moving average filter structure 
*	@param new_Value: next value to be filtered
*	@description This function implements a moving average filter of sample size FILTER_DEPTH. 
*/
void filterAdd (MovingAverageFilter *filter, int32_t new_Value) {
	int32_t old_Value;
	
	//case where max num elements is not reached
	if(filter->num_elements < (filter->max_elements))	{
			//push the new value to current position and increase num_elements
			filter->butffer[filter->cur] = new_Value;
			filter->num_elements++;
			
			//if current position is at the end then set cur to 0(wrap around) and move last by 1
			if(filter->cur == (filter->max_elements-1))	{
				filter->cur = 0;
				filter->last++;
			} else {
				filter->cur++;
			}
			
			//update sum and average
			filter->sum += new_Value;
			filter->average = filter->sum / filter->num_elements;
	} else {
			//saves the current position and overwrite it with new value
			old_Value = filter->butffer[filter->cur];
			filter->butffer[filter->cur] = new_Value;
			
			//check if either cur or last pointer is at the end of the buffer(do a wrap around)
			if(filter->cur == (filter->max_elements-1)) {
					filter->cur = 0;
					filter->last++;
			} else if(filter->last == (filter->max_elements-1)){
					filter->last = 0;
					filter->cur++;
			} else {
				filter->cur++;
				filter->last++;
			}

			//update sum and average
			filter->sum = filter->sum - old_Value + new_Value;
			filter->average = filter->sum / filter->num_elements;
	}
	
}
