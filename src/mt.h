#pragma once

#include <mt_protocol.h>

namespace mt_lib
{

  enum decoding_result
  {
    DEC_OK,
    DEC_PACKET_TOO_SHORT,
    DEC_PACKET_TOO_LONG,
    DEC_CRYPTO_ERR
  };

  enum encoding_result
  {
    ENC_OK,
    ENC_PB_TOO_LONG,
    ENC_CRYPTO_ERR
  };

  /*Decodes and decrypts the *payload.
  The result is written into the same *payload.
  The header will be extracted as well.*/
  decoding_result decode(
      uint8_t *payload,
      size_t &payload_size,
      mt_prot_lib::packet_header &header);

  /*Encrypts the PB and adds header into the &payload.
  &pb_buffer_size will be the new size to be send.*/
  encoding_result encode(
      uint8_t *pb_buffer,
      size_t &pb_buffer_size,
      mt_prot_lib::packet_header &header,
      mt_prot_lib::payload &payload);

  /* Configures decoding/encoding. Leave psk NULL for default psk. */
  bool configure(mt_prot_lib::psk *psk);
};
