/*******************************************************************************
* File Name: P6_5_pot.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P6_5_pot_H) /* Pins P6_5_pot_H */
#define CY_PINS_P6_5_pot_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P6_5_pot_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P6_5_pot__PORT == 15 && ((P6_5_pot__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P6_5_pot_Write(uint8 value);
void    P6_5_pot_SetDriveMode(uint8 mode);
uint8   P6_5_pot_ReadDataReg(void);
uint8   P6_5_pot_Read(void);
void    P6_5_pot_SetInterruptMode(uint16 position, uint16 mode);
uint8   P6_5_pot_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P6_5_pot_SetDriveMode() function.
     *  @{
     */
        #define P6_5_pot_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P6_5_pot_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P6_5_pot_DM_RES_UP          PIN_DM_RES_UP
        #define P6_5_pot_DM_RES_DWN         PIN_DM_RES_DWN
        #define P6_5_pot_DM_OD_LO           PIN_DM_OD_LO
        #define P6_5_pot_DM_OD_HI           PIN_DM_OD_HI
        #define P6_5_pot_DM_STRONG          PIN_DM_STRONG
        #define P6_5_pot_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P6_5_pot_MASK               P6_5_pot__MASK
#define P6_5_pot_SHIFT              P6_5_pot__SHIFT
#define P6_5_pot_WIDTH              1u

/* Interrupt constants */
#if defined(P6_5_pot__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P6_5_pot_SetInterruptMode() function.
     *  @{
     */
        #define P6_5_pot_INTR_NONE      (uint16)(0x0000u)
        #define P6_5_pot_INTR_RISING    (uint16)(0x0001u)
        #define P6_5_pot_INTR_FALLING   (uint16)(0x0002u)
        #define P6_5_pot_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P6_5_pot_INTR_MASK      (0x01u) 
#endif /* (P6_5_pot__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P6_5_pot_PS                     (* (reg8 *) P6_5_pot__PS)
/* Data Register */
#define P6_5_pot_DR                     (* (reg8 *) P6_5_pot__DR)
/* Port Number */
#define P6_5_pot_PRT_NUM                (* (reg8 *) P6_5_pot__PRT) 
/* Connect to Analog Globals */                                                  
#define P6_5_pot_AG                     (* (reg8 *) P6_5_pot__AG)                       
/* Analog MUX bux enable */
#define P6_5_pot_AMUX                   (* (reg8 *) P6_5_pot__AMUX) 
/* Bidirectional Enable */                                                        
#define P6_5_pot_BIE                    (* (reg8 *) P6_5_pot__BIE)
/* Bit-mask for Aliased Register Access */
#define P6_5_pot_BIT_MASK               (* (reg8 *) P6_5_pot__BIT_MASK)
/* Bypass Enable */
#define P6_5_pot_BYP                    (* (reg8 *) P6_5_pot__BYP)
/* Port wide control signals */                                                   
#define P6_5_pot_CTL                    (* (reg8 *) P6_5_pot__CTL)
/* Drive Modes */
#define P6_5_pot_DM0                    (* (reg8 *) P6_5_pot__DM0) 
#define P6_5_pot_DM1                    (* (reg8 *) P6_5_pot__DM1)
#define P6_5_pot_DM2                    (* (reg8 *) P6_5_pot__DM2) 
/* Input Buffer Disable Override */
#define P6_5_pot_INP_DIS                (* (reg8 *) P6_5_pot__INP_DIS)
/* LCD Common or Segment Drive */
#define P6_5_pot_LCD_COM_SEG            (* (reg8 *) P6_5_pot__LCD_COM_SEG)
/* Enable Segment LCD */
#define P6_5_pot_LCD_EN                 (* (reg8 *) P6_5_pot__LCD_EN)
/* Slew Rate Control */
#define P6_5_pot_SLW                    (* (reg8 *) P6_5_pot__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P6_5_pot_PRTDSI__CAPS_SEL       (* (reg8 *) P6_5_pot__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P6_5_pot_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P6_5_pot__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P6_5_pot_PRTDSI__OE_SEL0        (* (reg8 *) P6_5_pot__PRTDSI__OE_SEL0) 
#define P6_5_pot_PRTDSI__OE_SEL1        (* (reg8 *) P6_5_pot__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P6_5_pot_PRTDSI__OUT_SEL0       (* (reg8 *) P6_5_pot__PRTDSI__OUT_SEL0) 
#define P6_5_pot_PRTDSI__OUT_SEL1       (* (reg8 *) P6_5_pot__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P6_5_pot_PRTDSI__SYNC_OUT       (* (reg8 *) P6_5_pot__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P6_5_pot__SIO_CFG)
    #define P6_5_pot_SIO_HYST_EN        (* (reg8 *) P6_5_pot__SIO_HYST_EN)
    #define P6_5_pot_SIO_REG_HIFREQ     (* (reg8 *) P6_5_pot__SIO_REG_HIFREQ)
    #define P6_5_pot_SIO_CFG            (* (reg8 *) P6_5_pot__SIO_CFG)
    #define P6_5_pot_SIO_DIFF           (* (reg8 *) P6_5_pot__SIO_DIFF)
#endif /* (P6_5_pot__SIO_CFG) */

/* Interrupt Registers */
#if defined(P6_5_pot__INTSTAT)
    #define P6_5_pot_INTSTAT            (* (reg8 *) P6_5_pot__INTSTAT)
    #define P6_5_pot_SNAP               (* (reg8 *) P6_5_pot__SNAP)
    
	#define P6_5_pot_0_INTTYPE_REG 		(* (reg8 *) P6_5_pot__0__INTTYPE)
#endif /* (P6_5_pot__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P6_5_pot_H */


/* [] END OF FILE */
