#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMWORDS 5757
#define ATTEMPTS 6

char list[NUMWORDS][6], guess[100] = {};

int instructions() {
  printf("\e[1;1H\e[2J");  // clear screen
  printf("\n\e[36mInstructions\e[37m\n");
  printf("You've to guess the word in 6 attempts.\n");
  printf("Type a valid 5-letter word. Press \e[33mENTER\e[37m to submit.\n");
  printf(
      "After each guess, the colored hints will show you how close your guess "
      "was to the word.\n");
  printf("\e[36mExamples\e[37m\n");
  printf("\e[32mw\e[37meary\n");
  printf("'W' is in the word and in the \e[32mcorrect\e[37m position.\n");
  printf("p\e[33mi\e[37mlls\n");
  printf("'I' is in the word but in the \e[33mwrong\e[37m position.\n");
  printf("vag\e[31mu\e[37me\n");
  printf("'U' is \e[31mnot\e[37m in the word in any position.\n");
}

int bye() {
  printf("\e[1;1H\e[2J");  // clear screen
  printf("\n\e[36mThank you for playing my Wordle Clone.\e[37m\n");
  printf("-- \e[33mSoham\e[37m\n\n\n");
  exit(0);
}

int isword(char word[6]) {
  for (int i = 0; i < NUMWORDS; i++)
    if (!strcmp(word, list[i]))
      return 1;
  return 0;
}

int startgame() {
  printf("\e[1;1H\e[2J");  // clear screen
  printf(
      "The game has now begun. Make your first guess. To quit, type "
      "\e[33m..\e[37m and press \e[33mENTER.\e[37m\n\n");

  int i, attempts = 0;

  char word[6];
  strcpy(word, list[rand() % NUMWORDS]);  // choose random word
  // printf("%s\n", word);

  while (++attempts) {
    // count letter frequency of word
    int freq[26] = {0};
    for (i = 0; i < 6; i++)
      freq[word[i] - 'a']++;

    // input guess
    printf("%d\e[36m > \e[37m", attempts);
    scanf("%s", guess);

    // print guess with colored hints
    printf("    ");
    for (i = 0; i < 6; i++)
      if (word[i] == guess[i])
        freq[guess[i] - 'a']--;
    for (i = 0; i < 6; i++) {
      if (word[i] == guess[i])
        printf("\e[32m");
      else if (freq[guess[i] - 'a'] > 0)
        printf("\e[33m"), freq[guess[i] - 'a']--;
      else
        printf("\e[37m");
      printf("%c", guess[i]);
    }

    if (!isword(guess))
      printf("\e[31m is not a word!");
    printf("\e[37m\n");

    if (!strcmp(word, guess)) {  // win
      printf("\nYou got the correct answer!\n");
      printf("You took \e[33m%d\e[37m attempts.\n", attempts);
      break;
    } else if (attempts == ATTEMPTS) {  // lose
      printf("\n\e[31mGame over!\e[37m\n");
      printf("You've exhausted your \e[33m%d\e[37m attempts.\n", attempts);
      printf("The word was \e[33m%s\e[37m.\n", word);
      break;
    }
  }
}

int main() {
  srand(clock());
  FILE* words = fopen("words.txt", "r");
  if (!words) {
    printf("\e[31mError\e[37m\n");
    printf(
        "The file \e[33mwords.txt\e[37m with the list of words not found in "
        "this folder!\n\n\n");
    exit(0);
  }

  // load word list
  for (int i = 0; i < NUMWORDS; i++)
    fscanf(words, "%s", list[i]);
  fclose(words);

  while (1) {
    printf("\n\e[35mWelcome to the Wordle Clone!\e[37m\n");
    printf("1. Play\n");
    printf("2. Instructions\n");
    printf("3. Exit\n");
    printf("\e[36m> \e[37m");

    scanf("%s", guess);
    if (!strcmp(guess, "1"))
      startgame();
    else if (!strcmp(guess, "2"))
      instructions();
    else if (!strcmp(guess, "3"))
      bye();
    else
      printf("\e[31mIncorrect choice!\e[37m\n");
  }
}