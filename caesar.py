import cs50
import sys

def main():
    if len(sys.argv) != 2:
        print("Error!")
        exit(1)
    k = int(sys.argv[1])
    t = []
    print("plaintext: ",end = "")
    s = cs50.get_string()
    k = k%26
    for c in s:
        if(c.isalpha):
            if(c.isupper()):
                a = chr(((ord(c) - 65 + k) % 26) + 65)
                t.append(a)
            elif(c.islower()):
                a = chr(((ord(c) - 97 + k) % 26) + 97)
                t.append(a)
            else:
                t.append(c)
    print("ciphertext: ",end = "")
    print("".join(t))

if __name__ == "__main__":
    main()
            
            
