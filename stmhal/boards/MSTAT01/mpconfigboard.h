#define MSTAT01
//// PYBV10 must be defined for some features to work
#define PYBV10

#define MICROPY_HW_BOARD_NAME       "MSTAT01"
#define MICROPY_HW_MCU_NAME         "STM32F405RG"
#define MICROPY_PY_SYS_PLATFORM     "pyboard"

#define MICROPY_HW_HAS_SWITCH       (1)
#define MICROPY_HW_HAS_SDCARD       (0)
#define MICROPY_HW_HAS_MMA7660      (0)
#define MICROPY_HW_HAS_LIS3DSH      (0)
#define MICROPY_HW_HAS_LCD          (0) 
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_TIMER     (1)
#define MICROPY_HW_ENABLE_SERVO     (0)
#define MICROPY_HW_ENABLE_DAC       (0)
#define MICROPY_HW_ENABLE_I2C1      (1)
#define MICROPY_HW_ENABLE_SPI1      (1)
#define MICROPY_HW_ENABLE_SPI2      (1) // new AM
#define MICROPY_HW_ENABLE_SPI3      (0)
#define MICROPY_HW_ENABLE_CC3K      (0)
#define MICROPY_HW_ENABLE_CAN       (0)


// USRSW has no pullup or pulldown, and pressing the switch makes the input go low
#define MICROPY_HW_USRSW_PIN        (pin_A0)  /// (pin_A0) //=nustat10 //B3 = pyV10
#define MICROPY_HW_USRSW_PULL       (GPIO_NOPULL) //(GPIO_PULLDOWN) //(GPIO_PULLUP)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_RISING) // (GPIO_MODE_IT_FALLING)
#define MICROPY_HW_USRSW_PRESSED    (1) // (0)

/*
// The pyboard has 4 LEDs
#define MICROPY_HW_LED1             (pin_A13) // red
#define MICROPY_HW_LED2             (pin_A14) // green
#define MICROPY_HW_LED3             (pin_A15) // yellow
#define MICROPY_HW_LED4             (pin_B4)  // blue

#define MICROPY_HW_LED1             (pin_A2) // red
#define MICROPY_HW_LED2             (pin_A1) // green 
#define MICROPY_HW_LED3             (pin_A3) // blue
#define MICROPY_HW_LED4             (pin_A3)  // yellow
#define MICROPY_HW_LED_OTYPE        (GPIO_MODE_OUTPUT_PP)
#define MICROPY_HW_LED_ON(pin)      (pin->gpio->BSRRL = pin->pin_mask) // BSRRL = reverse, shines when turned on 
#define MICROPY_HW_LED_OFF(pin)     (pin->gpio->BSRRH = pin->pin_mask) // BSRRH = reverse logic
*/
// SD card detect switch
/*#define MICROPY_HW_SDCARD_DETECT_PIN        (pin_C5)  // was pin_A4 floating ...
#define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP) // was GPIO_PULLUP
#define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_RESET)
*/