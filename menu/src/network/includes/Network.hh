#ifndef NETWORK_HH
#define NETWORK_HH

#include <string>
#include <iostream>

class    Network
{
public:
    typedef enum e_cmd{
              EXIT = 0,
              SYN,
              ACK,
              MSG,
              MAP,
              UP,
              DOWN,
              LEFT,
              RIGHT,
              START,
              END
    } cmd;

    static std::string      cmdToString(Network::cmd cmd);
    static Network::cmd  stringToCmd(std::string cmd);
};

/*
 *
 *  - Envoi d'une action au serveur (mouvement, exit, pause...)
 *     * Client envoi le code de l'action
 *     * Client attend réponse du serveur avant d'envoyer une autre action
 *     * Serveur envoi ACK
 *     * Client peut envoyer une autre action
 *
 *  - Envoi de la map au client (10 x 10 cases autour de la position)
 *     * Serveur envoi le code MAP avec la taille et les data
 *     * Attend 100ms
 *
 *  - Envoi d'un message au serveur
 *     * Client envoi le code MSG avec la taille et le message
 *     * Client attend réponse serveur avant d'envoyer un autre message
 *     * Serveur envoi le message à chaques clients
 *     * Serveur envoi ACK une fois le message relayé à chaque client
 *     * Client peut envoyer un autre message
 *
 *  - Envoi d'un message au client
 *     * Serveur envoi le code MSG avec la taille et le message
 *
 */

#endif // NETWORK_HH
