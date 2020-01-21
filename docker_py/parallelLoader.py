import subprocess
import sys
import time


if __name__ == '__main__':
    processes = [subprocess.Popen(['python', 'loader.py', '0', '1000000']),
                 subprocess.Popen(['python', 'loader.py', '1000000', '2000000']),
                 subprocess.Popen(['python', 'loader.py', '2000000', '3000000']),
                 subprocess.Popen(['python', 'loader.py', '3000000', '4000000']),
                 subprocess.Popen(['python', 'loader.py', '4000000', '5000000']),
                 subprocess.Popen(['python', 'loader.py', '5000000', '6000000']),
                 subprocess.Popen(['python', 'loader.py', '6000000', '7000000']),
                 subprocess.Popen(['python', 'loader.py', '7000000', '8000000']),
                 subprocess.Popen(['python', 'loader.py', '8000000', '9000000']),
                 subprocess.Popen(['python', 'loader.py', '9000000', '10000000']),
                ]
    
    for process in processes:
        while process.poll() is None:
            time.sleep(.1)


