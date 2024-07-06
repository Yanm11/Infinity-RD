#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h> /* free() */
#include <assert.h>

#include "dhcp.h"

#define TESTNUM 3

static char failed_tests_print[300] = {'\0'};

static void AddFailedTest(const char *str);

static int TestAllocateIP(void);
static int TestFreeIP(void);
static int TestCountFree(void);

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestAllocateIP();
	printf("Tested AllocateIP\n");

	failed_tests_num += TestFreeIP();
	printf("Tested FreeIP\n");

	failed_tests_num += TestCountFree();
	printf("Tested CountFree\n");

	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}

static void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}

static int TestAllocateIP(void)
{
	DHCP_Server_t *dhcp = NULL;
	unsigned char network_id[BYTES_IN_IP] = {192,168,100,0};
	unsigned char address1[BYTES_IN_IP] = {192,168,100,1};
	unsigned char address2[BYTES_IN_IP] = {192,168,100,2};
	unsigned char address3[BYTES_IN_IP] = {192,168,100,3};
	unsigned char address4[BYTES_IN_IP] = {192,168,100,4};
	unsigned char address5[BYTES_IN_IP] = {192,168,100,5};
	unsigned char address6[BYTES_IN_IP] = {192,168,100,6};
	unsigned char address30[BYTES_IN_IP] = {192,168,100,30};
	unsigned char get_address[BYTES_IN_IP] = {0,0,0,0};
	status_e status = SUCCESS;
	size_t count = 0;
	
	dhcp = DHCPCreate(network_id, 27);
	
	/* check if allocate a free address successfully allocates the address */
	status = DHCPAllocateIP(dhcp, address1, get_address);
	count = DHCPCountFree(dhcp);
	if (memcmp(address1, get_address, 4) || count != 28 || SUCCESS != status)
	{
		AddFailedTest("TestAllocateIP1\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	status = DHCPAllocateIP(dhcp, address2, get_address);
	count = DHCPCountFree(dhcp);
	if (memcmp(address2, get_address, 4) || count != 27 || SUCCESS != status)
	{
		AddFailedTest("TestAllocateIP2\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	status = DHCPAllocateIP(dhcp, address3, get_address);
	count = DHCPCountFree(dhcp);
	if (memcmp(address3, get_address, 4) || count != 26 || SUCCESS != status)
	{
		AddFailedTest("TestAllocateIP3\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	status = DHCPAllocateIP(dhcp, address4, get_address);
	count = DHCPCountFree(dhcp);
	if (memcmp(address4, get_address, 4) || count != 25 || SUCCESS != status)
	{
		AddFailedTest("TestAllocateIP4\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	/* 	check if allocate a non-free address successfully allocates 
		the next available address */
	status = DHCPAllocateIP(dhcp, address2, get_address);
	count = DHCPCountFree(dhcp);
	if (memcmp(address5, get_address, 4) || count != 24 || SUCCESS != status)
	{
		AddFailedTest("TestAllocateIP5\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	/* 	check if allocate a big non-free address successfully allocates 
		the smallest available address */
	status = DHCPAllocateIP(dhcp, address30, get_address);
	count = DHCPCountFree(dhcp);
	if (memcmp(address6, get_address, 4) || count != 23 || SUCCESS != status)
	{
		AddFailedTest("TestAllocateIP5\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	DHCPDestroy(dhcp);
	
	dhcp = DHCPCreate(network_id, 30);
	status = DHCPAllocateIP(dhcp, address1, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 0 || SUCCESS != status)
	{
		AddFailedTest("TestAllocateIP6\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	/* 	check if allocate to a full dhcp returns DHCP_FULL status */
	status = DHCPAllocateIP(dhcp, address1, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 0 || DHCP_FULL != status)
	{
		AddFailedTest("TestAllocateIP7\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	DHCPDestroy(dhcp);
	return 0;
}

static int TestFreeIP(void)
{
	DHCP_Server_t *dhcp = NULL;
	unsigned char network_id[BYTES_IN_IP] = {192,168,100,0};
	unsigned char address1[BYTES_IN_IP] = {192,168,100,1};
	unsigned char address2[BYTES_IN_IP] = {192,168,100,2};
	unsigned char address3[BYTES_IN_IP] = {192,168,100,3};
	unsigned char address4[BYTES_IN_IP] = {192,168,100,4};
	unsigned char address5[BYTES_IN_IP] = {192,168,100,5};
	unsigned char address6[BYTES_IN_IP] = {192,168,100,6};
	unsigned char address30[BYTES_IN_IP] = {192,168,100,30};
	unsigned char get_address[BYTES_IN_IP] = {0,0,0,0};
	status_e status = SUCCESS;
	size_t count = 0;
	
	dhcp = DHCPCreate(network_id, 27);
	
	DHCPAllocateIP(dhcp, address1, get_address);
	DHCPAllocateIP(dhcp, address2, get_address);
	DHCPAllocateIP(dhcp, address3, get_address);
	DHCPAllocateIP(dhcp, address4, get_address);
	DHCPAllocateIP(dhcp, address5, get_address);
	DHCPAllocateIP(dhcp, address6, get_address);
	
	/* check if free successfully frees an address */
	status =  DHCPFreeIP(dhcp, address4);
	count = DHCPCountFree(dhcp);
	if (count != 24 || SUCCESS != status)
	{
		AddFailedTest("TestFreeIP1\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	/* check if free'd address can be allocated */
	DHCPAllocateIP(dhcp, address4, get_address);
	count = DHCPCountFree(dhcp);
	if (memcmp(address4, get_address, 4) || count != 23)
	{
		AddFailedTest("TestFreeIP2\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	status =  DHCPFreeIP(dhcp, address5);
	count = DHCPCountFree(dhcp);
	if (count != 24 || SUCCESS != status)
	{
		AddFailedTest("TestFreeIP1\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	/* check if freeing a free address returns double free */
	status =  DHCPFreeIP(dhcp, address5);
	count = DHCPCountFree(dhcp);
	if (count != 24 || DOUBLE_FREE != status)
	{
		AddFailedTest("TestFreeIP1\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	DHCPDestroy(dhcp);
	return 0;
}

static int TestCountFree(void)
{
	DHCP_Server_t *dhcp = NULL;
	unsigned char network_id[BYTES_IN_IP] = {192,168,100,0};
	unsigned char address1[BYTES_IN_IP] = {192,168,100,1};
	unsigned char address2[BYTES_IN_IP] = {192,168,100,2};
	unsigned char address3[BYTES_IN_IP] = {192,168,100,3};
	unsigned char address4[BYTES_IN_IP] = {192,168,100,4};
	unsigned char address5[BYTES_IN_IP] = {192,168,100,5};
	unsigned char address6[BYTES_IN_IP] = {192,168,100,6};
	unsigned char get_address[BYTES_IN_IP] = {0,0,0,0};
	size_t count = 0;
	
	dhcp = DHCPCreate(network_id, 27);
	count = DHCPCountFree(dhcp);
	if (count != 29)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}
	
	DHCPAllocateIP(dhcp, address1, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 28)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPAllocateIP(dhcp, address3, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 27)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPFreeIP(dhcp, address3);
	count = DHCPCountFree(dhcp);
	if (count != 28)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPAllocateIP(dhcp, address4, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 27)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPFreeIP(dhcp, address1);
	count = DHCPCountFree(dhcp);
	if (count != 28)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPFreeIP(dhcp, address4);
	count = DHCPCountFree(dhcp);
	if (count != 29)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPAllocateIP(dhcp, address6, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 28)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPAllocateIP(dhcp, address2, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 27)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPAllocateIP(dhcp, address5, get_address);
	count = DHCPCountFree(dhcp);
	if (count != 26)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPFreeIP(dhcp, address6);
	count = DHCPCountFree(dhcp);
	if (count != 27)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPFreeIP(dhcp, address5);
	count = DHCPCountFree(dhcp);
	if (count != 28)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPFreeIP(dhcp, address2);
	count = DHCPCountFree(dhcp);
	if (count != 29)
	{
		AddFailedTest("TestCountFree1\n");
		DHCPDestroy(dhcp);
		return 1;
	}

	DHCPDestroy(dhcp);
	return 0;
}




















