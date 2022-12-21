import http.client
import json
import re
from bs4 import BeautifulSoup
import argparse
import os

debug = False

parser = argparse.ArgumentParser(description='getting a game rating')
parser.add_argument("-agent", dest='name')
parser.add_argument("-game", dest='game')
args = parser.parse_args()
if args.name == "gameRating":
    conn = http.client.HTTPSConnection("ru.wikipedia.org")
    
    query = args.game
    # query = "Battlefield: Heroes"
    
    conn.request("GET",
                 f'/w/api.php?action=opensearch&format=json&search={query.replace(" ", "%20")}&formatversion=2')
    game_info = conn.getresponse().read().decode("utf-8")
    
    try:
        url: str = json.loads(game_info)[-1][0]
    except Exception:
        print("Game not found")
        try:
            os.remove("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/game_rating.txt")
        except Exception:
            pass
        exit(1)
    if debug:
        print(url[url.find("/", 8):])
    
    conn.request("GET", url[url.find("/", 8):])
    data = conn.getresponse().read()
    dataFound = False
    soup = BeautifulSoup(data.decode("utf-8"), 'html.parser')
    tables = soup.find_all('table', class_='wikitable collapsible')
    for table in tables:
        try:
            table_body = table.find('tbody')
        except Exception:
            print("Rating not found")
            try:
                os.remove("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/game_rating.txt")
            except Exception:
                pass
            exit(1)
        headers = table_body.find_all('th', class_='Reception')
        if len(headers) == 0:
            continue
        rows = table_body.find_all('tr')
        scores = []
        for row in rows:
            cols = row.find_all('td')
            if list(cols):
                cols = [ele.text.strip() for ele in cols]
                scores.append([ele for ele in cols if ele])
    
        if debug:
            print(scores)
        file = open("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/game_rating.txt", "w")
        for score in scores:
            match = re.search('\d.{0,2}[ ]?/[ ]?\d{2,3}', score[1])
            if match:
                file.write(score[0] + ": " + match[0].replace(" ", "") + "\n")
                # print(score[0] + ": " + match[0].replace(" ", "") + "\n")
                dataFound = True
        file.close()
    if not dataFound:
        try:
            print("Rating not found")
            os.remove("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/game_rating.txt")
        except Exception:
            pass
        
