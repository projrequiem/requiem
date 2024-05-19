import socket
import json

class PlotClient:
    
    def __init__(self, addr='localhost', port=33333):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.addr = addr
        self.port = port
        self.sock.bind((addr, port))
        self.sock.listen(1)
        self.connection, self.client_address = self.sock.accept()
        self.current_packet = {}

    def est_pos(self, pos):
        self.current_packet['est_pos'] = pos

    def timestamp(self, t):
        self.current_packet['timestamp'] = t

    def innov(self, innov):
        self.current_packet['innov'] = innov

    def gps_pos(self, pos):
        self.current_packet['gps_pos'] = pos

    def send_data(self):
        if 'timestamp' not in self.current_packet:
            print("'timestamp' is not in the current packet")
            return
        if 'est_pos' not in self.current_packet:
            print("'est_pos' is not in the current packet")
            return
        if 'gps_pos' not in self.current_packet:
            print("'gps_pos' is not in the current packet")
            return
        if 'innov' not in self.current_packet:
            print("'innov' is not in the current packet")
            return
        self.connection.sendall(json.dumps(self.current_packet).encode())
        self.connection.recv(1024)
        self.current_packet = {}
    
    def close(self):
        self.connection.sendall(json.dumps({'quit':1}).encode())
        self.connection.close()
        self.sock.close()