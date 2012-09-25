import os

os.system('sudo iptables -A OUTPUT -p icmp -j NFQUEUE --queue-num 0')

