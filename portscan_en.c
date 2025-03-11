#include <stdio.h> // Library for input and output (I/O).
#include <sys/socket.h> // Library for creating sockets.
#include <netdb.h> // Library for network functions.
#include <unistd.h> // Library for process manipulation (close).
#include <string.h> // Library for string manipulation (fgets).
#include <arpa/inet.h> // Library for IP address conversion (inet_addr).

int main(void)
{
        char host[25]; // Stores the target IP address.
        int mysock, conect; // Variables for the socket and connection.
        int port, port_limit; // Range of ports to be scanned.
        struct sockaddr_in alvo; // Structure to store target data.

        printf("HOST: "); // Prompt for the target IP address.
        fgets(host, sizeof(host), stdin);
        host[strcspn(host, "\n")] = '\0'; // Remove the newline character left by fgets.

        printf("PORT LIMIT: "); // Prompt for the number of ports to scan.
        scanf("%d", &port_limit);

        printf("\033[H\033[J"); // Clear the terminal screen.
        printf("=======================[Scanning host %s]=======================\n", host);

        // Loop to scan the range of ports specified by the user.
        for(port = 0; port < port_limit; port++)
        {
                mysock = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket over IPv4.
                if(mysock == -1) // Check for errors in socket creation.
                {
                        printf("Error creating socket.\n");
                        return 1; // Exit the program if there is an error.
                }

                // Set the target's IP and port.
                alvo.sin_family = AF_INET; 
                alvo.sin_port = htons(port); // Convert the port to the correct format.
                alvo.sin_addr.s_addr = inet_addr(host); // Convert the IP to network format.

                conect = connect(mysock, (struct sockaddr *)&alvo, sizeof(alvo)); // Try to connect to the target.

                if(conect == 0) // If the connection is successful, the port is open.
                {
                        printf("%d - status OPEN.\n", port);
                }

                close(mysock); // Close the socket after each attempt.
        }
        printf("=======================[By: cosmic]=============================\n");
        return 0;
}
