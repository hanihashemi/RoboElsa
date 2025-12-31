#pragma once

#include <Client.h>

#if !defined(TRANSPORT_WIFI) && !defined(TRANSPORT_GSM)
#error "Define TRANSPORT_WIFI or TRANSPORT_GSM in build_flags."
#endif

bool TransportBegin();
Client &TransportClient();
const char *TransportName();
