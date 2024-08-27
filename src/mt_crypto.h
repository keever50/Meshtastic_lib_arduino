#pragma once
#include <mt_protocol.h>

/*******************************************************************************
 * Public prototypes for crypto implementation
 ******************************************************************************/

/*Meshtastic can switch between two modes depending on key length*/
bool mt_crypto_mode(mt_prot_lib::crypt_method mode);

bool mt_crypto_set_IV(mt_prot_lib::IV &iv);

bool mt_crypto_set_PSK(mt_prot_lib::psk &psk);

bool mt_crypto_encrypt(mt_prot_lib::payload &payload);

bool mt_crypto_decrypt(mt_prot_lib::payload &payload);

bool mt_crypto_set_counter_size(uint8_t count);