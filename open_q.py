import os

os.system('sudo iptables -D OUTPUT -p icmp -j NFQUEUE --queue-num 0')

