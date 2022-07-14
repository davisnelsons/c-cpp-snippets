
/** I N C L U D E S *************************************************/
#include "config.h"
#include <stdlib.h>

/** D E F I N E S ***************************************************/
#define PUSHED 0

/** P R I V A T E   V A R I A B L E S *******************************/
static unsigned int audio_on_counter;
static unsigned int audio_off_counter;
static unsigned int audio_decreaser_off;


static enum {FSM_BEEP,
             FSM_IDLE
        
            } current_state;
            
            

void audio_beeps_init(void) {
    AUDIO_stop();
	current_state = FSM_IDLE;
    audio_on_counter = 0;
    audio_off_counter = 0;
    audio_decreaser_off=3000;
}

void audio_beeps(void) {
    
    switch (current_state) { 
        case FSM_IDLE :
            
            audio_off_counter++;
            if(audio_decreaser_off<audio_off_counter) {
                audio_decreaser_off--;
                audio_off_counter = 0;
                current_state = FSM_BEEP;
            }
            break;
        case FSM_BEEP :
            AUDIO_play(F1);
            audio_on_counter++;
            if(audio_on_counter >100) {
                audio_on_counter = 0;
                current_state = FSM_IDLE;
                AUDIO_stop();
            }
            
            break;
        
        default : 
            current_state = FSM_IDLE;
            break;
    }
    
}


