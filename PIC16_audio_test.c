#include "config.h"
#include <stdlib.h>

/** D E F I N E S ***************************************************/
#define PUSHED 0

/** P R I V A T E   V A R I A B L E S *******************************/
static unsigned int audio_on_counter;
static unsigned int audio_off_counter;
static unsigned int audio_decreaser_on;
static unsigned int audio_decreaser_off;
static unsigned int frequency;
static unsigned int beepcount;
static unsigned char random_length;
//static unsigned int random_counter;

static enum {FSM_SHORT_BEEP,FSM_LONG_BEEP,
             FSM_IDLE,
        FSM_VICTORY, FSM_LOSS, FSM_AUDIOSTOP,
        FSM_NOISE
        
            } current_state;
            
void audio_test_init(void) {
    AUDIO_stop();
	current_state = FSM_IDLE;
    audio_on_counter = 0;
    audio_off_counter = 0;
    audio_decreaser_on = 100;
    audio_decreaser_off=300;
    random_length = 20;
    beepcount = 0;
    srand(random_seed);
}


void audio_test(void) {
    
    switch (current_state) { 
        case FSM_IDLE :
            beepcount = 0;
            //AUDIO_stop();
            current_state = FSM_IDLE;
            break;
        case FSM_SHORT_BEEP :
            audio_on_counter++;
            AUDIO_play(frequency);
            if(audio_on_counter>200) {
                audio_on_counter = 0;
                AUDIO_stop();
                current_state = FSM_IDLE;
            }
            break;
        case FSM_LONG_BEEP :
            audio_on_counter++;
            AUDIO_play(frequency);
            if(audio_on_counter>400) {
                audio_on_counter = 0;
                AUDIO_stop();
                current_state = FSM_IDLE;
            }
            break;
        case FSM_VICTORY: 
            audio_on_counter++;
            if(audio_on_counter<50) {
                
            }
            else if ((audio_on_counter >=50) &&( audio_on_counter <100)) {
                AUDIO_play(C1);
            }
            else if ((audio_on_counter >= 100) && (audio_on_counter<300) ) {
                AUDIO_play(G2);
            } else if (audio_on_counter >= 300) {
                AUDIO_stop;
                audio_on_counter =0;
                current_state = FSM_AUDIOSTOP;
            }
            break;
        case FSM_LOSS :
            
            if(audio_on_counter < 50) {
                AUDIO_play(F2);
                audio_on_counter++;
            } else if ((audio_on_counter>=50) && (audio_on_counter <100)) {
                AUDIO_stop();
                audio_on_counter++;
            } else if (audio_on_counter>=100) {
                audio_on_counter =0;
                beepcount++;
            }
            if(beepcount>5) {
                
                current_state = FSM_IDLE;
            } else {
                current_state = FSM_LOSS;
            }
            break;
        case FSM_AUDIOSTOP :
            AUDIO_stop();
            current_state = FSM_IDLE;
            break;
            
            
            
        case FSM_NOISE :
            
            audio_on_counter++;            
            if(audio_on_counter %random_length == 0) {
                AUDIO_stop();
            } else if (audio_on_counter %random_length == 1) {
                AUDIO_play(((rand() % 200) + 100) * random_seed );
                random_length = rand() % 40;
            }
            if(audio_on_counter > 2000) {
                AUDIO_stop();
                current_state = FSM_IDLE;
                        
            }
            
            break;      
            
            
            
        default : 
            current_state = FSM_IDLE;
            break;
    }
    
}

void audio_short_beep(unsigned int freq) {
    frequency = freq;
    current_state = FSM_SHORT_BEEP;
    
}
void audio_long_beep(unsigned int freq) {
    frequency = freq;
    current_state = FSM_LONG_BEEP;
    
}
void audio_victory(void) {
    current_state = FSM_VICTORY;
}
void audio_loss(void) {
    current_state = FSM_LOSS;
}
void audio_noise(void) {
    current_state = FSM_NOISE;
}
