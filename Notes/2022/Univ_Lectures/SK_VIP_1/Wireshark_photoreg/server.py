import socket

HOST = "127.0.0.1"
PORT = 9800

class Packet:
    src: str
    dst: str
    srcp: int
    dstp: int
    data: int

def hex_to_int(data = []):
    output = 0
    for i in range(1):
        output += data[i] * (256 ** i)
    
    return output

def data_to_packet(data):
    p = Packet()
    p.src = data[0:15].decode()
    p.dst = data[16:31].decode()
    p.srcp = hex_to_int(data[32:36])
    p.dstp = hex_to_int(data[36:40])
    p.data = hex_to_int(data[40:44])

    return p
    
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    print(conn.getsockname())
    with conn:
        print(f"Connected by {addr}")
        data = b''
        while True:
            rcvd = conn.recv(1024)
            if not rcvd:
                break
            data += rcvd

        # print(data).decode()
        # print(data)
        print(hex_to_int(data))
        print(hex_to_int(data[1:2]))
        print(hex_to_int(data[2:3]))
        print(hex_to_int(data[3:4]))

        # print(data[0:15].decode())
        # print(data[16:31].decode())
        # print(hex_to_int(data[32:36]))
        # print(hex_to_int(data[36:40]))
        # print(hex_to_int(data[40:44]))

        # p = data_to_packet(data)
        # print(p.src)
        # print(p.srcp)