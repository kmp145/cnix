#define SHARED 1
#define NOTSHARED 0
#define FALSE 0
#define TRUE !FALSE

typedef struct settings_t{
	char username[20];
	char IPAddress[16];
	char logFile[20];
	int port;
} settings_t;

typedef struct shareList_t{
	char fileName[10][12];
	char userName[10][20];
	char permissionLevel[10][10];
} shareList_t;
