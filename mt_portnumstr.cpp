#include <mt_portnumstr.h>
#include <meshtastic/portnums.pb.h>

String mt_portnum_to_str(int portnum)
{
  switch (portnum)
  {
  case meshtastic_PortNum_UNKNOWN_APP:
    return "Unknown(0)";

  case meshtastic_PortNum_TEXT_MESSAGE_APP:
    return "Text message";
  case meshtastic_PortNum_REMOTE_HARDWARE_APP:
    return "Remote hardware";
  case meshtastic_PortNum_POSITION_APP:
    return "Position";
  case meshtastic_PortNum_NODEINFO_APP:
    return "Node info";
  case meshtastic_PortNum_ROUTING_APP:
    return "Routing";
  case meshtastic_PortNum_ADMIN_APP:
    return "Admin";
  case meshtastic_PortNum_TEXT_MESSAGE_COMPRESSED_APP:
    return "Text message, compressed";
  case meshtastic_PortNum_WAYPOINT_APP:
    return "Way point";
  case meshtastic_PortNum_AUDIO_APP:
    return "Audio";
  case meshtastic_PortNum_DETECTION_SENSOR_APP:
    return "Detection sensor";
  case meshtastic_PortNum_REPLY_APP:
    return "Reply";
  case meshtastic_PortNum_IP_TUNNEL_APP:
    return "IP tunnel";
  case meshtastic_PortNum_PAXCOUNTER_APP:
    return "Paxcounter";
  case meshtastic_PortNum_SERIAL_APP:
    return "Serial";
  case meshtastic_PortNum_STORE_FORWARD_APP:
    return "Store forward";
  case meshtastic_PortNum_RANGE_TEST_APP:
    return "Range test";
  case meshtastic_PortNum_TELEMETRY_APP:
    return "Telemetry";
  case meshtastic_PortNum_ZPS_APP:
    return "ZPS";
  case meshtastic_PortNum_SIMULATOR_APP:
    return "Simulator";
  case meshtastic_PortNum_TRACEROUTE_APP:
    return "Traceroute";
  case meshtastic_PortNum_NEIGHBORINFO_APP:
    return "Neighbor info";
  case meshtastic_PortNum_ATAK_PLUGIN:
    return "ATAK plugin";
  case meshtastic_PortNum_ATAK_FORWARDER:
    return "ATAK forwarder";
  case meshtastic_PortNum_POWERSTRESS_APP:
    return "Power stress";
  case meshtastic_PortNum_MAP_REPORT_APP:
    return "Map report";
  case meshtastic_PortNum_PRIVATE_APP:
    return "Private";
  case meshtastic_PortNum_MAX:
    return "MAX";
  default:
    return "Unknown/Invalid";
  }
}