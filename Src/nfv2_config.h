#ifndef NFV2CONF_H
#define NFV2CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/*
* External config file.
* Uncomment and update buffers' size [no of param set instances] for commands
* to be supported by module:
*/

#define NF_BroadcastAddress 0
#define NF_RobotAddress     0x01
#define NF_TerminalAddress  123

/*
* Uncomment and update buffers' size [no of param set instances] for commands
* to be supported by module:
*/
//	#define NF_BUFSZ_ReadDeviceStatus	1
    #define NF_BUFSZ_ReadDeviceVitals	8

    #define NF_BUFSZ_SetDrivesMode		4
    #define NF_BUFSZ_SetDrivesPWM		4
    #define NF_BUFSZ_SetDrivesSpeed		4
    #define NF_BUFSZ_SetDrivesCurrent	4
    #define NF_BUFSZ_SetDrivesPosition	4

#define NF_BUFSZ_ReadDrivesPosition	4
#define NF_BUFSZ_ReadDrivesStatus	4

//	#define NF_BUFSZ_SetServosMode		8
    #define NF_BUFSZ_SetServosPosition	16
//	#define NF_BUFSZ_SetServosSpeed		8

    #define NF_BUFSZ_SetDigitalOutputs	6
    #define NF_BUFSZ_ReadAnalogInputs	16
    #define NF_BUFSZ_ReadDigitalInputs  3

/*
* Remember to declare:
* extern NF_STRUCT_ComBuf	NFComBuf;
*/


#ifdef __cplusplus
}
#endif

#endif //NFV2CONF_H
