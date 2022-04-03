#include "source/library/bank_helpers.h"

// Top-left tile of the sprite of the player facing downward.
#define PLAYER_SPRITE_TILE_ID 0x00

// The id of the first sprite in the 4 sprites comprising the player. (out of 64 total sprites)
#define PLAYER_SPRITE_INDEX 0x10

#define PLAY_AREA_TOP 60
#define PLAY_AREA_LEFT 32

// Track the player's position and direction
ZEROPAGE_EXTERN(unsigned char, playerDirection);
ZEROPAGE_EXTERN(unsigned char, playerGridPositionX);
ZEROPAGE_EXTERN(unsigned char, playerGridPositionY);

// Used to animate the player's movement between tiles
ZEROPAGE_EXTERN(signed char, animationPositionX);
ZEROPAGE_EXTERN(signed char, animationPositionY);
ZEROPAGE_EXTERN(unsigned char, undoNumber);
ZEROPAGE_EXTERN(unsigned int, undoArrayPosition);


// Helper macro to convert the player's X and Y position into a position on the map
#define PLAYER_MAP_POSITION(xPos, yPos) (xPos>>4) + (yPos & 0xf0)

// Move the player around, and otherwise deal with controller input. (NOTE: Pause/etc are handled here too)
void handle_player_movement();

// Update the player's sprite, and put it onto the screen as necessary
void update_player_sprite();

// Wipe the undo list
void clear_undo(void);

void update_single_tile(unsigned char x, unsigned char y, unsigned char newTile, unsigned char palette);
void run_tile_batch(void);

// Set this to 0 to start queueing up tiles for a batch (up to 4 tiles)
ZEROPAGE_EXTERN(unsigned char, runTileBatch);
