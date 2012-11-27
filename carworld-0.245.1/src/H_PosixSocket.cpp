
#ifdef USE_POSIX_SOCKETS

#include <iostream>
using namespace std;

extern "C" {
#include <unistd.h> //close
//#include <stdlib.h> //rand
#include <string.h> //strerror
#include <sys/types.h> //bind
#include <sys/socket.h> //udp/socket bind
#include <netinet/in.h>
#include <fcntl.h> //fcntl
#include <netdb.h>
#include <errno.h>

#include <iostream>
using namespace std;

/*
struct hostent
{
	char *h_name;
	char **h_aliases;
	int h_addrtype;
	int h_length;
	char **h_addr_list;
};
#define h_addr  h_addr_list[0]  
int close(int); //unistd.h
char *strerror(int errnum); //string.h
int recv(int s, void *buf, int len, unsigned int flags); //netdb.h
int recvfrom(int s, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen); //netdb.h
int recvmsg(int  s,  struct  msghdr  *msg,  unsigned  int flags); //netdb.h
int socket(int domain, int type, int protocol);
int bind(int   sockfd,  struct  sockaddr  *my_addr, int addrlen);
int sendto(int s, const void *msg, int len, unsigned int flags, const struct sockaddr *to, int tolen);
int connect(int  sockfd,  struct sockaddr *serv_addr, int addrlen);
int send(int s, const  void *msg, int len, unsigned int flags);
hostent *gethostbyname(const char *name); //netdb.h*/
}

#include <iostream> //cout

//extern int errno;

//the beos "socket.h" header does ot define socklen_t
#if defined(B_BEOS_VERSION) || defined(__MORPHOS__)
#define socklen_t int
#endif

#include "H_Socket.h"

//UTILS
void write_error(const char* Where, bool bad=true)
{
	if (bad)
		cout << "ERROR(" << __FILE__ << "," << Where << "): " << strerror(errno) << endl;
}


//CLASS HSocServer
HSocServer::HSocServer(short portno)
{
	int ret;

//open socket
	s = socket(AF_INET, SOCK_DGRAM, 0);
	write_error("socket creation",s==0);

//set non blocking
	ret = fcntl(s, F_SETFL, O_NONBLOCK);
	write_error("set nonblocking",ret!=0);

//bind
	sockaddr_in name;
	name.sin_family = AF_INET;
	name.sin_port = htons(portno);
	name.sin_addr.s_addr = INADDR_ANY;
	ret = bind(s, (sockaddr*)&name, sizeof(name));
	write_error("bind",ret!=0);
	cout << "waiting on port: " << portno << endl;
}

HSocServer::~HSocServer()
{
	close(s);
}

#include <map>
using std::map;

static int NextClientID = 1;
static map<int,sockaddr> ClientAdresses;
bool operator==(const sockaddr &A, const sockaddr &B)
{
	return memcmp((void*)&A,(void*)&B,sizeof(sockaddr))==0;
}


int HSocServer::Recieve(void* buffer, int size, int *id)
{
//read incomming
	sockaddr from;
	socklen_t fromlen = sizeof(from);
	int recieved_bytes = recvfrom(s,  buffer, size, 0, &from, &fromlen);
	//write_error("recieveing bytes",recieved_bytes!=-1);
	if (recieved_bytes>0)
	{
		*id = *((int*)buffer);
		if (*id==0)
		{
		//the client does not have an ID yet, give him one
			*id = NextClientID++;
			ClientAdresses[*id] = from;
		}
		else
		{
		//we know about this client, check his ID
			/*map<int,sockaddr>::iterator I = ClientAdresses.find(*id);
			if ((I==ClientAdresses.end()) || !(I->second==from))
			{
				cout << "bad ID/adress pair: ID=" << (*id) << endl;
				return -1;
			}*/
		}
		return recieved_bytes;
	}
	return -1;
}

bool HSocServer::Send(void* buffer, int size, int id)
{
	map<int,sockaddr>::iterator I = ClientAdresses.find(id);
	if (I==ClientAdresses.end())
	{
		cout << "bad ID: ID=" << id << endl;
		return false;
	}
	int sent_bytes = sendto(s,  buffer, size, 0, &I->second, sizeof(I->second));
	return (sent_bytes==size);
}

bool HSocServer::Broadcast(void* buffer, int size)
{
	int sent_bytes = 0;
	map<int,sockaddr>::iterator I;
	for (I = ClientAdresses.begin() ; I!=ClientAdresses.end() ; I++)
	{
		sent_bytes += sendto(s,  buffer, size, 0, &I->second, sizeof(I->second));
	}
	return sent_bytes*ClientAdresses.size();
}

//CALSS HSocClient
HSocClient::HSocClient(const char *servername, short portno)
{
	int ret;

//open socket
	s = socket(AF_INET, SOCK_DGRAM, 0);
	write_error("socket creation",s==0);

//get the server adress
	hostent *mmserv = gethostbyname(servername);
	write_error("gethostbyname",mmserv==0);
	sockaddr_in name;
	memcpy((char*)(&(name.sin_addr.s_addr)), mmserv->h_addr, mmserv->h_length);
	name.sin_family = AF_INET;
	name.sin_port = htons(portno);

//connect
	ret = connect(s, (sockaddr*)&name, sizeof(name));
	write_error("connect",ret!=0);
}

HSocClient::~HSocClient()
{
	close(s);
}

void HSocClient::SetBlocking(bool IsBlocking)
{
	if (IsBlocking)
	{
		int ret = fcntl(s, F_SETFL, 0/*O_ASYNC*/);
		write_error("set blocking",ret!=0);
	}
	else
	{
		int ret = fcntl(s, F_SETFL, O_NONBLOCK);
		write_error("set nonblocking",ret!=0);
	}
}

bool HSocClient::Send(void* buffer, int size)
{
	int sent_bytes = send(s, buffer, size, 0);
	write_error("sending bytes",sent_bytes!=size);
	return sent_bytes==size;
}


int HSocClient::Recieve(void* buffer, int size)
{
	int recv_bytes = recv(s, buffer, size, 0);
	if (recv_bytes>0)
	{
	}
	else
	{
		write_error("recieving bytes");
		return false;
	}
	return recv_bytes;
}

#endif //USE_POSIX_SOCKETS
