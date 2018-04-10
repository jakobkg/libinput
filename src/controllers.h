#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <dynamic_libs/padscore_functions.h>
#include <dynamic_libs/vpad_functions.h>
#include <utils/logger.h>

enum buttons {
    PAD_BUTTON_A,
    PAD_BUTTON_B,
    PAD_BUTTON_X,
    PAD_BUTTON_Y,
    PAD_BUTTON_UP,
    PAD_BUTTON_DOWN,
    PAD_BUTTON_LEFT,
    PAD_BUTTON_RIGHT,
    PAD_BUTTON_L,
    PAD_BUTTON_R,
    PAD_BUTTON_ZL,
    PAD_BUTTON_ZR,
    PAD_BUTTON_PLUS,
    PAD_BUTTON_MINUS,
    PAD_BUTTON_Z,
    PAD_BUTTON_C,
    PAD_BUTTON_STICK_L,
    PAD_BUTTON_STICK_R,
    PAD_BUTTON_HOME,
    PAD_BUTTON_SYNC,
    PAD_BUTTON_TV,
    PAD_BUTTON_1,
    PAD_BUTTON_2,
    PAD_BUTTON_ANY
};

enum buttonStates {
    PRESS,
    HOLD,
    RELEASE
};

enum sticks {
    STICK_L = 0,
    STICK_R = 1,
    STICK_BOTH = 2
};

enum stickDirections {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_ANY
};

uint32_t buttons_hold[5]; // Held buttons
uint32_t buttons_pressed[5]; // Pressed buttons
uint32_t buttons_released[5]; // Released buttons
f32 stickPositions[5][2][2];
/* State of joysticks.
First index is controller, second is stick (L and R) and third is direction (X or Y)
These are to be read with checkStick(stick, stickDirection, threshold)
TODO: Implement function to write raw stick data to location of a pointer for direct reading*/

void initControllers();                                         // Initializes controllers, uses a function from dynamic_libs to do so
void deinitControllers();                                       // Deinitializes controllers. Currently disconnects them, as a deinit method is not known. Sets all used memory to 0
void disconnectControllers();                                   // Turns off all connected wireless controllers that are not the gamepad
void pingControllers();                                         // Checks the "slots" for all wireless controllers that are not the gamepad, and writes response to padErrors[]
void updateControllers();                                       // Grabs button and joystick states from all connected wireless controllers and writes them to vpad and pads[]
bool isWiimote(KPADData *padData);                              // Looks at an entry in pads[] and returns whether the controller is a wiimote or not
bool hasNunchuck(KPADData *padData);                            // Looks at an entry in pads[] and returns whether the controller has a nunchuck attached or not
bool isClassicController(KPADData *padData);                    // Looks at an entry in pads[] and returns whether the controller is the Wii Classic Controller or not
bool isProController(KPADData *padData);                        // Looks at an entry in pads[] and returns whether the controller is a Pro Controller or not
bool checkStick(u8 stick, u8 stickDirection, f32 threshold);    // Checks one or both joysticks (see enum sticks) of all controllers
                                                                // and returns whether the stick is being held past a threshold (range 0 - 1) in a given direction (see enum stickDirections)
                                                                // For example, checkStick(STICK_L, DIR_UP, 0.7) returns whether any controller has its left stick pushed more than 70% up
bool checkButton(int button, int state);                        // Checks one, or any, button (see enum buttons) and returns whether or not the button is in a given state (see enum buttonStates)

#ifdef __cplusplus
    }
#endif

#endif //CONTROLLERS_H
