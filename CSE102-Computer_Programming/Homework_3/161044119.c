#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZ 51

// Function prototypes
void delete_newline(char str[]);
int divide_arguments(char str[], char arguments[][10]);
void menu();
void simple_calculator();
int add(int number1, int number2);
int sub(int number1, int number2);
int mul(int number1, int number2);
int divi(int number1, int number2);
int powe(int number1, int number2);
int mod(int number1, int number2);
int doit(int fun(), int first_number, int second_number);
void draw_a_diamond();
int take_grades(int arr[]);
int take_exam_grades(int arr[]);
double calculate_homework(int hw_grades[]);
double calculate_lab(int lab_grades[]);
double calculate_all(int hw, int exam_grades[], int lab);
void calc_average_of_grades();

int main(void) {
  menu();

  return 0;
}

void menu() 
{
  // Menu function
  int ch=0;
  while(ch != 4) {
    printf("***** MENU *****\n");
    printf("1. Simple Calculator\n2. Calculate Average of Grades\n3. Draw a Diamond\n4. Exit\n");
    printf("Choice: ");
    scanf("%d", &ch);

    // choice switch
    switch(ch) {
      case 1:
        simple_calculator();
        break;

      case 2:
        calc_average_of_grades();
        break;

      case 3:
        draw_a_diamond();
        break;

      // do nothing but not default, it will exit program later
      case 4:
        break;

      default:
        printf("Invalid choice!\n");
        break;

    }

  }
}

void delete_newline(char str[])
{
  int i, len;
  len = strlen(str);

  if(str[len-1] == '\n')
    str[len-1] = '\0';
}

int divide_arguments(char str[], char arguments[][10])
{
  // variable definitions
  int i=0, j=0, k=0;

  // divide into arguments
  while(str[k] != '\0')
  {
    arguments[i][j] = str[k];
    j++;
    if(str[k+1] == ' ')
    {
      arguments[i][j+1] = '\0';
      i++;
      j=0;
    }
    
    k++;
  }
  arguments[i][j] = '\0';

  // return count
  return i+1;
}

void simple_calculator() 
{
  char input[STRSIZ], arguments[3][10], operation;
  int spaces, numbers[2], result=0, arguments_count, i, j, first_run=1;

  // Program stops when user enters "k"
  while(strcmp(input, "k") != 0)
  {
    // Clear arguments
    for(i = 0; i < 3; i++)
      for(j = 0; j < 10; j++)
        arguments[i][j] = '\0';
    
    // Get input from user then delete new line at end of string, which comes with fgets function
    fgets(input, STRSIZ, stdin);
    delete_newline(input);

    // Determine operation
    arguments_count = divide_arguments(input, arguments);
    if(arguments[0][1] == '*')
      operation = '^';
    else
      operation = arguments[0][0];
    
    // Get numbers from string-
    numbers[0] = atoi(arguments[1]);
    if(arguments_count > 2)
      numbers[1] = atoi(arguments[2]);

    // Operator switch
    switch(operation) {
      case '+':
        if(arguments_count == 2)
          result = doit(add, result, numbers[0]);
        else if(arguments_count == 3)
          result = doit(add, numbers[0], numbers[1]);
        break;

      case '-':
        if(arguments_count == 2)
          result = doit(sub, result, numbers[0]);
        else if(arguments_count == 3)
          result = doit(sub, numbers[0], numbers[1]);
        break;

      case '*':
        if(arguments_count == 2)
          result = doit(mul, result, numbers[0]);
        else if(arguments_count == 3)
          result = doit(mul, numbers[0], numbers[1]);
        break;

      case '/':
        if(arguments_count == 2)
          result = doit(divi, result, numbers[0]);
        else if(arguments_count == 3)
          result = doit(divi, numbers[0], numbers[1]);
        break;

      case '^':
        if(arguments_count == 2)
          result = doit(powe, result, numbers[0]);
        else if(arguments_count == 3)
          result = doit(powe, numbers[0], numbers[1]);
        break;

      case '%':
        if(arguments_count == 2)
          result = doit(mod, result, numbers[0]);
        else if(arguments_count == 3)
          result = doit(mod, numbers[0], numbers[1]);
        break;

      default:
        break;
    }

      printf("%d\n", result);
  }
}

int add(int number1, int number2) 
{
  int result;
  result = number1 + number2;
  return result;
}

int sub(int number1, int number2) 
{
  int result;
  result = number1 - number2;
  return result;
}

int mul(int number1, int number2) 
{
  int result;
  result = number1 * number2;
  return result;
}

int divi(int number1, int number2) 
{
  int result;
  result = number1 / number2;
  return result;
}

int powe(int number1, int number2) 
{
  int i, result=1;
  for(i = 0; i < number2; i++)
    result = result * number1;
  return result;
}

int mod(int number1, int number2) 
{
  int result;
  result = number1 % number2;
  return result;
}

// Doit calls nested function
int doit(int fun(), int first_number, int second_number)
{
  int result;
  result = fun(first_number, second_number);
  return result;
}

// Function that draws a diamond
void draw_a_diamond()
{
  int i, input, j, k, l;

  // gets length from user
  printf("Length= ");
  scanf("%d", &input);


  for(i = input * -1; i<=input; i++)
  {
    if(i != 0)
    {
      for(j = 0; j < abs(i) - 1 ; j++)
      { 
        printf(" ");
      }

      if(i < 0)
        printf("/");
      else if(i > 0)
        printf("\\");

      for(k = 0; k < ( input - abs(i) ) * 2; k++)
      {
        printf("*");
      }

      if(i < 0)
        printf("\\");
      else if(i > 0)
        printf("/");

      printf("\n");
    }
  }
}

int take_grades(int arr[])
{
  int i;
  for(i = 0; i < 10; i++)
  {
    printf("Enter grade #%d: ", i+1);
    scanf("%d",&arr[i]);
    while(arr[i] > 100 || arr[i] < 0)
    {
      printf("Enter a number between 0 and 100: ");
      scanf("%d", &arr[i]);
    }
  }

  return 0;
}

int take_exam_grades(int arr[])
{
  int i;
  printf("Enter midterm grade: ");
  scanf("%d", &arr[0]);
  while(arr[0] > 100 || arr[0] < 0)
  {
    printf("Enter a number between 0 and 100: ");
    scanf("%d", &arr[0]);
  }
  printf("Enter final grade: ");
  scanf("%d", &arr[1]);
  while(arr[1] > 100 || arr[1] < 0)
  {
    printf("Enter a number between 0 and 100: ");
    scanf("%d", &arr[1]);
  }

  return 0;
}

double calculate_homework(int hw_grades[]) 
{
  double sum=0.0, average;
  int i;

  for(i = 0; i < 10; i++)
  {
    sum = sum + (double) hw_grades[i];
  }

  average = sum / 10.0;

  return average;

}

double calculate_lab(int lab_grades[]) 
{
  double sum=0.0, average;
  int i;

  for(i = 0; i < 10; i++)
  {
    sum = sum + (double) lab_grades[i];
  }

  average = sum / 10.0;

  return average;

}

double calculate_all(int hw, int exam_grades[], int lab) 
{
  double average;
  average = 0.1 * hw + 0.2 * lab + 0.3 * exam_grades[0] + 0.4 * exam_grades[1];
  return average;
}

void calc_average_of_grades() 
{
  int hw_grades[10], lab_grades[10], exam_grades[2], i;
  double hw_avg, lab_avg, weighted_average;

  printf("\nHOMEWORK GRADES:\n");
  take_grades(hw_grades);

  printf("\nLABORATORY GRADES:\n");
  take_grades(lab_grades);

  printf("\nEXAM GRADES:\n");
  take_exam_grades(exam_grades);

  hw_avg = calculate_homework(hw_grades);
  
  lab_avg = calculate_lab(lab_grades);

  weighted_average = calculate_all((int) hw_avg, exam_grades, (int) lab_avg );

  printf("Your weighted average is %.2lf\n", weighted_average);
}