import json
import webbrowser

"""data = '{ "values" : [ { "unit" : "Unit_1", "value" : "20" },\
{ "unit" : "Unit_2" , "value" : "10" },{ "unit" : "Unit_3" ,\
"value" : "30" } ]}'"""

data = {
	"JSChart" : {
		"datasets" : [
			{
				"type" : "line",
				"data" : [
					{
						"unit" : "10",
						"value" : "2"
					},
					{
						"unit" : "15",
						"value" : "0"
					},
					{
						"unit" : "18",
						"value" : "3"
					},
					{
						"unit" : "19",
						"value" : "6"
					},
					{
						"unit" : "20",
						"value" : "8.5"
					},
					{
						"unit" : "25",
						"value" : "10"
					},
					{
						"unit" : "30",
						"value" : "9"
					},
					{
						"unit" : "35",
						"value" : "8"
					},
					{
						"unit" : "40",
						"value" : "5"
					},
					{
						"unit" : "45",
						"value" : "6"
					},
					{
						"unit" : "50",
						"value" : "2.5"
					}
				]
			}
		]
	}
}

                     
json.dump(data, open('data.json', 'w'))

webbrowser.open('index.html', new=0, autoraise=True)

