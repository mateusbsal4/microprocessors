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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=main.c ../RL2/adc.c ../RL2/battery.c ../RL2/delay.c ../RL2/key.c ../RL2/led_rgb.c ../RL2/sensor.c ../RL2/serial.c ../RL2/spi.c ../RL2/compass.c pwm.c ../RL2/lcd8x2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/1360904297/adc.p1 ${OBJECTDIR}/_ext/1360904297/battery.p1 ${OBJECTDIR}/_ext/1360904297/delay.p1 ${OBJECTDIR}/_ext/1360904297/key.p1 ${OBJECTDIR}/_ext/1360904297/led_rgb.p1 ${OBJECTDIR}/_ext/1360904297/sensor.p1 ${OBJECTDIR}/_ext/1360904297/serial.p1 ${OBJECTDIR}/_ext/1360904297/spi.p1 ${OBJECTDIR}/_ext/1360904297/compass.p1 ${OBJECTDIR}/pwm.p1 ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/main.p1.d ${OBJECTDIR}/_ext/1360904297/adc.p1.d ${OBJECTDIR}/_ext/1360904297/battery.p1.d ${OBJECTDIR}/_ext/1360904297/delay.p1.d ${OBJECTDIR}/_ext/1360904297/key.p1.d ${OBJECTDIR}/_ext/1360904297/led_rgb.p1.d ${OBJECTDIR}/_ext/1360904297/sensor.p1.d ${OBJECTDIR}/_ext/1360904297/serial.p1.d ${OBJECTDIR}/_ext/1360904297/spi.p1.d ${OBJECTDIR}/_ext/1360904297/compass.p1.d ${OBJECTDIR}/pwm.p1.d ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/1360904297/adc.p1 ${OBJECTDIR}/_ext/1360904297/battery.p1 ${OBJECTDIR}/_ext/1360904297/delay.p1 ${OBJECTDIR}/_ext/1360904297/key.p1 ${OBJECTDIR}/_ext/1360904297/led_rgb.p1 ${OBJECTDIR}/_ext/1360904297/sensor.p1 ${OBJECTDIR}/_ext/1360904297/serial.p1 ${OBJECTDIR}/_ext/1360904297/spi.p1 ${OBJECTDIR}/_ext/1360904297/compass.p1 ${OBJECTDIR}/pwm.p1 ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1

# Source Files
SOURCEFILES=main.c ../RL2/adc.c ../RL2/battery.c ../RL2/delay.c ../RL2/key.c ../RL2/led_rgb.c ../RL2/sensor.c ../RL2/serial.c ../RL2/spi.c ../RL2/compass.c pwm.c ../RL2/lcd8x2.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F886
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/adc.p1: ../RL2/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/adc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/adc.p1 ../RL2/adc.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/adc.d ${OBJECTDIR}/_ext/1360904297/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/battery.p1: ../RL2/battery.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/battery.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/battery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/battery.p1 ../RL2/battery.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/battery.d ${OBJECTDIR}/_ext/1360904297/battery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/battery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/delay.p1: ../RL2/delay.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/delay.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/delay.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/delay.p1 ../RL2/delay.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/delay.d ${OBJECTDIR}/_ext/1360904297/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/key.p1: ../RL2/key.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/key.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/key.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/key.p1 ../RL2/key.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/key.d ${OBJECTDIR}/_ext/1360904297/key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/led_rgb.p1: ../RL2/led_rgb.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/led_rgb.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/led_rgb.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/led_rgb.p1 ../RL2/led_rgb.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/led_rgb.d ${OBJECTDIR}/_ext/1360904297/led_rgb.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/led_rgb.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/sensor.p1: ../RL2/sensor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/sensor.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/sensor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/sensor.p1 ../RL2/sensor.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/sensor.d ${OBJECTDIR}/_ext/1360904297/sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/serial.p1: ../RL2/serial.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/serial.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/serial.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/serial.p1 ../RL2/serial.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/serial.d ${OBJECTDIR}/_ext/1360904297/serial.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/serial.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/spi.p1: ../RL2/spi.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/spi.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/spi.p1 ../RL2/spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/spi.d ${OBJECTDIR}/_ext/1360904297/spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/compass.p1: ../RL2/compass.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/compass.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/compass.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/compass.p1 ../RL2/compass.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/compass.d ${OBJECTDIR}/_ext/1360904297/compass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/compass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pwm.p1: pwm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.p1.d 
	@${RM} ${OBJECTDIR}/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pwm.p1 pwm.c 
	@-${MV} ${OBJECTDIR}/pwm.d ${OBJECTDIR}/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/lcd8x2.p1: ../RL2/lcd8x2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1 ../RL2/lcd8x2.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/lcd8x2.d ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/adc.p1: ../RL2/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/adc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/adc.p1 ../RL2/adc.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/adc.d ${OBJECTDIR}/_ext/1360904297/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/battery.p1: ../RL2/battery.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/battery.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/battery.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/battery.p1 ../RL2/battery.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/battery.d ${OBJECTDIR}/_ext/1360904297/battery.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/battery.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/delay.p1: ../RL2/delay.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/delay.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/delay.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/delay.p1 ../RL2/delay.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/delay.d ${OBJECTDIR}/_ext/1360904297/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/key.p1: ../RL2/key.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/key.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/key.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/key.p1 ../RL2/key.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/key.d ${OBJECTDIR}/_ext/1360904297/key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/led_rgb.p1: ../RL2/led_rgb.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/led_rgb.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/led_rgb.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/led_rgb.p1 ../RL2/led_rgb.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/led_rgb.d ${OBJECTDIR}/_ext/1360904297/led_rgb.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/led_rgb.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/sensor.p1: ../RL2/sensor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/sensor.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/sensor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/sensor.p1 ../RL2/sensor.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/sensor.d ${OBJECTDIR}/_ext/1360904297/sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/serial.p1: ../RL2/serial.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/serial.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/serial.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/serial.p1 ../RL2/serial.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/serial.d ${OBJECTDIR}/_ext/1360904297/serial.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/serial.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/spi.p1: ../RL2/spi.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/spi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/spi.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/spi.p1 ../RL2/spi.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/spi.d ${OBJECTDIR}/_ext/1360904297/spi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/spi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/compass.p1: ../RL2/compass.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/compass.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/compass.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/compass.p1 ../RL2/compass.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/compass.d ${OBJECTDIR}/_ext/1360904297/compass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/compass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pwm.p1: pwm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm.p1.d 
	@${RM} ${OBJECTDIR}/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/pwm.p1 pwm.c 
	@-${MV} ${OBJECTDIR}/pwm.d ${OBJECTDIR}/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360904297/lcd8x2.p1: ../RL2/lcd8x2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/1360904297" 
	@${RM} ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1 ../RL2/lcd8x2.c 
	@-${MV} ${OBJECTDIR}/_ext/1360904297/lcd8x2.d ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360904297/lcd8x2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
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
${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits -std=c90 -gdwarf-3 -mstack=compiled:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../RL2" -I"/Applications/microchip/xc8/v2.40/pic/include/proc" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mdefault-config-bits -std=c90 -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/HW_Test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
