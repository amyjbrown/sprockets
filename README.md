# Sprockets
Friendly single-header wrapper API for the C socket family
 
 ## Design Goals
 This library is meant to a friendly and
 easy to drop in and use interface for working for C socket programming that removes the boilerplate and presents a more modern API.
 Additionally, it is meant to act as convnience layer, it does not abstract away or hide state or hijack the control flow of your program.
 Sockets created using the methods provided can easily be used with the original sockets API, and sockets created using the old function calls
 work with `TCPSend`, `TCPRecv` and `TCPRecvall`. This allows for extra flexibility in programming applications, plus generates a pleasent aura of niceness.
 This library is a single header `sprockets.h` and the associated implmenetation file, making it easy to copy and paste or implement into your project.
 
 ## Compatability
 Sprockets is currently experimental and has only been built on Linux via gcc, using the GNU99 standard.
 Future releases are looking towards making this more cross-platform.
 Please let me know if you experience any bugs!
 
 ## Integrating Sprockets
 To integrate the Sprockets library into your project, copy and paste the header file and implementation file `sprockets.h` and `sprockets.c` into your project and compile as necessary.
