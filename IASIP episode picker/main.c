// Ryan Jensen
// 2013-09-15
// This program will pick a random episode from it's always sunny in philadelphia for you to watch.

#include <stdio.h>
#include <time.h>

int main(){
	
	srand(time(NULL));
	
	int numberOfSeasons = 8;
	int numberOfEpisodes = 15;
	char dummy;
	
	while(1){
		
		int season = rand()%numberOfSeasons + 1;
		int episode = rand()%numberOfEpisodes + 1;
		
		printf("Season  %2d\nEpisode %2d",season, episode);
		system("pause>nul");
		system("cls");
	}
	
	
	return 0;
}
