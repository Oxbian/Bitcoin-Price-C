#include "bitcoin_api.h"
#include <unistd.h>

#define MAX 257
#define TABMAX 1025

int main()
{
    int L = 19; // Width of each ascii char
    int H = 19; // Height of each ascii char
    char tab[L][TABMAX]; // Tab containing the ascii art
    char T[MAX]; // String containing the bitcoin price

    /* Getting ascii art style from the file */
    FILE* fptr = fopen("src/ascii_art.txt","r");

    if (fptr == NULL) {
        fprintf(stderr, "file opening failed\n");
		exit(EXIT_FAILURE);
    }

    for (int i = 0; i < H; i++) {
        char ROW[TABMAX]; //A tab containing one line of the ascii_art.txt file
        char ch;
        int k = 0;

        //Strange bugs with my .txt so I use n char instead of the classic \n to know if we change of line and changing the \n to a space
        while( (ch = getc(fptr)) != 'n' ) {
            if (ch == '\n') {
                ch = ' ';
            }

            //Adding the char to the ROW tab, adding one the the k indice
            ROW[k] = ch;
            k++;
        }

        //Adding the row content into the tab
        for (int j=0; j<TABMAX; j++) {
            tab[i][j] = ROW[j];
        }
    }

    //Closing the file containing the ascii art
    fclose(fptr);

    //Infinite loop
    while (1)
    {    
        //Calling the function from bitcoinapi.c to get the bitcoin current price
        get_bitcoin_price(T,MAX);
        //printf("%s\n",T);
        
        int size=0;

        //Length of the word
        for (int i =0; i < 257; i++) {
            if (T[i] != '.') {
                size++;
                //Converting the bitcoin price ascii value into int (ascii table)
                if (T[i] >= 48 && T[i] <= 57)
                    T[i] -= 48;
            } else {
                break;
            }
        }

        //Print the bitcoin price
        for (int i = 0; i < H; i++) { // Loop for each line
            for (int j = 0; j< size; j++) { // Loop for each number in the bitcoin price
                //Id take the value of the Jth number of bitcoin price
                int id = T[j];
                if (id > 0 && id <= 10) { //Compare if id is inside 0 and 10
                    for (int k = (id*L)+id; k<((id+1)*(L))+id+1; k++) {
                        printf("%c",tab[i][k]);
                    }
                } else if (id == 0) { //Correcting the problem with 0 Ascii
                    for (int k =(id*L)+1; k<(id+1)*(L)+2; k++) {
                        printf("%c",tab[i][k]);
                    } 
                }
            }
            printf("\n");
        }
        sleep(60); //Waiting 1 minutes between each refresh of bitcoin price
    }
    return 0;
}
