// Network messages

#pragma once

#include <cstdint>

enum MessageType {
    mt_basic = 0,
    mt_movement = mt_basic + 1,
    mt_chatMsg = mt_basic + 2,
    mt_connect = mt_basic + 3,
    mt_disconnect = mt_basic + 4
};

struct NetworkMessage {
public:
    void* GetData() { return data; }
    void SetData(void* _data) { data = _data; }

    uint64_t GetDataSize() { return dataSize; }
    void SetDataSize(uint64_t _dataSize) { dataSize = _dataSize; }

private:
    void* data;
    uint32_t dataSize;
};

struct Msg_Movement {
public:
    uint8_t GetMsgType() { return msgType; };

    uint8_t GetPaddle1_x() { return paddle1_x; };
    void SetPaddle1_x(uint8_t val) { paddle1_x = val; }

    uint8_t GetPaddle1_y() { return paddle1_y; };
    void SetPaddle1_y(uint8_t val) { paddle1_y = val; }

    uint8_t GetPaddle2_x() { return paddle2_x; };
    void SetPaddle2_x(uint8_t val) { paddle2_x = val; }

    uint8_t GetPaddle2_y() { return paddle2_y; };
    void SetPaddle2_y(uint8_t val) { paddle2_y = val; }

    uint8_t GetBall_x() { return ball_x; };
    void SetBall_x(uint8_t val) { ball_x = val; }

    uint8_t GetBall_y() { return ball_y; };
    void SetBall_y(uint8_t val) { ball_y = val; }

private:
    const uint8_t msgType = mt_movement;
    uint8_t paddle1_x;
    uint8_t paddle1_y;
    uint8_t paddle2_x;
    uint8_t paddle2_y;
    uint8_t ball_x;
    uint8_t ball_y;
};

struct Msg_ChatMsg {
public:
    uint8_t GetMsgType() { return msgType; };

    char* GetChatMsg() { return chatMsg; };
    void SetChatMsg(char msg[256]) { for (int i = 0; i < 256; i++) { chatMsg[i] = msg[i]; } };

private:
    const uint8_t msgType = mt_chatMsg;
    char chatMsg[256];
};

struct Msg_Connect {
public:
    uint8_t GetMsgType() { return msgType; };

    char* GetName() { return name; };
    void SetName(char _name[16]) { for (int i = 0; i < 16; i++) { name[i] = _name[i]; } } 

private:
    const uint8_t msgType = mt_connect;
    char name[16];
};

struct Msg_Disconnect {
public:
    uint8_t GetMsgType() { return msgType; };

    char* GetName() { return name; };
    void SetName(char _name[16]) { for (int i = 0; i < 16; i++) { name[i] = _name[i]; } } 

private:
    const uint8_t msgType = mt_disconnect;
    char name[16];
};