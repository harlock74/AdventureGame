// A very simple Adventure Game written in C. Still WIP.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ROOMS_NUMBER 8
#define MAP_WIDTH 7
#define MAP_HEIGHT 5

typedef struct{
	//char name[30];
	char* name;
	int north;
	int south;
	int east;
	int west;
	bool hasKey;
	bool isLocked;
	int x, y;  // Room's Coordinates on the map
} Room;

typedef struct{
	bool hasKey1;
	bool hasKey2;
	int x, y;  // Player's coordinates on the map
} Player;

/*   x = invalid direction
 *   Rooms 4 is locked and need Key1
 *   Rooms 7 islocked and need Key2
 *   Room 1 kas Key1 to unlock room 4
 *   Room 6 kas Key2 to unlock room 7
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
	rooms[0].hasKey = false;
	rooms[0].isLocked = false;
	rooms[0].x = 2; rooms[0].y = 2;

    // Room 1: Throne Room with Key1
    //strcpy(rooms[1].name, "Throne Room");
	rooms[1].name = "Throne Room";
	rooms[1].north = 4;
	rooms[1].south = 0;
	rooms[1].east = -1;
	rooms[1].west = 5;
	rooms[1].hasKey = true;  // Key 1
	rooms[1].isLocked = false;
	rooms[1].x = 2; rooms[1].y = 1;


    // Room 2: Dining Room
    //strcpy(rooms[2].name, "Dining Room");
    rooms[2].name = "Dining Room";
	rooms[2].north = 3;
    rooms[2].south = -1;
    rooms[2].east = 7;
    rooms[2].west = 0;
	rooms[2].hasKey = false;
    rooms[2].isLocked = false;
    rooms[2].x = 3; rooms[2].y = 2;

    // Room 3: Kitchen
    //strcpy(rooms[3].name, "Kitchen");
    rooms[3].name = "Kitchen";
	rooms[3].north = -1;
    rooms[3].south = 2;
    rooms[3].east = -1;
    rooms[3].west = -1;
	rooms[3].hasKey = false;
    rooms[3].isLocked = false;
	rooms[3].x = 3; rooms[3].y = 1;


    // Room 4: Balcony which is locked and needs Key1
    //strcpy(rooms[4].name, "Balcony");
    rooms[4].name = "Balcony";
	rooms[4].north = -1;
    rooms[4].south = 1;
    rooms[4].east = 6;
    rooms[4].west = -1;
	rooms[4].hasKey = false;
    rooms[4].isLocked = true;  // Locked Room
    rooms[4].x = 2; rooms[4].y = 0;

    // Room 5: Armory
    //strcpy(rooms[5].name, "Armory");
    rooms[5].name = "Armory";
	rooms[5].north = -1;
    rooms[5].south = -1;
    rooms[5].east = 1;
    rooms[5].west = -1;
	rooms[5].isLocked = false;
    rooms[5].x = 1; rooms[5].y = 1;

    // Room 6: Library with Key2
    //strcpy(rooms[6].name, "Library");
    rooms[6].name = "Library";
	rooms[6].north = -1;
    rooms[6].south = -1;
    rooms[6].east = -1;
    rooms[6].west = 4;
	rooms[6].hasKey = true;  // Key 2
    rooms[6].isLocked = false;
    rooms[6].x = 3; rooms[6].y = 0;

    // Room 7: Secret Chamber which is locked and need Key2
    //strcpy(rooms[7].name, "Secret Chamber");
    rooms[7].name = "Secret Chamber";
	rooms[7].north = -1;
    rooms[7].south = -1;
    rooms[7].east = -1;
    rooms[7].west = 2;
	rooms[7].hasKey = false;
    rooms[7].isLocked = true;  // Locked Room
	rooms[7].x = 4; rooms[7].y = 2;

}

void displayMap(Room rooms[ ], Player player) {
    char map[MAP_HEIGHT][MAP_WIDTH];

    // Initialize the map with empty spaces
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map[i][j] = ' ';
        }
    }

    // Place each room on the map
    for (int i = 0; i < ROOMS_NUMBER; i++) {
        map[rooms[i].y][rooms[i].x] = 'R';
    }

    // Place the player on the map
    map[player.y][player.x] = 'P';

    // Display the map
    printf("\nMap:\n");
	 printf("\n");
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void move_player(char direction, Room rooms[ ], int *currentRoom, Player *player) {
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
	// Check if the room is locked and if the player has the correct key
    } else if (rooms[nextRoom].isLocked) {
	  if ((nextRoom == 4 && player->hasKey1) || (nextRoom == 7 && player->hasKey2)) {
			rooms[nextRoom].isLocked = false;  // Unlock the room
			*currentRoom = nextRoom;
			player->x = rooms[*currentRoom].x;
		    player->y = rooms[*currentRoom].y;
			printf("You used a key to unlock %s.\n", rooms[*currentRoom].name);
	  } else {
            printf("The door to %s is locked. You need a key.\n", rooms[nextRoom].name);
	  }	
    } else {
        *currentRoom = nextRoom;
		player->x = rooms[*currentRoom].x;
		player->y = rooms[*currentRoom].y;
		printf("You moved to %s\n", rooms[*currentRoom].name);
    }
    // Check if the current room has a key
    if (rooms[*currentRoom].hasKey) {
        if (*currentRoom == 1) {
            player->hasKey1 = true;
            printf("You found Key 1!\n");
        } else if (*currentRoom == 6) {
            player->hasKey2 = true;
            printf("You found Key 2!\n");
        }
        rooms[*currentRoom].hasKey = false;  // Remove the key from the room after picking it up
    }
}

int main() {
	Room rooms[ROOMS_NUMBER];
	Player player = {false, false, 2, 2};
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
	printf("Welcome %s!", player_name);
	
	while(1)
	{
			displayMap(rooms, player);
			printf("You are in the %s.\n", rooms[currentRoom].name);
			printf("Where do you want to move: (N)orth, (S)outh, (E)ast, (W)est? Or Q to quit.\n");
			scanf(" %c", &player_input); 
		   
		   /*The space before %c is needed to skip any leading whitespace chrarcters
		     including newlines, so this will prevent it from reading the newline as input.
			 scanf reads one character, but it leaves a newline character ( '\n' ) in the 
		     input buffer, which causes the next iteration of the loop to immediately read
		     the new line character as input, resulting in the "invalid direction!"
		     message.*/
		   
		   if (player_input == 'Q'){
			printf("As you wish, see you soon %s!\n", player_name);
			   break;
		   }
		   
    move_player(player_input, rooms, &currentRoom, &player);
	}
	return 0;
}