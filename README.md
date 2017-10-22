# Proof of concept opc client

Sends a stream of open pixel control messages at roughly 60 fps ( aka every 16.66ms).  Each frame is sent with every pixel color set to an incrementing number.  

## Usage
```
$ mkdir build
$ cd build
$ cmake ..
$ make && ./main OPC_SERVER

