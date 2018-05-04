#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <dynamic_libs/padscore_functions.h>
#include <dynamic_libs/vpad_functions.h>
#include <utils/logger.h>

#define CONTROLLER_BUTTON_A         0x00000001
#define CONTROLLER_BUTTON_B         0x00000002
#define CONTROLLER_BUTTON_X         0x00000004
#define CONTROLLER_BUTTON_Y         0x00000008
#define CONTROLLER_BUTTON_UP        0x00000010
#define CONTROLLER_BUTTON_DOWN      0x00000020
#define CONTROLLER_BUTTON_LEFT      0x00000040
#define CONTROLLER_BUTTON_RIGHT     0x00000080
#define CONTROLLER_BUTTON_L         0x00000100
#define CONTROLLER_BUTTON_R         0x00000200
#define CONTROLLER_BUTTON_ZL        0x00000400
#define CONTROLLER_BUTTON_ZR        0x00000800
#define CONTROLLER_BUTTON_PLUS      0x00001000
#define CONTROLLER_BUTTON_MINUS     0x00002000
#define CONTROLLER_BUTTON_Z         0x00004000
#define CONTROLLER_BUTTON_C         0x00008000
#define CONTROLLER_BUTTON_1         0x00010000
#define CONTROLLER_BUTTON_2         0x00020000
#define CONTROLLER_BUTTON_HOME      0x00040000
#define CONTROLLER_BUTTON_SYNC      0x00080000
#define CONTROLLER_BUTTON_TV        0x00100000
#define CONTROLLER_BUTTON_STICK_L   0x00200000
#define CONTROLLER_BUTTON_STICK_R   0x00400000
#define CONTROLLER_BUTTON_ANY       0xFFFFFFFF

#define CONTROLLER_TYPE_WIIMOTE     0x01
#define CONTROLLER_TYPE_NUNCHUCK    0x03
#define CONTROLLER_TYPE_MOTIONPLUS  0x05
#define CONTROLLER_TYPE_CLASSIC     0x08
#define CONTROLLER_TYPE_PRO         0x10
#define CONTROLLER_TYPE_GAMEPAD     0x20
#define CONTROLLER_TYPE_ALL         0xFF

#define NIN_CTR_TYPE_WIIMOTE        0
#define NIN_CTR_TYPE_NUNCHUCK       1
#define NIN_CTR_TYPE_CLASSIC        2
#define NIN_CTR_TYPE_MOTIONPLUS     5
#define NIN_CTR_TYPE_MPLUSNUNCHUCK  6
#define NIN_CTR_TYPE_MPLUSCLASSIC   7
#define NIN_CTR_TYPE_PRO            31

typedef struct _ControllerData {
    u32 btns_h,
    u32 btns_d,
    u32 btns_r,
    f32 lstick_x,
    f32 lstick_y,
    f32 rstick_x,
    f32 rstick_y,
    u8 controller_type,
    s8 controller_error
} ControllerData;

// enum buttons {
//     PAD_BUTTON_A = 1,
//     PAD_BUTTON_B = 1 << 1,
//     PAD_BUTTON_X = 1 << 2,
//     PAD_BUTTON_Y = 1 << 3,
//     PAD_BUTTON_UP = 1 << 4,
//     PAD_BUTTON_DOWN = 1 << 5,
//     PAD_BUTTON_LEFT = 1 << 6,
//     PAD_BUTTON_RIGHT = 1 << 7,
//     PAD_BUTTON_L = 1 << 8,
//     PAD_BUTTON_R = 1 << 9,
//     PAD_BUTTON_ZL = 1 << 10,
//     PAD_BUTTON_ZR = 1 << 11,
//     PAD_BUTTON_PLUS = 1 << 12,
//     PAD_BUTTON_MINUS = 1 << 13,
//     PAD_BUTTON_Z = 1 << 14,
//     PAD_BUTTON_C = 1 << 15,
//     PAD_BUTTON_1 = 1 << 16,
//     PAD_BUTTON_2 = 1 << 17,
//     PAD_BUTTON_HOME = 1 << 18,
//     PAD_BUTTON_SYNC = 1 << 19,
//     PAD_BUTTON_TV = 1 << 20,
//     PAD_BUTTON_STICK_L = 1 << 21,
//     PAD_BUTTON_STICK_R = 1 << 22,
//     PAD_BUTTON_ANY = 1 << 31
// };

enum buttonStates {
    PRESS,
    HOLD,
    RELEASE
};

enum sticks {
    STICK_L = 0x01,
    STICK_R = 0x10,
    STICK_BOTH = 0x11
};

enum stickDirections {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_ANY
};

void initControllers();                                         // Initializes controllers, uses a function from dynamic_libs to do so
void deinitControllers();                                       // Deinitializes controllers. Currently disconnects them, as a deinit method is not known. Sets all used memory to 0
void ControllerRead(ControllerData *data);                      // Read all available controllers and OR their data together
void ControllerRead(ControllerData *data, u16 filter);
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
