#include "../../types/packets.hpp"
#include "../session-management/session-manager.cpp"

void processConnect(ConnectPacket connectPacket, std::string sourceURI){
    SessionManager sessManager = SessionManager::getInstance();
    sessManager.handleConnect(connectPacket, sourceURI);
}