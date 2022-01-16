#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRIAL_LIMIT 10

// User-defined function prototypes
int ikinin_ussu(int sayi);
int make_a_guess(int trial, int min, int max);
void draw_hourglass(int height);
void draw_mountain_road(int length, int max_radius);
void menu();
void show_scores(int score_user, int score_computer);

// Main function
int main(void) {
  srand(time(NULL));
  menu();
  return 0;
}

// Menu function
void menu()
{
  int choice = 0, difference, distance, guess_number, height, i, j, k, len, lucky_number, max, min, mr, score_human = 0, score_program = 0, trial;

  while(choice != 4) 
  {
    // Print menu and get choice from user
    printf("***** MENU *****\n1. Play Lucky Number\n2. Draw Hourglass\n3. Draw Mountain Road\n4. Exit\nChoice: ");
    scanf("%d", &choice);

    // Menu switch
    switch(choice)
    {
      case 1: // Lucky number game
        trial = 1;
        min = 1;
        max = 1024;
        lucky_number = rand() % max + min;
        while(trial <= TRIAL_LIMIT)
        {
          guess_number = make_a_guess(trial, min, max);
          difference = abs( lucky_number - guess_number );
          i = 0;
          // Distance calculation
          while(i <= 10 && ikinin_ussu(i) < difference + 1)
          {
            i++;
          }
          distance = i;
          printf("Distance is %d. ", distance);
          // If user guess is true, user wins and loop breaks
          if(guess_number == lucky_number)
          {
            break;
          }
          // Elsewhere Update min and max
          else if(guess_number > lucky_number && lucky_number < max)
          {
            max = guess_number;
          }
          else if(lucky_number > guess_number && lucky_number > min)
          {
            min = guess_number;
          }

          // Update trial number
          trial++;
        }
        if(guess_number == lucky_number && trial <= 10)
        {
          // User won game
          printf("You win!\n");
          score_human = score_human + 1;
        }
        else if(guess_number != lucky_number && trial > 10)
        {
          // User lost game, computer wins
          printf("You lost!\n");
          score_program = score_program + 1;
        }
        show_scores(score_human, score_program);
        break;

      case 2: // Hourglass drawing
        printf("Enter height of hour glass:");
        scanf("%d", &height);
        draw_hourglass(height);
        break;

      case 3: // Mountain road drawing
        printf("Enter length for mountain road:");
        scanf("%d", &len);
        printf("Enter maximum radius for mountain road:");
        scanf("%d", &mr);
        draw_mountain_road (len, mr);
        break;

      case 4:
        break;

      default:
        // Error
        printf("This choice is not correct.\n");
        break;
    }
  }
}

void draw_hourglass(int height)
{
  int i, j, k, ns=0-height;

  // Get height from user till he/she enters and odd number
  while(height % 2 == 0)
  {
    printf("Error! You should enter an odd number: ");
    scanf("%d", &height);
  }

  // First half of hourglass
  for(i = ns; i < -1; i += 2)
  {
    for(j = 0; j < ((i-ns)*1) / 2; j++)
    {
      printf(" ");
    }
    for(k = i; k < 0; k++)
    {
      printf("*");
    }
    printf("\n");
  }

  // Second half of hourglass
  for(i = 1; i <= height; i += 2)
  {
    for(j = 0; j < (height-i)/2; j++)
    {
      printf(" ");
    }
    for(k = 0; k < i; k++)
    {
      printf("*");
    }
    printf("\n");
  }

  // Print an extra new line before back to menu
  printf("\n");
}

void show_scores(int score_user, int score_computer) {
  printf("Your score: %d, Program score: %d\n", score_user, score_computer);
}

int ikinin_ussu(int sayi)
{
  int i, sonuc=1;

  for(i=1; i<=sayi; i++)
  {
    sonuc = sonuc * 2;
  }

  return sonuc;
}

int make_a_guess(int trial, int min, int max) {
  int guess_number, temp;

  printf("\n(Trial: %d) Make a guess between %d and %d: ", trial, min, max);
  scanf("%d", &guess_number);

  return guess_number;
}

void draw_mountain_road(int length, int max_radius)
{
  int i, j, l, // loop counters
      part, // there are two parts in circle
      r, // radius
      sc; // count of spaces on left
  sc = max_radius + 1;

  for(i = 0; i < length; i++)
  {
    // Random number between 0 and maximum radius
    r = rand() % (max_radius + 1);

    // Two parts of circle: before center and after center
    for(part = 0; part < 2; part++)
    {
      for(j = 0; j < r; j++)
      {
        for(l = 0; l < sc; l++) 
        {
          // Print space on left
          printf(" ");
        }
        if(part == i % 2)
        {
          // Print road and decrease spaces
          printf("/\n");
          if(r > 0)
            sc--;
        }
        else if(part != i % 2)
        {
          // Print road and increase spaces
          printf("\\\n");
          if(r > 0)
            sc++;
        }
      }
      if(part == 0) {
        // At the end of first half, there is center represented by '|' character
        for(l = 0; l < sc; l++)
        {
          // Print space on left
          printf(" ");
        }
        printf("|\n");
        if(i % 2 == 1) 
        {
          // Decrease spaces
          if(r > 0)
            sc--;
        } 
        else 
        {
          // Increase spaces
          if(r > 0)
            sc++;
        }
      }
    }
  }
}