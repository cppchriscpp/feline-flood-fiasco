; This is done in assembly so we can be a little more sure about where the linker will put this data.
; If it gets moved around, the application patcher will no longer work.

; NOTE: If you're editing the raw code of your own game you can ignore the warnings in this file, and move it wherever
; you want! These warnings only apply if your rom will continue to be used with the  web-based editor.

; DO NOT REMOVE/EDIT! Used by engine to identify game and align patching
.asciiz "PATCH TARGET 1.00"

; These are imported in map.h for the most part
_gameName:
    .asciiz "     Retro Puzzle Maker     "
.export _gameName

_gameLevelData:
    /*
    .byte $01, $23, $45, $67, $89, $ab,
    .byte $12, $34, $56, $78, $9a, $bc,
    .byte $23, $45, $67, $89, $ab, $cd,
    .byte $34, $56, $78, $9a, $bc, $de,
    .byte $45, $67, $09, $ab, $cd, $ef,

    .byte $01, $23, $45, $67, $89, $ab,
    .byte $10, $00, $56, $78, $9a, $bc,
    .byte $20, $45, $67, $89, $ab, $cd,
    .byte $34, $56, $78, $9a, $bc, $de,
    .byte $45, $67, $89, $ab, $cd, $ef,
    */
    
    .byte $01, $11, $11, $11, $11, $11
    .byte $01, $22, $22, $22, $22, $21
    .byte $01, $21, $06, $00, $12, $21
    .byte $01, $21, $50, $00, $12, $21
    .byte $01, $21, $00, $00, $12, $21

    .byte $00, $00, $00, $00, $00, $00
    .byte $01, $21, $50, $45, $12, $21
    .byte $01, $21, $00, $40, $12, $21
    .byte $01, $22, $17, $11, $22, $21
    .byte $01, $11, $11, $11, $11, $11


    ; Extra data...
    ; Tile id for border
    .byte $02
    ; Gameplay mode FIXME: implement
    .byte $00 
    
    ; start position (top nybble is y, bottom nybble is x - starts at first playable space, no border)
    .byte $44
    ; Unused
    .byte $67
.export _gameLevelData

; FIXME: Move to patch area
_tileCollisionTypes:
    .byte $00, $00, $01, $01, $04, $03, $05, $07
    .byte $00, $00, $00, $00, $00, $00, $00, $00
.export _tileCollisionTypes

_tilePalettes:
    .byte $00, $01, $02, $03, $00, $01, $02, $03
    .byte $00, $01, $02, $03, $00, $01, $02, $03
.export _tilePalettes