"""
best_fit.py
@author Neil Jassal

Code to find and plot CSV files using matplotlib. Data in CSV files must be
provided in x,y format, where the first row represents the axis titles.

Automatically saves plots.
Provides functionality to find and plot best fit line, as well as find
R^2 value.

Requires scipy, matplotlib

Usage:
python best_fit.py csv_filename.csv 'Plot Title'

"""

import sys
import csv
import matplotlib.pyplot as plt
from scipy import stats

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
    

  def plot(self, best_fit=True):
    self.addCSV()

    # Generate data scatterplot
    plt.scatter(self.x_data,self.y_data)
    plt.title(self.title)
    plt.xlabel(self.x_title)
    plt.ylabel(self.y_title)

    if best_fit:
      # Increase y-axis by 20% To make space for displaying best fit/R^2
      y_min,y_max = plt.ylim()
      plt.ylim(y_min, y_max*1.2)

      # Create points for best-fit line and plot
      slope, intercept, r_value, p_value, std_err = stats.linregress(self.x_data,self.y_data)
      r_sq = round(r_value**2,5)

      xl = [min(self.x_data), max(self.x_data)]
      yl = [slope*xx + intercept  for xx in xl]
      plt.plot(xl, yl, '-r')

      # Generate best fit string and print/display stats on command line
      eqn_string = 'y = '+str(round(slope,5))+'x'+' + '+str(round(intercept,5))
      print "Best fit line is:\n" + eqn_string
      print 'R Squared = ' + str(r_sq)

      # Annotate figure
      fig_string = eqn_string + '\n$R^2$ = ' + str(r_sq)
      plt.gca().annotate(fig_string, xy=(0.05, 0.95), xycoords='axes fraction', fontsize=14, horizontalalignment='left', verticalalignment='top')

    plt.savefig(self.title + '.png')

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


