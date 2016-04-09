//Qt.include("D3.d3.js")
//Qt.include("Techan.techan.js")
.import "d3.js" as D3
.import "techan.js" as Techan

function drawGraph(canvas){
//    var w = canvas.width;
//    var h = canvas.height;
//    var delta = 4; // Spacing between lines
//    var phase = 1;
//    var x1 = 0;
//    var y1 = 0;
//    var x2 = w;
//    var y2 = 0;

//    while (true) {
//        ctx.moveTo(x1, y1);
//        ctx.lineTo(x2, y2);
//        ctx.stroke();

//        switch (phase) {
//        case 1:
//            x1 += delta; y2 += delta;
//            if (x1 >= w || y2 >= h) {
//                x1 = w; y2 = h;
//                phase = 2;
//            }
//            break;
//        case 2:
//            y1 += delta; x2 -= delta;
//            if (y1 >= w || x2 <= 0) {
//                y1 = h; x2 = 0;
//                phase = 3;
//            }
//            break;
//        case 3:
//            x1 -= delta; y2 -= delta;
//            if (x1 <= 0 || y2 <= 0) {
//                x1 = 0; x2 = 0;
//                phase = 4;
//            }
//            break;
//        case 4:
//            y1 -= delta; x2 += delta;
//            if (y1 <= 0 || x2 >= w) {
//                y1 = 0; x2 = w;
//                phase = 5;
//            }
//            break;
//        case 5:
//            return;
//        }
//    }
    console.log("In javascript file");
    var margin = {top: 20, right: 20, bottom: 30, left: 50},
            width = 960 - margin.left - margin.right,
            height = 500 - margin.top - margin.bottom;
    var parseDate = D3.d3.time.format("%d-%b-%y").parse;
    var x = Techan.techan.scale.financetime()
            .range([0, width]);
    var y = D3.d3.scale.linear()
            .range([height, 0]);
    var candlestick = Techan.techan.plot.candlestick()
            .xScale(x)
            .yScale(y);
    var xAxis = D3.d3.svg.axis()
            .scale(x)
            .orient("bottom");
    var yAxis = D3.d3.svg.axis()
            .scale(y)
            .orient("left");
    var svg = D3.d3.select(canvas).append("svg")
            .attr("width", width + margin.left + margin.right)
            .attr("height", height + margin.top + margin.bottom)
            .append("g")
            .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    D3.d3.csv("data.csv", function(error, data) {
        var accessor = candlestick.accessor(),
            timestart = Date.now();
        data = data.slice(0, 200).map(function(d) {
            return {
                date: parseDate(d.Date),
                open: +d.Open,
                high: +d.High,
                low: +d.Low,
                close: +d.Close,
                volume: +d.Volume
            };
        }).sort(function(a, b) { return D3.d3.ascending(accessor.d(a), accessor.d(b)); });
        x.domain(data.map(accessor.d));
        y.domain(Techan.techan.scale.plot.ohlc(data, accessor).domain());
        svg.append("g")
                .datum(data)
                .attr("class", "candlestick")
                .call(candlestick);
        svg.append("g")
                .attr("class", "x axis")
                .attr("transform", "translate(0," + height + ")")
                .call(xAxis);
        svg.append("g")
                .attr("class", "y axis")
                .call(yAxis)
                .append("text")
                .attr("transform", "rotate(-90)")
                .attr("y", 6)
                .attr("dy", ".71em")
                .style("text-anchor", "end")
                .text("Price ($)");
        console.log("Render time: " + (Date.now()-timestart));
    });
}
