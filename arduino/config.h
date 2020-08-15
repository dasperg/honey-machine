// config.h
/**
 * This is main configuration file
 */
#define SECOND 1000
#define LOCK HIGH
#define UNLOCK LOW

#define R1 47000
#define R2 8200

int config() 
{
    #ifndef LED_BUILTIN {
        #define LED_BUILTIN 24
    #endif

    /* Display */
    #define DISPLAY_ADDR 0x3c
    #ifndef SDA 
        #define SDA 42
    #endif
    #ifndef SCL
        #define SCL 35
    #endif

    /* Positions/doors */
    #define DOOR_TIME 0.1 * SECOND

    /* Coins & price */
    #define COIN_PIN 18
    #define COIN_AMOUNT 2

    // Voltage monitor
    #define VOLTAGE_PIN A0
}
