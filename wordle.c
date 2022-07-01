#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//code written from James Gui
//CS Username: gui
//Comp Sci 537 Project 1

// This method displays lines from a file or user input which begin with a certain string. 

int main(int argc, char *argv[])
{   

    int length_Max = 255; //sets max value of acceptable chars
    char file_Name[255]; //filename
    char userInput[255]; //user input word to search

    char loadedFile[255]; //array to hold contents of file
    char list_Of_Strings[255][255]; //array or array of individual words
    char list_Of_ParsedStrings[255][255]; //length of parsed array
    
    char* returnWord;

    int tempCount = 0;
    
    //mallocs length_Max of char (char only 1) 
    returnWord = malloc( length_Max );

    //this function reads command line arguments, provides suitable response. 
    if(argc != 3 )
    {
        printf("wordle: invalid number of args\n");
        exit(1);
    }

    strcpy(file_Name, argv[argc-2]); //sets file to last value user intered 
    strcpy(userInput, argv[argc-1]);  //sets user input to the argv to user input

    
    for(int x = 0; userInput[x] != '\0'; x++)
    {
        int i = 0;

        while (! (( ( userInput[x]>='a'&& userInput[x]<='z' ) ) || 
        ( ( userInput[x]>='A' && userInput[x]<='Z' ) || userInput[x]=='\0')))
        {
            for(i = x; userInput[i] !='\0'; ++i)
            {
                userInput[i] = userInput[i + 1];
            }

            userInput[i]='\0';
        }
    }
    

    if(file_Name == NULL)
    {
        printf("no file found");
    }


    FILE *file = fopen(file_Name, "r");
    if (file == NULL) {
        printf("wordle: cannot open file\n");
        exit(1);
    }

    
    if( fgets (loadedFile, sizeof(loadedFile), file) == NULL ) {
        printf("wordle: cannot open file\n");
        exit(1);
    }

    tempCount = 0;
    
    returnWord = strtok(loadedFile, " ");
    if(returnWord != NULL)
    {
        strcpy(list_Of_Strings[tempCount], returnWord);
    }
    else
    {
        printf("wordle: no values"); 
        exit(0);
    }
     
    
    while(returnWord != NULL)
    {
        tempCount++;
        returnWord = strtok(NULL, " ");
        if(returnWord != NULL)
        {
            strcpy(list_Of_Strings[tempCount], strtok(NULL, " ") );
        }
    }


    //copy values of loaded file into parsed list 
    for(int i = 0; i < length_Max; i++)
    {
        for( int x = 0; x < length_Max; x ++)
        {
            list_Of_ParsedStrings[i][x] = list_Of_Strings[i][x]; 
        }
    }

    
    //removes all non alphabetical from the word
    //TODO check strlen
    int i = 0;
    for( int j = 0; j < length_Max ; j++ )
    {
        if(list_Of_ParsedStrings[j] == NULL)
        {
            continue;
        }
        for(int x = 0; list_Of_ParsedStrings[j][x] != '\0'; x++)
        {
            while (! (( ( list_Of_ParsedStrings[j][x]>='a'&& list_Of_ParsedStrings[j][x]<='z' ) ) || 
            ( ( list_Of_ParsedStrings[j][x]>='A' && list_Of_ParsedStrings[j][x]<='Z' ) 
            || list_Of_ParsedStrings[j][x]=='\0')))
            {
                for(int i = x; list_Of_ParsedStrings[j][i] !='\0'; ++i)
                {
                    list_Of_ParsedStrings[j][i] = list_Of_ParsedStrings[j][i + 1];
                }

                list_Of_ParsedStrings[j][i]='\0';
            }
        }
    }

    //checks and prints out words that meet criteria 

    //this for loop iterates through the list of strings and prints strings that are done
    for(int x = 0; x < length_Max; x++)
    {
        int isPrintable = 1;
        //exits program upon null or empty string, ask ta if i can use ! to check for null
        if(list_Of_Strings[x] == NULL)
        {
            //TODO close memory
            fclose(file);
            exit(0);
        }

        else if(*list_Of_Strings[x] == '\0')
        {
            printf("reached end of stuff");
            break;
        }

        if(strlen(list_Of_Strings[x]) > 5)
        {
            isPrintable = 0;
            continue;
        }

        for(int j = 0; j < strlen(list_Of_ParsedStrings[x]); j++)
        {
            for(int n = 0; n < strlen(userInput); n++)
            {
                if(list_Of_ParsedStrings[x][j] == userInput[n])
                {
                    isPrintable = 0;
                }
            }
            
        }
        
        
        if(isPrintable == 1)
        {
            printf("%s", list_Of_Strings[x]);
        }

    }

    free (returnWord);
    fclose(file);
}