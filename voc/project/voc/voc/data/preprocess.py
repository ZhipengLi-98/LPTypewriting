import json
res={}
with open("lexicon.txt","r") as file:
    for line in file:
        line=line.strip()
        word,freq=line.split(" ")
        freq=int(freq)
        
        for i in range(1,len(word)+1):
            substr=word[0:i]
            res[substr]=res.get(substr,0)+freq

with open("prefix","w")as file:
    json.dump(res,file)
        