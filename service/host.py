import socket
import select
import csv

ADDRESS = '127.0.0.1'#'172.17.235.52'
PORT = 8110
BUFSIZE = 1024

class User:
    client:socket.socket = None
    username:str = None
    def __init__(self, name:str, client:socket.socket):
        self.client = client
        self.username = name

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((ADDRESS, PORT))
    server.listen()
    accept(server)
    return None

def accept(server:socket.socket):
    rlist = [server]
    wlist = []
    xlist = []

    while True:
        rl, wl, xs = select.select(rlist, wlist, xlist)
        for item in rl:
            if item is server:
                conn, addr = server.accept()
                print(str(addr)+':connect')
                if validate(conn):
                    rlist.append(conn)
                    conn.sendall(str('success').encode(encoding='UTF-8'))
                    break
                else:
                    conn.sendall(str('passworld error').encode(encoding='UTF-8'))
                    conn.close()
                    break

            else:
                try:
                    data = item.recv(BUFSIZE).decode(encoding='UTF-8')
                    if not data:
                        item.close()
                        rlist.remove(item)
                    else:
                        print(data)
                        for i in rlist[1:]:
                            if i is not item:
                                i.sendall(str(data).encode())
                except ConnectionResetError:
                    item.close()
                    rlist.remove(item)
                    print('[-]远程主机关闭了一个连接')

    return None

def validate(client:socket.socket) ->bool:
    data = str(client.recv(BUFSIZE).decode(encoding='UTF-8'))
    if data.count(';') != 1:
        return False
    index = data.find(';')
    username = data[0:index]
    password = data[index+1:]
    with open('user.csv', 'r') as f:
        userdata = csv.reader(f)
        for row in userdata:
            #print(row)
            if row[0] == username:
                if row[1] == password:
                    print('[+]success login')
                    return True
                else:
                    print('[-]faliled')
                    return False
                break
    return False



if __name__ == "__main__":
    main()