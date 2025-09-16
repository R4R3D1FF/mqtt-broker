#include <string>
#include <map>
#include <vector>
#include "will-properties.hpp"

struct ConnectFlags {
    bool username;
    bool password;
    bool willRetain;
    uint8_t willQos;
    bool willFlag;
    bool cleanStart;
    bool reserved;
};

typedef std::map<std::string, std::string> UserProperty;

struct ConnectProperties {
    uint32_t propertyLength;
    uint32_t sessionExpiryInterval;
    uint16_t receiveMaximum;
    uint32_t maximumPacketSize;
    uint16_t topicAliasMaximum;
    bool requestResponseInformation;
    bool requestProblemInformation;
    UserProperty userProperty;
    std::string authenticationMethod; 
    std::vector<uint8_t> authenticationData;
};

struct ConnectVariableHeader {
    uint8_t protocolVersion;
    ConnectFlags connectFlags;
    uint16_t keepAlive;
    ConnectProperties connectProperties;
};



struct ConnectPayload {
    std::string clientId;
    WillProperties willProperties;
    std::string willTopic;
    std::vector<uint8_t> willPayload;
    std::string username;
    std::vector<uint8_t> password; // Even though it is called password, it can be used to store any credential information.

};

struct ConnectPacket {
    ConnectVariableHeader connectVariableHeader;
    ConnectPayload connectPayload;
};

struct DisconnectPacket {
    
};