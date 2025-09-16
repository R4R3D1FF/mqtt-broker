#include <unordered_map>
#include <set>
#include "../types/packets/connect.hpp"
#include "../types/packets/disconnect.hpp"
#include "../types/packets/subscribe.hpp"
#include "session-details.hpp"

class SessionManager
{
public:
    static SessionManager &getInstance()
    {
        static SessionManager instance;
        return instance;
    }

    std::unordered_map<std::string, SessionDetails> &getSessions() { return sessions; }

    void handleConnect(ConnectPacket packet, std::string sourceURI)
    {

        std::string clientId = packet.connectPayload.clientId;

        if (sessions.find(clientId) != sessions.end())
        {
            clientIdFromURI[sessions[clientId].hostURI].erase(clientId);
        }
        // Remove the previous IP

        clientIdFromURI[sourceURI].insert(clientId);

        sessions[clientId].hostURI = sourceURI;

        sessions[clientId].willProperties = packet.connectPayload.willProperties;

        uint32_t offsetByte = packet.connectVariableHeader.connectProperties.sessionExpiryInterval;
        std::chrono::seconds offset = std::chrono::seconds(offsetByte);
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

        sessions[clientId].expiryTime = now + offset;
    }

    void handleSubscribe(SubscribePacket packet, std::string sourceURI)
    {
        std::set<std::string> clientIds = clientIdFromURI[sourceURI];
        for (std::string clientId : clientIds)
        {
            sessions[clientId].subscriptions[packet.subscribeVariableHeader.subscribeProperties.subscriptionId] =
                {
                    {
                        packet.subscribePayload.topicFilters, // Change to separate out shared and non-shared
                        packet.subscribePayload.topicFilters,
                    }
                };


        }
        // for (int i = 0;)
    }

    void removeClient(DisconnectPacket packet)
    {
    }

    void publishMessage(std::string clientId)
    {
    }

private:
    std::unordered_map<std::string, std::set<std::string>> clientIdFromURI;

    SessionManager() = default;

    std::unordered_map<std::string, SessionDetails> sessions; // <client identifier: sessionDetails>
};