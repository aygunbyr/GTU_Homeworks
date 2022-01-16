#include <stdio.h>

// Part 1
int common(int n1, int n2, int divisor)
{
  // Keep running if divisor less than n1 and n2
  if(divisor > n1 || divisor > n2)
    return 1;
  else
  {
    if(n1 % divisor == 0 && n2 % divisor == 0)
    {
      // update n1 and n2
      n1 /= divisor;
      n2 /= divisor;
      // recursion
      return divisor * common(n1, n2, divisor);
    }
    else
      return common(n1,n2, divisor+1);
  }
}

// Part 2
// Helper function: Merges two subarrays of arr[].
void birlestir(int dizi[], int sol, int orta, int sag) 
{ 
    int i, j, k; 
    int boyut1 = orta - sol + 1; 
    int boyut2 =  sag - orta; 
    int Sol[boyut1], Sag[boyut2]; 
  
    // Copy main array to two arrays
    for (i = 0; i < boyut1; i++) 
        Sol[i] = dizi[sol + i]; 
    for (j = 0; j < boyut2; j++) 
        Sag[j] = dizi[orta + 1 + j]; 
  
    // Merge temp arrays Sol[] and Sag[]
    i = 0;
    j = 0;
    k = sol;
    while (i < boyut1 && j < boyut2) 
    { 
        if (Sol[i] <= Sag[j]) 
        { 
            dizi[k] = Sol[i]; 
            i++; 
        } 
        else
        { 
            dizi[k] = Sag[j]; 
            j++; 
        } 
        k++; 
    } 
  
    // swap in left
    while (i < boyut1) 
    { 
        dizi[k] = Sol[i]; 
        i++; 
        k++; 
    } 
  
    // swap in right
    while (j < boyut2) 
    { 
        dizi[k] = Sag[j]; 
        j++; 
        k++; 
    } 
} 
  
/* It divides array to two subarrays */
void birlestirmeSiralamasi(int dizi[], int sol, int sag) 
{
  int orta; 
    if (sol < sag) 
    { 
        // It prevents overflow
        orta = sol+(sag-sol) / 2; 
  
        // Sort two halves 
        birlestirmeSiralamasi(dizi, sol, orta); // from left to middle
        birlestirmeSiralamasi(dizi, orta + 1, sag); // from middle + 1 to right
  
        birlestir(dizi, sol, orta, sag); // recursion
    } 
} 

// Part 3
void fun_two_conditions(int n)
{
  printf("%d ", n);
  if(n == 1)
    return;   
  if(n % 2 == 0)
    fun_two_conditions(n/2);
  else 
  if(n % 2 == 1)
    fun_two_conditions(3*n+1);
}

// Recursive power (helper function)
int power(int num, int exp)
{
  if(num==0)
    return 0;
  else
  if(exp==0)
    return 1;
  else
    return num * power(num, exp-1);
}

// Recursive total of powers of digits (helper function)
int power_digits(int num, int n, int total)
{
  if(num==0)
    return 0;
  else
  {
    total += power(num % 10, n);
    // Go to left digit by diving number by ten
    return total + power_digits(num/10, n, 0);
  }
}

// Part 4
void is_number_fits(int number, int n, int total)
{
  total = power_digits(number, n, 0);
  if(total == number)
  {
    printf("Equal");
    return; // Stop function
  } else
  if(total > number)
  {
    printf("Not equal");
    return; // Stop function
  }
  else if(total < number) 
  {
    // Continue by increasing n
    is_number_fits(number, n + 1, 0);
  }
}

// Part 5
void findFirstCapital(char *str)
{
  if(*str != '\0') {
    // If it is a capital letter, print
    if(*str >= 'A' && *str <= 'Z')
    {
      putchar(*str);
      return;
    }
    else // Keep searching
      findFirstCapital(++str);
  }
}

int main(void) {
  char string[36];
  printf("Welcome to Homework 6!\n");
  int i, secim, num, num2, result, dizi[30], dizi_boyutu;
  char input_string[40];
  do {
    printf("1. Part 1: Find Greatest Common Divisor\n2. Part 2: Merge Sort\n3. Part 3: Function with Two Conditions\n4. Part 4: Is Number Fits Formula\n5. Part 5: Find First Capital Letter in String\n6. Exit program\nChoice:");
    scanf("%d", &secim);

    switch( secim ) {
      case 1:
        printf("Enter two numbers (n1 n2): ");
        scanf("%d %d", &num, &num2);
        result = common(num, num2, 2);
        printf("GCD(%d, %d): %d \n", num, num2, result);
        break;

      case 2:
        // Merge sort part
        printf("Enter the length of the list: ");
        scanf("%d", &dizi_boyutu);
        if(dizi_boyutu > 0)
        {
          printf("Enter the elements of list:\n");
          for(i = 0; i < dizi_boyutu; i++)
            scanf("%d", &dizi[i]);
        }
        birlestirmeSiralamasi(dizi, 0, dizi_boyutu - 1); 
        printf("Sorted array is:");
        for(i = 0; i < dizi_boyutu; i++)
          printf(" %d", dizi[i]);
        printf(".\n");
        break;

      case 3:
        printf("Enter a number: ");
        scanf("%d", &num);
        fun_two_conditions(num);
        printf("\n");
        break;

      case 4:
        printf("Enter a number to check: ");
        scanf("%d", &num);
        is_number_fits(num, 0, 0);
        printf("\n");
        break;

      case 5:
        printf("Enter a string without space: ");
        scanf("%s", input_string);
        findFirstCapital( input_string );
        printf("\n");
        break;

      case 6:
        break;

      default:
        printf("Invalid choice!\n");
        break;
    }

  } while(secim != 6);
  
  return 0;
}