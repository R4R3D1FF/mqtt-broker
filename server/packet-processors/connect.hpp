#include "../../types/packets.hpp"
#include "../session-manager.hpp"

void processConnect(ConnectPacket connectPacket){
    SessionManager sessManager = SessionManager::getInstance();
    sessManager.handleConnect(connectPacket);
}