#define SHARED 1
#define NOTSHARED 0
#define FALSE 0
#define TRUE !FALSE

typedef struct friendsList_t{
	char username[20];
	char IPAddress[17];
	int port;
} friendsList_t;

typedef struct settings_t{
	char username[20];
	char IPAddress[17];
	char logFile[20];
	int port;
} settings_t;

typedef struct shareList_t{
	char fileLocation[256];
	char fileName[20];
	char userName[20];
	char permissionLevel[2];//1 = shared, 0 = not shared	
} shareList_t;

extern int forkHandler();
