# C-mple Chat: A simple IM server and client in c

C-mple (read like 'simple') chat is an immediate messaging server and client.


## Installation

## Usage

Running the server:

```sh
./seker_server ~/my_dir/users_info ~/my_dir/
```

Running one client:
```sh
./seker_client 
Welcome! Please log in.
User: yuv
Password: hi
Hi yuv, good to see you!
```

Running another client:
```sh
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

## Authors

Peleg Neufeld and Yuval Barak

## Test

The server and client was tested by us with tests/ex[1-9].in which resulted in the right output. 
You can try it yourself with
The project was not tested with valgring.

gif/animation of usage might be added later on
