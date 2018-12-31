// Saving and loading game data, parsing it out of large structures...
// Also handles the temporary storage for the editor.
#include "source/neslib_asm/neslib.h"
#include "source/globals.h"
#include "source/map/map.h"
#include "source/map/map_data.h"
#include "source/library/bank_helpers.h"
#include "source/menus/error.h"
#include "source/game_data/game_data.h"
// Using this to "Borrow" a variable to put our text into.
#include "source/menus/text_input.h"
#include "source/configuration/system_constants.h"

unsigned char currentGameData[256];

ZEROPAGE_DEF(unsigned char, __extraBits);

SRAM_ARRAY_DEF(unsigned char, savedGameData, 2048);
SRAM_ARRAY_DEF(unsigned char, currentSramGameData, 256);


void unload_game() {
    memfill(currentGameData, 0x00, 256);
}

void load_game() {
    if (selectedGameId < 128) {
        bank_push(PRG_BANK_MAP_DATA);

        memcpy(currentGameData, (&(builtInMapData[0]) + (selectedGameId<<8)), 256);
        bank_pop();
    } else {
        memcpy(currentGameData, (&(savedGameData[0]) + ((selectedGameId-128)<<8)), 256);

        // IF this isn't the right version, give the user an empty game. (It won't show in the list, except for "new game")
        if (currentGameData[GAME_DATA_OFFSET_VERSION] != GAME_DATA_VERSION_ID) {
            memfill(currentGameData, 0, 256);
            currentGameData[GAME_DATA_OFFSET_VERSION] = GAME_DATA_VERSION_ID;
            currentGameData[GAME_DATA_OFFSET_TILESET_ID] = CHR_BANK_ZORIA;
            currentGameData[GAME_DATA_OFFSET_SONG_ID] = SONG_OVERWORLD;
            currentGameData[GAME_DATA_OFFSET_SPRITE_ID] = GAME_SPRITE_ZORIA;
            for (i = 0; i != 8; ++i) {
                currentGameData[GAME_DATA_OFFSET_MAP + (i*GAME_DATA_OFFSET_MAP_WORLD_LENGTH) + 2] = TILE_COLLISION_LEVEL_END;
            }
            memcpy((&(currentGameData[GAME_DATA_OFFSET_TITLE])), "NO NAME             ", GAME_DATA_OFFSET_TITLE_LENGTH);
            memcpy((&(currentGameData[GAME_DATA_OFFSET_AUTHOR])), "ANONYMOUS           ", GAME_DATA_OFFSET_AUTHOR_LENGTH);
        }
    }
}

void load_game_name_to_input() {
    if (selectedGameId < 128) {
        bank_push(PRG_BANK_MAP_DATA);
        if (builtInMapData[(selectedGameId<<8) + GAME_DATA_OFFSET_VERSION] == GAME_DATA_VERSION_ID) {
            memcpy(inputText, (&(builtInMapData[0]) + (selectedGameId<<8)) + GAME_DATA_OFFSET_TITLE, GAME_DATA_OFFSET_TITLE_LENGTH);
        } else {
            inputText[0] = NULL;
        }
        bank_pop();
    } else {
        if (savedGameData[((selectedGameId-128)<<8) + GAME_DATA_OFFSET_VERSION] == GAME_DATA_VERSION_ID) {
            memcpy(inputText, (&(savedGameData[0]) + ((selectedGameId-128)<<8) + GAME_DATA_OFFSET_TITLE), GAME_DATA_OFFSET_TITLE_LENGTH);
        } else {
            inputText[0] = NULL;
        }
    }
}

void save_game() {
    if (selectedGameId < 128) {
        crash_error("Invalid Save Id", "Tried to save to a built-in game slot", "slot id", selectedGameId);
        return;
    }

    memcpy((&(savedGameData[0]) + ((selectedGameId-128)<<8)), currentGameData, 256);
}
