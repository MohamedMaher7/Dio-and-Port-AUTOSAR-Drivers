 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Maher
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif
   
/*variable to store the port status */
static volatile uint8  PORT_Status = PORT_NOT_INITIALIZED;



/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr ){

	/* variable to track the error */
	boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{       error = TRUE;
	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
			PORT_E_PARAM_CONFIG);
	}
	else{
		/*do nothing*/
	}
#endif  
	/* run the service if there is no error (or the DEV error detect is off )*/
	if(error == FALSE){
		/*counter for the for loop looping on the array of config structures*/
		uint8 counter = 0 ;
		/*variable to store the PORT ID in the MCU*/
		uint8 Port_Num = 0 ;
		/*variable to store the Pin ID in the MCU */
		uint8 Pin_Num = 0 ;

		for(counter = 0; counter < PORT_NUMBER_OF_PINS_SUPPORTED; counter++ ){
                  
			Port_Num = ConfigPtr->Channels[counter].port_num;
			Pin_Num = ConfigPtr->Channels[counter].pin_num;
			volatile uint32 * GPIO_PORT_BASE_REG = NULL_PTR;
			volatile uint32 delay = 0;


			switch(Port_Num){
			/* Port A */
			case PORT_A:	  
				GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_A_BASE;
				break;

				/*Port B */  
			case PORT_B:
				GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_B_BASE;
				break;

				/*Port c */  
			case PORT_C:
				GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_C_BASE;
				break;

				/*Port D */  
			case PORT_D:
				GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_D_BASE;
				break;

				/*Port E */  
			case PORT_E:
				GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_E_BASE;
				break;

				/*Port F */  
			case PORT_F:
				GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_F_BASE;
				break;

			}

			/* Enable clock for PORT and allow time for clock to start*/
			SYSCTL_REGCGC2_REG |= (1<<Port_Num);
			delay = SYSCTL_REGCGC2_REG;

			/*start of configuration */
			/*unlock the locked pins */
			if( ((Port_Num == PORT_D) && (Pin_Num == 7)) || ((Port_Num == PORT_F) && (Pin_Num == 0)) ) /* PD7 or PF0 */
			{
				*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_COMMIT_REG_OFFSET) , Pin_Num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
			}
			else if( (Port_Num == PORT_C) && (Pin_Num <= 3) ) /* PC0 to PC3 */
			{
				/* skip this loop iteration */
				continue;
				/* Do Nothing ...  this is the JTAG pins */

			}
			else
			{
				/* Do Nothing ... No need to unlock the commit register for this pin */
			}

			/*configure the pin direction */
			switch(ConfigPtr->Channels[counter].PORT_PIN_DIRECTION){
			/* the pin is configured as input pin  */
			case PORT_PIN_IN:
				/*configure the pin as input pin*/
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DIR_REG_OFFSET) , Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
				/*Enable the internal pull up resistance */
				if(ConfigPtr->Channels[counter].resistor == PULL_UP){
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_PULL_UP_REG_OFFSET) , Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
				}
				/*Enable the internal pull down resistance */
				else if(ConfigPtr->Channels[counter].resistor == PULL_DOWN){
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_PULL_DOWN_REG_OFFSET) , Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
				}
				/*disable both the internal pull up and pull down resistance */
				else{
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_PULL_UP_REG_OFFSET) , Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_PULL_DOWN_REG_OFFSET) , Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
				}
				break;
				/*the pin is configured as output pin */  
			case PORT_PIN_OUT:
				/*configure the pin as output pin*/
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DIR_REG_OFFSET) , Pin_Num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
				/* put the intial output value */
				if(ConfigPtr->Channels[counter].PORT_PIN_LEVEL_VALUE == PORT_PIN_LEVEL_HIGH)
				{
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DATA_REG_OFFSET) , Pin_Num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
				}
				else
				{
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DATA_REG_OFFSET) , Pin_Num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
				}
				break;
			}
			/*configure the pin Analog or digital */
			switch(ConfigPtr->Channels[counter].signal){
			/* the pin is configured as analog pin  */
			case ANALOG:
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DIGITAL_ENABLE_REG_OFFSET),Pin_Num);
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ANALOG_MODE_SEL_REG_OFFSET),Pin_Num);
				break;
				/*the pin is configured as digital pin */  
			case DIGITAL:
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DIGITAL_ENABLE_REG_OFFSET),Pin_Num);
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ANALOG_MODE_SEL_REG_OFFSET),Pin_Num);
				break;
			}

			/*configure the pin function */
			switch(ConfigPtr->Channels[counter].PORT_PIN_INITIAL_MODE){
			/* the pin intital mode is Digital input output */
			case PORT_PIN_MODE_DIO :
				/* clear the bit in GPIO alternate function select register to configure the bit as DIO pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ALT_FUNC_REG_OFFSET) , Pin_Num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

				/* configure the pin direction */
				break;
				/* the pin intital mode is analog digital converter */ 
			default:
				/*Enable the alternative function */
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ALT_FUNC_REG_OFFSET),Pin_Num);

				break;
			}
			/* set the mode number in the CTL reg */
			*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_Num * 4)) | ((ConfigPtr->Channels[counter].PORT_PIN_INITIAL_MODE)<<(Pin_Num*4));


			/*end of loop */

		}
		/* change the port status to intitialized */    
		PORT_Status = PORT_INITIALIZED;
	}
	else{
		/*do nothing */
	}


}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - port pin ID number
                   Direction - port pin direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the port pin direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){
    
    /* variable to track the error */
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
  /*check if the port driver is not intiallized */
    if(PORT_Status == PORT_NOT_INITIALIZED){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID,
		     PORT_E_UNINIT);
      
    }
    else{
    /* do nothing */
    }
    
    /*check if the pin ID passed is correct */
    if(Pin >= PORT_NUMBER_OF_PINS_SUPPORTED){
      error = TRUE ;
       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID,
		     PORT_E_PARAM_PIN);
    
    }
    else{
      /*do nothing */
    }
    
    /* check if the port pin is not configured as changeable */
    if(Port_Configuration.Channels[Pin].PORT_PIN_DIRECTION_CHANGEABLE == STD_OFF){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID,
		     PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else{
    /*do nothing*/
    }
#endif
    /* run the service if there is no error (or the DEV error detect is off )*/
    if(error == FALSE){
		
        /*variable to store the Pin ID in the MCU */
        uint8 Pin_Num = Port_Configuration.Channels[Pin].pin_num;
		
        volatile uint32 * GPIO_PORT_DIR_REG = NULL_PTR;
                 
                      
                      if(Pin < 8)
					  {
                          /*set the PTR to port A*/
                          GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTA_DIR_REG;
					  }
                          
                      else if(Pin < 16)
					  {
                          /*set the PTR to port B*/
                          GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTB_DIR_REG;
					  }
                      
					  else if(Pin < 24)
					  {
                          /*set the PTR to port C*/
                          GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTC_DIR_REG;
					  }
                      else if(Pin < 32)
					  {
                          /*set the PTR to port D*/
                         GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTD_DIR_REG;
					  }
                      else if(Pin < 38)
					  {
                          /*set the PTR to port E*/
                         GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTE_DIR_REG;
					  }
					  else if(Pin < 43)
					  {
                          /*set the PTR to port F*/
                          GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTF_DIR_REG;
					  }
                             
                       
                    if(Direction == PORT_PIN_IN){
                          CLEAR_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                          }
                          /*the pin is configured as output pin */ 
                    else if(Direction == PORT_PIN_OUT){
                            SET_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                    }
    
    
    }





}
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to refresh port direction
 ************************************************************************************/
void Port_RefreshPortDirection( void ){
	/* variable to track the error */
	boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/*check if the port driver is not intiallized */
	if(PORT_Status == PORT_NOT_INITIALIZED){
		error = TRUE;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIR_SID,
				PORT_E_UNINIT);

	}
	else{
		/* do nothing */
	}
#endif
	if(error == FALSE){
		/*counter for the for loop looping on the array of config structures*/
		uint8 counter = 0 ;
		/*variable to store the PORT ID in the MCU*/
		uint8 Port_Num = 0 ;
		/*variable to store the Pin ID in the MCU */
		uint8 Pin_Num = 0 ;
		/* run the service if there is no error (or the DEV error detect is off )*/

		/* set the gloable ptr with the address of the config structure*/

		for(counter = 0; counter < PORT_NUMBER_OF_PINS_SUPPORTED; counter++ ){
			Pin_Num = Port_Configuration.Channels[counter].pin_num;
			Port_Num = Port_Configuration.Channels[counter].port_num;
			volatile uint32 * GPIO_PORT_DIR_REG = NULL_PTR;
			switch(Port_Num){

			case PORT_A:
				/*set the PTR to port A*/
				GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTA_DIR_REG;

				break;
			case PORT_B:
				/*set the PTR to port B*/
				GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTB_DIR_REG;
				break;
			case PORT_C:
				/*set the PTR to port C*/
				GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTC_DIR_REG;
				break;
			case PORT_D:
				/*set the PTR to port D*/
				GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTD_DIR_REG;
				break;
			case PORT_E:
				/*set the PTR to port E*/
				GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTE_DIR_REG;
				break;
			case PORT_F:
				/*set the PTR to port F*/
				GPIO_PORT_DIR_REG = (volatile uint32 *)GPIO_PORTF_DIR_REG;
				break;



			}
                        /* Exclude pins configured as pin direction changeable */
                        if(Port_Configuration.Channels[counter].PORT_PIN_DIRECTION_CHANGEABLE == CHANGEABLE_D)
                        {
                          return ;
                        }
                        else if(Port_Configuration.Channels[counter].PORT_PIN_DIRECTION_CHANGEABLE == NON_CHANGEABLE_D)
                        {
                            /*configure the pin as input pin*/
                            if(Port_Configuration.Channels[counter].PORT_PIN_DIRECTION == PORT_PIN_IN){
				CLEAR_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                            }
                            /*the pin is configured as output pin */ 
                            else if(Port_Configuration.Channels[counter].PORT_PIN_DIRECTION == PORT_PIN_OUT){
				SET_BIT(*GPIO_PORT_DIR_REG,Pin_Num);

                            }
                        }

		}



	}





}


/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - pointer to where to store the version 
                                  information of this module 
 * Return value: None
 * Description: Function to Return the version information of this module
 ************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo ){
	/* variable to track the error */
	boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/*check if the port driver is not intiallized */
	if(PORT_Status == PORT_NOT_INITIALIZED){
		error = TRUE;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,
				PORT_E_UNINIT);

	}
	else{
		/* do nothing */
	}
	/*check if the API is called with a NULL pointer parameter */
	if(versioninfo == NULL_PTR){
		error = TRUE;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,
				PORT_E_PARAM_POINTER);
	}
	else{
		/*do nothing*/
	}

#endif
	/* run the service if there is no error (or the DEV error detect is off )*/
	if(error == FALSE){


		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;



	}




}
#endif


/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin - port pin ID number
                   Mode - new port pin mode to be set on port pin
 * Parameters (inout): None
 * Parameters (out): None 
 * Return value: None
 * Description: Function to set the port pin mode
 ************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ){
	/* variable to track the error */
	boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/*check if the port driver is not intiallized */
	if(PORT_Status == PORT_NOT_INITIALIZED){
		error = TRUE;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
				PORT_E_UNINIT);

	}
	else{
		/* do nothing */
	}
	/*check if the pin ID passed is correct */
	if(Pin>=PORT_NUMBER_OF_PINS_SUPPORTED){
		error = TRUE ;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
				PORT_E_PARAM_PIN);

	}
	else{
		/*do nothing */
	}

	/* check if the port pin is not configured as changeable */
	if(Port_Configuration.Channels[Pin].PORT_PIN_MODE_CHANGEABLE == STD_OFF){
		error = TRUE;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
				PORT_E_MODE_UNCHANGEABLE);
	}
	else{
		/*do nothing*/
	}
	/*check if the mode passed is not valid*/
	if(Mode >= PORT_NUMBER_OF_MODES_SUPPORTED){
		error = TRUE;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
				PORT_E_PARAM_INVALID_MODE);

	}

	else{
		/*do nothing*/
	}

#endif
	/* run the service if there is no error (or the DEV error detect is off )*/
	if(error == FALSE){


		/*variable to store the PORT ID in the MCU*/
		uint8 Port_Num = Port_Configuration.Channels[Pin].port_num;
		/*variable to store the Pin ID in the MCU */
		uint8 Pin_Num = Port_Configuration.Channels[Pin].pin_num;

		volatile uint32 * GPIO_PORT_BASE_REG = NULL_PTR; /* pointer to hold the base address of the current port */

		switch(Port_Num){
		/* Port A */
		case PORT_A:	  
			GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_A_BASE;
			break;

			/*Port B */  
		case PORT_B:
			GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_B_BASE;
			break;

			/*Port c */  
		case PORT_C:
			GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_C_BASE;
			break;

			/*Port D */  
		case PORT_D:
			GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_D_BASE;
			break;

			/*Port E */  
		case PORT_E:
			GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_E_BASE;
			break;

			/*Port F */  
		case PORT_F:
			GPIO_PORT_BASE_REG = (volatile uint32 *)GPIO_PORT_F_BASE;
			break;

		}
		/*configure the pin Analog or digital */
		switch(Port_Configuration.Channels[Pin].signal){
		/* the pin is configured as analog pin  */
		case ANALOG:
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DIGITAL_ENABLE_REG_OFFSET),Pin_Num);
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ANALOG_MODE_SEL_REG_OFFSET),Pin_Num);
			break;
			/*the pin is configured as digital pin */  
		case DIGITAL:
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_DIGITAL_ENABLE_REG_OFFSET),Pin_Num);
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ANALOG_MODE_SEL_REG_OFFSET),Pin_Num);
			break;
		}

		switch(Mode){
		/* the pin intital mode is Digital input output */
		case PORT_PIN_MODE_DIO :
			/* clear the bit in GPIO alternate function select register to configure the bit as DIO pin */
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ALT_FUNC_REG_OFFSET),Pin_Num);


			/* configure the pin direction */
			break;
			/* the pin intital mode is analog digital converter */ 
		default:
			/*Enable the alternative function */
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_ALT_FUNC_REG_OFFSET),Pin_Num);


			break;
		}
		/* set the mode number in the CTL reg */
		*(volatile uint32 *)((volatile uint8 *)GPIO_PORT_BASE_REG + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_Num * 4)) | ((Port_Configuration.Channels[Pin].PORT_PIN_INITIAL_MODE)<<(Pin_Num*4));



	}




}
#endif


