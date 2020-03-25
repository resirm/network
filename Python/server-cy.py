#!/usr/bin/env python3

import socket, threading, time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1',9888))

s.listen(10)
slist = []
slist.append(s)
print('Waiting for connection...')


##def tcplink(sock, addr):
##    print('Accept new connection from %s:%s' % addr)
##    sock.send(b'Hello!')
##    while True:
##        try:
##            data = sock.recv(1024)
##        except:
##            print "he has gone"
##            sock.close()
##            break
##        if not data or data == 'exit':
##            break
##        sock.send(b'You said: %s' % data)
##    sock.close()
##    print('Connection from %s:%s closed.' % addr)
def new_conn(s):
    while True:
        sock, addr = s.accept()
        
        sock.send('Fuck You: Welcome, Baby!?'.encode('utf-8'))
        name = sock.recv(1024).decode('utf-8')
        print(name+" come")
        slist.append(sock)
        for other_sck in slist:
            if other_sck != s and other_sck != sock:
                other_sck.send((name+" come").encode('utf-8'))
        if len(slist) == 2:
            sock.send('Nobody Here, Hitoribocchi'.encode('utf-8'))
        threading.Thread(target=listen, args=(sock,name,)).start()

def listen(sock,name):
    while True:
        try:
            d = sock.recv(1024).decode('utf-8')
            print(d)
        except:
            print(name+" has gone")
            sock.close()
            slist.remove(sock)
            for other_sck in slist:
                if other_sck != s:
                    other_sck.send((name+" has gone").encode('utf-8'))
                    if len(slist) == 2:
                        other_sck.send('Nobody Here, Hitoribocchi'.encode('utf-8'))
            break
        for o in slist:
            if o != s and o != sock:
                msg = name+':'+d
                o.send(msg.encode('utf-8'))


                
t = threading.Thread(target=new_conn, args=(s,))
t.start()
