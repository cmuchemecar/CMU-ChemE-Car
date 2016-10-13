
function updateData() {

  var dataPoints = [{ key: "Sensor", values: [] }];
  
  nv.addGraph(function() {
	var chart = nv.models.lineChart()
                .margin({left: 100})
                .useInteractiveGuideline(true)
                .duration(300)
                .showLegend(true)
                .showYAxis(true)
                .showXAxis(true);
	
	chart.xAxis
      .axisLabel('Time (s)')
      .tickFormat(d3.format('.02f'));

    chart.yAxis
      .axisLabel('Value')
      .tickFormat(d3.format('.02f'));

	nv.utils.windowResize(chart.update);

	setInterval(function () {
	  d3.json($SCRIPT_ROOT+'_dataJson', function(data) {
	  //d3.json('http://silver.ddns.commx.ws:5000/data.json', function(data) {
	    dataPoints[0].values.push({x: data.time, y: data.value});
	    d3.select('#chart')
		.datum(dataPoints)
		.call(chart);
	  jQuery('#show-data').text("Time: " + data.time + " Value: " + data.value);
	  });
	}, 1000);
	
	
	return chart;
  });
}