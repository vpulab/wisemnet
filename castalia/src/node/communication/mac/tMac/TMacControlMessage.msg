cplusplus {{
#include "TMacPacket_m.h"
}}

class TMacPacket;

enum TmacControlMessage_type {
	TMAC_TX_FAILURE = 1;
	TMAC_TX_SUCCESS = 2;
}

message TMacControlMessage {
	int type enum (TmacControlMessage_type);
	TMacPacket macPacket;
	unsigned int maxTxRetries;
	unsigned int txRetries;
}
