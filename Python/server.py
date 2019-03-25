#!/usr/bin/env python3

import socket, threading, time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1',8999))

s.listen(10)

print('Waiting for connection...')


def tcplink(sock, addr):
    print('Accept new connection from %s:%s' % addr)
    sock.send(b'Hello!')
    while True:
        data = sock.recv(1024)
        time.sleep(1)
        if not data or data.decode('utf-8') == 'exit':
            break
        sock.send(b'You said: %s' % data.decode('utf-8').encode('utf-8'))
    sock.close()
    print('Connection from %s:%s closed.' % addr)


while True:
    sock, addr = s.accept()
    t = threading.Thread(target=tcplink, args=(sock, addr))
    t.start()