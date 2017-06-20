import cs50

def main():
    while True:
        print("Height: ",end = "")
        n = cs50.get_int()
        if(n<=23 and n>=0):
            break
    for i in range (1,n+1):
        for j in range (1,n-i+1):
            print(" ",end = "")
        for k in range (1,i+1):
            print("#",end = "")
        print("#")
if __name__ == "__main__":
    main()
