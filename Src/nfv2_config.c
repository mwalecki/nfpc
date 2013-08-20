#include "nfv2.h"

void NFv2_Config2(NF_STRUCT_ComBuf *NFComBuf, uint8_t myAddress, uint8_t deviceAddress){

    NFComBuf->myAddress = myAddress;
    NFComBuf->ReadDeviceVitals.addr[0] = deviceAddress;
    NFComBuf->ReadDeviceVitals.addr[1] = deviceAddress;
    NFComBuf->ReadDeviceVitals.addr[2] = deviceAddress;
    NFComBuf->ReadDeviceVitals.addr[3] = deviceAddress;
    NFComBuf->ReadDeviceVitals.addr[4] = deviceAddress;
    NFComBuf->ReadDeviceVitals.addr[5] = deviceAddress;
    NFComBuf->ReadDeviceVitals.addr[6] = deviceAddress;
    NFComBuf->ReadDeviceVitals.addr[7] = deviceAddress;

    NFComBuf->SetDrivesMode.addr[0] = deviceAddress;
    NFComBuf->SetDrivesMode.addr[1] = deviceAddress;
    NFComBuf->SetDrivesMode.addr[2] = deviceAddress;
    NFComBuf->SetDrivesMode.addr[3] = deviceAddress;

    NFComBuf->SetDrivesPWM.addr[0] = deviceAddress;
    NFComBuf->SetDrivesPWM.addr[1] = deviceAddress;
    NFComBuf->SetDrivesPWM.addr[2] = deviceAddress;
    NFComBuf->SetDrivesPWM.addr[3] = deviceAddress;

    NFComBuf->SetDrivesCurrent.addr[0] = deviceAddress;
    NFComBuf->SetDrivesCurrent.addr[1] = deviceAddress;
    NFComBuf->SetDrivesCurrent.addr[2] = deviceAddress;
    NFComBuf->SetDrivesCurrent.addr[3] = deviceAddress;

    NFComBuf->SetDrivesSpeed.addr[0] = deviceAddress;
    NFComBuf->SetDrivesSpeed.addr[1] = deviceAddress;
    NFComBuf->SetDrivesSpeed.addr[2] = deviceAddress;
    NFComBuf->SetDrivesSpeed.addr[3] = deviceAddress;

    NFComBuf->SetDrivesPosition.addr[0] = deviceAddress;
    NFComBuf->SetDrivesPosition.addr[1] = deviceAddress;
    NFComBuf->SetDrivesPosition.addr[2] = deviceAddress;
    NFComBuf->SetDrivesPosition.addr[3] = deviceAddress;

    NFComBuf->ReadDrivesPosition.addr[0] = deviceAddress;
    NFComBuf->ReadDrivesPosition.addr[1] = deviceAddress;
    NFComBuf->ReadDrivesPosition.addr[2] = deviceAddress;
    NFComBuf->ReadDrivesPosition.addr[3] = deviceAddress;

    NFComBuf->ReadDrivesStatus.addr[0] = deviceAddress;
    NFComBuf->ReadDrivesStatus.addr[1] = deviceAddress;
    NFComBuf->ReadDrivesStatus.addr[2] = deviceAddress;
    NFComBuf->ReadDrivesStatus.addr[3] = deviceAddress;

    NFComBuf->ReadAnalogInputs.addr[0] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[1] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[2] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[3] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[4] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[5] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[6] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[7] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[8] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[9] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[10] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[11] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[12] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[13] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[14] = deviceAddress;
    NFComBuf->ReadAnalogInputs.addr[15] = deviceAddress;

    NFComBuf->SetDigitalOutputs.addr[0] = deviceAddress;
    NFComBuf->SetDigitalOutputs.addr[1] = deviceAddress;
    NFComBuf->SetDigitalOutputs.addr[2] = deviceAddress;
    NFComBuf->SetDigitalOutputs.addr[3] = deviceAddress;
    NFComBuf->SetDigitalOutputs.addr[4] = deviceAddress;
    NFComBuf->SetDigitalOutputs.addr[5] = deviceAddress;

    NFComBuf->ReadDigitalInputs.addr[0] = deviceAddress;
    NFComBuf->ReadDigitalInputs.addr[1] = deviceAddress;
    NFComBuf->ReadDigitalInputs.addr[2] = deviceAddress;

    NFComBuf->SetServosPosition.addr[0] = deviceAddress;
    NFComBuf->SetServosPosition.addr[1] = deviceAddress;
    NFComBuf->SetServosPosition.addr[2] = deviceAddress;
    NFComBuf->SetServosPosition.addr[3] = deviceAddress;
    NFComBuf->SetServosPosition.addr[4] = deviceAddress;
    NFComBuf->SetServosPosition.addr[5] = deviceAddress;
    NFComBuf->SetServosPosition.addr[6] = deviceAddress;
    NFComBuf->SetServosPosition.addr[7] = deviceAddress;
    NFComBuf->SetServosPosition.addr[8] = deviceAddress;
    NFComBuf->SetServosPosition.addr[9] = deviceAddress;
    NFComBuf->SetServosPosition.addr[10] = deviceAddress;
    NFComBuf->SetServosPosition.addr[11] = deviceAddress;
    NFComBuf->SetServosPosition.addr[12] = deviceAddress;
    NFComBuf->SetServosPosition.addr[13] = deviceAddress;
    NFComBuf->SetServosPosition.addr[14] = deviceAddress;
    NFComBuf->SetServosPosition.addr[15] = deviceAddress;
}
