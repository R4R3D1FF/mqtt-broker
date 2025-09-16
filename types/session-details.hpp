#include <vector>
#include <string>
#include <chrono>
#include <optional>
#include <map>
#include "will-properties.hpp"



struct topicFilterLists {
    std::vector<std::string> nonSharedTopicFilters;
    std::vector<std::string> sharedTopicFilters;
};

struct SessionDetails
{
    std::string hostURI;
    std::map<std::string, topicFilterLists> subscriptions; // mapping subscription id to topic filters, if no id provided, take ""
    std::chrono::steady_clock::time_point expiryTime; // But the CONNECT packet contains interval
    WillProperties willProperties;
    uint8_t willQoS;
    bool cleanStart;
    // std::optional<std::string> username;
    // std::optional<std::string> password;
    // not sure if these two are needed
    uint16_t topicAliasMaximum;

};