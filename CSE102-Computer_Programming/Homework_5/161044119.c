#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

// Directions are pre-defined
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define LEFT_UP 5
#define RIGHT_UP 6
#define LEFT_DOWN 7
#define RIGHT_DOWN 8

int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

/* Function that returns a random character (lowercase letter) */
char random_character()
{
  char c = (char) ( rand() % 26 ) + 'a';
  return c;
}

/* Function that prints puzzle */
void print_puzzle(char puzzle[15][15])
{
  int i, j;
  for(i = 0; i < 15; i++)
  {
    for(j = 0; j < 15; j++)
      printf("%c", puzzle[i][j]);
    printf("\n");
  }
}

/* Function that returns uppercase equivalent of lowercase letter */
char to_upper(char c)
{
  c = (char) c - 32;
  return c;
}

/* Function that returns lowercase quivalent of uppercase letter */
char to_lower(char c)
{
  c = (char) c + 32;
  return c;
}

/* Function that checks are strings same or not */
int are_strings_equal (char str[], char str2[]) {
  int i = 0, result = 1;
  while(str[i] != '\0' || str2[i] != '\0')
  {
    if(str[i] != str2[i])
      result = 0;
    i++;
  }
  
  return result;
}

/* Function that places words in puzzle board */
void place_words_in_puzzle(char puzzle[15][15], char *dict[DICT_SIZE], int coord[DICT_SIZE][4])
{
  int i, j, len, x1, y1, x2, y2, x, y;
  // At first, fill puzzle with random characters
  for(i = 0; i < 15; i++)
    for(j=0; j<15; j++)
      puzzle[i][j] = random_character();

  // Place words from dictionary
  for(i = 0; i < DICT_SIZE; i++) 
  {
    len = get_line_size( dict[i] );
    x = coord[i][0];
    y = coord[i][1];
    x2 = coord[i][2];
    y2 = coord[i][3];

    for(j = 0; j < len; j++)
    {
      puzzle[x][y] = dict[i][j];

      if(x > x2)
        x--;
      else if(x2 > x)
        x++;

      if(y > y2)
        y--;
      else if(y2 > y)
        y++;
    }
  }
}

/* Function that inverts a string */
char * invert_string(char string[LINE_LEN]) //char *
{
  int i, len;
  char reverse_str[LINE_LEN];
  len = get_line_size( string );
  for(i = 0; i < len; i++)
  {
    reverse_str[i] = string[len - i - 1];
  }
  reverse_str[len] = '\0';

  copy_string( reverse_str, string );

  return string;
}

/* Function that searchs a word in puzzle */
int search_word(char puzzle[15][15], char word[LINE_LEN], int x1, int y1)
{
  int counter, direct, i, j, len, ret = 0, x, y;
  len = get_line_size( word );

  for( direct=1; direct <= 8; direct++)
  {
    x = x1;
    y = y1;
    counter = 0;

    for( i = 0; i < len; i++)
    {
      if(word[i] == puzzle[x][y] || word[i] == to_lower( puzzle[x][y] ) ) 
        counter++;

      // there are 8 directions
      switch( direct )
      {
        case UP:
          x--;
          break;
          
        case DOWN:
          x++;
          break;
            
        case LEFT:
          y--;
          break;

        case RIGHT:
          y++;
          break;
            
        case LEFT_UP:
          x--;
          y--;
          break;
          
        case RIGHT_UP:
          x--;
          y++;
          break;
          
        case LEFT_DOWN:
          x++;
          y--;
          break;

        case RIGHT_DOWN:
          x++;
          y++;

        default:
          break;
      }
    }

    if(counter == len)
      {
        ret = 1;
        // If word is found, make them upper case
        for(j = 0; j < len; j++)
        {
          if(x > x1)
            x--;
          else if(x < x1)
            x++;

          if(y > y1)
            y--;
          else if(y < y1)
            y++;
            
          puzzle[x][y] = to_upper( puzzle[x][y] );
        }
        break;
      }
  }

  return ret;
}

int main(){
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
	FILE *fp = fopen("word_hunter.dat", "r");
  char puzzle[15][15];
  char input[LINE_LEN], word[LINE_LEN];
  int ret, ret2, word_found_count = 0, x, y;
  // Random number generation
  srand(time(NULL));
	
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);

  // Place words in puzzle
  place_words_in_puzzle(puzzle, dict, coord);
  
  // Stop game when user enters "exit game"
  do 
  {
    // At first, prints puzzle
    print_puzzle(puzzle);
    // Get input from user to let him/her play
    printf("Enter a word (or type exit game) : ");
    fgets(word, LINE_LEN, stdin);
    remove_newline( word );

    if( ! are_strings_equal( word, "exit game") )
    {
      printf("Enter coordinate x: ");
      fgets(input, LINE_LEN, stdin);
      x = atoi( input );
      printf("Enter coordinate y: ");
      fgets(input, LINE_LEN, stdin);
      y = atoi( input );
      // Check that do user found a word or not
      ret = search_word(puzzle, word, x, y);
      ret2 = search_word(puzzle, invert_string( word ) , x, y);
      if( ret || ret2 )
      {
        word_found_count++;
        printf("Word was found in puzzle. Remaining words = %d\n", 15 - word_found_count );
      }
      else
        printf("Word was not found.\n");
    }
  } while ( ! are_strings_equal( word, "exit game" ) && word_found_count != 15 );

  // End Game
  if(word_found_count == 15)
  {
    print_puzzle( puzzle );
    printf("You have found all words in puzzle. YOU WIN!\n");
  }
		
	return 0;
}