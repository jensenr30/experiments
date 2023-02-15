#include "seizesv.h"
#include <SDL2/SDL.h>
// the maximum number of independent variables there can be on a single plot
#define SSV_PLOT_MAX_X 3

// this describes how fast the user wants to run this program
#define SSV_PLOT_TARGET_FPS 30
#define SSV_PLOT_TARGET_FRAME_PERIOD_MS (1000/SSV_PLOT_TARGET_FPS)


typedef uint32_t ssv_color;

/// this structure describes how ssv data should be plotted
struct ssv_plot {
	
	//--------------------------------------------------------------------------
	// data, columns, rows,
	//--------------------------------------------------------------------------
	
	// this is a pointer to the ssv_file that contains all the data needed for plotting
	struct ssv_file *data;
	
	// this is used to determine which column(s) are the INdependent variables
	ssv_type x[SSV_PLOT_MAX_X];
	// this keeps track of how many independent variables there are
	// 1 = only x[0] is an independent variable
	// 2 = x[0] and x[1] are both independent variables
	int xs;
	// this is used to determine which column is the dependent variables
	ssv_type y;
	
	// this specifies which column is used to determine color
	// this is NOT ACTUALLY COLOR DATA. It just points to the column which will control the color of the plot on 
	ssv_type color;
	
	//--------------------------------------------------------------------------
	// colors
	//--------------------------------------------------------------------------
	
	// this is the color the is most prevalent in the lowest value data points
	ssv_color color_low;
	// this is the color the is most prevalent in the lowest value data points
	ssv_color color_high;
	// this is the color of the plot background
	ssv_color color_background;
	// this is the color of the grid
	// to hide the grid, make it the same color as the background.
	ssv_color color_grid;
	// the colors of all the x axes
	ssv_color color_axis_x[SSV_PLOT_MAX_X];
	// the colors of the y axis
	ssv_color color_axis_y;
	
	//--------------------------------------------------------------------------
	// which variables are plotted, and how they are plotted
	//--------------------------------------------------------------------------
	
	/* HOW THE x_axis AND y_log NUMBERS WORK:
	positive number, a (not 1)	plotted data is logarithmic (log(a,x))
	1							plotted data is linear - no distortion
	0							data is NOT plotted
	negative number, a			plotted data is exponentially (exp(-a,x))
	
	// positive log bases are interpreted as normal logarithmic functions
		x_axis[0] = 0,	The data is not plotted
		x_axis[0] = 1,	The data is plotted linearly
		x_axis[0] = 10, The x-data will be plotted as log_base_10(x).
						The x-axis will have regular tick marks every decade (or more inbetween decades)
		x_axis[0] = 2	The x-data will be plotted as log_base_2(x).
		x_axis[0] = -5	The x-data will be plotted as 5^x.
	*/
	double x_axis[SSV_PLOT_MAX_X];
	double y_axis;
	
	//--------------------------------------------------------------------------
	// camera location, scale
	//--------------------------------------------------------------------------
	
	// this specifies the scale of x data ( in x units) to pixels (screen unit)
	// basically, this is how "zoomed in/out" the camera is
	// (x pixels)/(x units)
	double x_pixels_per_x[SSV_PLOT_MAX_X];
	// (y pixels)/(y units)
	double y_pixels_per_y;
	
	// The x[] value that will be mapped to the right edge of the SDL_Surface
	double x_origin[SSV_PLOT_MAX_X];
	// The y  value that will be mapped to the bottom edge of the SDL_Surface
	double y_origin;
	
};


//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
int ssv_plot(struct ssv_plot *p, SDL_Surface *dest);
int ssv_plot_init(struct ssv_plot *p);
int ssv_plot_zoom_fit(struct ssv_plot *p, SDL_Surface *surf, double fit);

