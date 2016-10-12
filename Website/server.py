from flask import Flask
from flask import render_template
import json
import time

app = Flask(__name__)

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/_dataJson')
def dataJson():
	data = loadData()
	return json.dumps(data)


def saveData(time, value):
	filename = 'data.json'
	data = {'time': time, 'value': value}
	with open(filename, 'w') as file:
		json.dump(data, file)
		
def loadData():
	filename = 'data.json'
	with open(filename, 'r') as file:
		data = json.load(file)
	return data
		
	
if __name__ == '__main__':
	app.debug = False
	app.run(host='0.0.0.0')
	