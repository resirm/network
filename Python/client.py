#!/usr/bin/env python3

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.1.67',8999))

print(s.recv(1024).decode('utf-8'))

for data in [b'Fuck', b'You', b'Hahaha']:
    s.send(data)
    print(s.recv(1024).decode('utf-8'))

s.send(b'exit')
s.close()