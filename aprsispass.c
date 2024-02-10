/**
 * Generates an APRS-IS passcode for the provided callsign, using the algorithm
 * described in the APRS-IS source code.
 * 
 * Daria Juniper
 * Github: @juniberry
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum length of callsign */ 
#define MAX_CALLSIGN 12

/* Function Prototypes */
unsigned int generateAPRSISPasscode(const char* callsign);

int main(int argc, const char* argv[])
{
	unsigned int passcode = 0;
	
	if (argc < 2) {
		printf("APRS-IS Passcode Generator\n");
		printf("Usage: %s <callsign>\nNote -- only supply the base callsign, do not supply an SSID or prefix.\n", argv[0]);
		return -1;
	}

	/* Validate callsign length */
	if (strlen(argv[1]) > MAX_CALLSIGN) {
		printf("Error: Callsign is too long. Maximum length is %i characters.\n", MAX_CALLSIGN);
		return -1;
	}

	char callsign[MAX_CALLSIGN] = {0};
	strncpy(callsign, argv[1], MAX_CALLSIGN - 1);

	passcode = generateAPRSISPasscode(callsign);
	printf("%s passcode: %u\n", callsign, passcode);

	return 0;
}

/**
 * Generates an APRS-IS passcode for the provided callsign.
 * 
 * @param callsign The callsign for which to generate the passcode.
 * @return The passcode for the provided callsign.
 */
unsigned int generateAPRSISPasscode(const char* callsign)
{
	if (callsign == NULL)
		return 0;
	
    const short int INITIAL_HASH = 0x73e2;   /* Hash value from APRS-IS source code */
    short int hash = INITIAL_HASH;

    const char *ptr = callsign;
    size_t len = strlen(callsign);

	/* XOR the callsign with the hash */
    for (size_t i = 0; i < len; i += 2) {
		if (ptr[i] != '\0')
        	hash ^= ptr[i] << 8;

		if (ptr[i + 1] != '\0')
        	hash ^= ptr[i + 1];
    }
    
	/* drop sign and return the passcode */
    return (unsigned int)abs(hash);
}
