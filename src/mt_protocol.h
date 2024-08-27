#pragma once
#include <Arduino.h>

#define MT_PROT_BITS_HOPLIMIT 0
#define MT_PROT_BITS_HOPLIMIT_MASK 0b111
#define MT_PROT_BITS_WANTACK 3
#define MT_PROT_BITS_VIAMQTT 4
#define MT_PROT_BITS_HOPSTART 5
#define MT_PROT_BITS_HOPSTART_MASK 0b111
#define MT_PROT_DEFAULT_PSK {0xd4, 0xf1, 0xbb, 0x3a, 0x20, 0x29, 0x07, 0x59, 0xf0, 0xbc, 0xff, 0xab, 0xcf, 0x4e, 0x69, 0x01}
#define MT_PROT_PAYLOAD_SIZE 256
#define MT_PROT_CRYPT_COUNTER_SIZE 4
namespace mt_prot_lib
{
  enum crypt_method
  {
    CRYPT_AES_CTR128,
    CRYPT_AES_CTR256
  };

  struct IV
  {
    uint8_t bytes[16];
  };
  struct psk
  {
    uint8_t bytes[16] = MT_PROT_DEFAULT_PSK;
    uint8_t size = 16;
  };

  struct nonce
  {
    uint8_t bytes[16];
  };

  /* Fixed size payload */
  struct payload
  {
    uint8_t bytes[MT_PROT_PAYLOAD_SIZE];
  };

  struct packet_header
  {
    uint32_t destination;
    uint32_t node_id;
    uint32_t packet_id;
    uint8_t bit_flags;
    uint8_t channel_hash;
    uint16_t reserved;
  };

  struct packet_header_flags
  {
    uint8_t hop_limit;
    bool want_ack;
    bool via_mqtt;
    uint8_t hop_start;
  };

  struct header_bytes
  {
    uint8_t data[sizeof(packet_header)];
  };

  /*Turns mt flags into a byte*/
  uint8_t packet_flags_to_byte(const packet_header_flags &flags);
  /*Turns a header into bytes*/
  void packet_to_bytes(header_bytes &dest, const packet_header &packet);
  /*Extracts an mt header out of data*/
  void get_packet_header(packet_header &packet, const uint8_t *data);
  /*Extracts flags out of a mt flag byte*/
  void get_packet_header_flags(packet_header_flags &flags, const uint8_t flag_bits);
  /*Turns a header into a human readable string*/
  void header_to_string(packet_header &packet, String &str);
  /*Creates a nonce using a header*/
  void get_nonce(const struct packet_header &header, struct nonce &nonc);
}