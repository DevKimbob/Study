import socket

# HOST = "127.0.0.1"
HOST = input("enter host : ")
PORT = 9800
TARGET = (HOST, PORT)

arr = HOST.split(sep='.')
print(arr)
arr_int = []
for i in range(4):
    arr_int.append(int(arr[i]))

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    print(s.getsockname())
    print(s.getpeername())
    s.send(bytearray(arr_int))