#include "seizesv_plot.h"
#include "utilities.h"
#include "graphics.h"

/// this will plot a ssv_plot
int ssv_plot(struct ssv_plot *p, SDL_Surface *dest) {
	// if the plot pointer is bad
	if (p == NULL) {
		// report and error and return an error code
		error("ssv_plot() was sent a bad [p] ssv_plot pointer!");
		return -1;
	}
	
	// if the destination SDL_Surface ios bad,
	if (dest == NULL) {
		// report and error and return an error code
		error("ssv_plot() was sent a bad [dest] SDL_Surface pointer!");
		return -2;
	}
	
	// these are containers for where you want to print your marker
	double x_pxl,y_pxl;
	// save a local pointer to the ssv_file
	struct ssv_file *f = p->data;
	struct ssv_value v;
	ssv_type r;
	double x,y;
	for (r = 0; r < f->rows; r++) {
		// get the value in the x column
		ssv_file_get_value(f,p->x[0],r,&v);
		x = v.num;
		// if the x value found was NOT nan
		if (x == x) {
			// get the value in the y column
			ssv_file_get_value(f,p->y,r,&v);
			y = v.num;
			// if the y value found was NOT nan
			if (y == y) {
				x_pxl =  (x - p->x_origin[0]) * p->x_pixels_per_x[0];
				y_pxl = -(y - p->y_origin)    * p->y_pixels_per_y     + dest->h;
				// draw the point
				draw_circle(dest, x_pxl, y_pxl, 3, 0x9900ff00);
			}
		}
	}
	
	return 0;
}



/// initialize the plot
int ssv_plot_init(struct ssv_plot *p) {
	// if the plot pointer is bad
	if (p == NULL) {
		// report and error and return an error code
		error("ssv_plot() was sent a bad [p] ssv_plot pointer!");
		return -1;
	}
	
	p->data = NULL;
	
	ssv_type i;
	for (i = 0; i < SSV_PLOT_MAX_X; i++) {
		p->x[i] = 0;
		p->color_axis_x[i] = 0xff444444;
		p->x_axis[i] = 1;
		p->x_pixels_per_x[i] = 1;
		p->x_origin[i] = 0;
	}
	
	p->xs = 1;
	p->y = 1;
	p->color = 2;
	
	p->color_low = 0xff0000ff;
	p->color_high = 0xffff0000;
	p->color_background = 0xff000000;
	p->color_grid = 0xff444444;
	p->color_axis_y = 0xff444444;
	
	p->y_axis = 1;
	
	p->y_pixels_per_y = 1;
	
	p->y_origin = 0;
	
	return 0;
}


/// this will configure a plot to be fitted to its data
// returns:
//	0	success
//	-1	NULL [p]
//	-2	bad [fit] value
//	-3 	couldn't navigate columns for x
//	-4 	couldn't navigate columns for y
int ssv_plot_zoom_fit(struct ssv_plot *p, SDL_Surface *surf, double fit){
	// if the plot pointer is bad
	if (p == NULL) {
		// report and error and return an error code
		error("ssv_plot_zoom_fit() was sent a bad [p] ssv_plot pointer!");
		return -1;
	}
	
	if (fit <= 0 || fit > 1) {
		error_f("ssv_plot_zoom_fit() was sent a [fit] that was invalid:",fit);
		return -2;
	}
	
	int i;
	// this is used to navigate p->data (the ssv_file block structure)
	struct ssv_block *b;
	double range = 0;
	// for each independent x variable that exists,
	for (i = 0; i < p->xs; i++) {
		// start at the first column and work your way to the next columns.
		b = ssv_file_get_column_top(p->data,p->x[i]);
		if (b == NULL) {
			error("ssv_plot_zoom_fit() couldn't get column top for an x! ssv_file_get_column_top() returned NULL!");
			return -3;
		}
		// calcualte the x[] fit
		range = b->cmax - b->cmin;
		// calculate how long the x[] axis is
		p->x_pixels_per_x[i] = surf->w*fit/(range);
		// calculate where to start the x[] axis
		p->x_origin[i] = b->cmin - range*(1.0-fit)/(fit*2.0);
		
	}
	
	// get the y column
	b = ssv_file_get_column_top(p->data,p->y);
	if (b == NULL) {
		error("ssv_plot_zoom_fit() couldn't get column top for y! ssv_file_get_column_top() returned NULL!");
		return -4;
	}
	// calculate y fit
	range = b->cmax - b->cmin;
	// calculate how long the y axis is
	p->y_pixels_per_y = surf->h*fit/(range);
	// calculate where to start the y[] axis
	p->y_origin = b->cmin - range*(1.0-fit)/(fit*2.0);
	
	return 0;
}

