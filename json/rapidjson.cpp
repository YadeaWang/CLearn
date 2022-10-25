#include "rapidjson/document.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

int main()
{
    const char* json_ptr = "{\"project\":\"rapidjson\",\"stars\":10,\"hello\":\"world\"}";
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    
    Document doc;
    doc.Parse(json);

    assert(doc.IsObject());
    assert(doc.HasMember("hello"));
    assert(doc["hello"].IsString());
    printf("hello = %s\n", doc["hello"].GetString());

    assert(doc["t"].IsBool());
    cout << (doc["t"].GetBool() ? "true" : "false") << endl;

    cout << (doc["n"].IsNull()? "nullptr" : "?") << endl;

    assert(doc["i"].IsNumber());
    // 在此情况下，IsUint()/IsInt64()/IsUint64() 也会返回 true
    assert(doc["i"].IsInt());          
    printf("i = %d\n", doc["i"].GetInt());
    // 另一种用法： (int)doc["i"]
    
    assert(doc["pi"].IsNumber());
    assert(doc["pi"].IsDouble());
    printf("pi = %g\n", doc["pi"].GetDouble());

    const Value& a = doc["a"];
    assert(a.IsArray());
    for(SizeType i = 0; i < a.Size(); ++i)
        printf("a[%d] = %d\n", i, a[i].GetInt());
        
}