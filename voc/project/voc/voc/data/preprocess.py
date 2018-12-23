import json

def getPrefix():
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

def getJson():
    res={}
    with open("lexicon.txt","r") as file:
        for line in file:
            line=line.strip()
            word,freq=line.split(" ")
            freq=int(freq)
            res[word]=freq

    with open("lexicon.json","w")as file:
        json.dump(res,file)

def getPrefix2Word():
    res={}
    with open("lexicon.txt","r") as file:
        for line in file:
            line=line.strip()
            word,freq=line.split(" ")
            for i in range(1,len(word)+1):
                substr=word[0:i]
                if res.get(substr,False):
                    res[substr].append(word)
                else:
                    res[substr]=[word]

    with open("prefix2Word","w")as file:
        json.dump(res,file)

if __name__ == '__main__':
    getPrefix2Word()
        