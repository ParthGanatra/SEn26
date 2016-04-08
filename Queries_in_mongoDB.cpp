// for connection with database
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::finalize;

mongocxx::instance inst{};
mongocxx::client conn{};

auto db = conn["test"];


// to return all the collections in the "Temp" database 

auto cursor = db["Temp"].find({});
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}

// the following query will find the documents which have its "temp_field" field has value equals to "temp_value"  

auto cursor = db["restaurants"].find(document{} << "temp_feild"
                                                << "temp_value" << finalize);

for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}

// if one of our feild is also a document and if want to query according to the specific value of the the
// feild of the document of one of the feild
// suppose in our collection "address" feild contains a document and the document in the "address" field has a field named "zipcode"
// and we want to find documents which "zipcode" feild has a value "10075"

bsoncxx::builder::stream::document filter_builder;
filter_builder << "address.zipcode"
               << "10075";

auto cursor = db["restaurants"].find(filter_builder.view());
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}


// let's say we have a array as one of our field and it's name is "grades" and it contains embedded documents as its elements. if 
// we want to find documents whose grades array contains an embedded document with a field "grade" equal to "B".

bsoncxx::builder::stream::document filter_builder;
filter_builder << "grades.grade"
               << "B";

auto cursor = db["restaurants"].find(filter_builder.view());
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}


// if we want to find documents whose grades array contains an embedded document with a field score greater than 30.

bsoncxx::builder::stream::document filter_builder;
filter_builder << "grades.score" << open_document << "$gt" << 30 << close_document;

auto cursor = db["restaurants"].find(filter_builder.view());
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}

//if we want to find documents whose grades array contains an embedded document with a field score less than 10.

 bsoncxx::builder::stream::document filter_builder;
filter_builder << "grades.score" << open_document << "$lt" << 10 << close_document;

auto cursor = db["restaurants"].find(filter_builder.view());
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}

// we can use logical conjunction (AND) for a list of query conditions by inserting (i.e. <<) multiple query 
// conditions to the query document.

bsoncxx::builder::stream::document filter_builder;
filter_builder << "cuisine"
               << "Italian"
               << "address.zipcode"
               << "10075";

auto cursor = db["restaurants"].find(filter_builder.view());
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}

// we can use logical disjunction (OR) for a list of query conditions by using the $or query operator.

bsoncxx::builder::stream::document filter_builder;
filter_builder << "$or" << open_array << open_document << "cuisine"
               << "Italian" << close_document << open_document << "address.zipcode"
               << "10075" << close_document << close_array;

auto cursor = db["restaurants"].find(filter_builder.view());
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}

//To specify an order for the result set, pass to the find method a sort option to specify the sort order.
// The sort options take a document that contains the field(s) to sort by and the corresponding sort type,
// e.g. 1 for ascending and -1 for descending.
// For example, the following operation returns all documents in the restaurants collection,
// sorted first by the borough field in ascending order, and then, within each borough, 
// by the "address.zipcode" field in decending order

mongocxx::options::find opts;
bsoncxx::builder::stream::document order_builder;
order_builder << "borough" << 1 << "address.zipcode" << -1;
opts.sort(order_builder.view());

auto cursor = db["restaurants"].find({}, opts);
for (auto&& doc : cursor) {
    std::cout << bsoncxx::to_json(doc) << std::endl;
}








