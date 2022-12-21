import requests
from bs4 import BeautifulSoup
import argparse
import os
parser = argparse.ArgumentParser(description = 'getting an age rating')
parser.add_argument("-agent",dest = 'name')
parser.add_argument("-site",dest = 'url')
args = parser.parse_args()

if args.name == "ageRating":
    r = requests.get(args.url)
    soup = BeautifulSoup(r.text, 'html.parser')
    items = soup.find_all('div', class_='age-restrictions')
    f = open("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/age_rating.txt", "w")
    for item in items:
        f.write(item.text.strip())
    f.close()

elif args.name == "GamePlatforms":
    r = requests.get(args.url)
    soup = BeautifulSoup(r.text, 'html.parser')
    items = soup.find_all('div', class_='table__row details__rating details__row')[0]
    items = items.find_all('div', class_='details__content table__row-content')
    with open("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/platforms.txt", "w") as f:
        for item in items:
            print(f"{item.text.strip()}")
            f.write(item.text.strip())
elif args.name == "Price":
    r = requests.get(args.url)
    soup = BeautifulSoup(r.text, 'html.parser')
    items_s = soup.find_all('div', class_='product-actions-price')
    f = open("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/price.txt", "w")
    f.write(str(items_s[0].text.strip()[0:5:]))
    f.write(" руб.")
    f.close()    
