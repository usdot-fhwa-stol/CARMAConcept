/*
 * File: ParseBSM.c
 *
 *
  *
  *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
  *
  *   This file is an S-function produced by the S-Function
  *   Builder which only recognizes certain fields.  Changes made
  *   outside these fields will be lost the next time the block is
  *   used to load, edit, and resave this file. This file will be overwritten
  *   by the S-function Builder block. If you want to edit this file by hand, 
  *   you must change it only in the area defined as:  
  *
  *        %%%-SFUNWIZ_defines_Changes_BEGIN
  *        #define NAME 'replacement text' 
  *        %%% SFUNWIZ_defines_Changes_END
  *
  *   DO NOT change NAME--Change the 'replacement text' only.
  *
  *   For better compatibility with the Simulink Coder, the
  *   "wrapper" S-function technique is used.  This is discussed
  *   in the Simulink Coder's Manual in the Chapter titled,
  *   "Wrapper S-functions".
  *
  *  -------------------------------------------------------------------------
  * | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
  *  ------------------------------------------------------------------------- 
 * Created: Wed Aug 19 12:52:04 2015
 * 
 *
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME ParseBSM
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS          2
/* Input Port  0 */
#define IN_PORT_0_NAME      Buffer
#define INPUT_0_WIDTH       1472
#define INPUT_DIMS_0_COL    1
#define INPUT_0_DTYPE       uint8_T
#define INPUT_0_COMPLEX     COMPLEX_NO
#define IN_0_FRAME_BASED    FRAME_NO
#define IN_0_BUS_BASED      0
#define IN_0_BUS_NAME       
#define IN_0_DIMS           1-D
#define INPUT_0_FEEDTHROUGH 1
#define IN_0_ISSIGNED        0
#define IN_0_WORDLENGTH      8
#define IN_0_FIXPOINTSCALING 1
#define IN_0_FRACTIONLENGTH  9
#define IN_0_BIAS            0
#define IN_0_SLOPE           0.125
/* Input Port  1 */
#define IN_PORT_1_NAME      Length
#define INPUT_1_WIDTH       1
#define INPUT_DIMS_1_COL    1
#define INPUT_1_DTYPE       uint32_T
#define INPUT_1_COMPLEX     COMPLEX_NO
#define IN_1_FRAME_BASED    FRAME_NO
#define IN_1_BUS_BASED      0
#define IN_1_BUS_NAME       
#define IN_1_DIMS           1-D
#define INPUT_1_FEEDTHROUGH 1
#define IN_1_ISSIGNED        0
#define IN_1_WORDLENGTH      8
#define IN_1_FIXPOINTSCALING 1
#define IN_1_FRACTIONLENGTH  9
#define IN_1_BIAS            0
#define IN_1_SLOPE           0.125

#define NUM_OUTPUTS          1
/* Output Port  0 */
#define OUT_PORT_0_NAME      BSM
#define OUTPUT_0_WIDTH       1
#define OUTPUT_DIMS_0_COL    1
#define OUTPUT_0_DTYPE       uint8_T
#define OUTPUT_0_COMPLEX     COMPLEX_NO
#define OUT_0_FRAME_BASED    FRAME_NO
#define OUT_0_BUS_BASED      1
#define OUT_0_BUS_NAME       BasicSafetyMessage
#define OUT_0_DIMS           1-D
#define OUT_0_ISSIGNED        1
#define OUT_0_WORDLENGTH      8
#define OUT_0_FIXPOINTSCALING 1
#define OUT_0_FRACTIONLENGTH  3
#define OUT_0_BIAS            0
#define OUT_0_SLOPE           0.125

#define NPARAMS              0

#define SAMPLE_TIME_0        INHERITED_SAMPLE_TIME
#define NUM_DISC_STATES      0
#define DISC_STATES_IC       [0]
#define NUM_CONT_STATES      0
#define CONT_STATES_IC       [0]

#define SFUNWIZ_GENERATE_TLC 1
#define SOURCEFILES "__SFB__bsm_parser.c__SFB__der_decoder.c"
#define PANELINDEX           6
#define USE_SIMSTRUCT        0
#define SHOW_COMPILE_STEPS   0                   
#define CREATE_DEBUG_MEXFILE 0
#define SAVE_CODE_ONLY       0
#define SFUNWIZ_REVISION     3.0
/* %%%-SFUNWIZ_defines_Changes_END --- EDIT HERE TO _BEGIN */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "simstruc.h"
#include "ParseBSM_bus.h"
/*
* Code Generation Environment flag (simulation or standalone target).
 */
static int_T isSimulationTarget;
/*  Utility function prototypes. */
static int_T GetRTWEnvironmentMode(SimStruct *S);
/* Macro used to check if Simulation mode is set to accelerator */
#define isDWorkPresent !(ssRTWGenIsCodeGen(S) && !isSimulationTarget)

extern void ParseBSM_Outputs_wrapper(const uint8_T *Buffer,
                          const uint32_T *Length,
                          BasicSafetyMessage *BSM);

/*====================*
 * S-function methods *
 *====================*/
/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS);
     if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
	 return; /* Parameter mismatch will be reported by Simulink */
     }

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);

    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;
    /*Input Port 0 */
    ssSetInputPortWidth(S,  0, INPUT_0_WIDTH);
    ssSetInputPortDataType(S, 0, SS_UINT8);
    ssSetInputPortComplexSignal(S, 0, INPUT_0_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 0, INPUT_0_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/

    /*Input Port 1 */
    ssSetInputPortWidth(S,  1, INPUT_1_WIDTH); /* */
    ssSetInputPortDataType(S, 1, SS_UINT32);
    ssSetInputPortComplexSignal(S,  1, INPUT_1_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 1, INPUT_1_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/


    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;

  /* Register BasicSafetyMessage datatype for Output port 0 */

  #if defined(MATLAB_MEX_FILE)
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY)
    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(S, "BasicSafetyMessage", &dataTypeIdReg);
      if(dataTypeIdReg == INVALID_DTYPE_ID) return;
        ssSetOutputPortDataType(S,0, dataTypeIdReg);
    }
    #endif

    ssSetBusOutputObjectName(S, 0, (void *) "BasicSafetyMessage");
    ssSetOutputPortWidth(S, 0, OUTPUT_0_WIDTH);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);
    ssSetBusOutputAsStruct(S, 0,OUT_0_BUS_BASED);
    ssSetOutputPortBusMode(S, 0, SL_BUS_MODE);
    if (ssRTWGenIsCodeGen(S)) {
       isSimulationTarget = GetRTWEnvironmentMode(S);
    if (isSimulationTarget==-1) {
       ssSetErrorStatus(S, " Unable to determine a valid code generation environment mode");
       return;
     }
       isSimulationTarget |= ssRTWGenIsModelReferenceSimTarget(S);
    }
  
    /* Set the number of dworks */
    if (!isDWorkPresent) {
      if (!ssSetNumDWork(S, 0)) return;
    } else {
      if (!ssSetNumDWork(S, 1)) return;
    }


   if (isDWorkPresent) {
   
    /*
     * Configure the dwork 0 (y0BUS)
     */
#if defined(MATLAB_MEX_FILE)

    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(S, "BasicSafetyMessage", &dataTypeIdReg);
      if (dataTypeIdReg == INVALID_DTYPE_ID) return;
      ssSetDWorkDataType(S, 0, dataTypeIdReg);
    }

#endif

    ssSetDWorkUsageType(S, 0, SS_DWORK_USED_AS_DWORK);
    ssSetDWorkName(S, 0, "y0BUS");
    ssSetDWorkWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetDWorkComplexSignal(S, 0, COMPLEX_NO);
}
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR | 
		     SS_OPTION_WORKS_WITH_CODE_REUSE));
}

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct        *S, 
                                         int_T            port,
                                         const DimsInfo_T *dimsInfo)
{
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO)
static void mdlSetOutputPortDimensionInfo(SimStruct        *S, 
                                          int_T            port, 
                                          const DimsInfo_T *dimsInfo)
{
 if (!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif
#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
  DECL_AND_INIT_DIMSINFO(portDimsInfo);
  int_T dims[2] = { INPUT_0_WIDTH, 1 };
  bool  frameIn = ssGetInputPortFrameData(S, 0) == FRAME_YES;

  /* Neither the input nor the output ports have been set */

  portDimsInfo.width   = INPUT_0_WIDTH;
  portDimsInfo.numDims = frameIn ? 2 : 1;
  portDimsInfo.dims    = frameIn ? dims : &portDimsInfo.width;
  if (ssGetInputPortNumDimensions(S, 0) == (-1)) {  
   ssSetInputPortDimensionInfo(S, 0, &portDimsInfo);
  }
  portDimsInfo.width   = OUTPUT_0_WIDTH;
  dims[0]              = OUTPUT_0_WIDTH;
  dims[1]              = 1;
  portDimsInfo.dims    = frameIn ? dims : &portDimsInfo.width;
 if (ssGetOutputPortNumDimensions(S, 0) == (-1)) {  
  ssSetOutputPortDimensionInfo(S, 0, &portDimsInfo);
 }
  return;
}
# define MDL_SET_INPUT_PORT_FRAME_DATA
static void mdlSetInputPortFrameData(SimStruct  *S, 
                                     int_T      port,
                                     Frame_T    frameData)
{
    ssSetInputPortFrameData(S, port, frameData);
}
/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, SAMPLE_TIME_0);
    ssSetOffsetTime(S, 0, 0.0);
}


#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
static void mdlStart(SimStruct *S)
{
    /* Bus Information */
    slDataTypeAccess *dta = ssGetDataTypeAccess(S);
    const char *bpath = ssGetPath(S);
	DTypeId BasicSafetyMessageId = ssGetDataTypeId(S, "BasicSafetyMessage");

	int_T *busInfo = (int_T *)malloc(142*sizeof(int_T));
	if(busInfo==NULL) {
        ssSetErrorStatus(S, "Memory allocation failure");
        return;
    }

      /* Calculate offsets of all primitive elements of the bus */

	busInfo[0] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,0);
	busInfo[1] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[2] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,1);
	busInfo[3] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[4] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,2);
	busInfo[5] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[6] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,3);
	busInfo[7] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[8] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,4);
	busInfo[9] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[10] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,5);
	busInfo[11] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[12] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,6);
	busInfo[13] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[14] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,7);
	busInfo[15] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[16] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,8);
	busInfo[17] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[18] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,9);
	busInfo[19] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[20] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,10);
	busInfo[21] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[22] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,11);
	busInfo[23] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[24] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,12);
	busInfo[25] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[26] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,13);
	busInfo[27] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[28] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,14);
	busInfo[29] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[30] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,15);
	busInfo[31] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "int16"));
	busInfo[32] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,16);
	busInfo[33] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "int16"));
	busInfo[34] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,17);
	busInfo[35] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "int16"));
	busInfo[36] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,18);
	busInfo[37] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[38] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,19);
	busInfo[39] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[40] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,20);
	busInfo[41] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[42] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,21);
	busInfo[43] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[44] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,22);
	busInfo[45] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[46] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,23);
	busInfo[47] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[48] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,24);
	busInfo[49] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[50] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,25);
	busInfo[51] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[52] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,26);
	busInfo[53] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[54] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,27);
	busInfo[55] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[56] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,28);
	busInfo[57] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[58] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,29);
	busInfo[59] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[60] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,30);
	busInfo[61] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[62] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,31);
	busInfo[63] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[64] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,32);
	busInfo[65] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[66] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,33);
	busInfo[67] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[68] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,34);
	busInfo[69] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[70] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,35);
	busInfo[71] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[72] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,36);
	busInfo[73] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[74] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,37);
	busInfo[75] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[76] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,38);
	busInfo[77] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint16"));
	busInfo[78] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,39);
	busInfo[79] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[80] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,40);
	busInfo[81] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[82] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,41);
	busInfo[83] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint32"));
	busInfo[84] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,42);
	busInfo[85] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint16"));
	busInfo[86] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,43);
	busInfo[87] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[88] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,44);
	busInfo[89] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[90] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,45);
	busInfo[91] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[92] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,46);
	busInfo[93] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[94] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,47);
	busInfo[95] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[96] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,48);
	busInfo[97] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[98] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,49);
	busInfo[99] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[100] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,50);
	busInfo[101] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[102] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,51);
	busInfo[103] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[104] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,52);
	busInfo[105] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[106] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,53);
	busInfo[107] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[108] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,54);
	busInfo[109] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[110] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,55);
	busInfo[111] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[112] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,56);
	busInfo[113] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "single"));
	busInfo[114] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,57);
	busInfo[115] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[116] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,58);
	busInfo[117] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "boolean"));
	busInfo[118] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,59);
	busInfo[119] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[120] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,60);
	busInfo[121] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[122] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,61);
	busInfo[123] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[124] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,62);
	busInfo[125] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[126] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,63);
	busInfo[127] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[128] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,64);
	busInfo[129] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint32"));
	busInfo[130] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,65);
	busInfo[131] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint32"));
	busInfo[132] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,66);
	busInfo[133] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[134] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,67);
	busInfo[135] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[136] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,68);
	busInfo[137] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[138] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,69);
	busInfo[139] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	busInfo[140] = dtaGetDataTypeElementOffset(dta, bpath,BasicSafetyMessageId,70);
	busInfo[141] = dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "uint8"));
	ssSetUserData(S, busInfo);
}
#endif /*  MDL_START */

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
  ssSetInputPortDataType( S, 0, SS_DOUBLE);
 ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}

#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)

static void mdlSetWorkWidths(SimStruct *S)
{
  /* Set the width of DWork(s) used for marshalling the IOs */
  if (isDWorkPresent) {

     /* Update dwork 0 */
     ssSetDWorkWidth(S, 0, ssGetOutputPortWidth(S, 0));
        
    }
}

#endif
/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const uint8_T   *Buffer  = (const uint8_T*) ssGetInputPortSignal(S,0);
    const uint32_T   *Length  = (const uint32_T*) ssGetInputPortSignal(S,1);
    char *BSM = (char *) ssGetOutputPortSignal(S,0);

	int_T* busInfo = (int_T *) ssGetUserData(S);

	/* Temporary bus copy declarations */
	BasicSafetyMessage _y0BUS;

	/*Copy input bus into temporary structure*/
	
	ParseBSM_Outputs_wrapper(Buffer, Length, &_y0BUS);

	/*Copy temporary structure into output bus*/
	(void) memcpy(BSM+ busInfo[0], &_y0BUS.caccFlags_bitmask, busInfo[1]);
	(void) memcpy(BSM+ busInfo[2], &_y0BUS.setSpeed_m_s, busInfo[3]);
	(void) memcpy(BSM+ busInfo[4], &_y0BUS.throtPos_percent, busInfo[5]);
	(void) memcpy(BSM+ busInfo[6], &_y0BUS.lclPN_mm, busInfo[7]);
	(void) memcpy(BSM+ busInfo[8], &_y0BUS.lclPE_mm, busInfo[9]);
	(void) memcpy(BSM+ busInfo[10], &_y0BUS.lclPD_mm, busInfo[11]);
	(void) memcpy(BSM+ busInfo[12], &_y0BUS.roll_deg, busInfo[13]);
	(void) memcpy(BSM+ busInfo[14], &_y0BUS.pitch_deg, busInfo[15]);
	(void) memcpy(BSM+ busInfo[16], &_y0BUS.yaw_deg, busInfo[17]);
	(void) memcpy(BSM+ busInfo[18], &_y0BUS.hPosAcry_m, busInfo[19]);
	(void) memcpy(BSM+ busInfo[20], &_y0BUS.vPosAcry_m, busInfo[21]);
	(void) memcpy(BSM+ busInfo[22], &_y0BUS.frwdVel_m_s, busInfo[23]);
	(void) memcpy(BSM+ busInfo[24], &_y0BUS.rightVel_m_s, busInfo[25]);
	(void) memcpy(BSM+ busInfo[26], &_y0BUS.downVel_m_s, busInfo[27]);
	(void) memcpy(BSM+ busInfo[28], &_y0BUS.velAcc_m_s, busInfo[29]);
	(void) memcpy(BSM+ busInfo[30], &_y0BUS.frwdAcc_mm_s_s, busInfo[31]);
	(void) memcpy(BSM+ busInfo[32], &_y0BUS.rightAcc_mm_s_s, busInfo[33]);
	(void) memcpy(BSM+ busInfo[34], &_y0BUS.dwnAcc_mm_s_s, busInfo[35]);
	(void) memcpy(BSM+ busInfo[36], &_y0BUS.grpID, busInfo[37]);
	(void) memcpy(BSM+ busInfo[38], &_y0BUS.grpSize, busInfo[39]);
	(void) memcpy(BSM+ busInfo[40], &_y0BUS.grpMode, busInfo[41]);
	(void) memcpy(BSM+ busInfo[42], &_y0BUS.grpManDes, busInfo[43]);
	(void) memcpy(BSM+ busInfo[44], &_y0BUS.grpManID, busInfo[45]);
	(void) memcpy(BSM+ busInfo[46], &_y0BUS.vehID, busInfo[47]);
	(void) memcpy(BSM+ busInfo[48], &_y0BUS.frntCutIn, busInfo[49]);
	(void) memcpy(BSM+ busInfo[50], &_y0BUS.vehGrpPos, busInfo[51]);
	(void) memcpy(BSM+ busInfo[52], &_y0BUS.vehFltMode, busInfo[53]);
	(void) memcpy(BSM+ busInfo[54], &_y0BUS.vehManDes, busInfo[55]);
	(void) memcpy(BSM+ busInfo[56], &_y0BUS.vehManID, busInfo[57]);
	(void) memcpy(BSM+ busInfo[58], &_y0BUS.distToPVeh_m, busInfo[59]);
	(void) memcpy(BSM+ busInfo[60], &_y0BUS.relSpdPVeh_m_s, busInfo[61]);
	(void) memcpy(BSM+ busInfo[62], &_y0BUS.distToLVeh_m, busInfo[63]);
	(void) memcpy(BSM+ busInfo[64], &_y0BUS.relSpdLVeh_m_s, busInfo[65]);
	(void) memcpy(BSM+ busInfo[66], &_y0BUS.desTGapPVeh_s, busInfo[67]);
	(void) memcpy(BSM+ busInfo[68], &_y0BUS.desTGapLVeh_s, busInfo[69]);
	(void) memcpy(BSM+ busInfo[70], &_y0BUS.estDisPVeh_m, busInfo[71]);
	(void) memcpy(BSM+ busInfo[72], &_y0BUS.estDisLVeh_m, busInfo[73]);
	(void) memcpy(BSM+ busInfo[74], &_y0BUS.desSpeed_m_s, busInfo[75]);
	(void) memcpy(BSM+ busInfo[76], &_y0BUS.desTrq_N_m, busInfo[77]);
	(void) memcpy(BSM+ busInfo[78], &_y0BUS.msgID, busInfo[79]);
	(void) memcpy(BSM+ busInfo[80], &_y0BUS.msgCnt, busInfo[81]);
	(void) memcpy(BSM+ busInfo[82], &_y0BUS.id, busInfo[83]);
	(void) memcpy(BSM+ busInfo[84], &_y0BUS.secMark_ms, busInfo[85]);
	(void) memcpy(BSM+ busInfo[86], &_y0BUS.lat_deg, busInfo[87]);
	(void) memcpy(BSM+ busInfo[88], &_y0BUS.lon_deg, busInfo[89]);
	(void) memcpy(BSM+ busInfo[90], &_y0BUS.elev_m, busInfo[91]);
	(void) memcpy(BSM+ busInfo[92], &_y0BUS.semi_major_accuracy_m, busInfo[93]);
	(void) memcpy(BSM+ busInfo[94], &_y0BUS.semi_minor_accuracy_m, busInfo[95]);
	(void) memcpy(BSM+ busInfo[96], &_y0BUS.semi_major_accuracy_orientation_deg, busInfo[97]);
	(void) memcpy(BSM+ busInfo[98], &_y0BUS.speed_m_s, busInfo[99]);
	(void) memcpy(BSM+ busInfo[100], &_y0BUS.transmission_enum, busInfo[101]);
	(void) memcpy(BSM+ busInfo[102], &_y0BUS.heading_deg, busInfo[103]);
	(void) memcpy(BSM+ busInfo[104], &_y0BUS.angle_deg, busInfo[105]);
	(void) memcpy(BSM+ busInfo[106], &_y0BUS.vertical_acceleration_g, busInfo[107]);
	(void) memcpy(BSM+ busInfo[108], &_y0BUS.lat_acceleration_m_s_s, busInfo[109]);
	(void) memcpy(BSM+ busInfo[110], &_y0BUS.long_acceleration_m_s_s, busInfo[111]);
	(void) memcpy(BSM+ busInfo[112], &_y0BUS.yaw_rate_deg_s, busInfo[113]);
	(void) memcpy(BSM+ busInfo[114], &_y0BUS.wheelBrakes_bitmask, busInfo[115]);
	(void) memcpy(BSM+ busInfo[116], &_y0BUS.wheelBrakesUnavailable, busInfo[117]);
	(void) memcpy(BSM+ busInfo[118], &_y0BUS.tractionControlState_enum, busInfo[119]);
	(void) memcpy(BSM+ busInfo[120], &_y0BUS.anti_lock_brake_status_enum, busInfo[121]);
	(void) memcpy(BSM+ busInfo[122], &_y0BUS.stability_control_status_enum, busInfo[123]);
	(void) memcpy(BSM+ busInfo[124], &_y0BUS.brake_boost_enum, busInfo[125]);
	(void) memcpy(BSM+ busInfo[126], &_y0BUS.auxiliary_brakes_status_enum, busInfo[127]);
	(void) memcpy(BSM+ busInfo[128], &_y0BUS.vehicle_height_cm, busInfo[129]);
	(void) memcpy(BSM+ busInfo[130], &_y0BUS.vehicle_width_cm, busInfo[131]);
	(void) memcpy(BSM+ busInfo[132], &_y0BUS.userDE1, busInfo[133]);
	(void) memcpy(BSM+ busInfo[134], &_y0BUS.userDE2, busInfo[135]);
	(void) memcpy(BSM+ busInfo[136], &_y0BUS.userDE3, busInfo[137]);
	(void) memcpy(BSM+ busInfo[138], &_y0BUS.userDE4, busInfo[139]);
	(void) memcpy(BSM+ busInfo[140], &_y0BUS.userDE5, busInfo[141]);
}



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    /*Free stored bus information*/
    int_T *busInfo = (int_T *) ssGetUserData(S);
    if(busInfo!=NULL) {
      free(busInfo);
    }
}


static int_T GetRTWEnvironmentMode(SimStruct *S)
{
    int_T status;
    mxArray *plhs[1];
    mxArray *prhs[1];
    int_T err;
    
    /*
      * Get the name of the Simulink block diagram
    */
    prhs[0] = mxCreateString(ssGetModelName(ssGetRootSS(S)));
    plhs[0] = NULL;
    
    /*
      * Call "isSimulationTarget = rtwenvironmentmode(modelName)" in MATLAB
    */
    mexSetTrapFlag(1);
    err = mexCallMATLAB(1, plhs, 1, prhs, "rtwenvironmentmode");
    mexSetTrapFlag(0);
    mxDestroyArray(prhs[0]);
    
    /*
     * Set the error status if an error occurred
    */
    if (err) {
        if (plhs[0]) {
            mxDestroyArray(plhs[0]);
            plhs[0] = NULL;
        }
        ssSetErrorStatus(S, "Unknow error during call to 'rtwenvironmentmode'.");
        return -1;
    }
    
    /*
      * Get the value returned by rtwenvironmentmode(modelName)
    */
   if (plhs[0]) {
       status = (int_T) (mxGetScalar(plhs[0]) != 0);
       mxDestroyArray(plhs[0]);
       plhs[0] = NULL;
   }
    
    return (status);
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


