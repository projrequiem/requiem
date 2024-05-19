#!/bin/python3
import subprocess

PX4SUCC = 'INFO  [px4] Startup script returned successfully'

class PX4ExecutionError(Exception):
    pass


class PX4Proc:

    def __init__(self, px4_path, args):
        self.px4_path = px4_path 
        self.args = args
        self.proc = None
    
    def run(self):
        self.proc =  subprocess.Popen(self.px4_path, **self.args)
        # Should print sucess within 100 lines
        for i in range(100):
            output = self.proc.stdout.readline()
            if PX4SUCC in output.decode('utf-8'):
                return
        self.kill()
        self.proc = None
        raise PX4ExecutionError('Could not find the success message in the PX4 STDOUT')

    def shutdown(self):
        if self.proc is None:
            print('PX4 is already shutdown')
        print('Sending "shutdown" command to PX4')
        print(self.proc.communicate(input='shutdown\n'.encode())[0])
        return

    def kill(self):
        self.proc.terminate()
        self.proc.kill()

    def pause(self):
        os.killpg(os.getpgid(self.proc.pid), signal.SIGSTOP)

    def resume(self):
        os.killpg(os.getpgid(self.proc.pid), signal.SIGCONT)

    def collect_logs(self, outputDir):
        pass
