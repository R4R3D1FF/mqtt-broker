#include <string>
#include <map>
#include <vector>
#include "../will-properties.hpp"

struct PublishFixedHeader {
    bool dup;
    uint16_t QoSLevel;
    bool retain;
};

struct PublishProperties {
    // uint32_t propertyLength; //MAybe should remove?
    bool payloadFormatIndicator;
    uint32_t messageExpiryInterval;
    uint16_t topicAliasValue;
    
};

struct PublishVariableHeader {
    std::string topicName;
    uint16_t packetIdentifier;
    std::string responseTopic;
    std::vector<uint8_t> correlationData;
    UserProperty userProperty;
    uint32_t subscriptionId;
    std::string contentType;
};

struct PublishPayload {
    std::vector<uint16_t> applicationMessage;
};

typedef std::map<std::string, std::string> UserProperty;

struct SubscribeProperties {
    // uint32_t propertyLength; // I don't think we need this in the high level struct
    std::string subscriptionId;
    UserProperty userProperty;

};

struct SubscribeVariableHeader {
    uint16_t packetIdentifier;
    SubscribeProperties subscribeProperties;
};

struct SubscriptionOptions {
    uint8_t QoS;
    bool noLocal;
    bool retainAsPublished;
    uint8_t retainHandling;
};

struct SubscribePayload {
    std::string clientId;
    std::vector<std::string> topicFilters;
    SubscriptionOptions subscriptionOptions;

};

struct SubscribePacket {
    SubscribeVariableHeader subscribeVariableHeader;
    SubscribePayload subscribePayload;
};

