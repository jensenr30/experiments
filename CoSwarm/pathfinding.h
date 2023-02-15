#define MAX_PATH_STEPS 1024
struct pathStepData{
	int x;	// current points
	int y;
	//int xn; // next points to go to (best)
	//int yn;
	struct pathPointData *prev;
};
