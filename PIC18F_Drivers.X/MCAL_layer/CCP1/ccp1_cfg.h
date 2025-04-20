/* 
 * File:   ccp1_cfg.h
 * Author: Naghm Ayman Omar
 *
 * Created on 27 July 2024, 17:04
 */

#ifndef CCP1_CFG_H
#define	CCP1_CFG_H

#define CCP_CFG_CAPTURE_MODE_SELECT     0x00
#define CCP_CFG_COMPARATOR_MODE_SELECT  0x01
#define CCP_CFG_PWM_MODE_SELECT          0x02

#define CCP1_CFG__MODE_SELECTED (CCP_CFG_COMPARATOR_MODE_SELECT)
#define CCP2_CFG__MODE_SELECTED (CCP_CFG_COMPARATOR_MODE_SELECT)
#endif	/* CCP1_CFG_H */

