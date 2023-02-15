#define quit_surface_error 1


void quit_game(int quitFlag, char *errmsg);
void set_window_size(int w, int h);
int init();
int load_files();
void clean_up();
int get_rand(int lowBound, int highBound);
int roll_ht(int chance);
