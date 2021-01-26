import csv

def main():
    data = input('>')
    index = data.find(';')
    username = data[0:index]
    password = data[index+1:]
    with open('user.csv', 'r') as f:
        userdata = csv.reader(f)
        for row in userdata:
            print(row)
            if row[0] == username:
                if row[1] == password:
                    print('success login')
                else:
                    print('faliled')
                break
    return None

if __name__ == "__main__":
    main()