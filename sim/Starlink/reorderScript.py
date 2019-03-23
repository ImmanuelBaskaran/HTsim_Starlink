import sys
expected = 1
with open(sys.argv[1]) as f:
    for line in f.read().splitlines():
        if(int(line.split(" ")[1])!=expected):
            print(line)
        expected+=1
