import time
import json
import random


t = 0
while True:
	x = random.randint(0, 100)
			
	filename = 'data.json'
	jsonData = {'time': t, 'value': x}
	with open(filename, 'w') as file:
		json.dump(jsonData, file)

	time.sleep(0.125)
	t += 0.125