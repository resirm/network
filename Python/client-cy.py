#!/usr/bin/env python3

import socket, threading



def speak(sock):
    while True:
        hanashi = input()
        sock.send(hanashi.encode('utf-8'))

def listen(sock):
    while True:
        print("----->"+sock.recv(1024).decode("utf-8"))


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('207.246.76.220',9888))
##s.connect(('127.0.0.1',9888))
print("success fuq")
print(s.recv(1024).decode("utf-8"))
name = input('input your name baby:')
s.send(name.encode('utf-8'))
t = threading.Thread(target=listen,args=(s,)) 
t.start()
t1 = threading.Thread(target=speak,args=(s,))
t1.start()
