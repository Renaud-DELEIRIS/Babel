ArtNo Inc.
Category: Babel documentation



                                                BABEL PROTOCOL



Table of Contents

        1. Introduction............................1
        2. VoIP Model..............................1
        3. The BABEL Protocol......................1
            3.1 Protocol example client to server..1


1 - Introduction

        The BABEL consists in a client/server architecture voice over IP application, similar to Skype 
        or TeamSpeak. Here is the RFC of the protocol we have created to make this project.


2 - VoIP Model

                        +---------------+                               +---------------+
                        |               |                               |               |
                        | /-----------\ |                               | /-----------\ |
                        | |  USER 1   | |                               | |  USER 2   | |
                        | \-----------/ |             Internet          | \-----------/ |
                        |               <------------------------------->               |
                        |               |        Voice transmission     |               |
                        |               |         through network       |               |
                        |               |                               |               |
                        |               |                               |               |
                        +---------------+                               +---------------+


        Voice over Internet Protocol (VoIP), also called IP telephony, is a method and group of technologies for the delivery of voice communications and multimedia sessions over Internet Protocol (IP) networks, such as the Internet. The terms Internet telephony, broadband telephony, and broadband phone service specifically refer to the provisioning of communications services (voice, fax, SMS, voice-messaging) over the Internet, rather than via the public switched telephone network (PSTN), also known as plain old telephone service (POTS). 


ArtNo                                       BABEL PROTOCOL                                             [Page 1]


3 - The BABEL Protocol

        Our binary protocol for the babel consist of a bitset array of the values.
        values are structured following this diagram:

        <username>;<password>;<command>

        each part of the value is encoded in binary of 16b

        The server encodes the entire answere and decode the response from the client
        The client uses the same encoder and decoder
        All data transfered from Client to Server and Server to Client are a binary array

3.1 - Protocol example Client to Server

        Username:  
            0000000100100001, 
            0000000001100000,
            0000000011111001,
            0000000001111111,
            0000000010000011

        Password:
            0000000100100001, 
            0000000001100000,
            0000000011111001,
            0000000001111111,
            0000000010000011,
            0000D00010001001,
            0000101100011110,

        Command:
            0000000001110101,
            0000010011100111,
            0000000101010110,
            0000000001100100,

        Payload:
        [
            Username,
            Password,
            Command
        ]

        +--------------+       payload  +--------------+
        |   tcp server | <--------------|  tcp client  |
        |              |                +--------------+
        +--------------+


3.2 - Protocol example Server to Client

        Status:
            0000000011111001


        +--------------+       status   +--------------+
        |   tcp server |--------------->|  tcp client  |
        |              |                +--------------+
        +--------------+

