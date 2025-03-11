#include <stdio.h> // Biblioteca para entrada e saída de dados (I/O).
#include <sys/socket.h> // Biblioteca para criação de sockets.
#include <netdb.h> // Biblioteca para funções de rede.
#include <unistd.h> // Biblioteca para manipulação de processos (close).
#include <string.h> // Biblioteca para manipulação de strings (fgets).
#include <arpa/inet.h> // Biblioteca para conversão de endereços IP (inet_addr).

int main(void)
{
        char host[25]; // Armazena o IP do alvo.
        int mysock, conect; // Variáveis para o socket e conexão.
        int port, port_limit; // Intervalo de portas a serem escaneadas.
        struct sockaddr_in alvo; // Estrutura para armazenar os dados do alvo.

        printf("HOST: "); // Solicita o endereço IP do alvo.
        fgets(host, sizeof(host), stdin);
        host[strcspn(host, "\n")] = '\0'; // Remove o caractere de nova linha deixado pelo fgets.

        printf("LIMITE DE PORTAS: "); // Solicita o limite de portas a serem escaneadas.
        scanf("%d", &port_limit);

        printf("\033[H\033[J"); // Limpa a tela do terminal.
        printf("=======================[Varrendo host %s]=======================\n", host);

        // Loop para verificar o intervalo de portas informado pelo usuário.
        for(port = 0; port < port_limit; port++)
        {
                mysock = socket(AF_INET, SOCK_STREAM, 0); // Cria socket TCP sobre IPv4.
                if(mysock == -1) // Verifica se houve erro na criação do socket.
                {
                        printf("Erro ao criar socket.\n");
                        return 1; // Encerra o programa em caso de erro.
                }

                // Configuração do alvo (endereço IP e porta).
                alvo.sin_family = AF_INET; 
                alvo.sin_port = htons(port); // Converte a porta para o formato correto.
                alvo.sin_addr.s_addr = inet_addr(host); // Converte o IP para o formato de rede.

                conect = connect(mysock, (struct sockaddr *)&alvo, sizeof(alvo)); // Tenta conexão com o alvo.

                if(conect == 0) // Se a conexão for bem-sucedida, a porta está aberta.
                {
                        printf("%d - status ABERTA.\n", port);
                }

                close(mysock); // Fecha o socket após cada tentativa.
        }
        printf("=======================[By: cosmic]=============================\n");
        return 0;
}
