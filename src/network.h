#ifndef SOULFU_NETWORK_H
#define SOULFU_NETWORK_H

// <ZZ> This file contains functions to handle networking
//      network_blah			- Blah

extern unsigned char  network_script_newly_spawned;
extern unsigned char  network_script_extra_data;
extern unsigned char  network_script_remote_index;
extern unsigned char  network_script_netlist_index;
extern unsigned short network_script_x;
extern unsigned short network_script_y;
extern unsigned char  network_script_z;
extern unsigned char  network_script_facing;
extern unsigned char  network_script_action;
extern unsigned char  network_script_team;
extern unsigned char  network_script_poison;
extern unsigned char  network_script_petrify;
extern unsigned char  network_script_alpha;
extern unsigned char  network_script_deflect;
extern unsigned char  network_script_haste;
extern unsigned char  network_script_other_enchant;
extern unsigned char  network_script_eqleft;
extern unsigned char  network_script_eqright;
extern unsigned char  network_script_eqcol01;
extern unsigned char  network_script_eqcol23;              // high-data only
extern unsigned char  network_script_eqspec1;              // high-data only
extern unsigned char  network_script_eqspec2;              // high-data only
extern unsigned char  network_script_eqhelm;               // high-data only
extern unsigned char  network_script_eqbody;               // high-data only
extern unsigned char  network_script_eqlegs;               // high-data only
extern unsigned char  network_script_class;                // high-data only
extern unsigned short network_script_mount_index;          // high-data only

extern unsigned short num_remote;
extern unsigned char network_on;
extern unsigned char global_version_error;
extern unsigned short required_executable_version;
extern unsigned short required_data_version;

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
