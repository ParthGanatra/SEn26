//Qt.include("D3.d3.js")
//Qt.include("Techan.techan.js")
// .import "d3.js" as D3
// .import "techan.js" as Techan

'use strict';
var wsUri = "ws://localhost:12345";
var dataRecieved = 0, value;
window.onresize = function(){ location.reload(); }
var indicatorType, currentLevel;

window.onload = function() {
    var socket = new WebSocket(wsUri);

    socket.onclose = function()
    {
        console.error("web channel closed");
    };
    socket.onerror = function(error)
    {
        console.error("web channel error: " + error);
    };
    socket.onopen = function()
    {
        new QWebChannel(socket, function(channel) {
            window.chart = channel.objects.chartdata;

            // chart.getWH(function (returnValue){
            //     value_recieved(chart,returnValue);
            // });

            chart.getStockList(function (returnValue){
                add_tabs(returnValue);
            });
        });
    }
    var tabList = {
        list: [
            {
                name: "stock1",
                maxlevels: 3
            },
            {
                name: "stock2",
                maxlevels: 6
            },
            {
                name: "stock3",
                maxlevels: 2
            },
            {
                name: "stock4",
                maxlevels: 5
            }
        ]
    };
    // add_tabs(tabList);
}

function add_tabs(tabList){
    var numTabs = 0,mainData;

    for(numTabs=0;numTabs<tabList.list.length;numTabs++){
        if(numTabs==0){
            $("#mainTabs").append($("<li class=\"active\">\
                                <a href=\"#tab" + (numTabs+1) + "\" data-toggle=\"tab\">" + tabList.list[numTabs].name + "</a>\
                                </li>"));
            $("#mainTabsContent").append($("<div class=\"tab-pane active\" id=\"tab" + (numTabs+1) + "\">\
                                    <button class=\"btn\" id=\"buttontab" + (numTabs+1) + "\">Reset</button>\
                                </div>"));
        }
        else{
            $("#mainTabs").append($("<li>\
                                <a href=\"#tab" + (numTabs+1) + "\" data-toggle=\"tab\">" + tabList.list[numTabs].name + "</a>\
                                </li>"));
            $("#mainTabsContent").append($("<div class=\"tab-pane\" id=\"tab" + (numTabs+1) + "\">\
                        <button class=\"btn\" id=\"buttontab" + (numTabs+1) + "\">Reset</button>\
                        </div>"));

            $('a[data-toggle="tab"]').on('shown.bs.tab', function(e){
                var currentTab = "tab" + e.target.href.slice(-1); // get current tab
                value_recieved(currentTab,mainData);
            });
        }
        addContent(numTabs+1,tabList.list[numTabs]);
    }
    
    d3.csv("data.csv", function(error, data) {
        var parseDate = d3.time.format("%d-%b-%y").parse;

        data = data.slice(0, 200).map(function(d) {
            return {
                date: parseDate(d.Date),
                open: +d.Open,
                high: +d.High,
                low: +d.Low,
                close: +d.Close,
                volume: +d.Volume
            };
        });
        mainData = data;
        value_recieved("tab1",mainData);
    });
}

function addContent(index,dataObject){
    $("#tab" + index).append($("\
        <div style=\"position: absolute; left: 15%; top: 12%;\" class=\"btn-group\">\
            <a class=\"btn dropdown-toggle\" data-toggle=\"dropdown\" href=\"#\">\
                <span id=\"mainName"+index+"\">Indicators</span>\
                <span class=\"caret\"></span>\
            </a>\
            <ul class=\"dropdown-menu\" role=\"menu\" aria-labelledby=\"dropdownMenu\">\
                <li><a id=\"normal" + index + "\" tabindex=\"-1\" href=\"#\">Normal</a></li>\
                <li><a id=\"elliott" + index + "\" tabindex=\"-1\" href=\"#\">Elliott Wave Count</a></li>\
            </ul>\
        </div>\
    "));

    $("#normal"+index).click(function() {
        indicatorType = "normal";
        currentLevel = -1;
        $("#levels").remove();
        $("#mainName"+index).html("Normal");
        console.log(indicatorType,currentLevel);
    });

    $("#elliott"+index).click(function() {
        indicatorType = "elliott";
        currentLevel = 1;

        $("#mainName"+index).html("Elliott Wave Count");
        $("#tab" + index).append($("\
            <div id=\"levels\" style=\"position: absolute; left: 50%; top: 12%\" class=\"btn-group\">\
                <a class=\"btn dropdown-toggle\" data-toggle=\"dropdown\" href=\"#\">\
                    <span id=\"mainLevel"+index+"\">Levels</span>\
                    <span class=\"caret\"></span>\
                </a>\
                <ul id=\"levelDrop" + index + "\" class=\"dropdown-menu\" role=\"menu\" aria-labelledby=\"dropdownMenu\">\
                </ul>\
            </div>\
        "));
        for(var i=0;i<dataObject.maxlevels;i++){
            $("#levelDrop" + index).append($("\
                <li><a id=\"level_"+i+"_"+index+"\" tabindex=\"-1\" href=\"#\">Level " + (i+1) + "</a></li>\
            "));

            $("#level_"+i+"_"+index).click(function(e) {
                currentLevel = e.target.text.slice(-1);
                $("#mainLevel"+index).html("Level " + e.target.text.slice(-1));
                console.log(indicatorType,currentLevel);
            });
        }
        // <li><a tabindex=\"-1\" href=\"#\">Level 1</a></li>\
    });
}

function value_recieved(displayTab,data){
    var margin = {top: 50, right: 70, bottom: 50, left: 50},
        width = window.innerWidth - margin.left - margin.right,
        height = window.innerHeight - margin.top - margin.bottom;

    var parseDate = d3.time.format("%d-%b-%y").parse;

    var x = techan.scale.financetime()
        .range([0, width]);

    var y = d3.scale.linear()
        .range([height, 0]);

    var candlestick = techan.plot.candlestick()
        .xScale(x)
        .yScale(y);

    var xAxis = d3.svg.axis()
        .scale(x)
        .orient("bottom");

    var yAxis = d3.svg.axis()
        .scale(y)
        .orient("left");

    var accessor = candlestick.accessor();

    data.sort(function(a, b) { return d3.ascending(accessor.d(a), accessor.d(b)); });

    var zoom = d3.behavior.zoom()
    .on("zoom", draw);

    d3.select("svg").remove();

    console.log(displayTab);

    var svg = d3.select("#" + displayTab).append("svg")
            .attr("width", width + margin.left + margin.right)
            .attr("height", height + margin.top + margin.bottom)
        .append("g")
            .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    svg.append("clipPath")
            .attr("id", "clip")
        .append("rect")
            .attr("x", 0)
            .attr("y", y(1))
            .attr("width", width)
            .attr("height", y(0) - y(1));

    svg.append("g")
            .attr("class", "candlestick")
            .attr("clip-path", "url(#clip)");

    svg.append("g")
            .attr("class", "x axis")
            .attr("transform", "translate(0," + height + ")");

    svg.append("g")
            .attr("class", "y axis")
        .append("text")
            .attr("transform", "rotate(-90)")
            .attr("y", 6)
            .attr("dy", ".71em")
            .style("text-anchor", "end")
            .text("Price ($)");

    svg.append("rect")
            .attr("class", "pane")
            .attr("width", width)
            .attr("height", height)
            .call(zoom);

        // var accessor = candlestick.accessor();

    x.domain(data.map(accessor.d));
    y.domain(techan.scale.plot.ohlc(data, accessor).domain());

    svg.select("g.candlestick").datum(data);
    draw();

    d3.select("#button" + displayTab).on("click", reset);
    // Associate the zoom with the scale after a domain has been applied
    zoom.x(x.zoomable().clamp(false)).y(y);

    function draw() {
        svg.select("g.candlestick").call(candlestick);
        svg.select("g.x.axis").call(xAxis);
        svg.select("g.y.axis").call(yAxis)
    }

    function reset() {
        zoom.scale(1);
        zoom.translate([0,0]);
        draw();
    }
}
