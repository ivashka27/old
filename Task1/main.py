import requests
from bs4 import BeautifulSoup
import os

width = 80
to_collect = ["h1", "h2", "h3", "h4", "h5", "h6", "p", "title"]

#def solve() - function giving needed format of text

def solve(inform, width):
    res, current = [], ""
    for strr in inform:
        for elem in strr.split():
            #check if length of string bigger than width
            if len(current) + len(elem) < width or len(current) == 0:
                current += elem
                current += " "
            else:
                res.append(current)
                current = elem + " "
        res.append(current)
        res.append("")
        current = ""
    return res

#def NAME() - function for getting name of file and directory path

def NAME(smth):
    tmp_str = smth
    n, cur = len(tmp_str), 0
    for i in range(n - 2):
        if (tmp_str[i] == ':' and tmp_str[i + 1] == '/' and tmp_str[i + 2] == '/'):
            cur = i
            break
    tmp_str = tmp_str[cur + 3:]
    if (tmp_str[-1] == '/'):
        tmp_str = tmp_str[:-1]
    n, pos = len(tmp_str), 0
    for i in range(n - 1, -1, -1):
        if (tmp_str[i] == '/'):
            pos = i
            break
    filee = list(tmp_str[pos+1:])
    dir = list(tmp_str[:pos])
    taboo_chars = ['/', ':', '*', '?', '"', '<', '>', '|', '+', '%', '!', '@', '~', "#"]
    for i in range(len(filee)):
        if (filee[i] in taboo_chars):
            filee[i] = '_'
    if (not(len(filee))):
        filee = "smth"
    if (not (len(dir))):
        dir = "smth"

    return (''.join(dir), ''.join(filee) + ".txt")


#----------
print("Enter URL ?")
print()
url = ''.join(input().split())  #getting url, file-name, dir path
t = NAME(str(url))
file_name = t[1]
dir = "TEST/"+t[0]
#----------

#----------
final_inf = []
document_ = requests.get(url).content.decode(requests.get(url).encoding) #getting, encoding, parsing html-document
bs = BeautifulSoup(document_, 'html.parser')
all_ = bs.body.findAll(to_collect)

for curr in all_:
    for link in curr.findAll('a'):
        link.replaceWith(link.text + ' [ ' + link['href'] + ' ]')
    if curr.get_text():
        final_inf.append(curr.get_text().strip())
#----------

#----------
tmpp = solve(final_inf, width)  #opening directory, formating information, collecting final file
if not os.path.exists(dir):
    os.makedirs(dir)
with open(os.path.join(dir, file_name), 'w', encoding='utf-8') as file:
    for el in tmpp:
        file.write(el + "\n")
print("Check result file:", file_name)
#----------