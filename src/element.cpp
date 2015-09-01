#include "src/json/json.h"
#include "element.h"

Element* loadElement(json::Value* element)
{
    Element* to_return = new Element();
    
    //TODO every catch block should write to a future logger as well.
    for(int i = 0; i < 3; ++i)
    {
        try
        {
            if((*element)["from"] == NULL) to_return->to[i] = 0;
            else if((*(*element)["from"])[i] == NULL) to_return->to[i] = 0;
            else to_return->from[i] = (*(*element)["from"])[i]->as_int();
        }
        catch(json::json_exception)
        {
            to_return->from[i] = 0;
        }
        
        try
        {
            if(((*element)["to"]) == NULL) to_return->to[i] = 0;
            else if((*(*element)["to"])[i] == NULL) to_return->to[i] = 0;
            //json::Value* value = (*(*element)["to"])[i];
            else to_return->to[i] = (*(*element)["to"])[i]->as_int();
        }
        catch(json::json_exception)
        {
            to_return->to[i] = 0;
        }
        
//        try
//        {
//            to_return->rotation_origin[i] = 
//                    (*(*(*element)["rotation"])["origin"])[i]->as_int();
//        }
//        catch(json::json_exception)
//        {
//            to_return->rotation_origin[i] = 0;
//        }
    }
}

Element* loadElement(json::Value* element, Element* target)
{
    
}

json::Value* saveElement(Element* element)
{
    
}

json::Value* saveElement(Element* element, json::Value* target)
{
    
}

