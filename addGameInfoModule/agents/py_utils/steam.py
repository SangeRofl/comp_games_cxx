import requests
from bs4 import BeautifulSoup
import argparse
parser = argparse.ArgumentParser(description = 'getting a parameters')
parser.add_argument("-agent",dest = 'name')
parser.add_argument("-site",dest = 'url')
args = parser.parse_args()
   
if args.name == "Review":
    r = requests.get(args.url)
    soup = BeautifulSoup(r.text, 'html.parser')
    items = soup.find_all('div',{'class': 'summary column'})

    f = open("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/review.txt", "w")
    i=1
    for item in items:
        if i == 1:
            f.write(f"{i})")
            f.write(item.text.strip())
            f.write(" ")
        i=i+1
    f.close()

if args.name == "supportedLanguage":
    r = requests.get(args.url)
    soup = BeautifulSoup(r.text, 'html.parser')
    items = soup.find_all('td',{'class': 'ellipsis'})

    f = open("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/supported_language.txt", "w")
    i=1
    for item in items:
        f.write(f"{i})")
        f.write(item.text.strip())
        f.write(" ")
        i=i+1
    f.close()
    
if args.name == "systemRequirements":
    r = requests.get(args.url)
    soup = BeautifulSoup(r.text, 'html.parser')
    items = soup.find_all('div', class_='game_area_sys_req_leftCol') # only minimum
    # items.append(soup.find('div', class_='game_area_sys_req_rightCol')) # min+recommended
    f = open("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/system_requirements.txt", "w")
    i=1
    for item in items:
        newsoup = BeautifulSoup(str(item), 'html.parser')
        uli = newsoup.find_all('li')
        for li in uli:
            f.write(f"{i})")
            f.write(li.text.strip())
            f.write("\n")
            i = i + 1
    f.close()
