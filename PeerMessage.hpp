#pragma once

#include "FixedBuffer.hpp"

#define MAX_PEER_MSG  (5 * 10000)


class PeerMessage {
 public:
 private:
  uint8_t _data[1024];
};


typedef FixedObjCreator<PeerMessage, MAX_PEER_MSG> PMCreator;




















