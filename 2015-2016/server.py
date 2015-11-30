import json

data = [{'title':'Chem E Car', 'body':"Your big, blue, roundness impresses us all."}]
json.dump(data, open('demo_data.json', 'w'))
