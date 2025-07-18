#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//GLOVAL VARIABLES
int lives = 9;
bool isPlaying = true;



char* selectWord();

void playGame();

char playerInput();

void changeLivesCount(bool foundLetter);

bool checkWinCondition(char* tempWord, char* word);

bool checkLostCondition();

void restartGame();

int main(){

  while(isPlaying){
  playGame();
  }


  return 0;
}

char* selectWord(){

  FILE *fptr;
  fptr = fopen("words.txt", "r");
  
  char string[100];
  
  int lineCount;
  while(fgets(string, 100, fptr)){
    lineCount++;
  }
  
  //generate random number
  srand(time(NULL));
  int randNumber = rand() % lineCount + 1;

  fclose(fptr);

  //create a new instance of the file pointer
  FILE *fptr2;
  fptr2 = fopen("words.txt", "r");

  int i = 0;
  while(fgets(string, 100, fptr2)){
    if(i >= randNumber){
      //strips the \n from the string itself and replaces it with the string end
      string[strcspn(string, "\n")] = '\0';
      break;
    }
    i++;
  }

  fclose(fptr2);


  //allocate memory for the word
  char* wordCopy = malloc(strlen(string));
  
  //copy the string into the memory
  strcpy(wordCopy, string);
  
  return wordCopy;
 
}

void playGame(){

  //pointer to the word in memory;
  char* word = selectWord();

  //allocate one extra byte for the null terminator \0

  char tempWord[strlen(word) + 1];
  char* ptrTW = tempWord;


  for(int i = 0; i < strlen(word); i++){
    tempWord[i] = '*';
  }
  //fill the last char with a null terminator
  tempWord[strlen(word)] = '\0';


  //playGame
    printf("Welcome to Hang Man in C!\n");
    while(isPlaying){
    bool foundLetter = false;
    printf("lives remaining: %d\n", lives);   
    printf("%s\n", tempWord);
    printf("Take a guess: ");
    char input;
    input = playerInput();
    printf("%c\n", input);

    //check the input
    for(int i = 0; i < strlen(word); i++){
      if(input == word[i]){
        tempWord[i] = input;
        foundLetter = true;
      }
    }
    
    changeLivesCount(foundLetter);
    

    if(checkWinCondition(ptrTW, word)){
      restartGame();
      break;
    }

    if(checkLostCondition()){
      printf("The word was: %s\n", word);
      restartGame();
      break;
    }
    
  }

}

char playerInput(){
  char buffer[100];
  char input;
  fgets(buffer, sizeof(buffer), stdin);
  input = buffer[0];
  return input;
}

void changeLivesCount(bool foundLetter){
  if(!foundLetter){
    lives--;
  }
}

bool checkWinCondition(char* tempWord, char* word){
  if(strcmp(tempWord, word) == 0){
    printf("You Have Won!\n");
    return true;
  }
  else if(lives <= 0){
  printf("You Have Lost\n");
  return false;
  }

  return false;
}

bool checkLostCondition(){
  if(lives <= 0){

    return true;
  }
  return false;
}

void restartGame(){
  printf("Do you want to play again? y/n: ");
  char input =  playerInput(); 
  
  if(input == 'y'){
    isPlaying = true;
    lives = 9;
  }
  else if(input == 'n'){
    isPlaying = false;
  }
  else{
    printf("Input invalid!");
    restartGame();
  }
}



