# C-mple Chat: A simple course rate server and client

C-mple (read like 'simple') chat is a course rate and immediate messaging server and client.
You can add, rate and get courses, and the protocol is open so you can implement your server/client 
if you want to.


## Installation

1. Download the files

```sh
git clone https://github.com/yuvalyehudab/c-mplechat.git
cd c-mplechat
```
2. Compile server

```sh
cd server
make
```
3. Compile client

```sh
cd ../client
make
```

4. See usage section to use the server and client 


## Usage

Running the server:

```sh
cd c-mplechat/server
./seker_server ../users.txt ./
```

Running one client:
```sh
../client/seker_client 
Welcome! Please log in.
User: yuv
Password: hi
Hi yuv, good to see you!
```

Running another client:
```sh
cd c-mplechat/client
./seker_client
Welcome! Please log in.
User: peleg
Password: bi
Hi yuv, good to see you!
```

Adding course:

```sh
add_course 1234 "intro to whatever"
```

Sending broadcast:

```sh
broadcast "HI! I'm peleg!"
```

Show list of courses:

```sh
list_of_courses
```

Rating course:
```sh
rate_course 1234 99 "best course I'v done"
```

Getting rate of course:
```sh
get_rate 1234
```

Quitting:

```sh
quit
```

## Authors

Peleg Neufeld and Yuval Barak

## Test

The server and client was tested by us with tests/ex[1-9].in which resulted in the right output. 
You can try it yourself (you need to fix the paths) with
```sh
./seker_server ../users.txt ./ &
./seker_client < ex1.in > ex1.out
```
The project was not tested with valgring.

gif/animation of usage might be added later on
