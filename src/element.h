#ifndef MODEL_H
#define	MODEL_H

#include "src/json/json.h"

enum {X, Y, Z};

struct Element
{
    //Start point of a cube according to the scheme [x, y, z]
    //Must be between -16 to 32
    int from[3];
    
    //Stop point of a cube according to the scheme [x, y, z]
    //Must be between -16 to 32
    int to[3];
    
    //Sets the center of the rotation according to the scheme [x, y, z]
    //Defaults to [8, 8, 8] in Minecraft.
    int rotation_origin[3];
    
    //Specifies the direction of the rotation.
    //One of X, Y or Z.
    size_t rotation_axis;
    
    //Specifies the angle of the rotation.
    //Valid values are -45, -22.5, 0, 22.5 and 45.
    signed int rotation_angle[3];
    
    //Defines the area of the textures for faces 1-6 according to the scheme
    //[x1, y1, x2, y2].
    //If unset, defaults to values equal to xyz pos of the element.
    //Must be between 0 to 16
    uint8_t uv_faces[6][4];
    
    //Specifies the faces textures in form of a texture variable starting with #
    std::string texture_faces[6];
    
    //Specifies whether non-visible elements should be rendered for the faces.
    bool cull_faces[6];
    
    //Rotates the texture in increments of 90 degrees. 
    //Must be between 0 to 3
    uint8_t rotation_faces[6];
    
    //Determens if the texture should be tinted by Minecrafts renderer.
    //Tinting is a hardcoded color adjustment.
    unsigned int tint_index_faces[6];
};

//Loads an element from a json Object.
Element* loadElement(json::Value* element);

//Loads an element from a json Object.
//Does not create a new element, instead overrides target.
Element* loadElement(json::Value* element, Element* target);

//Saves an element to json.
//Allocates a new value and returns a pointer to it.
//Note that it's still cached, not written to a file,
//only in a proper json format.
json::Value* saveElement(Element* element);

//Saves an element to json.
//Overrides whatever is set in target.
json::Value* saveElement(Element* element, json::Value* target);

#endif	// MODEL_H

