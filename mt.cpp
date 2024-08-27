#include <mt.h>
#include <mt_crypto.h>

using namespace mt_prot_lib;

mt_lib::decoding_result mt_lib::decode(
    uint8_t *payload,
    size_t &payload_size,
    packet_header &header)
{

  /* Payload size has to be bigger than one header.
  Also smaller than the max size. */
  size_t header_size = sizeof(packet_header);
  if (payload_size < header_size)
  {
    return decoding_result::DEC_PACKET_TOO_SHORT;
  }
  if (payload_size > MT_PROT_PAYLOAD_SIZE)
  {
    return decoding_result::DEC_PACKET_TOO_LONG;
  }

  /* Decodes header from payload */
  get_packet_header(header, payload);

  /* Move protobuf area to the front, if there is any */
  size_t pb_len = payload_size - header_size;
  if (pb_len == 0)
    return decoding_result::DEC_OK;
  memmove(payload, payload + header_size, pb_len);

  /* Add zero padding to compensate for removed header */
  memset(payload + pb_len, 0, header_size);

  /* Set new payload size to only protobuf area */
  payload_size = pb_len;

  /* Setup crypto */
  nonce nonc;
  get_nonce(header, nonc);
  IV iv;
  memcpy(iv.bytes, nonc.bytes, sizeof(iv.bytes));
  bool iv_success = mt_crypto_set_IV(iv);
  if (!iv_success)
    return decoding_result::DEC_CRYPTO_ERR;
  mt_crypto_set_counter_size(MT_PROT_CRYPT_COUNTER_SIZE);

  /* Decrypt the pb */
  mt_prot_lib::payload padded_payload = {0}; /* This adds zero padding for decryption */
  memcpy(padded_payload.bytes, payload, pb_len);
  bool success = mt_crypto_decrypt(padded_payload);
  if (!success)
    return decoding_result::DEC_CRYPTO_ERR;

  /* Return the decryped payload */
  memcpy(payload, padded_payload.bytes, pb_len);

  return decoding_result::DEC_OK;
}

mt_lib::encoding_result mt_lib::encode(
    uint8_t *pb_buffer,
    size_t &pb_buffer_size,
    mt_prot_lib::packet_header &header,
    mt_prot_lib::payload &payload)
{

  /* A payload cannot be too large */
  const size_t header_size = sizeof(mt_prot_lib::header_bytes);
  const size_t max_pb_size = MT_PROT_PAYLOAD_SIZE - header_size;
  if (pb_buffer_size > max_pb_size)
  {
    return encoding_result::ENC_PB_TOO_LONG;
  }

  /* Setup crypto */
  nonce nonc;
  get_nonce(header, nonc);
  IV iv;
  memcpy(iv.bytes, nonc.bytes, sizeof(iv.bytes));
  bool iv_success = mt_crypto_set_IV(iv);
  if (!iv_success)
    return encoding_result::ENC_CRYPTO_ERR;
  mt_crypto_set_counter_size(MT_PROT_CRYPT_COUNTER_SIZE);

  /* Add header to payload */
  mt_prot_lib::header_bytes header_bytes = {0};
  mt_prot_lib::packet_to_bytes(header_bytes, header);
  memcpy(payload.bytes, header_bytes.data, sizeof(header_bytes));

  /* Encrypt PB */
  mt_prot_lib::payload padded_payload = {0};
  memcpy(padded_payload.bytes, pb_buffer, pb_buffer_size);
  mt_crypto_encrypt(padded_payload);

  /* Add PB to payload */
  memcpy(payload.bytes + sizeof(header_bytes), padded_payload.bytes, pb_buffer_size);

  pb_buffer_size = sizeof(header_bytes) + pb_buffer_size;
  return encoding_result::ENC_OK;
}

bool mt_lib::configure(mt_prot_lib::psk *psk)
{

  /* NULL psk sets the default */
  if (psk == NULL)
  {
    mt_prot_lib::psk default_psk;
    return mt_crypto_set_PSK(default_psk);
  }

  /* Keys longer than 32 should not be used */
  if (psk->size > 32)
  {
    return false;
  }

  /* Meshtastic switches crypto methods based on key length */
  crypt_method mode;
  if (psk->size > 16)
  {
    mode = CRYPT_AES_CTR256;
  }
  else
  {
    mode = CRYPT_AES_CTR128;
  }

  /* This might fail if implementer does not support the mode */
  bool success = mt_crypto_mode(mode);
  if (!success)
    return false;

  return mt_crypto_set_PSK(*psk);
}
