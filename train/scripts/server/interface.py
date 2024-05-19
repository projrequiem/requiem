import time
import json
import socket

class EKFInterface:

    def __init__(self, addr, port):
        self.server = None
        self.server_addr = addr
        self.server_port = port
        self._connect()
    
    def _connect(self):
        self.server =socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.connect((self.server_addr, self.server_port))

    def recieveJson(self, bufferLen=49152):
        output = {}
        buffer = ''
        while True:
            data = self.server.recv(bufferLen)
            if not data:
                break
            else:
                buffer += data.decode("utf-8")
                try:
                    output = json.loads(buffer)
                    break
                except ValueError:
                    continue
        return output

    def sendJson(self, jsonObj):
        self.server.send(json.dumps(jsonObj).encode())

    def sendRequest(self, reqId, dataJson):
        data = json.dumps({'ekf':dataJson})
        reqJson = {'reqId':reqId,'len':len(data)}

        self.sendJson(reqJson)
        respJson = self.recieveJson()
        if 'ACK' not in respJson:
            exit('Communication error')
        self.server.send(data.encode())
        respJson = self.recieveJson()
        if 'ekf' not in respJson:
            exit('Communication error')
        return respJson

    
    def close(self):
        reqJson = {'reqId':'quit'}
        self.sendJson(reqJson)
        self.server.close()

class SimulationInterface:
    def __init__(self, addr, port):
        self.server = None
        self.server_addr = addr
        self.server_port = port
        self._connect()
        pass

    def close(self):
        self.server.close()
    
    def _connect(self):
        self.server =socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.server_addr, self.server_port))
        self.server.listen()
        self.conn, addr = self.server.accept()
        self.conn.settimeout(10)
        print('connected to', addr)

    def recieveJson(self, bufferLen=49152):
        output = {}
        buffer = ''
        while True:
            data = self.conn.recv(bufferLen)
            if not data:
                break
            else:
                try:
                    buffer += data.decode("utf-8")
                except ValueError:
                    print("RECIEVE JSON EXCEPTION", buffer)
                    exit()
                try:
                    output = json.loads(buffer)
                    break
                except ValueError:
                    print("UNABLE TO PARSE")
                    continue
        return output

    def _test_recive_snapshot(self):
        meta = self.recieveJson()
        expectedLen = meta['len']
        self._test_send_ack(expectedLen)
        return self.recieveJson(expectedLen)

    def _test_send_values(self, values):
        serialized_v = ','.join(values).encode()
        self.conn.send(('%d\n'%len(serialized_v)).encode()) # send len
        self._test_recv_ack() # get ack
        self.conn.send(serialized_v) # send data
        # self._test_recv_ack() # get ack

    def _test_send_ack(self, v=1):
        self.conn.send(('%d'%v).encode())

    def _test_recv_ack(self):
        timeout_counter = 0
        while True:
            data = self.conn.recv(24)
            if not data:
                if timeout_counter > 10:
                    return -1
                else:
                    timeout_counter+=1
                time.sleep(0.1)
            else:
                if len(data.decode()) > 0:
                    return data.decode()
                return -1
    def _test_recv_number(self):
        while True:
            data = self.conn.recv(8)
            if not data:
                break
            else:
                if int(data.decode()) >= 0:
                    return int(data.decode())
                return -1
