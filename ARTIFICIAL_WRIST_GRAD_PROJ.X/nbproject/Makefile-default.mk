#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ECU_Layer/PCA9865/pca9685.c MCAL_Layer/I2C_BUS/i2c.c MCAL_Layer/USART/USART.c Main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o ${OBJECTDIR}/MCAL_Layer/USART/USART.o ${OBJECTDIR}/Main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o.d ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o.d ${OBJECTDIR}/MCAL_Layer/USART/USART.o.d ${OBJECTDIR}/Main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o ${OBJECTDIR}/MCAL_Layer/USART/USART.o ${OBJECTDIR}/Main.o

# Source Files
SOURCEFILES=ECU_Layer/PCA9865/pca9685.c MCAL_Layer/I2C_BUS/i2c.c MCAL_Layer/USART/USART.c Main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega32A
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o: ECU_Layer/PCA9865/pca9685.c  .generated_files/flags/default/2bf194ffc92948dfacbd336ccc1e069224cbedcc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/PCA9865" 
	@${RM} ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o.d" -MT "${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o.d" -MT ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o -o ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o ECU_Layer/PCA9865/pca9685.c 
	
${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o: MCAL_Layer/I2C_BUS/i2c.c  .generated_files/flags/default/2034e39fecce1e24e61e3dbdff868825ea6094b8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/I2C_BUS" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o.d" -MT "${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o.d" -MT ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o -o ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o MCAL_Layer/I2C_BUS/i2c.c 
	
${OBJECTDIR}/MCAL_Layer/USART/USART.o: MCAL_Layer/USART/USART.c  .generated_files/flags/default/1edd4c9d93211304ce54544dd4e0a133eefde07e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/USART" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/USART/USART.o.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/USART/USART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/MCAL_Layer/USART/USART.o.d" -MT "${OBJECTDIR}/MCAL_Layer/USART/USART.o.d" -MT ${OBJECTDIR}/MCAL_Layer/USART/USART.o -o ${OBJECTDIR}/MCAL_Layer/USART/USART.o MCAL_Layer/USART/USART.c 
	
${OBJECTDIR}/Main.o: Main.c  .generated_files/flags/default/5842f71a615f46c9ddbb40816b8fb088b2abe97a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Main.o.d" -MT "${OBJECTDIR}/Main.o.d" -MT ${OBJECTDIR}/Main.o -o ${OBJECTDIR}/Main.o Main.c 
	
else
${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o: ECU_Layer/PCA9865/pca9685.c  .generated_files/flags/default/19e49b029689a7fd302836448ec0a4db306cbaaf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/PCA9865" 
	@${RM} ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o.d" -MT "${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o.d" -MT ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o -o ${OBJECTDIR}/ECU_Layer/PCA9865/pca9685.o ECU_Layer/PCA9865/pca9685.c 
	
${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o: MCAL_Layer/I2C_BUS/i2c.c  .generated_files/flags/default/17b32884fb4158203156b328ed0bf4ef6ce97cc5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/I2C_BUS" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o.d" -MT "${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o.d" -MT ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o -o ${OBJECTDIR}/MCAL_Layer/I2C_BUS/i2c.o MCAL_Layer/I2C_BUS/i2c.c 
	
${OBJECTDIR}/MCAL_Layer/USART/USART.o: MCAL_Layer/USART/USART.c  .generated_files/flags/default/803e0049a5b3c33ded2301c3a127aaac48d3a0f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/USART" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/USART/USART.o.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/USART/USART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/MCAL_Layer/USART/USART.o.d" -MT "${OBJECTDIR}/MCAL_Layer/USART/USART.o.d" -MT ${OBJECTDIR}/MCAL_Layer/USART/USART.o -o ${OBJECTDIR}/MCAL_Layer/USART/USART.o MCAL_Layer/USART/USART.c 
	
${OBJECTDIR}/Main.o: Main.c  .generated_files/flags/default/4afa21eb345be367db840c4d8bc50e30939c0aa6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Main.o.d" -MT "${OBJECTDIR}/Main.o.d" -MT ${OBJECTDIR}/Main.o -o ${OBJECTDIR}/Main.o Main.c 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/ARTIFICIAL_WRIST_GRAD_PROJ.X.${IMAGE_TYPE}.hex"
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
