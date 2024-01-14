import subprocess
import time
import random

while True:
    data = random.randrange(0, 1024)
    subprocess.check_call("./brw.sh %s %s %s %s %s %s %s" % ("test", "photoreg", "1.2.3.4", "5.6.7.8", 1234, 5678, data), shell=True)
    time.sleep(1)