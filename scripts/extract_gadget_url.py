import json, sys

path = sys.argv[1]
text = open(path, encoding="utf-8-sig").read()
text = text[text.index("{"):]
data = json.loads(text)
for a in data["assets"]:
    if "gadget" in a["name"].lower():
        print(a["name"], a["browser_download_url"])
