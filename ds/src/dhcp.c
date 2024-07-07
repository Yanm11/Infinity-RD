/********************************** 
   Code by: Yan Meiri	
   Project: DHCP
   Date: 03/07/24
   Review by: Amit
   Review Date: 07/05/24
   Approved by: Amit
   Approval Date: 07/07/24
**********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* maloc free */

#include "trie.h"
#include "dhcp.h"

#define BITS_PER_BYTE 8
#define NUM_ADDRESSES 3
#define NETWORK 0 /* 255.255.255.0 */
#define SERVER ~0-1 /* 255.255.255.254 */
#define BRODCAST ~0 /* 255.255.255.255 */

static trie_t *GetTrie(const DHCP_Server_t *dhcp);
static unsigned char *GetBaseAddress(const DHCP_Server_t *dhcp);
static size_t GetSubnetPrefix(const DHCP_Server_t *dhcp);
static unsigned int ConvertAddressToUnInt(unsigned char address[BYTES_IN_IP]);
static void ConvertAddressToUnChar(unsigned int address,
											 unsigned char *address_ptr);
static status_e InsertPreDefineAddress(DHCP_Server_t *dhcp);


struct DHCP_Server
{
	trie_t *trie;
	unsigned char *base_network_id;
	size_t subnet_prefix;
};

/******* API FUNCTIONS ***********/

DHCP_Server_t *DHCPCreate(unsigned char base_network_id[BYTES_IN_IP],
						  size_t subnet_prefix)
{
	DHCP_Server_t *dhcp = NULL;
	size_t host_bits = 0;
	status_e status = SUCCESS;

	assert(0 < subnet_prefix && 32 > subnet_prefix);
	assert(base_network_id);
	
	/* allocating the dhcp */
	dhcp = (DHCP_Server_t*)malloc(sizeof(DHCP_Server_t));
	if (NULL == dhcp)
	{
		return NULL;
	}
	
	/* creating the trie with the correct hight -> nuber of bits for host */
	host_bits = BYTES_IN_IP * BITS_PER_BYTE - subnet_prefix;
	dhcp->trie = TrieCreate(host_bits);
	if (NULL == GetTrie(dhcp))
	{
		free(dhcp);
		
		return NULL;
	}
	
	dhcp->base_network_id = base_network_id;
	dhcp->subnet_prefix = subnet_prefix;
	
	/* insert predefine addresses */
	status = InsertPreDefineAddress(dhcp);
	if (MEMORY_FALIURE == status)
	{
		TrieDestroy(GetTrie(dhcp));
		free(dhcp);
		
		return NULL;
	}
	
	return dhcp;
}

void DHCPDestroy(DHCP_Server_t *dhcp)
{
	if (NULL == dhcp)
	{
		return;
	}
	
	TrieDestroy(GetTrie(dhcp));
	free(dhcp);
}

size_t DHCPCountFree(const DHCP_Server_t *dhcp)
{
	size_t number_of_bits_for_host = 0;
	size_t subnet_prefix = 0;
	size_t total_possible_host_addresses = 1;
	
	assert(dhcp);
	
	subnet_prefix = GetSubnetPrefix(dhcp);
	number_of_bits_for_host = (BYTES_IN_IP * BITS_PER_BYTE) - subnet_prefix;
	

	total_possible_host_addresses <<= number_of_bits_for_host;
	
	
	return (total_possible_host_addresses - TrieCount(GetTrie(dhcp)));
}

status_e DHCPAllocateIP(DHCP_Server_t *dhcp,
                        unsigned char requested_ip[BYTES_IN_IP],
                        unsigned char received_ip[BYTES_IN_IP])
{
	unsigned int address_to_insert = 0;
	unsigned int inserted_address = 0;
	trie_status_e status = TRIE_SUCCESS;
	trie_t *trie = NULL;
	
	assert(dhcp);
	assert(received_ip);
	
	trie = GetTrie(dhcp);

	if (NULL == requested_ip)
	{
		address_to_insert = ConvertAddressToUnInt(GetBaseAddress(dhcp));
	}
	else
	{
		address_to_insert = ConvertAddressToUnInt(requested_ip);
	}
	
	status = TrieInsert(trie, address_to_insert, &inserted_address);
	if (TRIE_MEMORY_FALIURE == status)
	{
		return MEMORY_FALIURE;
	}
	else if (TRIE_FULL == status)
	{
		return DHCP_FULL;
	}
	
	inserted_address += ConvertAddressToUnInt(GetBaseAddress(dhcp));
	ConvertAddressToUnChar(inserted_address, received_ip);
	
	return SUCCESS;
}

status_e DHCPFreeIP(DHCP_Server_t *dhcp, unsigned char address[BYTES_IN_IP])
{
	unsigned int address_to_remove = 0;
	unsigned int network_address = 0;
	size_t subnet_prefix = 0; 
	size_t mask = 0;
	trie_status_e status = TRIE_SUCCESS;
	
	assert(dhcp);
	assert(address);
	
	address_to_remove = ConvertAddressToUnInt(address);
	network_address = ConvertAddressToUnInt(GetBaseAddress(dhcp));
	
	subnet_prefix = GetSubnetPrefix(dhcp);
	mask = (1 << subnet_prefix) - 1;
	mask = mask << (BYTES_IN_IP * BITS_PER_BYTE - subnet_prefix);
	
	if ((address_to_remove & mask )!= network_address)
	{
		return BAD_SUBNET;
	}
	
	status = TrieRemove(GetTrie(dhcp), address_to_remove);
	if (TRIE_DOUBLE_FREE == status)
	{
		return DOUBLE_FREE;
	}
	
	return SUCCESS;
}




/******* HELPER FUNCTIONS ***********/

static trie_t *GetTrie(const DHCP_Server_t *dhcp)
{
	assert(dhcp);
	
	return dhcp->trie;
}

static unsigned char *GetBaseAddress(const DHCP_Server_t *dhcp)
{
	assert(dhcp);
	
	return dhcp->base_network_id;
}

static size_t GetSubnetPrefix(const DHCP_Server_t *dhcp)
{
	assert(dhcp);
	
	return dhcp->subnet_prefix;
}

static unsigned int ConvertAddressToUnInt(unsigned char address[BYTES_IN_IP])
{
	unsigned int whole_address = 0;
	size_t i = 0;
	
	for (; i < BYTES_IN_IP; ++i)
	{
		whole_address = (whole_address << BITS_PER_BYTE) + address[i];
	}
	
	return whole_address;
}

static void ConvertAddressToUnChar(unsigned int address,
											 unsigned char *address_ptr)
{
	size_t i =  BYTES_IN_IP;
	
	assert(address_ptr);
	
	for (; i > 0; --i)
	{
		*address_ptr = (unsigned char)((address>>BITS_PER_BYTE *(i - 1)) & 0xFF);
		++address_ptr;
	}
}

static status_e InsertPreDefineAddress(DHCP_Server_t *dhcp)
{
	unsigned char addresses[NUM_ADDRESSES] = {NETWORK,SERVER,BRODCAST};
	unsigned char *base_address = NULL;
	size_t i = 0;
	unsigned int address_to_insert = 0;
	unsigned int inserted_address = 0;
	trie_status_e status = TRIE_SUCCESS;
	trie_t *trie = NULL;
	
	assert(dhcp);
	
	base_address = GetBaseAddress(dhcp);
	address_to_insert = ConvertAddressToUnInt(base_address);

	trie = GetTrie(dhcp);
	
	for (;i < NUM_ADDRESSES; ++i)
	{
		address_to_insert += addresses[i];
		
		status = TrieInsert(trie, address_to_insert, &inserted_address);
		if (TRIE_MEMORY_FALIURE == status)
		{
			return MEMORY_FALIURE;
		}
		
		address_to_insert -= addresses[i];
	}
	
	return SUCCESS;
}















