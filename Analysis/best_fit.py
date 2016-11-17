"""
best_fit.py
@author Neil Jassal

Code to find and plot CSV files using matplotlib. Data in CSV files must be
provided in x,y format, where the first row represents the axis titles.

Automatically saves plots.
Provides functionality to find and plot best fit line, as well as find
R^2 value.

Requires numpy, matplotlib

Usage:
python best_fit.py csv_filename.csv 'Plot Title'

"""

import sys
import csv
import matplotlib.pyplot as plt
import numpy as np

class BestFit():

  def __init__(self, filename, title):
    if filename is None:
      print "No data filename provided. Please provide a '.csv' file"
      sys.exit(2) # 2 generally used for command-line errors
    self.filename = filename

    self.title = title
    if title is None:
      self.title = filename

    # X and Y data for plot
    self.x_data = []
    self.y_data = []
    self.x_title = ''
    self.y_title = ''
    

  def plot(self, best_fit=True, r_sq=True):
    self.addCSV()
    line = self.findBestFit()
    self.findRSquared()

    plt.scatter(self.x_data,self.y_data)
    plt.xlabel(self.x_title)
    plt.ylabel(self.y_title)
    plt.show()

  def addCSV(self):
    """
    Parses CSV File, given each line is provided in x,y form.
    The first row of the CSV represents the corresponding axis titles.
    """
    f = open(self.filename)
    csv_f = csv.reader(f)
    first = True

    for row in csv_f:
      # Extract axis titles from first row of CSV file
      if first:
        first = False
        self.x_title = row[0]
        self.y_title = row[1]
        continue

      # Store data for plot
      self.x_data.append(float(row[0]))
      self.y_data.append(float(row[1]))


  def findBestFit(self):
    return np.polyfit(self.x_data, self.y_data, 1, full=True)

  def findRSquared(self):
    return 

  def savePlot(self):
    pass


if __name__ == "__main__":
  filename = None
  save = True

  # Parse command line args for filename and save T/F boolean
  if len(sys.argv) >= 2:
    filename = sys.argv[1]
  if len(sys.argv) >= 3:
    title = sys.argv[2]

  fit = BestFit(filename, title)
  fit.plot()


