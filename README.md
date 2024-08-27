# Meshtastic_lib_arduino
A simple arduino library to decode/encode meshtastic(https://github.com/meshtastic/firmware) packets

# Requires user crypto implementation!
The functions that have to be implemented are found in src/mt_crypto_skeleton.cpp.
The implementer can copy and paste this skeleton.
This is required because microcontrollers might or might not support hardware crypto.

# How to decode or encode?
You can simply use the mt_lib::decode or mt_lib::encode functions AFTER calling mt_lib::configure.

mt_lib::configure
Configures decoding/encoding. Leave psk NULL for default psk.

mt_lib::decode
Decodes and decrypts the *payload.
The result is written into the same *payload.
The header will be extracted as well.

mt_lib::encode
Encrypts the PB and adds header into the &payload.
&pb_buffer_size will be the new size to be send.

# How to read the header?
The header is returned by decoding, or used for encoding.
This is a struct that can directly be used.

Flags byte
The flags can extracted using mt_prot_lib::get_packet_header_flags
It can be encoded using mt_prot_lib::packet_flags_to_byte
