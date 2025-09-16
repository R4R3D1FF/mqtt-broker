#include <vector>
#define PROTOCOL_NAME_LENGTH 0x04
#define PROTOCOL_LEVEL 0x05

uint8_t generateFlagByte(
    uint8_t willRetain,
    uint8_t willQos,
    uint8_t willFlag,
    uint8_t cleanStart,
    uint8_t useUsername,
    uint8_t usePassword

)
{

    uint8_t connectFlags = 0x00;
    connectFlags |= (useUsername << 7);
    connectFlags |= (useUsername << 6);

    connectFlags |= (willRetain << 5);
    connectFlags |= (willQos << 3);
    connectFlags |= (willFlag << 2);
    connectFlags |= (cleanStart << 1);

    return connectFlags;
}

std::vector<uint8_t> generatePropertiesLengthBytes(uint32_t propertiesLength){
    std::vector<uint8_t> bytes;
    while (propertiesLength){
        uint8_t currentByte = propertiesLength/128;
        propertiesLength = propertiesLength >> 7;
        if (propertiesLength){
            currentByte |= (1 << 7);
        }

        bytes.push_back(currentByte);
    }

    return bytes;
}

std::vector<uint8_t> generateConnectVariablePacket(
    uint8_t willRetain,
    uint8_t willQos,
    uint8_t willFlag,
    uint8_t cleanStart,
    uint8_t useUsername,
    uint8_t usePassword,
    uint16_t keepAlive,
    std::vector<uint8_t> properties // The raw properties bytes array, can generate a helper function elsewhere for it
)
{
    uint32_t propertiesLength = properties.size();
    std::vector<uint8_t> packet =
    {
        0x00,
        PROTOCOL_NAME_LENGTH,
        0x4d,
        0x51,
        0x54,
        0x54,
        PROTOCOL_LEVEL,
        generateFlagByte(
            willRetain,
            willQos,
            willFlag,
            cleanStart,
            useUsername,
            usePassword),
        ((uint8_t)(keepAlive >> 8)),
        (uint8_t)keepAlive
    };

    std::vector<uint8_t> propertiesLengthField = generatePropertiesLengthBytes(propertiesLength);

    packet.insert(packet.end(), propertiesLengthField.begin(), propertiesLengthField.end());
    packet.insert(packet.end(), properties.begin(), properties.end());

    return packet;
}

std::vector<int> generateConnectFixedPacket(uint8_t remainingLength)
{
    return {
        0x10,
        remainingLength
    };
}

std::vector<int> generatePacket(
    uint8_t willRetain,
    uint8_t willQos,
    uint8_t willFlag,
    uint8_t cleanStart,
    bool useAuth,
    uint16_t keepAlive)
{
    
}