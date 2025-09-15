#include "../../types/packets.cpp"
#include "../session-manager.cpp"

void processConnect(ConnectPacket connectPacket){
    SessionManager sessManager = SessionManager::getInstance();
    sessManager.handleConnect(connectPacket);
}