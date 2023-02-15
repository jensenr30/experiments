#include <stdio.h>

int main(){
    
    //open file
    FILE *testFile = fopen("test.txt", "r");
    if(testFile == NULL){
        printf("Couldn't open File");
        system("pause>nul");
        return 0;
    }
    
    
    char myChar1 = fgetc(testFile);
    char myChar2 = fgetc(testFile);
    
    //print out the first two characterscharacter
    printf("%d, %c\n%d %c\n", (int)myChar1, myChar1, (int)myChar2, myChar2);
    
    system("pause>nul");
    
    return 0;
}
