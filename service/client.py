import socket

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(('127.0.0.1', 8110))
    while True:
        a = input('>')
        if a == 'exit':
            break
        client.sendall(a.encode(encoding='UTF-8'))
    return None

if __name__ == "__main__":
    main()