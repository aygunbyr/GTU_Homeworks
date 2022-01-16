#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constant definitions
#define COUNT_OF_POKEMONS 10
#define POCKET_LIMIT 4

// Enumerations for pokemons and attack types of pokemons
enum attack_type {linear, quadratic};
enum pokemon {Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby, Empty_slot};

// Function prototypes
void pokedex (char Pokemon_name[10][11], int range[], enum attack_type type[], int attack_power[], int stamina[]);
void oaks_laboratory (char Pokemon_name[10][11], enum pokemon Pokemons[], enum pokemon *my_Pokemons);
void show_Pokemons (char Pokemon_name[10][11], enum pokemon Pokemons[], int pokemon_count);
void catch_a_pokemon (char Pokemon_name[10][11], enum pokemon Pokemons[], enum pokemon *my_pocket);
void release_a_pokemon (char Pokemon_name[10][11], enum pokemon Pokemons[], enum pokemon *my_pocket);
void battle (char Pokemon_name[10][11], int range[], enum attack_type type[], int attack_power[], int stamina[], enum pokemon user_Pokemons[]);
void show_area (char Pokemon_name[10][11], int area[8][8], int pokemon_staminas_view[8][8]);
void main_menu ( enum pokemon user_Pokemons[] );
int are_strings_equal (char str[], char str2[]);
int is_in_pocket (enum pokemon Pokemon_ID, enum pokemon *my_pocket);
void move_pokemon ( int area[8][8], int pokemon_staminas_view[8][8],enum pokemon user_Pokemons[], int pokemon_x, int pokemon_y, int dest_x, int dest_y);

// Main function
int main() {
  // User's pocket whic6,1h is empty as default
  enum pokemon users_pocket[4] = {10, 10, 10, 10};

  // For random number generation
  srand(time(NULL));

  // Call menu function
  main_menu( users_pocket );
  
  return 0;
}

void pokedex(char Pokemon_name[10][11], int range[], enum attack_type type[], int attack_power[], int stamina[])
{
  int i;
  char pokemon_name[11]; 

  printf("Please type name of the Pokémon (type exit to close Pokedex):");
  scanf("%s", pokemon_name);

  for(i = 0; i < COUNT_OF_POKEMONS; i++)
  {
    // When pokemon found in pokedex
    if( are_strings_equal(Pokemon_name[i], pokemon_name) == 1 )
    {
      // Print all specifications of the pokémon
      printf("Name : %s\n", Pokemon_name[i]);
      printf("A. Type : ");
      switch( type[i] )
      {
        case linear:
          printf("Linear\n");
          break;

        case quadratic:
          printf("Quadratic\n");
          break;

        default:
          break;
      }
      printf("Range : %d block(s)\n", range[i]);
      printf("A. Power : %d\n", attack_power[i]);
      printf("Stamina : %d\n", stamina[i]);
    }
  }
}

void oaks_laboratory (char Pokemon_name[10][11], enum pokemon Pokemons[], enum pokemon *my_Pokemons)
{
  int choice = 0;

  // This is Oak's Laboratory menu.

  printf("Welcome to Laboratory of Professor Oak. How can I help you?\n\n1) Show Pokémons\n2) Catch a Pokémon\n3) Release a Pokémon\n4) Show my pocket\n5) Back\nChoice:");
  scanf("%d", &choice);

  switch(choice){
    case 1:
      show_Pokemons( Pokemon_name, Pokemons, COUNT_OF_POKEMONS );
      break;

    case 2:
      catch_a_pokemon( Pokemon_name, Pokemons, my_Pokemons );
      break;

    case 3:
      release_a_pokemon( Pokemon_name, Pokemons, my_Pokemons );
      break;

    case 4:
      show_Pokemons( Pokemon_name, my_Pokemons, POCKET_LIMIT );
      break;

    case 5:
      main_menu( my_Pokemons );
      break;

    default:
      break;
  }
}

void show_Pokemons (char Pokemon_name[10][11], enum pokemon Pokemons[], int pokemon_count)
{
  int i;
  for(i = 0; i < pokemon_count; i++)
  {
    if(Pokemons[i] >= Charmander && Pokemons[i] <= Krabby)
      printf("%d - %s\n", Pokemons[i], Pokemon_name[Pokemons[i]]);  
    else if(Pokemons[i] == Empty_slot)
      printf("<Empty slot>\n");
  }
}

void catch_a_pokemon (char Pokemon_name[10][11], enum pokemon Pokemons[], enum pokemon *my_pocket) 
{
  int empty_slot, i, not_in_pocket = 1, empty_in_pocket = 0, empty_index;
  enum pokemon pokemon_to_catch;

  // Let user know what are pokemons that he/she can catch
  show_Pokemons(Pokemon_name, Pokemons, COUNT_OF_POKEMONS);

  printf("Enter ID of pokemon to catch: ");
  scanf("%d", &pokemon_to_catch);

  if( is_in_pocket(pokemon_to_catch, my_pocket) )
    not_in_pocket = 0;

  for(i = 0; i < 4; i++)
  {
    if(my_pocket[i] == Empty_slot)
    {
      if(empty_in_pocket == 0)
      {
        empty_index = i;
        empty_in_pocket = 1;
      }
    }
  }

  if(not_in_pocket && empty_in_pocket && pokemon_to_catch >= Charmander && pokemon_to_catch <= Krabby)
  {
    printf("You catched %s. Gotta catch 'em all!\n", Pokemon_name[pokemon_to_catch]);
    my_pocket[empty_index] = pokemon_to_catch;
  }
  else
  {
    printf("You could not catch %s.", Pokemon_name[pokemon_to_catch]);
    if( ! not_in_pocket )
      printf(" You already have this pokemon.");
    putchar('\n');
  }
}

void release_a_pokemon (char Pokemon_name[10][11], enum pokemon Pokemons[], enum pokemon *my_pocket) 
{
  int i, is_in_pocket = 0, pokemons_in_pocket = 4, index_in_pocket;
  enum pokemon pokemon_to_release;

  // Show pokemons in users pocket
  show_Pokemons( Pokemon_name, my_pocket, POCKET_LIMIT );

  // Check is pocket empty or not
  for(i = 0; i < 4; i++)
    if(my_pocket[i] == Empty_slot)
      pokemons_in_pocket--;

  if(pokemons_in_pocket == 0)
    printf("You do not have any pokemon to release!\n");
  else
  {
    printf("Enter ID of pokemon to release: ");
    scanf("%d", &pokemon_to_release);
    for(i = 0; i < 4; i++)
    {
      if(my_pocket[i] == pokemon_to_release)
      {
        is_in_pocket = 1;
        index_in_pocket = i;
      }
    }
    if( is_in_pocket )
    {
      printf("You released the pokemon %s!\n", Pokemon_name[pokemon_to_release]);
      my_pocket[index_in_pocket] = Empty_slot;
    }
    else
    {
      printf("You don't have this pokemon!\n");
    }
  }
}

void battle (char Pokemon_name[10][11], int range[], enum attack_type type[], int attack_power[], int stamina[], enum pokemon user_Pokemons[]) 
{
  int i, is_users_pocket_full = 1, coord_x, coord_y, pokemon_staminas_view[8][8], area[8][8]=
    {
      {10,10,10,10,10,10,10,10},
      {10,10,10,10,10,10,10,10},
      {10,10,10,10,10,10,10,10},
      {10,10,10,10,10,10,10,10},
      {10,10,10,10,10,10,10,10},
      {10,10,10,10,10,10,10,10},
      {10,10,10,10,10,10,10,10},
      {10,10,10,10,10,10,10,10}
    };
  int pokemon_x, pokemon_y, dest_x, dest_y, no_end = 1;
  enum pokemon AI_Pokemon, AI_pocket[4];
  
  // Check user's pocket
  if( is_in_pocket( Empty_slot, user_Pokemons ) )
      is_users_pocket_full = 0;

  if( is_users_pocket_full )
  {
    printf("Welcome to the tournament! To start, pick your pokemons and place in battle area.\nYou can place your pokemons on first two rows. 6 <= x <= 7 and, 0 <= y <= 7\nExample input: 7,0\n");

    show_Pokemons( Pokemon_name, user_Pokemons, POCKET_LIMIT );

    for(i = 0; i < 4; i++)
    {
      // If conditions are provided, pokemon will be placed.
      do
      {
        printf("You picked %s. Enter a coordinate to place it: ", Pokemon_name[ user_Pokemons[i] ] );
        scanf( "%d,%d", &coord_x, &coord_y );
      } while (area[coord_x][coord_y] != Empty_slot || coord_x < 6 || coord_x > 7 || coord_y < 0 || coord_y > 7 );

      // Place this pokemon and add its stamina to array
      area[coord_x][coord_y] = user_Pokemons[i];
      pokemon_staminas_view[coord_x][coord_y] = stamina[ user_Pokemons[i] ];

    }

    // Add Articial Intelligence's pokemons
    for(i = 0; i < 4; i++)
    {
      // AI takes pokemons randomly
      do
      {
        AI_Pokemon = rand() % 10;
      } while( is_in_pocket (AI_Pokemon, AI_pocket) );
      AI_pocket[i] = AI_Pokemon;

      // Set pokemon's location randomly but empty before placing
      do
      {
        coord_x = rand() % 2; // x is between 0 and 1
        coord_y = rand() % 8; // y is between 0 and 7
      } while( area[coord_x][coord_y] != Empty_slot );
      area[coord_x][coord_y] = AI_Pokemon;

      // Set pokemon's stamina
      pokemon_staminas_view[coord_x][coord_y] = stamina[ AI_pocket[i] ];
    }

    // Show battle area
    show_area(Pokemon_name, area, pokemon_staminas_view);
    while(no_end) 
    {
      do 
      {
        printf("Enter pokemon's coordinate to pick pokemon (x,y): ");
        scanf("%d,%d", &pokemon_x, &pokemon_y);
      } while ( ! is_in_pocket( area[pokemon_x][pokemon_y] , user_Pokemons ) );

      printf("Enter destination to move (max. 2 blocks) (x,y): ");
      scanf("%d,%d", &dest_x, &dest_y);

      move_pokemon( area, pokemon_staminas_view, user_Pokemons, pokemon_x,pokemon_y,dest_x, dest_y);

      show_area(Pokemon_name, area, pokemon_staminas_view);
    }
  }
  else
  {
    printf("To enter the tournament, you must have at least four pokemons. Come back later!\n");
  }
}

void show_area (char Pokemon_name[10][11], int area[8][8], int pokemon_staminas_view[8][8])
{
  int dl, i, n, s; // dl for dash line, i for all pokemons, n for names, s for staminas
  enum pokemon myPokemon;

  // Prints dash line
  for(dl = 0; dl <= 56; dl++) 
    putchar('-');
  putchar('\n');

  // Prints a row (8 blocks)
  for(i = 0; i < 8; i++) 
  {
    putchar('|'); // border of block

    // Prints first two letters of pokemon's name
    for(n = 0; n < 8; n++) 
    {
      myPokemon = area[i][n];
      if(myPokemon != Empty_slot)
        printf("  %c%c  ", Pokemon_name[myPokemon][0], Pokemon_name[myPokemon][1]);
      else
        printf("      ");
      putchar('|'); // border of block
    }
    printf("\n|");

    // Prints pokemon's stamina
    for(s = 0; s < 8; s++) {
      myPokemon = area[i][s];
      if(myPokemon != Empty_slot)
        printf("(%d)", pokemon_staminas_view[i][s]);
      else
        printf("      ");
      putchar('|'); // border of block
    }
    putchar('\n');

    // Prints dash line
    for(dl = 0; dl <= 56; dl++) 
      putchar('-');
    putchar('\n');
  }
}

void main_menu ( enum pokemon user_Pokemons[] ) {
  char Pokemon_name[10][11] = 
  {
    {'C', 'h', 'a', 'r', 'm', 'a', 'n', 'd', 'e', 'r', '\0'},
    {'P', 'i', 'k', 'a', 'c', 'h', 'u', '\0'},
    {'S', 'q', 'u', 'i', 'r', 't', 'l', 'e', '\0'},
    {'B', 'u', 'l', 'b', 'a', 's', 'a', 'u', 'r', '\0'},
    {'P', 'i', 'd', 'g', 'e', 'o', 't', 't', 'o','\0'},
    {'R', 'a', 't', 'a', 't', 'a', '\0'},
    {'M', 'u', 'g', '\0'},
    {'C', 'a', 't', 'e', 'r', 'p', 'i', 'e', '\0'},
    {'Z', 'u', 'b', 'a', 't', '\0'},
    {'K', 'r', 'a', 'b', 'b', 'y', '\0'}
  };
  int range[10] = {1, 3, 4, 3, 2, 2, 1, 2, 3, 2};
  enum attack_type type[10] = {quadratic, linear, linear, linear, quadratic, linear, quadratic, quadratic, linear, linear};
  int attack_power[10] = {500, 350, 300, 400, 250, 250, 350, 200, 350, 300};
  int stamina[10] = {2200, 1500, 1700, 2500, 1900, 2500, 3000, 1200, 1250, 2600};
  enum pokemon Pokemons[10] = {Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby};
  int choice = 0, infinite_loop = 1;

  while( infinite_loop ){
    printf("Please select an option to continue:\n1) Open Pokedex\n2) Go to Oak's Laboratory\n3) Enter the tournament\nChoice:");
    scanf("%d", &choice);
    
    switch(choice){
      case 1:
        pokedex(Pokemon_name, range, type, attack_power, stamina);
        break;

      case 2:
        oaks_laboratory(Pokemon_name, Pokemons, user_Pokemons);
        break;

      case 3:
        battle(Pokemon_name, range, type, attack_power, stamina, user_Pokemons);
        break;

      default:
        break;
    }
  }
}

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

int is_in_pocket (enum pokemon Pokemon_ID, enum pokemon *my_pocket)
{
  int i, result=0;
  for(i = 0; i < 4; i++)
    if(my_pocket[i] == Pokemon_ID)
      result = 1;

  return result;
}

void move_pokemon ( int area[8][8], int pokemon_staminas_view[8][8],enum pokemon user_Pokemons[], int pokemon_x, int pokemon_y, int dest_x, int dest_y)
{
  enum pokemon myPokemon = area[pokemon_x][pokemon_y];
  // You can not move to out of battle area and destination must be empty
  if( dest_x > 7 || dest_x < 0 || dest_y > 7 || dest_y < 0 || area[dest_x][dest_y] != Empty_slot ) 
  {
    printf("You can not do this move.\n");
  } else
  if( pokemon_x == dest_x ) // move on y-axis
  {
    if(dest_x - pokemon_x >= -2 && dest_x - pokemon_x <= 2)
    {
      area[dest_x][dest_y] = myPokemon;
      pokemon_staminas_view[dest_x][dest_y] = pokemon_staminas_view[pokemon_x][pokemon_y];
      area[pokemon_x][pokemon_y] = Empty_slot;
      pokemon_staminas_view[pokemon_x][pokemon_y] = 0;
    }
  } else
  if( pokemon_y == dest_y ) // move on x-axis
  {
    if(dest_y - pokemon_y >= -2 && dest_y - pokemon_y <= 2)
    {
      area[dest_x][dest_y] = myPokemon;
      pokemon_staminas_view[dest_x][dest_y] = pokemon_staminas_view[pokemon_x][pokemon_y];
      area[pokemon_x][pokemon_y] = Empty_slot;
      pokemon_staminas_view[pokemon_x][pokemon_y] = 0;
    }
  }
  else
  {
    printf("You can not do this move.\n");
  }
}