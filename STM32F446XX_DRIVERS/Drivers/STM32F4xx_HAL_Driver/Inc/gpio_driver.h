/*
 * gpio_driver.h
 *
 *  Created on: 29 Sep 2018
 *      Author: wjshin
 */

#ifndef STM32F4XX_HAL_DRIVER_INC_GPIO_DRIVER_H_
#define STM32F4XX_HAL_DRIVER_INC_GPIO_DRIVER_H_

//#include "stm32f4xx.h"
#include "stm32f446xx.h"

/*
 * Imported from RM0390 STM32F446xx Reference Manual
 */

/*
 * General Purpose I/O
 * Macros
 */

/* GPIOs are under AHB1 */
/* GPIOx Clock Enable/Disable Macros */
#define RCC_AHB1_GPIOA_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 0))
#define RCC_AHB1_GPIOA_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 0))
#define RCC_AHB1_GPIOB_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 1))
#define RCC_AHB1_GPIOB_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 1))
#define RCC_AHB1_GPIOC_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 2))
#define RCC_AHB1_GPIOC_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 2))
#define RCC_AHB1_GPIOD_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 3))
#define RCC_AHB1_GPIOD_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 3))
#define RCC_AHB1_GPIOE_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 4))
#define RCC_AHB1_GPIOE_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 4))
#define RCC_AHB1_GPIOF_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 5))
#define RCC_AHB1_GPIOF_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 5))
#define RCC_AHB1_GPIOG_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 6))
#define RCC_AHB1_GPIOG_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 6))
#define RCC_AHB1_GPIOH_CLOCK_ENABLE()  (RCC->AHB1ENR |= (1U << 7))
#define RCC_AHB1_GPIOH_CLOCK_DISABLE() (RCC->AHB1ENR &= (0U << 7))

/* register boundary addresses */
#define AHB1_BASE                   (0x40020000U)
#define AHB1_GPIOA_BASE             (AHB1_BASE + 0x0000U)
#define AHB1_GPIOB_BASE             (AHB1_BASE + 0x0400U)
#define AHB1_GPIOC_BASE             (AHB1_BASE + 0x0800U)
#define AHB1_GPIOD_BASE             (AHB1_BASE + 0x0C00U)
#define AHB1_GPIOE_BASE             (AHB1_BASE + 0x1000U)
#define AHB1_GPIOF_BASE             (AHB1_BASE + 0x1400U)
#define AHB1_GPIOG_BASE             (AHB1_BASE + 0x1800U)
#define AHB1_GPIOH_BASE             (AHB1_BASE + 0x1C00U)

#define GPIOA                       ((GPIO_REG_T *)AHB1_GPIOA_BASE)
#define GPIOB                       ((GPIO_REG_T *)AHB1_GPIOB_BASE)
#define GPIOC                       ((GPIO_REG_T *)AHB1_GPIOC_BASE)
#define GPIOD                       ((GPIO_REG_T *)AHB1_GPIOD_BASE)
#define GPIOE                       ((GPIO_REG_T *)AHB1_GPIOE_BASE)
#define GPIOF                       ((GPIO_REG_T *)AHB1_GPIOF_BASE)
#define GPIOG                       ((GPIO_REG_T *)AHB1_GPIOG_BASE)
#define GPIOH                       ((GPIO_REG_T *)AHB1_GPIOH_BASE)

/* GPIO Registers */
/* GPIOx_MODER (x = A..H) */
#define GPIO_MODER_BITS             (2U)    /*!< Bits 2y:2y+1 MODERy[1:0] (y = 0..15) */
#define GPIO_MODER_MASK             (3U)
#define GPIO_MODER_POS(Pin)         (Pin * GPIO_MODER_BITS)
#define GPIO_MODER_VAL_INPUT        (0U)    /*!< Input (reset state) */
#define GPIO_MODER_VAL_OUTPUT       (1U)    /*!< General purpose output mode */
#define GPIO_MODER_VAL_ALT          (2U)    /*!< Alternate function mode */
#define GPIO_MODER_VAL_ANAL         (3U)    /*!< Analog mode */

/* GPIOx_OTYPER (x = A..H) */
#define GPIO_OTYPER_BITS            (1U)    /*!< Bits 15:0 OTy (y = 0..15) */
#define GPIO_OTYPER_MASK            (1U)
#define GPIO_OTYPER_POS(Pin)        (Pin * GPIO_OTYPER_BITS)
#define GPIO_OTYPER_VAL_PUSHPULL    (0U)    /*!< Output push-pull (reset state) */
#define GPIO_OTYPER_VAL_OPENDRAIN   (1U)    /*!< Output open-drain */

/* GPIOx_OSPEEDR (x = A..H) */
#define GPIO_OSPEEDR_BITS           (2U)    /*!< Bits 2y:2y+1 OSPEEDRy[1:0] (y = 0..15) */
#define GPIO_OSPEEDR_MASK           (3U)
#define GPIO_OSPEEDR_POS(Pin)       (Pin * GPIO_OSPEEDR_BITS)
#define GPIO_OSPEEDR_VAL_LOW        (0U)    /*!< Low speed */
#define GPIO_OSPEEDR_VAL_MEDIUM     (1U)    /*!< Medium speed */
#define GPIO_OSPEEDR_VAL_FAST       (2U)    /*!< Fast speed */
#define GPIO_OSPEEDR_VAL_HIGH       (3U)    /*!< High speed */

/* GPIOx_PUPDR (x = A..H) */
#define GPIO_PUPDR_BITS             (2U)    /*!< Bits 2y:2y+1 PUPDRy[1:0] (y = 0..15) */
#define GPIO_PUPDR_MASK             (3U)
#define GPIO_PUPDR_POS(Pin)         (Pin * GPIO_PUPDR_BITS)
#define GPIO_PUPDR_VAL_NOPULLUPDOWN (0U)    /*!< No pull-up, pull-down */
#define GPIO_PUPDR_VAL_PULLUP       (1U)    /*!< Pull-up */
#define GPIO_PUPDR_VAL_PULLDOWN     (2U)    /*!< Pull-down */
//#define GPIO_PUPDR_VAL_RESERVED     (3U)    /*!< Reserved */

/* GPIOx_IDR (x = A..H) */
#define GPIO_IDR_BITS               (1U)    /*!< Bits 15:0 IDRy (y = 0..15) */
#define GPIO_IDR_MASK               (1U)
#define GPIO_IDR_POS(Pin)           (Pin * GPIO_IDR_BITS)

/* GPIOx_ODR (x = A..H) */
#define GPIO_ODR_BITS               (1U)    /*!< Bits 15:0 ODRy (y = 0..15) */
#define GPIO_ODR_MASK               (1U)
#define GPIO_ODR_POS(Pin)           (Pin * GPIO_IDR_BITS)

/* GPIOx_BSRR (x = A..H) */
#define GPIO_BSRR_BITS              (1U)    /*!< Bits 31:16 BRy (y = 0..15) */
                                            /*!< Bits 15:0 BSy (y = 0..15) */
#define GPIO_BSRR_MASK              (1U)
#define GPIO_BSRR_POS(Pin)          (Pin * GPIO_BSRR_BITS)
#define GPIO_BSRR_VAL_BS_NO         (0U)    /*!< No action on the corresponding ODRx bit */
#define GPIO_BSRR_VAL_BS_SET        (1U)    /*!< Resets the corresponding ODRx bit */
#define GPIO_BSRR_VAL_BR_NO         (0U)    /*!< No action on the corresponding ODRx bit */
#define GPIO_BSRR_VAL_BR_RESET      (1U)    /*!< Sets the corresponding ODRx bit */

/* GPIOx_LCKR (x = A..H) */
#define GPIO_LCKR_BITS              (1U)    /*!< Bit 16 LCKK[16] */
                                            /*!< Bit 15:0 LCKy (y= 0..15)*/
#define GPIO_LCKR_MASK              (1U)
#define GPIO_LCKR_POS(Pin)          (Pin * GPIO_LCKR_BITS)
#define GPIO_LCKR_VAL_LOCKNOTACTIVE (0U)    /*!< Port configuration lock key not active */
#define GPIO_LCKR_VAL_LOCKACTIVE    (1U)    /*!< Port configuration lock key active. The GPIOx_LCKR register is locked until an MCU reset occurs. */
#define GPIO_LCKR_VAL_NOLOCK        (0U)    /*!< Port configuration not locked */
#define GPIO_LCKR_VAL_LOCK          (1U)    /*!< Port configuration locked */
/*
 * LOCK key write sequence:
 *  WR LCKR[16] = '1' + LCKR[15:0]
 *  WR LCKR[16] = '0' + LCKR[15:0]
 *  WR LCKR[16] = '1' + LCKR[15:0]
 *  RD LCKR
 *  RD LCKR[16] = '1' (this read operation is optional but it confirms that the lock is active)
 * Note: During the LOCK key write sequence, the value of LCK[15:0] must not change.
 *       Any error in the lock sequence aborts the lock.
 *       After the first lock sequence on any bit of the port, any read access on the LCKK bit will return '1' until the next CPU reset.
 */

/* GPIOx_AFRL (x = A..H) */
#define GPIO_AFRL_BITS               (4U)    /*!< Bits 31:0 AFRLy (y = 0..7) */
#define GPIO_AFRL_MASK               (15U)
#define GPIO_AFRL_POS(Pin)           (Pin * GPIO_AFRL_BITS)
#define GPIO_AFRL_VAL_AF0            (0U)    /*!< AF0 */
#define GPIO_AFRL_VAL_AF1            (1U)    /*!< AF1 */
#define GPIO_AFRL_VAL_AF2            (2U)    /*!< AF2 */
#define GPIO_AFRL_VAL_AF3            (3U)    /*!< AF3 */
#define GPIO_AFRL_VAL_AF4            (4U)    /*!< AF4 */
#define GPIO_AFRL_VAL_AF5            (5U)    /*!< AF5 */
#define GPIO_AFRL_VAL_AF6            (6U)    /*!< AF6 */
#define GPIO_AFRL_VAL_AF7            (7U)    /*!< AF7 */
#define GPIO_AFRL_VAL_AF8            (8U)    /*!< AF8 */
#define GPIO_AFRL_VAL_AF9            (9U)    /*!< AF9 */
#define GPIO_AFRL_VAL_AF10           (10U)   /*!< AF10 */
#define GPIO_AFRL_VAL_AF11           (11U)   /*!< AF11 */
#define GPIO_AFRL_VAL_AF12           (12U)   /*!< AF12 */
#define GPIO_AFRL_VAL_AF13           (13U)   /*!< AF13 */
#define GPIO_AFRL_VAL_AF14           (14U)   /*!< AF14 */
#define GPIO_AFRL_VAL_AF15           (15U)   /*!< AF15 */

/* GPIOx_AFRH (x = A..H) */
#define GPIO_AFRH_BITS               (4U)    /*!< Bits 31:0 AFRHy (y = 8..15) */
#define GPIO_AFRH_MASK               (15U)
#define GPIO_AFRH_POS(Pin)           (Pin * GPIO_AFRH_BITS)
#define GPIO_AFRH_VAL_AF0            (0U)    /*!< AF0 */
#define GPIO_AFRH_VAL_AF1            (1U)    /*!< AF1 */
#define GPIO_AFRH_VAL_AF2            (2U)    /*!< AF2 */
#define GPIO_AFRH_VAL_AF3            (3U)    /*!< AF3 */
#define GPIO_AFRH_VAL_AF4            (4U)    /*!< AF4 */
#define GPIO_AFRH_VAL_AF5            (5U)    /*!< AF5 */
#define GPIO_AFRH_VAL_AF6            (6U)    /*!< AF6 */
#define GPIO_AFRH_VAL_AF7            (7U)    /*!< AF7 */
#define GPIO_AFRH_VAL_AF8            (8U)    /*!< AF8 */
#define GPIO_AFRH_VAL_AF9            (9U)    /*!< AF9 */
#define GPIO_AFRH_VAL_AF10           (10U)   /*!< AF10 */
#define GPIO_AFRH_VAL_AF11           (11U)   /*!< AF11 */
#define GPIO_AFRH_VAL_AF12           (12U)   /*!< AF12 */
#define GPIO_AFRH_VAL_AF13           (13U)   /*!< AF13 */
#define GPIO_AFRH_VAL_AF14           (14U)   /*!< AF14 */
#define GPIO_AFRH_VAL_AF15           (15U)   /*!< AF15 */

/*
 * General Purpose I/O Registers
 * Data Structure
 */
typedef struct _GPIO_REG_T {
  __IOM uint32_t MODER;    /*!< Offset: 0x00 (R/W) GPIO port mode register */
  __IOM uint32_t OTYPER;   /*!< Offset: 0x04 (R/W) GPIO port output type register */
  __IOM uint32_t OSPEEDR;  /*!< Offset: 0x08 (R/W) GPIO port output speed register */
  __IOM uint32_t PUPDR;    /*!< Offset: 0x0C (R/W) GPIO port pull-up/pull-down register */
  __IM  uint32_t IDR;      /*!< Offset: 0x10 (R/ ) GPIO port input data register */
  __IOM uint32_t ODR;      /*!< Offset: 0x14 (R/W) GPIO port output data register */
  __OM  uint32_t BSRR;     /*!< Offset: 0x18 ( /W) GPIO port bit set/reset register */
  __IOM uint32_t LCKR;     /*!< Offset: 0x1C (R/W) GPIO port configuration lock register */
  __IOM uint32_t AFRL;     /*!< Offset: 0x20 (R/W) GPIO alternate function low register */
  __IOM uint32_t AFRH;     /*!< Offset: 0x24 (R/W) GPIO alternate function high register */
} GPIO_REG_T;

typedef struct _GPIO_T {
  uint32_t pin;        /*!< GPIO pin number 0 - 15 for each GPIO port */
  uint32_t mode;       /*!< GPIO pin mode */
  uint32_t out_type;   /*!< GPIO pin output type */
  uint32_t out_speed;  /*!< GPIO pin output speed */
  uint32_t pullupdown; /*!< GPIO pin pull-up or pull-down */
  uint32_t alter_fun;  /*!< GPIO pin alternate function */
} GPIO_T;

/*
 * General Purpose I/O
 * Driver exposed APIs
 */

#endif /* STM32F4XX_HAL_DRIVER_INC_GPIO_DRIVER_H_ */
