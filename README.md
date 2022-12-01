# Bitcoin Price in C 
-----------------
![Release](https://img.shields.io/badge/Release-v1.0-brightgreen?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![Librarie](https://img.shields.io/badge/Librarie-Gtk-green?style=for-the-badge)
![Size](https://img.shields.io/github/repo-size/Oxbian/Bitcoin-Price-C?label=SIZE&style=for-the-badge)
![Licence](https://img.shields.io/github/license/Oxbian/Bitcoin-Price-C?style=for-the-badge)
![OpenSource](https://img.shields.io/badge/OpenSource-important?style=for-the-badge&logo=opencollective&logoColor=white)

        
I'm a fan of cryptocurrencies, so I decided to make a program to get the price of bitcoin and print it with ascii art.   
![Screen](https://imgur.com/aJg9hbp.png)
      
### Why ASCII ART?
        
Why not? ASCII ART is beautiful so I decided to use it :)

## How it works?
-----------
The program get the price of bitcoin from the [BlockChainInfo Website](https://www.blockchain.com/explorer), convert it into a string and from this string I can get the number and convert them into my ascii art.

## Requirements
-----------
- make
- gcc 
- json-c
- curl

### Archlinux and derivates

        sudo pacman -S gcc make json-c curl

### Ubuntu and derivates

        sudo apt install gcc make libjson-c-dev libcurl4-openssl-dev

And also need a network connection to get the bitcoin price from the api

## Installation
--------

        git clone https://github.com/Oxbian/Bitcoin-Price-C.git
        cd Bitcoin-Price-C/src
        make
        ./bitcoinprice
