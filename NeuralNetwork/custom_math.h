
#define square(value) ((value)*(value))

#define biggest(value1,value2) ( ((value1>=value2) * (value1-value2)) + value2 )
#define smallest(value1,value2) ( ((value1<=value2) * (value1-value2)) + value2 )


short bubble_sort_f(float *stuff, unsigned int elements, unsigned int *order);
