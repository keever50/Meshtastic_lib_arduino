/*******************************************************************************
 * Skeleton for meshtastic crypto implementation.
 *
 * This is required because crypto can be done on hardware, but also software.
 * Meshtastic also has a custom way of dealing with crypto.
 * Copying this file and leaving functions empty
 * will leave payloads unencrypted.
 ******************************************************************************/

#include <mt_crypto.h>

#if 0 /* Dont let the compiler compile the skeleton. */

/*Meshtastic can switch between two modes depending on key length*/
bool mt_crypto_mode(mt_prot_lib::crypt_method mode)
{
  return true;
}

bool mt_crypto_set_IV(mt_prot_lib::IV &iv)
{
  return true;
}

bool mt_crypto_set_PSK(mt_prot_lib::psk &psk)
{
  return true;
}

bool mt_crypto_encrypt(mt_prot_lib::payload &payload)
{
  return true;
}

bool mt_crypto_decrypt(mt_prot_lib::payload &payload)
{
  return true;
}

bool mt_crypto_set_counter_size(uint8_t count)
{
  return true;
}

#endif