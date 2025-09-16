#include <unordered_map>
#include "../types/packets.cpp"
#include "../types/session-details.cpp"


class SessionManager
{
public:
    static SessionManager &getInstance()
    {
        static SessionManager instance;
        return instance;
    }

    std::unordered_map<std::string, SessionDetails> &getSessions() { return sessions; }

    void handleConnect(ConnectPacket packet, std::string sourceURI){
        
        std::string clientId = packet.connectPayload.clientId;

        sessions[clientId].hostURI = sourceURI;

        sessions[clientId].willProperties = packet.connectPayload.willProperties;

        uint32_t offsetByte = packet.connectVariableHeader.connectProperties.sessionExpiryInterval;
        std::chrono::seconds offset = std::chrono::seconds(offsetByte);
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

        sessions[clientId].expiryTime = now + offset;


        

    }

    void removeClient(DisconnectPacket packet) {

    }

    void publishMessage(std::string clientId){

    }

private:
    SessionManager() = default;
    
    std::unordered_map<std::string, SessionDetails> sessions; // <client identifier: sessionDetails>

    
};