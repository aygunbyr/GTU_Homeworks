#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {noone, cap, car} player_type;
typedef enum {start, property, tax, punish} block_type;

#define NO_PROPERTY -1

struct player {
  player_type type;
  int current_block_id;
  int account;
  int turn_to_wait;
  char *name;
  int owned_block_ids[11];
};

struct block {
  int block_id;
  char *name;
  int price;
  int rent;
  int rent_1;
  int rent_2;
  int rent_3;
  int house_price;
  int house_count;
  struct player owner;
  block_type type;
};

void print_char(char c, int count)
{
  int i;
  for(i=0; i<count; i++)
    printf("%c", c);
}

int roll_the_dice()
{
  int r;
  r = rand() % 6 + 1;
  return r;
}

void print_block_line(struct block board, int line_no, struct player player_one, struct player player_two)
{
  int i, j, name_len, tab_c;

  printf("|");
  print_char(' ', 8);

  switch( line_no )
  {
    case 1:
      name_len = printf("%s", board.name);
      print_char(' ', 16-name_len);
      break;

    case 2:
      if(board.price > 0 || board.rent > 0)
      {
        if(board.type == tax)
          printf("%d$", board.rent);
        else if(board.type == property)
          printf("%d$", board.price);
        print_char(' ', 12);
      }
      else
        print_char(' ', 16);
      if(board.type == punish)
        print_char(' ', 4);
      break;

    case 3:
      tab_c=4;
      if(player_one.current_block_id == board.block_id)
      {
        name_len = printf("%s ", player_one.name);
        tab_c--;
      }
      if(player_two.current_block_id == board.block_id)
      {
        name_len = printf("%s ", player_two.name);
        tab_c--;
      }
      print_char(' ', tab_c*4);
      break;

    default:
      break;
  }
}

void init_the_board(struct block board[20])
{
  struct player no_one;
  no_one.type = noone;

  struct block b0 = {0, "Start", 0, 0, 0, 0, 0, 0, 0, no_one, start};
  board[0] = b0;

  struct block b1 = {1, "Esenyurt", 16000, 800, 4000, 9000, 25000, 10000,0, no_one, property};
  board[1] = b1;

  struct block b2 = {2, "Car Park", 0, 1500, 0, 0, 0, 0, 0, no_one, tax};
  board[2] = b2;

  struct block b3 = {3, "Tuzla", 16500, 850, 4250, 9500, 26000, 12000, 0, no_one, property};
  board[3] = b3;

  struct block b4 = {4, "Arnavutkoy", 17000, 875, 4500, 10000, 28000, 12000, 0, no_one, property};
  board[4] = b4;

  struct block b5 = {5, "Wait 2 Turn", 0, 2, 0, 0, 0, 0, 0, no_one, punish};
  board[5] = b5;

  struct block b6 = {6, "Catalca", 20000, 1000, 5000, 12000, 30000, 13000, 0, no_one, property};
  board[6] = b6;

  struct block b7 = {7, "Beykoz", 23000, 1100, 5500, 12500, 33000, 13000, 0, no_one, property};
  board[7] = b7;

  struct block b8 = {8, "Car Fix", 0, 1750, 0, 0, 0, 0, 0, no_one, tax};
  board[8] = b8;

  struct block b9 = {9, "Maltepe", 30000, 1350, 7000, 15000, 40000, 15000, 0, no_one, property};
  board[9] = b9;

  struct block b10 = {10, "Bills", 0, 2000, 0, 0, 0, 0, 0, no_one, tax};
  board[10] = b10;

  struct block b11 = {11, "Sisli", 33000, 1500, 8000, 16000, 42000, 16000,0, no_one, property};
  board[11] = b11;

  struct block b12 = {12, "Oil", 0, 2250, 0, 0, 0, 0, 0, no_one, tax};
  board[12] = b12;

  struct block b13 = {13, "Atasehir", 35000, 1600, 8500, 17000, 45000, 17000, 0, no_one, property};
  board[13] = b13;

  struct block b14 = {14, "Sariyer", 40000, 1750, 9500, 19000, 48000, 19000, 0, no_one, property};
  board[14] = b14;

  struct block b15 = {15, "Wait 1 Turn", 0, 1, 0, 0, 0, 0, 0, no_one, punish};
  board[15] = b15;

  struct block b16 = {16, "Kadikoy", 43000, 1900, 11000, 21500, 55000, 23000, 0, no_one, property};
  board[16] = b16;

  struct block b17 = {17, "Besiktas", 60000, 2500, 15000, 28000, 60000, 30000, 0, no_one, property};
  board[17] = b17;

  struct block b18 = {18, "Vocation", 0, 5000, 0, 0, 0, 0, 0, no_one, tax};
  board[18] = b18;

  struct block b19 = {19, "Bebek", 70000, 3500, 20000, 35500, 65000, 35000, 0, no_one, property};
  board[19] = b19;

}

void show_board(struct block board[20], struct player player_one, struct player player_two)
{
  int i, j;

  /* Part 1: Top */
  // Dash Line
  print_char('-', 145);
  printf("\n");
  // This loop prints three lines of block
  for(i=1; i<=3; i++)
  {
    for(j=0; j<6; j++)
      print_block_line(board[j], i, player_one, player_two);
    printf("|\n");
  }
  // Dash Line
  print_char('-', 145);
  printf("\n");

  /* Part 2: Middle */
  for(i=0; i<4; i++)
  {
    // This loop prints three lines of block
    for(j=1; j<=3; j++)
    {
      print_block_line(board[19-i], j, player_one, player_two);
      printf("|");
      print_char(' ', 95);
      print_block_line(board[19-(13-i)], j, player_one, player_two);
      printf("|\n");
    }
    if(i < 3)
    {
      print_char('-', 25);
      print_char(' ', 95);
      print_char('-', 25);
      printf("\n");
    }
  }

  /* Part 3: Footer */
  // Dash Line
  print_char('-', 145);
  printf("\n");
  // This loop prints three lines of block
  for(i=1; i<=3; i++)
  {
    for(j=15; j>=10; j--)
      print_block_line(board[j], i, player_one, player_two);
    printf("|\n");
  }
  // Dash Line
  print_char('-', 145);
  printf("\n");
  
}

void show_deed(struct block myblock)
{
  int i, name_len;
  print_char('-', 33);
  printf("\n|");
  print_char(' ', 12);
  name_len = printf("%s", myblock.name);
  print_char(' ', 20-name_len);

  printf("|\n");
  print_char('-', 33);

  printf("\n|");
  print_char(' ', 8);
  printf("Rent");
  print_char(' ', 12);
  printf("%d$", myblock.rent);
  print_char(' ', 4);

  for(i=1; i<=3; i++)
  {
    printf("|\n|");
    print_char(' ', 8);
    printf("Rent 1 H");
    print_char(' ', 8);
    if(i==1)
      printf("%d$", myblock.rent_1);
    else if(i==2)
      printf("%d$", myblock.rent_2);
    else if(i==3)
      printf("%d$", myblock.rent_3);
    print_char('\t', 1);
  }

  printf("|\n");
  print_char('-', 33);

  printf("\n|");
  print_char(' ', 8);
  printf("House Price");
  print_char(' ', 8);
  printf("%d$", myblock.house_price);
  print_char(' ', 4);

  printf("|\n");
  print_char('-', 33);
}

void show_properties(struct block board[20])
{
  int choice=-1, i, j;
  while(!(choice == 0 || board[choice].type == property))
  {
    printf("Please select a property to see details:\n");
    for(i=0; i<20; i++)
      if(board[i].type == property)
        printf("%d - \t%s\n", i, board[i].name);
    printf("0 - \tExit\nChoice: ");
    scanf("%d", &choice);
  }

  if(board[choice].type == property)
  {
    print_char('\n', 3);
    show_deed( board[choice] );
    printf("\n");
  }
}

void show_my_properties(struct block board[20], struct player* current_player)
{
  int i, id;
  for(i=0; i<11; i++)
    if(current_player->owned_block_ids[i] != NO_PROPERTY)
    {
      id = current_player->owned_block_ids[i];
      printf("%d - %s\n", board[id].block_id, board[id].name);
    }
}

void buy_house(struct block* current_block, struct player* current_player)
{
  int able_to_construct, user_cons;
  // buying houses
  if(current_player->account < current_block->house_price)
    printf("You don't have enough money to construct any house.\n");
  else
  {
    able_to_construct = current_player->account / current_block->house_price;
    if(able_to_construct > 3)
      able_to_construct = 3;
    printf("You can construct %d house(s).\nHow much house(s) do you want to construct? : ", able_to_construct);
    scanf("%d", & user_cons );
    while(user_cons > able_to_construct && able_to_construct != 0)
    {
      printf("You cannot construct more than %d house(s). Enter a different number: ", able_to_construct);
      scanf("%d", & user_cons);
    }
    if(current_player->account < user_cons * current_block->house_price)
      printf("You don't have enough money to construct %d house(s).\n", user_cons);
    else if(user_cons > 0 && able_to_construct <= 3)
    {
      // Construct house(s)
      current_block->house_count = user_cons;
      current_player->account = current_player->account - (user_cons*current_block->house_price);
      printf("You have constructed %d houses.\n", user_cons);   
    }
  }
}

void buy_property(struct block* current_block, struct player* current_player) {
  int i;

  if(current_block->type != property)
    printf("This is not a property!\n");
  else if(current_block->owner.type != noone)
    printf("This property is already owned!\n");
  else if(current_player->account < current_block->price)
    printf("You don't have enough money to buy this property.\n");
  else
  {
    // update block
    current_block->owner = *current_player;

    // update player
    current_player->account = current_player->account - current_block->price;
    for(i=0; i<11; i++)
      if(current_player->owned_block_ids[i] == NO_PROPERTY)
      {
        current_player->owned_block_ids[i] = current_block->block_id;
        break;
      }

    printf("You have bought property!\n");

    buy_house(current_block, current_player);
  }
}


void sell_property(struct block board[20], struct player* current_player)
{
  int ch=-1, i, gain, user_house_count=-1;
  
  // Sell until user want to exit or no house left 
  while(ch != 0 && user_house_count != 0)
  {
    user_house_count = 0;
    printf("Please select a property to sell to bank:\n");
    for(i=0; i<20; i++)
      if( board[i].type == property && board[i].owner.type == current_player->type )
      {
        printf("%d - \t%s\n", i, board[i].name);
        user_house_count++;
      }
        
    printf("0 - \tExit\nChoice: ");
    scanf("%d", &ch);

    if( board[ch].owner.type == current_player->type )
    {
      gain = 0;
      printf("Property sold. ");
      gain += board[ch].price / 2;
      // pay money for house(s)
      if(board[ch].house_count > 0)
        gain += (board[ch].house_price * board[ch].house_count) / 2;
      
      current_player->account += gain;

      // make house unowned
      board[ch].house_count = 0;
      board[ch].owner.type = noone;
      for(i=0; i<11; i++)
        if(current_player->owned_block_ids[i] == board[ch].block_id)
          current_player->owned_block_ids[i] = NO_PROPERTY;

      printf("You have received %d dollars from this sale.\n", gain);
    }
    else if(ch != 0)
      printf("You do not have this property!\n");
    user_house_count--;
  }
}

int get_prop_count(struct player* current_player)
{
  int i, hc=0;
  for(i=0; i<11; i++)
    if(current_player->owned_block_ids[i] != NO_PROPERTY)
      hc++;
  
  return hc;
}

void after_roll_dice(struct block board[20], struct player* current_player)
{
  int ch=-1, block_id = current_player->current_block_id, rent, house_c, ch_b;
  house_c = get_prop_count(current_player);
  printf("Your location: %s (Block %d) \n", board[block_id].name, block_id);
  if(board[block_id].type == property)
  {
    if(board[block_id].owner.type != current_player->type && board[block_id].owner.type != noone) // rent will be paid
    {
      // determine rent
      if(board[block_id].house_count == 0)
        rent = board[block_id].rent;
      else if(board[block_id].house_count == 1)
        rent = board[block_id].rent_1;
      else if(board[block_id].house_count == 2)
        rent = board[block_id].rent_2;
      else if(board[block_id].house_count == 3)
        rent = board[block_id].rent_3;

      printf("This property is owned by other player. You must pay rent.\n");
      if(board[block_id].house_count > 0)
        printf("This property has %d house(s).", board[block_id].house_count);
      else
        printf("This property has no houses.");
      printf(" Rent is %d $.\n", rent);
      if( rent < current_player->account )
      {
        current_player->account = current_player->account - rent;
        printf("Your money is enough. You have paid the rent.\n");
      }
      else
      {
        printf("Your money is not enough to pay rent.");
        // bankrupt
        if(house_c == 0)
        {
          current_player->account = -1;
          return;
        }
        printf(" You must sell some property.\n");
        while(rent > current_player->account)
          sell_property(board, current_player);
        if( rent <= current_player->account )
        {
          current_player->account = current_player->account - rent;
          printf("You have paid your rent %d $\n", rent);
        }
      }
    }
    else
    if(board[block_id].owner.type == noone) // unowned property
    {
      printf("%s is unowned. Do you want to buy this property?\nBUY (1), NO, THANKS (2)\nCHOICE: ", board[block_id].name);
      scanf("%d", &ch_b);
      if(ch_b == 1)
        buy_property(&board[block_id], current_player);
    }
    else
    if(board[block_id].owner.type == current_player->type)
    {
      printf("Welcome back to house!\n");
      buy_house(&board[block_id], current_player);

    } 
  }
  else if(board[block_id].type == punish)
  {
    current_player->turn_to_wait = current_player->turn_to_wait + board[block_id].rent;
    printf("You have punished for %d turn(s).\n", current_player->turn_to_wait);
  } else if(board[block_id].type == tax)
  {
    if(board[block_id].rent <= current_player->account)
    {
      current_player->account = current_player->account - board[block_id].rent;
      printf("You have paid your tax %d $\n", board[block_id].rent);
    }
    else
    {
      printf("Your money is not enough to pay.");
      // bankrupt
      if(house_c == 0)
      {
        current_player->account = -1;
        return;
      }
      printf("You must sell some property.\n");
      while(board[block_id].rent > current_player->account)
        sell_property(board, current_player);
      if( board[block_id].rent < current_player->account )
      {
        current_player->account = current_player->account - board[block_id].rent;
        printf("You have paid your tax %d $\n", board[block_id].rent);
      }
    }
  }  
}

void gameplay(struct block board[20], struct player player_one, struct player player_two)
{
  int ch=-1, player_one_dice=0, player_two_dice=0, dice_r, i, hc;
  struct player current_player, other_player;

  do {
    printf("Rolling dice for Player 1: ");
    player_one_dice = roll_the_dice();
    printf("%d\n", player_one_dice);
    printf("Rolling dice for Player 2: ");
    player_two_dice = roll_the_dice();
    printf("%d\n", player_two_dice);
    if(player_one_dice == player_two_dice)
      printf("They are equal. Roll again!\n");
  } while(player_one_dice == player_two_dice);

  if(player_one_dice > player_two_dice)
  {
    current_player = player_one;
    printf("Player 1 starts!\n");
  }
  else 
  if(player_two_dice > player_one_dice)
  {
    current_player = player_two;
    printf("Player 2 starts!\n");
  }

  // Game has started...


  while(ch != 0 && player_one.account != -1 && player_two.account != -1)
  {
    hc = get_prop_count(&current_player);
    
    // bankrupt case
    if(current_player.account == -1)
      break;
    printf("Current player: %s\n", current_player.name);
    printf("1 - Roll the dice\n2 - Show my account\n3 - Show my properties\n4 - Show property deeds\n5 - Buy Property\n6 - Buy house\n7 - Sell property\nPlease select an option to continue: ");
    scanf("%d", &ch);

    switch( ch )
    {
      case 1:
        // Roll dice
        dice_r = roll_the_dice();
        
        // If player pass on start, he/she gains 10,000 dollars
        if(current_player.current_block_id + dice_r >= 20)
        {
          printf("You have completed a tour from start. You won 10,000$\n");
          current_player.account = current_player.account + 10000;
        }

        // update player's location on board
        current_player.current_block_id = (current_player.current_block_id + dice_r) % 20;

        printf("Dice is %d.\n", dice_r);

        // open roll dice menu
        after_roll_dice(board, &current_player);
        
        // determine who's other player and update current player
        if(current_player.type == player_one.type)
        {
          other_player = player_two;
          player_one = current_player;
        }
        else if(current_player.type == player_two.type)
        {
          other_player = player_one;
          player_two = current_player;
        }

        // print account info
        printf("%s's Current Account:%d $\n", current_player.name, current_player.account);
        
        // check do other player have punishment
        if(other_player.turn_to_wait > 0)
        {
          if(other_player.type == player_one.type)
          {
            printf("%s's punishment continues, %d turn(s) left\n", player_one.name, player_one.turn_to_wait);
            player_one.turn_to_wait = player_one.turn_to_wait - 1;
          } else
          if(other_player.type == player_two.type)
          {
            printf("%s's punishment continues, %d turn(s) left\n", player_two.name, player_two.turn_to_wait);
            player_two.turn_to_wait = player_two.turn_to_wait - 1;
          }
        } else
        // if he/she has no punishment, switch player
        {
          if(current_player.type == player_one.type)
            current_player = player_two;
          else if(current_player.type == player_two.type)
            current_player = player_one;
        }
        
        // show board
        show_board(board, player_one, player_two);
        break;

      case 2:
        printf("Your balance: %d$\n", current_player.account);
        break;

      case 3:
        if(hc == 0)
          printf("You do not have any property!\n");
        else
          show_my_properties(board, &current_player);
        
        break;

      case 4:
        // show my property deeds
        if(hc == 0)
          printf("You do not have any property!\n");
        else
          {
            for(i=0; i<11; i++)
            if(current_player.owned_block_ids[i] != NO_PROPERTY)
            {
              show_deed(board[current_player.owned_block_ids[i]]);
              printf("\n");
            }
          }
        break;

      case 5:
        buy_property(&board[current_player.current_block_id], &current_player);
        break;

      case 6:
        if(board[current_player.current_block_id].type != property || board[current_player.current_block_id].owner.type != current_player.type)
          printf("You can not construct any house on this block.\n");
        else
          buy_house(&board[current_player.current_block_id], &current_player);
        break;

      case 7:
        sell_property(board, &current_player);
        break;

      default:
        break;
    } 
  }
  // BANKRUPT
  if(player_one.account == -1)
    printf("%s has got bankrupt. Game Over.\n%s has won the game!\n", player_one.name, player_two.name);
  else if(player_two.account == -1)
    printf("%s has got bankrupt. Game Over.\n%s has won the game!\n", player_two.name, player_one.name);
}

int main(void) 
{
  struct block board[20];
  int i;
  int p[11], r[11];

  // MENÜ YAPILDI TEST EDİLECEK...
  
  // create players
  struct player player_one = {cap, 0, 100000, 0, "Cap", p[0]};
  struct player player_two = {car, 0, 100000, 0, "Car", r[0]};
  
  for(int i=0; i<11; i++)
  {
    player_one.owned_block_ids[i] = NO_PROPERTY;
    player_two.owned_block_ids[i] = NO_PROPERTY;
  }

  srand(time(NULL));
  printf("\n");
  init_the_board(board);

  gameplay(board, player_one, player_two);

  return 0;
}