#include <stdio.h>
#include <string.h>

typedef struct{
	//char name[30];
	char* name;
	int north;
	int south;
	int east;
	int west;
}Room;

/*   x = invalid direction
 * 
 *       x  x
 *       |  |
 *    x--4--6--x
 *    |  |     |
 * x--5--1--x--3--x 
 *    |  |     |
 *    x--0-----2--7--x
 *       |     |  | 
 *       x     x  x 
 */ 

void initRooms(Room rooms[ ]){
	// Room 0: Entrance Hall
    //strcpy(rooms[0], "Entrance Hall");
	rooms[0].name = "Entrance Hall";
    rooms[0].north = 1;
    rooms[0].south = -1;
    rooms[0].east = 2;
    rooms[0].west = -1;

    // Room 1: Throne Room
    //strcpy(rooms[1].name, "Throne Room");
	rooms[1].name = "Throne Room";
    rooms[1].north = 4;
    rooms[1].south = 0;
    rooms[1].east = -1;
    rooms[1].west = 5;

    // Room 2: Dining Room
    //strcpy(rooms[2].name, "Dining Room");
    rooms[2].name = "Dining Room";
	rooms[2].north = 3;
    rooms[2].south = -1;
    rooms[2].east = 7;
    rooms[2].west = 0;

    // Room 3: Kitchen
    //strcpy(rooms[3].name, "Kitchen");
    rooms[3].name = "Kitchen";
	rooms[3].north = -1;
    rooms[3].south = 2;
    rooms[3].east = -1;
    rooms[3].west = -1;

    // Room 4: Balcony
    //strcpy(rooms[4].name, "Balcony");
    rooms[4].name = "Balcony";
	rooms[4].north = -1;
    rooms[4].south = 1;
    rooms[4].east = 6;
    rooms[4].west = -1;

    // Room 5: Armory
    //strcpy(rooms[5].name, "Armory");
    rooms[5].name = "Armory";
	rooms[5].north = -1;
    rooms[5].south = -1;
    rooms[5].east = 1;
    rooms[5].west = -1;

    // Room 6: Library
    //strcpy(rooms[6].name, "Library");
    rooms[6].name = "Library";
	rooms[6].north = -1;
    rooms[6].south = -1;
    rooms[6].east = -1;
    rooms[6].west = 4;

    // Room 7: Secret Chamber
    //strcpy(rooms[7].name, "Secret Chamber");
    rooms[7].name = "Secret Chamber";
	rooms[7].north = -1;
    rooms[7].south = -1;
    rooms[7].east = -1;
    rooms[7].west = 2;
}

void move_player(char direction, Room rooms[ ], int *currentRoom) {
    int nextRoom = -1;

    switch (direction) {
        case 'N': nextRoom = rooms[*currentRoom].north; break;
        case 'S': nextRoom = rooms[*currentRoom].south; break;
        case 'E': nextRoom = rooms[*currentRoom].east; break;
        case 'W': nextRoom = rooms[*currentRoom].west; break;
        default: printf("Invalid direction!\n"); return;
    }

    if (nextRoom == -1) {
        printf("Sorry, you can't go that way!\n");
    } else {
        *currentRoom = nextRoom;
        printf("You moved to %s\n", rooms[*currentRoom].name);
    }
}

int main() {
	Room rooms[8];
	initRooms(rooms);
	
	char player_name[30];
	// Start in the Entrance Hall
	int currentRoom = 0; 
    char player_input;
	
    printf("Hello stranger, what is you name?\n");
	
	// To read a full name with space,instead of scanf("%s", player_name); 
	fgets(player_name, sizeof(player_name), stdin); 
	
	// To remove the newline character that fgets() stores in the player_name when reading the name
    player_name[strcspn(player_name, "\n")] = '\0'; 
	printf("Well, welcome %s!", player_name);
	
	while(1)
	{
		   printf("You are in the %s.\n", rooms[currentRoom].name);
		   printf("Where do you want to move: (N)orth, (S)outh,(E)ast,(W)est? Or Q to quit.\n");
		   scanf("%c", &player_input);
		   
		   if (player_input == 'Q'){
			printf("As you wish, see you soon %s!\n", player_name);
			   break;
		   }
		   
    move_player(player_input, rooms, &currentRoom);
	}
	return 0;
}