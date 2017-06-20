import cs50

def main():
    while True:
        print("O hai! How much change is owed?")
        change = cs50.get_float()
        if(change>=0):
            break
    cents = change * 100
    count = 0
    while cents:
        if(cents>=25):
            cents = cents - 25
            count = count + 1
        elif(cents>=10):
            cents = cents - 10
            count = count + 1
        elif(cents>=5):
            cents = cents - 5
            count = count + 1
        else:
            cents = cents - 1
            count = count + 1
    print("{}".format(count))
        
    
if __name__ == "__main__":
    main()
