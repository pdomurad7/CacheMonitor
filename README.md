# CacheMonitor

## Installation
First you have to install needed libraries
### hiredis
```sh
git clone https://github.com/redis/hiredis.git

cd hiredis

make

make install # may be needed sudo permissions
```

### redis-plus-plus
```sh
git clone https://github.com/sewenew/redis-plus-plus.git

cd redis-plus-plus

mkdir build

cd build

cmake ..

make

make install # may be needed sudo permissions

cd ..
```

After installation both previous libraries you can compile application by running `compile.sh` script and run using `run.sh` scirpt. If you do some changes and want to compile and run application you can use `run.sh` command with `--build` or `-b` flag. 

## Usage

Usage of this library assume that you have running `redis-server` on binded in config port.

### Installation redis-server
```sh
sudo apt install redis-server
redis-server                    # runs redis server on default host and port 127.0.0.1:6379
```

It would be also easier to check status of server, debug library etc., by running `redis-commander`

### Instalation redis-commander
```sh
sudo apt install npm
sudo npm install redis-commander
redis-commander             # runs redis-commander server on default host and port 127.0.0.1:8081
```
