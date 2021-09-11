 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H
/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1000U)

/* Dio Module Id */
#define PORT_MODULE_ID    (124U)

/* Dio Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Dio Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"
/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "PortCfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PortCfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PortCfg.h does not match the expected version"
#endif

#include "Common_Macros.h"


   
/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORT_A_BASE                (uint32)0x40004000

#define GPIO_PORT_B_BASE                (uint32)0x40005000

#define GPIO_PORT_C_BASE                (uint32)0x40006000

#define GPIO_PORT_D_BASE                (uint32)0x40007000

#define GPIO_PORT_E_BASE                (uint32)0x40024000

#define GPIO_PORT_F_BASE                (uint32)0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
   
#define PORT_DIR_REG_OFFSET               0x400
   
#define PORT_ALT_FUNC_REG_OFFSET          0x420
   
#define PORT_PULL_UP_REG_OFFSET           0x510
   
#define PORT_PULL_DOWN_REG_OFFSET         0x514
   
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
   
#define PORT_LOCK_REG_OFFSET              0x520
   
#define PORT_COMMIT_REG_OFFSET            0x524
   
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
   
#define PORT_CTL_REG_OFFSET               0x52C
   
/* Port Numbering */

#define PORT_A                   (0U)

#define PORT_B                   (1U)

#define PORT_C                   (2U)

#define PORT_D                   (3U)

#define PORT_E                   (4U)

#define PORT_F                   (5U)
   
/* PIN Indexing */

#define PORT_A_PIN_0                     (uint8)(0)
#define PORT_A_PIN_1                     (uint8)(1)
#define PORT_A_PIN_2                     (uint8)(2)
#define PORT_A_PIN_3                     (uint8)(3)
#define PORT_A_PIN_4                     (uint8)(4)
#define PORT_A_PIN_5                     (uint8)(5)
#define PORT_A_PIN_6                     (uint8)(6)
#define PORT_A_PIN_7                     (uint8)(7)
#define PORT_B_PIN_0                     (uint8)(8)
#define PORT_B_PIN_1                     (uint8)(9)
#define PORT_B_PIN_2                     (uint8)(10)
#define PORT_B_PIN_3                     (uint8)(11)
#define PORT_B_PIN_4                     (uint8)(12)
#define PORT_B_PIN_5                     (uint8)(13)
#define PORT_B_PIN_6                     (uint8)(14)
#define PORT_B_PIN_7                     (uint8)(15)
#define PORT_C_PIN_0                     (uint8)(16)
#define PORT_C_PIN_1                     (uint8)(17)
#define PORT_C_PIN_2                     (uint8)(18)
#define PORT_C_PIN_3                     (uint8)(19)
#define PORT_C_PIN_4                     (uint8)(20)
#define PORT_C_PIN_5                     (uint8)(21)
#define PORT_C_PIN_6                     (uint8)(22)
#define PORT_C_PIN_7                     (uint8)(23)
#define PORT_D_PIN_0                     (uint8)(24)
#define PORT_D_PIN_1                     (uint8)(25)
#define PORT_D_PIN_2                     (uint8)(26)
#define PORT_D_PIN_3                     (uint8)(27)
#define PORT_D_PIN_4                     (uint8)(28)
#define PORT_D_PIN_5                     (uint8)(29)
#define PORT_D_PIN_6                     (uint8)(30)
#define PORT_D_PIN_7                     (uint8)(31)
#define PORT_E_PIN_0                     (uint8)(32)
#define PORT_E_PIN_1                     (uint8)(33)
#define PORT_E_PIN_2                     (uint8)(34)
#define PORT_E_PIN_3                     (uint8)(35)
#define PORT_E_PIN_4                     (uint8)(36)
#define PORT_E_PIN_5                     (uint8)(37)
#define PORT_F_PIN_0                     (uint8)(38)
#define PORT_F_PIN_1                     (uint8)(39)
#define PORT_F_PIN_2                     (uint8)(40)
#define PORT_F_PIN_3                     (uint8)(41)
#define PORT_F_PIN_4                     (uint8)(42)

   
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port Init */
#define PORT_INIT_SID                       (uint8)0x00

#define PORT_SET_PIN_DIR_SID                (uint8)0x01
   
#define PORT_REFRESH_PORT_DIR_SID           (uint8)0x02
   
#define PORT_GET_VERSION_INFO_SID           (uint8)0x03
   
#define PORT_SET_PIN_MODE_SID               (uint8)0x04
   
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                    (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE       (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                 (uint8)0x0C

/* DET code to report API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_PARAM_INVALID_MODE           (uint8)0x0D

/* DET code to report API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_MODE_UNCHANGEABLE            (uint8)0x0E
   
/* DET code to report API service called without module initialization */
#define PORT_E_UNINIT                       (uint8)0x0F
   
/* DET code to report APIs called with a Null Pointer */       
#define PORT_E_PARAM_POINTER                (uint8)0x10

   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Enum to hold direction changeability type for PIN */
typedef enum
{
    NON_CHANGEABLE_D , CHANGEABLE_D
}Port_ChangeableDirection;

/* Description: Enum to hold mode changeability type for PIN */
typedef enum
{
    NON_CHANGEABLE_M , CHANGEABLE_M
}Port_ChangeableMode;

/* Description: Enum to hold signal type for PIN */
typedef enum
{
    ANALOG , DIGITAL
}Port_PinSignalType;

/* Description: Enum to hold mode type for PIN */
typedef enum
{
    PORT_PIN_MODE_DIO , OTHER
}Port_PinModeType;

/* Description: Enum to hold initial value for PIN */
typedef enum
{
    PORT_PIN_LEVEL_LOW , PORT_PIN_LEVEL_HIGH
}Port_InitialValue;

/* Description: Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Description: Data type for the symbolic name of a port number */
typedef uint8 Port_PortNum;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct 
{
    Port_PortNum port_num; 
    Port_PinType pin_num; 
    Port_PinDirectionType PORT_PIN_DIRECTION;
    Port_ChangeableDirection PORT_PIN_DIRECTION_CHANGEABLE;
    Port_InternalResistor resistor;
    Port_PinModeType PORT_PIN_INITIAL_MODE;
    Port_ChangeableMode PORT_PIN_MODE_CHANGEABLE;
    Port_PinSignalType signal;
    Port_InitialValue PORT_PIN_LEVEL_VALUE;
}Port_ConfigPin;

typedef struct
{
  Port_ConfigPin Channels[PORT_NUMBER_OF_PINS_SUPPORTED];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );

/* Function for PORT set pin Direction API*/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif


/* Function for PORT refresh port direction API */
void Port_RefreshPortDirection( void );

/* Function for PORT get version info API*/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif


/* Function for PORT set pin mode API */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif


 /*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
