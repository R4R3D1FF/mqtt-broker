#include <string>

struct WillProperties {
    uint32_t propertyLength;
    uint32_t willDelayInterval;
    uint8_t payloadFormatIndicator;
    uint32_t messageExpiryInterval;     // Make this optional.
    std::string contentType;
    std::string reponseType;

    std::string userProperty;
};