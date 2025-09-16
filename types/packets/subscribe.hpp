#include <string>
#include <map>
#include <vector>
#include "../will-properties.hpp"


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

