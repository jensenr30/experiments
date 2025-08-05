#include <stdio.h>
#include <SDL2/SDL.h>
#include <sys/types.h> // Required for pid_t
#include <unistd.h>    // Required for getpid()
#include <iostream>
#include <time.h>

int main(void) {
    while(1) {

        for (int i = 0; i < 1000; i++) {
            // trying to replicate a bug where nanosleep() hangs
            SDL_Delay(1);

            // show when the app hangs
            if (i % 100 == 0) {
                std::cout << 'a' + i/100 << std::flush;
            }
        }

        pid_t current_pid = getpid();
        std::cout << "I froze!!! Attach to PID: " << current_pid << std::endl;

        time_t result = time(NULL);
        std::cout << asctime(gmtime(&result)) << std::endl;
    }
    return 0;
}
