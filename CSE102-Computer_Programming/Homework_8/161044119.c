#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define PROPERTY_COUNT 13
typedef enum block_type{start=0,property,fortune,tax,punish}b_type;
typedef enum player_type{none=-1,car=0,cap=1}player_type;

typedef struct
{
	player_type type;
	int current_block_id;
	int owned_blocks[PROPERTY_COUNT];
	int account;
	int turn_to_wait;
	char *player_name;
} player;

typedef struct block
{
    int id;
    char * name;
    int price;
    int rent;
    int rent_1;
    int rent_2;
    int rent_3;
    int house_price;
    int h_count;
    player owner;
    b_type type;
    struct block *next;
} block;

typedef struct fortune_card
{
  int id;
  char * name;
} fortune_card;


int roll_dice()
{

    int i=rand()%6+1;
    return i;
}

void show_property_deed(block *head)
{
    int exit_flag=0,i,selection;
    block *current;
    while (exit_flag==0)
    {
        printf("Please select a property to see details:\n");
        for (current = head; current->next != NULL; current = current->next) {
            if (current->type==property)
                printf("%d -\t%s \n", current->id, current->name);
        }
        printf("0 -\tExit\n");
        scanf("%d",&selection);
        if (selection==0)
            exit_flag=1;
        else {
            for(current=head; current->id != selection; )
              current = current->next;
            if (selection > 0 && selection < 24 && current->type == property) {
                printf("\n\n---------------------------------\n");
                if (strlen(current->name) < 8)
                    printf("|\t\t%s\t\t|\n", current->name);
                else
                    printf("|\t    %s\t\t|\n", current->name);
                printf("---------------------------------\n");
                printf("|\tRent \t\t%d$\t|\n", current->rent);
                printf("|\tRent 1 H \t%d$\t|\n", current->rent_1);
                printf("|\tRent 2 H \t%d$\t|\n", current->rent_2);
                printf("|\tRent 3 H \t%d$\t|\n", current->rent_3);
                printf("---------------------------------\n");
                printf("|\tHouse Price \t%d$\t|\n", current->house_price);
                printf("|\tHouse count \t%d\t|\n", current->h_count);
                printf("---------------------------------\n\n\n");
            } else printf("\nWrong Selection! Please Try Again.\n\n");
        }
    }
}

void show_board(block *head, player player_one, player player_two)
{
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	int i=0,space_flag=0;
  block *current;
	for (current = head; current->id<7; current=current->next)
	{
        if (strlen(current->name)<8)
		    printf("|\t%s\t\t",current->name);
        else
            printf("|\t%s\t",current->name);
	}
	printf("|\n");
	for (current = head; current->id<7; current=current->next)
	{
		if (current->type==property || current->type==tax)
		    printf("|\t%d$ \t\t",current->price);
		else if (strlen(current->name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");
	}
    printf("|\n");
    for (current = head; current->id<7; current=current->next)
    {
        space_flag=0;
        printf("|\t");
        if (current->id==player_one.current_block_id && current->id==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {
            if (current->id == player_one.current_block_id) {
                printf("%s \t\t", player_one.player_name);
                space_flag = 1;
            }
            if (current->id == player_two.current_block_id) {
                printf("%s \t\t", player_two.player_name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(current->name)<8)
                printf("     \t\t");
            else
                printf(" \t\t");
        }
    }
    printf("|\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    //Middle
    for (i=0;i<5;i++)
    {
        //Names

        for(current=head; current->id != 23 - i; )
          current = current->next;

        if (strlen(current->name)<8)
            printf("|\t%s\t\t|",current->name);
        else
            printf("|\t%s\t|",current->name);

        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");



        for(current=head; current->id != 7 + i; )
          current = current->next;
        if (strlen(current->name)<8)
            printf("|\t%s\t\t|",current->name);
        else
            printf("|\t%s\t|",current->name);
        printf("\n");

        for(current=head; current->id != 23 - i; )
          current = current->next;
        //prices
        if (current->type==property || current->type==tax)
            printf("|\t%d$ \t\t|",current->price);
        else if (strlen(current->name)<8)
            printf("|\t     \t|");
        else
            printf("|\t\t \t|");


        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");

        for(current=head; current->id != 7 + i; )
          current = current->next;

        if (current->type==property || current->type==tax)
            printf("|\t%d$ \t\t", current->price);
        else if (strlen(current->name)<8)
            printf("|\t     \t");
        else
            printf("|\t\t \t");

        printf("|\n");
        //spaces

        space_flag=0;
        printf("|\t");
        if (23-i==player_one.current_block_id && 23-i==player_two.current_block_id)
        {
            printf("%s, %s \t|",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {
            if (23 - i == player_one.current_block_id) {
                printf("%s \t\t|", player_one.player_name);
                space_flag = 1;
            }
            if (23 - i == player_two.current_block_id) {
                printf("%s \t\t|", player_two.player_name);
                space_flag = 1;
            }
        }
        for(current=head; current->id != 23 - i; )
          current = current->next;
        if (space_flag==0) {
            if (strlen(current->name)<8)
                printf("\t\t|");
            else
                printf("    \t\t|");
        }

        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        space_flag=0;
        printf("|\t");
        if (7+i==player_one.current_block_id && 7+i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {

            if (7+i==player_one.current_block_id)
            {
                printf("%s \t\t",player_one.player_name);
                space_flag=1;
            }
            if (7+i==player_two.current_block_id)
            {
                printf("%s \t\t",player_two.player_name);
                space_flag=1;
            }
        }

        for(current=head; current->id != 7 + i; )
          current = current->next;

        if (space_flag==0) {
            if (strlen(current->name)<8)
                printf("\t\t");
            else
                printf("    \t\t");
        }

        printf("|\n");
        if (i!=4) {
            printf("-------------------------");
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            printf("-------------------------");
            printf("\n");
        }

    }

    //bottom row
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i=18;i>=12;i--)
    {
      for(current = head; current->id != i;)
        current = current->next;
        if (strlen(current->name)<8)
            printf("|\t%s\t\t",current->name);
        else
            printf("|\t%s\t",current->name);
    }
    printf("|\n");
    for (i=18;i>=12;i--)
    {
      for(current = head; current->id != i;)
        current = current->next;
        if (current->type==property || current->type==tax)
            printf("|\t%d$ \t\t",current->price);
        else if (strlen(current->name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");
    }
    printf("|\n");
    for (i=18;i>=12;i--)
    {
      for(current = head; current->id != i;)
        current = current->next;
        space_flag=0;
        printf("|\t");
        if (i==player_one.current_block_id && i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {
            if (i == player_one.current_block_id) {
                printf("%s \t\t", player_one.player_name);
                space_flag = 1;
            }
            if (i == player_two.current_block_id) {
                printf("%s \t\t", player_two.player_name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(current->name)<8)
                printf("     \t\t");
            else
                printf(" \t\t");
        }

    }
    printf("|\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
}

void init_board(block* head)
{
  block* current = head;
	player temp_player;
	temp_player.type=none;

    current->type=start;
    current->id=0;
    current->name="Start";
    current->price=0;
    current->rent=0;
    current->rent_1=0;
    current->rent_2=0;
    current->rent_3=0;
    current->owner=temp_player;
    current->house_price=0;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;  

    current->type=property;
    current->id=1;
    current->name="Esenyurt";
    current->price=16000;
    current->rent=800;
    current->rent_1=4000;
    current->rent_2=9000;
    current->rent_3=25000;
    current->house_price=10000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;
    
    current->type=tax;
    current->name="Car park";
    current->id=2;
    current->price=1500;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=fortune;
    current->name="Fortune Card";
    current->id=3;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=4;
    current->name="Tuzla";
    current->price=16500;
    current->rent=850;
    current->rent_1=4250;
    current->rent_2=9500;
    current->rent_3=26000;
    current->house_price=12000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=5;
    current->name="Arnavutkoy";
    current->price=17000;
    current->rent=850;
    current->rent_1=4500;
    current->rent_2=10000;
    current->rent_3=28000;
    current->house_price=12000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=punish;
	  current->name="Wait 2 turn";
	  current->price=2;
    current->id=6;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=7;
    current->name="Catalca";
    current->price=20000;
    current->rent=1000;
    current->rent_1=5000;
    current->rent_2=12000;
    current->rent_3=30000;
    current->house_price=13000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=8;
    current->name="Beykoz";
    current->price=23000;
    current->rent=1100;
    current->rent_1=5500;
    current->rent_2=12500;
    current->rent_3=33000;
    current->house_price=13000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=fortune;
    current->name="Fortune Card";
    current->id=9;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;
    
    current->type=tax;
    current->name="Car fix";
    current->id=10;
    current->price=1750;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=11;
    current->name="Maltepe";
    current->price=30000;
    current->rent=1350;
    current->rent_1=7000;
    current->rent_2=15000;
    current->rent_3=40000;
    current->house_price=15000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;
    
    current->type=tax;
    current->name="Bills";
    current->id=12;
    current->price=2000;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=13;
    current->name="Sisli";
    current->price=33000;
    current->rent=1500;
    current->rent_1=8000;
    current->rent_2=16000;
    current->rent_3=42000;
    current->house_price=16000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;
    
    current->type=tax;
    current->name="Oil";
    current->id=14;
    current->price=2250;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=fortune;
    current->name="Fortune Card";
    current->id=15;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=16;
    current->name="Atasehir";
    current->price=35000;
    current->rent=1600;
    current->rent_1=8500;
    current->rent_2=17000;
    current->rent_3=45000;
    current->house_price=17000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=property;
    current->id=17;
    current->name="Sariyer";
    current->price=40000;
    current->rent=1750;
    current->rent_1=9500;
    current->rent_2=19000;
    current->rent_3=48000;
    current->house_price=19000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=punish;  
	  current->name="Wait 1 turn";
	  current->price=1;
    current->id=18;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

	  current->type=property;
    current->id=19;
    current->name="Kadikoy";
    current->price=43000;
    current->rent=1900;
    current->rent_1=11000;
    current->rent_2=21500;
    current->rent_3=55000;
    current->house_price=23000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;
    
	  current->type=property;
    current->id=20;
    current->name="Besiktas";
    current->price=60000;
    current->rent=2500;
    current->rent_1=15000;
    current->rent_2=28000;
    current->rent_3=60000;
    current->house_price=30000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=fortune;
    current->name="Fortune Card";
    current->id=21;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current->type=tax;
    current->name="Vocation";
    current->id=22;
    current->price=5000;
    
    current->next = (block*) malloc(sizeof(block));
    current = current->next;

	  current->type=property;
    current->id=23;
    current->name="Bebek";
    current->price=70000;
    current->rent=3500;
    current->rent_1=20000;
    current->rent_2=35500;
    current->rent_3=65000;
    current->house_price=35000;
    current->h_count=0;

    current->next = (block*) malloc(sizeof(block));
    current = current->next;

    current = NULL;
    
}

void show_player_properties(block *board_ll, player current_player)
{
    int i,counter=0,selection;
    block *current;
    while (selection!=0) {
        printf("----------------------------------------\n");
        for (i = 0; i < PROPERTY_COUNT; i++) {
            if (current_player.owned_blocks[i] != -1) {
              for(current = board_ll; current->id != current_player.owned_blocks[i]; )
                current=current->next;
                printf("%d - %s\n", current->id,
                       current->name);
                counter++;
            }

        }
        if (counter == 0)
        {
            printf("You have not owned any property yet.\n");
            printf("----------------------------------------\n");
            selection=0;
        }
        else
        {

            printf("0 - Back \n");
            printf("----------------------------------------\n");
            printf("Please select an property to see details.\n");
            scanf("%d", &selection);

            if (selection!=0) {
              for(current = board_ll; current->id != selection; )
                current=current->next;
                if (current->owner.type != current_player.type)
                    printf("You made a wrong selection!\n");
                else {
                    printf("\n\n---------------------------------\n");
                    if (strlen(current->name) < 8)
                        printf("|\t\t%s\t\t|\n", current->name);
                    else
                        printf("|\t    %s\t\t|\n", current->name);
                    printf("---------------------------------\n");
                    printf("|\tRent \t\t%d$\t|\n",current->rent);
                    printf("|\tRent 1 H \t%d$\t|\n", current->rent_1);
                    printf("|\tRent 2 H \t%d$\t|\n", current->rent_2);
                    printf("|\tRent 3 H \t%d$\t|\n", current->rent_3);
                    printf("---------------------------------\n");
                    printf("|\tHouse Price \t%d$\t|\n", current->house_price);
                    printf("|\tHouse count \t%d\t|\n", current->h_count);
                    printf("---------------------------------\n\n\n");
                }
            }
        }


    }

}

int build_house(block* current_block, player* current_player)
{
    int flag=0;
    if (current_player->type==current_block->owner.type)
    {
        if (current_block->h_count<3)
        {
            if (current_block->house_price<=current_player->account)
            {
                flag=1;
                current_player->account-=current_block->house_price;
                current_block->h_count+=1;
            }
            else
                printf("You don't have enough money to build house!\n");
        }
        else
            printf("You can't buy more than 3 houses in a property!\n");
    }
    else
        printf("You don't have permission to build house on this property!\n ");
    return flag;
}

int count_properties(player current_player)
{
    int i,count=0;
    for (i=0;i<PROPERTY_COUNT;i++)
    {
        if (current_player.owned_blocks[i]!=-1)
            count++;
    }
    return count;
}

void sell_property(block *board_ll, player* current_player)
{
    int property_id,flag=0,is_owned=-1,i,index,counter=0;
    block *current;
        if (count_properties(*current_player)!=0)
        {
            for (i = 0; i < PROPERTY_COUNT; i++) {
                if (current_player->owned_blocks[i] != -1) {
                  for(current = board_ll; current->id != current_player->owned_blocks[i]; )
                    current = current->next;
                    printf("%d - %s\n", current->id, current->name);
                    counter++;
                }

            }
            printf("0 - Back\n");
            printf("Please select to sell the property:\n");

            scanf("%d",&property_id);
            if (property_id!=0)
            {
                for(i=0;i<PROPERTY_COUNT;i++)
                {
                    if (current_player->owned_blocks[i]==property_id)
                    {
                        is_owned=1;
                        index=i;
                        break;
                    }
                }
                if(is_owned!=-1)
                {
                  for(current = board_ll; current->id != property_id; )
                    current = current->next;

                    current_player->owned_blocks[index]=-1;
                    player temp;
                    current->owner.type=none;
                    if(current->h_count==0)current_player->account+=current->price/2;
                    if(current->h_count==1)
                    {
                        current_player->account+=(current->price+current->house_price)/2;
                    }
                    if(current->h_count==2)
                    {
                        current_player->account+=(current->price+(2*current->house_price))/2;
                    }
                    if(current->h_count==3)
                    {
                        current_player->account+=(current->price+(3*current->house_price))/2;
                    }
                }
            }
        } else
        {
            printf("You don't have any property to sell.\n");
        }

}

int insufficient_fund(block *board_ll, player* current_player,int required_money)
{
    int selection,flag=1;
    while (selection!=4 && current_player->account<required_money && count_properties(*current_player)!=0)
    {
        printf("You don't have enough money to continue your transaction.You need %d$ more. Please select an option to continue: \n",required_money-current_player->account);
        printf("1- Sell Property\n");
        printf("2- Show my Properties\n");
        printf("3- Show my Account\n");
        printf("0- Back\n");
        scanf("%d",&selection);
        switch (selection)
        {
            case 1:
                sell_property(board_ll,current_player);
                break;
            case 2:
                show_player_properties(board_ll,*current_player);
                break;
            case 3:
                printf("\n\nThere are %d $ in your account.\n\n",current_player->account);
                break;
            case 0:
                flag=0;
                break;
            default:
                printf("You made a wrong selection!\n");
                break;

        }
    }
    return flag;

}

void pay_rent(block *board_ll, player* current_player, player* other)
{
    int rent=0,owned_property_count;
    block *current_block;
    for(current_block = board_ll; current_block->id != current_player->current_block_id; )
      current_block = current_block->next;
    rent=current_block->rent;
    if (current_block->h_count==1)rent=current_block->rent_1;
    if (current_block->h_count==2)rent=current_block->rent_2;
    if (current_block->h_count==3)rent=current_block->rent_3;
    if (rent>current_player->account)
    {
        owned_property_count=count_properties(*current_player);
        while(rent>current_player->account && owned_property_count!=0)
        {
            insufficient_fund(board_ll,current_player,rent);
            owned_property_count=count_properties(*current_player);
        }
    }
    if (rent<current_player->account)
    {
        current_player->account-=rent;
        other->account+=rent;
    } else
        current_player->account=0;
}

void add_to_owned(player* current_player)
{
    for (int i = 0; i < PROPERTY_COUNT; ++i) {
        if (current_player->owned_blocks[i]==-1) {
            current_player->owned_blocks[i] = current_player->current_block_id;
            printf("Current block id %d\n",current_player->current_block_id);
            break;
        } else
            printf("%d ",current_player->owned_blocks[i]);
    }
    printf("\n");
}

void copy_owner(player* old, player* new)
{
    old->type=new->type;
    old->account=new->account;
    old->turn_to_wait=new->turn_to_wait;
    old->player_name=new->player_name;
    old->current_block_id=new->current_block_id;
    for (int i = 0; i < PROPERTY_COUNT; ++i) {
        old->owned_blocks[i]=new->owned_blocks[i];
    }
}

void buy_property(block* current_block, player* current_player)
{
    if (current_block->price<=current_player->account)
    {
        current_player->account-=current_block->price;
        copy_owner(&current_block->owner,current_player);
        add_to_owned(current_player);

        printf("Congratiulations! You have buy %s.\n",current_block->name);
        printf("You left %d$ in your account.\n",current_player->account);

    }
    else
        printf("You don't have enough money to buy this property!\n");
}

void house_dialog(block *board_ll, player* current_player)
{
    int house_flag=1,selection,insuf_flag=1,build_flag=1;
    block *current_block;
    for(current_block = board_ll; current_block->id != current_player->current_block_id; )
      current_block = current_block->next;
    while (house_flag && build_flag) {
        printf("Do you want to build house on %s ?\n",
               current_block->name);
        printf("1- Yes\n");
        printf("2- No\n");
        scanf("%d", &selection);
        if (selection == 1) {

            if (current_player->account < current_block->house_price) {
                while (count_properties(*current_player)!=0 && current_player->account<current_block->house_price && insuf_flag==1)
                    insuf_flag=insufficient_fund(board_ll,current_player,current_block->house_price);
            }
            if (current_player->account >= current_block->house_price)
                build_flag=build_house(current_block, current_player);
            else
                house_flag=0;


        } else
            house_flag=0;
    }
}

void after_dice_menu(block *board_ll, player* current_player, player* other)
{
    int selection,insuf_flag=1, card_num, cp_house_count, dice, i;
    block *current;
    fortune_card *fort_card;
    fort_card = ( fortune_card*) malloc(sizeof( fortune_card));
    for(current = board_ll; current->id != current_player->current_block_id; )
      current = current->next;
    switch (current->type)
    {
        case property:
            printf("%s has arrived %s \n",current_player->player_name,current->name);
            if (current->owner.type==none)
            {
                printf("Do you want to buy %s ?\n", current->name);
                printf("1- Yes\n");
                printf("2- No\n");
                scanf("%d",&selection);
                if (selection==1)
                {

                    if (current_player->account< current->price)
                    {
                        while (count_properties(*current_player)!=0 && current_player->account<current->price && insuf_flag==1 )
                        {
                            insuf_flag=insufficient_fund(board_ll,current_player, current->price);
                        }
                    }
                    buy_property(current, current_player);
                    if (current_player->type==current->owner.type)
                    {
                        house_dialog(board_ll,current_player);
                    }

                }
            } else
            {
                pay_rent(board_ll,current_player,other);
            }
            break;
        case tax:
            printf("%s has arrived tax block(%s)\n",current_player->player_name,current->name);
            while (count_properties(*current_player)!=0 && current_player->account<current->price) {
                insuf_flag = insufficient_fund(board_ll, current_player,
                                               current->price);
                if (insuf_flag == 0 && current_player->account < current->price)
                    printf("You must pay your tax!\n");
            }
            if (current_player->account>current->price)
                current_player->account=current_player->account - current->price;
            else
            {
                current_player->account=0;
            }
            break;
        case punish:
            printf("%s has punished for %d turn. \n",current_player->player_name,current->price);
            current_player->turn_to_wait+=current->price;
            break;

        case fortune:
            card_num = rand() % 5 + 1;
            fort_card->id = card_num;
            if(card_num == 1)
            {
              fort_card->name = "Free House";
              printf("You have draw %s card.\n", fort_card->name);
              cp_house_count = 0;
              for(i=0; i<PROPERTY_COUNT; i++)
                if(current_player->owned_blocks[i] != -1)
                  cp_house_count++;
              if(cp_house_count > 0) // NOT FREE
                build_house(current, current_player);
              else
                printf("You don't have any property to construct a house.\n");
            }
            else if(card_num == 2)
            {
              fort_card->name = "Time Travel";
              printf("You have draw %s card.\n", fort_card->name);
              dice = roll_dice();
              printf("You rolled the dice: %d\n", dice);
              if(dice > 0 && dice < 4)
              {
                current_player->current_block_id += 2;
                printf("You moved 2 blocks forward.\n");
              }
              else
              {
                current_player->current_block_id -= 2;
                printf("You moved 2 blocks backward.\n");
              }
            }
            else if(card_num == 3)
            {
              fort_card->name = "Garnishment";
              printf("You have draw %s card. You paid 5,000$ to the bank.\n", fort_card->name);
              current_player->account -= 5000;              
            }
            else if(card_num == 4)
            {
              fort_card->name = "Generosity";
              printf("You have draw %s card. You paid 10,000$ to the opponent player.\n", fort_card->name);
              other->account += 10000;
            }
            else if(card_num == 5)
            {
              fort_card->name = "Treasure Hunter";
              printf("You have draw %s card. You received 20,000 $ from the bank.\n", fort_card->name);
              current_player->account += 20000;
            }
            break;

        case start:
            break;
    }
}

void turn(block *board_ll, player* current_player, player * other)
{
    int flag=1,next_block;
    while(flag)
    {
        int selection;
        block *current;
        printf("1 - Roll the dice\n");
        printf("2 - Show my account\n");
        printf("3 - Show my properties\n");
        printf("4 - Show property deeds\n");
        printf("5 - Buy Property\n");
        printf("6 - Buy house \n");
        printf("7 - Sell property\n");
        printf("Please select an option to continue (%s):\n",current_player->player_name);
        scanf("%d",&selection);
        switch(selection)
        {
            case 1:
                if (current_player->turn_to_wait==0) {
                    next_block=(current_player->current_block_id + roll_dice());
                    if (next_block>=24)current_player->account+=10000;
                    current_player->current_block_id = next_block % 24;
                    after_dice_menu(board_ll,current_player,other);
                    flag = 0;
                } else
                {
                    printf("You need to wait %d turn to continue.\n",current_player->turn_to_wait);
                    current_player->turn_to_wait-=1;
                    flag=0;
                }
                break;
            case 2:
                printf("\n\nThere are %d $ in your account.\n\n",current_player->account);
                break;
            case 3:
                show_player_properties(board_ll,*current_player);
                break;
            case 4:
                show_property_deed(board_ll);
                break;
            case 5:
                for(current = board_ll; current->id != current_player->current_block_id; )
                  current = current->next;
                if (current->type==property && current->owner.type==-1)
                  buy_property(current,current_player);
                else
                {
                    printf("You don't have permission to buy this block!\n");
                }

                break;
            case 6:
                for(current = board_ll; current->id != current_player->current_block_id; )
                  current = current->next;
                if (current_player->type==current->owner.type) {
                    house_dialog(board_ll ,current_player);
                }else
                {
                    printf("You don't have permission to build house on this block!\n");
                }
                break;
            case 7:
                sell_property(board_ll,current_player);
                break;
            default:
                printf("Wrong selection!\n");
        }
    }
}

int check_end(player current_player)
{
    int owned_property_count=count_properties(current_player);
    if (current_player.account<=0 && owned_property_count==0)return 1;
    else return 0;
}

void play_game(block *board_ll, player* player_one, player* player_two)
{
    int is_end=0;
    printf("Welcome to Monopoly! %s will roll the dice first.\n",player_one->player_name);
    while(is_end!=1)
    {
        printf("%s :%d$ , %s:%d$\n",player_one->player_name,player_one->account,player_two->player_name,player_two->account);
        turn(board_ll,player_one,player_two);
        show_board(board_ll,*player_one,*player_two);
        is_end=check_end(*player_one);
        if (is_end==0)
        {
            printf("%s :%d$ , %s:%d$\n",player_one->player_name,player_one->account,player_two->player_name,player_two->account);
            turn(board_ll,player_two,player_one);
            show_board(board_ll,*player_one,*player_two);
            is_end=check_end(*player_two);
            if (is_end==1)
                printf("%s don't have enough money to payment, unfortunately %s lost the game!\n",player_two->player_name,player_two->player_name);
        } else
            printf("%s don't have enough money to payment, unfortunately %s lost the game!\n",player_one->player_name,player_one->player_name);

    }

}

void init_owned(player* current_player)
{
    int i;
    for (i=0;i<PROPERTY_COUNT;i++)
    {
        current_player->owned_blocks[i]=-1;
    }
}

int main() {
    block* board_ll;
    block* current;
    board_ll = ( block*) malloc(sizeof( block));  // head
    init_board( board_ll );
    for(current = board_ll; current->next != NULL; current=current->next)
      current->owner.type = none;
    srand(time(NULL));
    player player_one,player_two;

    player_one.player_name="Cap";
	player_one.type=cap;
	player_one.current_block_id=0;
    player_one.turn_to_wait=0;
	player_one.account=100000;
    init_owned(&player_one);

	player_two.player_name="Car";
	player_two.type=car;
	player_two.current_block_id=0;
    player_two.turn_to_wait=0;
	player_two.account=100000;
    init_owned(&player_two);

    show_board(board_ll,player_one,player_two);
    play_game(board_ll,&player_one,&player_two);

    return 0;
}