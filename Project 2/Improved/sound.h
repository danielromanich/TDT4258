#include <stdint.h>
 
/* The period between sound samples, in clock cycles */ 
#define   SAMPLE_PERIOD   317
    
typedef struct Note
{
    uint16_t noteCount;
    uint8_t length[];
} Note;

 
typedef struct Song
{
    uint8_t size;
    Note * notes[];
} Song;

 
 
void chooseSong(Song *, uint16_t);
void stopSong();
void setNote(Note *, int);
void setSleep(int);

//Externals
extern int ENABLE_SLEEP;
extern Song* currentSong;
extern uint16_t currentNoteLen;
extern uint32_t i;
extern uint16_t songProgress;
extern uint16_t progress;
 
extern Note G7;
extern Note G6;
extern Note G5;
extern Note G4;
extern Note G3;
extern Note A3;
extern Note A5;
extern Note A4;
extern Note E5;
extern Note E4;
extern Note E7;
extern Note E6;
extern Note C7;
extern Note C6;
extern Note C5;
extern Note C4;
extern Note AS4;
extern Note CS5;
extern Note CS4;
extern Note F3;
extern Note F4;
extern Note F5;
extern Note B4;
extern Note B5;
extern Note FS3;
extern Note FS4;
extern Note FS5;
extern Note B3;
extern Note D4;
extern Note D5;
extern Note D3;
extern Song A;
extern Song B;
extern Song C;
extern Song GOT;
extern Song SHOOTING;
extern Song OUT;
extern Song PING;
extern Song PONG;
extern Song WALL;
