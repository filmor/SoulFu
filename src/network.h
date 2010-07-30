#ifndef SOULFU_NETWORK_H
#define SOULFU_NETWORK_H

/* network.c */
unsigned char packet_valid(void);
void network_clear_remote_list(void);
unsigned char network_add_remote(unsigned char *remote_name);
void network_delete_remote(unsigned short remote);
void network_close(void);
unsigned char network_setup(void);
void network_send(unsigned char send_code);
unsigned short network_find_remote_character(unsigned int ip_address_of_remote, unsigned char local_index_on_remote);
void network_listen(void);
unsigned char network_find_script_index(unsigned char *filename);
void network_send_chat(unsigned char speaker_class, unsigned char *speaker_name, unsigned char *message);
void network_send_room_update(void);
#endif
