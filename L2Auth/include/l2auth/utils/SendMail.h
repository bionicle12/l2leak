#pragma once

#include <windows.h>

class SendMail
{
public:
    SendMail();

    bool Init();                                                                // L2AuthD 0x00432AB3
    bool SendMessageA(const char* mailTo, const char* subj, const char* body);  // L2AuthD 0x00432D8F

private:
    static char* PrintErrorMessage(DWORD dwMessageId, char* message);  // L2AuthD 0x00432BD3
    bool ConnectMailServer();                                          // L2AuthD 0x00432C19
    void SocketClose();                                                // L2AuthD 0x00432A61
    bool PacketHelo();                                                 // L2AuthD 0x00432FC9
    bool PacketMailFrom();                                             // L2AuthD 0x00433100
    bool PacketRcptTo();                                               // L2AuthD 0x0043322F
    bool PacketData(const char* subject, const char* body);            // L2AuthD 0x004333B7
    bool PacketQuit();                                                 // L2AuthD 0x00433661

private:
    SOCKET m_socket;
    sockaddr_in m_mailServerAddr;
    char m_mails[1024];
};

extern SendMail g_MailService;
