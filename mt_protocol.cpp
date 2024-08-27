#include <mt_protocol.h>

void mt_prot_lib::get_packet_header(
    packet_header &packet,
    const uint8_t *data)
{
  packet.destination = *(uint32_t *)data;
  packet.node_id = *(uint32_t *)(data + 0x04);
  packet.packet_id = *(uint32_t *)(data + 0x08);
  packet.bit_flags = data[0x0C];
  packet.channel_hash = data[0x0D];
  packet.reserved = *(uint16_t *)(data + 0x0E);
}

void mt_prot_lib::get_packet_header_flags(
    packet_header_flags &flags,
    const uint8_t flag_bits)
{
  flags.hop_limit = flag_bits & MT_PROT_BITS_HOPLIMIT_MASK;
  flags.want_ack = (flag_bits >> MT_PROT_BITS_WANTACK) & 0x1;
  flags.via_mqtt = (flag_bits >> MT_PROT_BITS_VIAMQTT) & 0x1;
  flags.hop_start = (flag_bits >> MT_PROT_BITS_HOPSTART) & MT_PROT_BITS_HOPSTART_MASK;
}

void mt_prot_lib::packet_to_bytes(header_bytes &dest, const packet_header &packet)
{
  memcpy(dest.data + 0x00, &packet.destination, 4);
  memcpy(dest.data + 0x04, &packet.node_id, 4);
  memcpy(dest.data + 0x08, &packet.packet_id, 4);
  memcpy(dest.data + 0x0C, &packet.bit_flags, 1);
  memcpy(dest.data + 0x0D, &packet.channel_hash, 1);
  memcpy(dest.data + 0x0E, &packet.reserved, 4);
}

uint8_t mt_prot_lib::packet_flags_to_byte(const packet_header_flags &flags)
{
  uint8_t b = 0;
  b |= ((flags.hop_limit & MT_PROT_BITS_HOPLIMIT_MASK) << 0);
  b |= (flags.want_ack << MT_PROT_BITS_WANTACK);
  b |= (flags.via_mqtt << MT_PROT_BITS_VIAMQTT);
  b |= ((flags.hop_start & MT_PROT_BITS_HOPSTART_MASK) << MT_PROT_BITS_HOPSTART);
  return b;
}

void mt_prot_lib::header_to_string(
    packet_header &packet,
    String &str)
{
  str += "destination: 0x" + String(packet.destination, HEX) + "\n\r";
  str += "node_id: 0x" + String(packet.node_id, HEX) + "\n\r";
  str += "packet_id: 0x" + String(packet.packet_id, HEX) + "\n\r";
  str += "bit_flags: 0b" + String(packet.bit_flags, BIN) + "\n\r";
  packet_header_flags flags;
  get_packet_header_flags(flags, packet.bit_flags);
  str += "    hop limit: " + String(flags.hop_limit) + "\n\r";
  str += "    want ack: " + String(flags.want_ack) + "\n\r";
  str += "    via mqtt: " + String(flags.via_mqtt) + "\n\r";
  str += "    hop start: " + String(flags.hop_start) + "\n\r";

  str += "channel_hash: 0x" + String(packet.channel_hash, HEX) + "\n\r";
  str += "reserved: 0x" + String(packet.reserved, HEX);

  str += "\n\r";
}

void mt_prot_lib::get_nonce(const struct packet_header &header, struct nonce &nonc)
{
  memset(nonc.bytes, 0, sizeof(nonc.bytes));
  memcpy(nonc.bytes, &header.packet_id, 4);
  memcpy(nonc.bytes + 8, &header.node_id, 4);
}