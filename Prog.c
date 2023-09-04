#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#define IFACE_NAME "eth0" // Change this to the desired network interface

int main()
{
    int fd;
    struct ifreq ifr;

    // Create a socket for IPv4 communication
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Set the network interface name
    strncpy(ifr.ifr_name, IFACE_NAME, IFNAMSIZ);

    // Retrieve the IP address associated with the network interface
    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
        perror("Failed to retrieve IP address");
        close(fd);
        return 1;
    }

    // Close the socket
    close(fd);

    // Extract and print the IP address
    struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
    char* ip_address = inet_ntoa(ipaddr->sin_addr);

    printf("System IP Address on %s is: %s\n", IFACE_NAME, ip_address);

    return 0;
}
