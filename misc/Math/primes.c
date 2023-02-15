#include <stdio.h>
#include <windows.h>
//#include <time.h>

int main()
{
    while(1)
    {
        // most variable definitions here (some are defined later in code)
        time_t seconds; //declare the sec variable for use with timing the calculations
        int minutes, hours;
        long int nop = 3; // the number of primes the program has calculated. starts as 1
        long int numb2test = 7; // the number that will be checked to see if it is a prime. starts as 3
        long int i; // used in for() loops
        long int primes2calc; // this is how many prime numbers we will calculate
        short int numbaprime; // used to indicate whether or not a number is prime
        short int messageboxbutton; // used in the message box. will store result of MessageBox()
        char filename[64];
        
        // this asks the user how many primes he/she wants to calculate
        printf("how many prime numbers would you like calculated? ");
        scanf("%ld", &primes2calc); // user decides how many prime numbers to calculate
        getchar(); // clears the left over '\n' character (I don't know why i have to have this in here, but it is the only way it works that I know of.)
        if(primes2calc < 5)
            primes2calc = 5; // we will calculate at least 5 primes
        if(primes2calc > 500000)
            primes2calc = 500000; // we will calculate at most 500,000 primes
        long int primes[primes2calc]; // the prime number array defined here
        primes[0] = 2; primes[1] = 3; primes[2] = 5; // load the first three primes into array
        
        // lets the user name the .txt file
        messageboxbutton = MessageBox(NULL,
            "this program will write prime numbers to a .txt file. would you like to name this text file?",
            "name file?",
            MB_YESNO | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND | MB_DEFBUTTON2
        );
        if(messageboxbutton==IDYES)
        {
            printf("name your file: ");
            for(i=0; i<63; i++)
            {
                filename[i] = getchar();
                if(filename[i] == 10)
                {
                    break;
                }
            }
            filename[i]  = '.'; // add .txt to the end of the user's string (plus a NULL character)
            filename[i+1]= 't';
            filename[i+2]= 'x';
            filename[i+3]= 't';
            filename[i+4]='\0';
        }
        else
        {
            filename[0]= 'p'; // name it primes.txt by default
            filename[1]= 'r';
            filename[2]= 'i';
            filename[3]= 'm';
            filename[4]= 'e';
            filename[5]= 's';
            filename[6]= '.';
            filename[7]= 't';
            filename[8]= 'x';
            filename[9]= 't';
            filename[10]='\0';
        }
            
        
        // this is where the primes are calculated
        seconds = time(NULL); // store the current time (in seconds)
        while(nop < primes2calc)
        {
            numbaprime=1;
            for(i = 1; (i < nop); i++)
            {
                if(primes[i] > numb2test/2) break;
                if((numb2test % primes[i]) == 0) numbaprime = 0; // if number is divisible by a prime, it is not prime
            }
            if(numbaprime)
            {
                primes[nop] = numb2test; // add the current number being checked into the primes array.
                nop++;
            }
            numb2test = numb2test + 2; // increment the number to test by 2. (move to the next odd number)
            if(!(nop % 23))printf("\rcalculating #%d: %d", nop, primes[nop-1]);
        }
        printf("\rcalculating #%d: %d", nop, primes[nop-1]);
        
        // writing to *.txt file
        printf("\nwriting primes to \"%s\" . . .\n", filename);
        FILE *fp;
        fp = fopen(filename, "w");
        for(i = 0; i < primes2calc; i++)
            fprintf(fp, "%d:\t\t%d\n", i+1,primes[i]);
        fclose(fp);
        //time calculations
        seconds = (time(NULL) - seconds);
        minutes = seconds/60;
        hours = minutes/60;
        seconds %= 60;
        minutes %= 60;
        printf("done!\ntime: ");
        if(hours) printf("%d hours, ", hours);
        if(minutes) printf("%d minutes, and ", minutes);
        printf("%d seconds.\n", seconds);
        
        //ask user if he/she wants to go calculate more primes
        messageboxbutton = MessageBox(NULL,
            "primes have been written to file. would you like to calculate more primes?",
            "moar primes?",
            MB_RETRYCANCEL | MB_ICONQUESTION | MB_APPLMODAL | MB_SETFOREGROUND | MB_DEFBUTTON2
            );
        if(messageboxbutton == IDCANCEL) return 0;
    }// end while(1) loop
}// end main
