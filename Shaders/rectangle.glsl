//shader vertex
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_MVP;
out vec4 lok;

void main(){
    gl_Position = u_MVP * position;
    lok = position;
};


//shader fragment
#version 330 core
layout(location = 0) out vec4 color;

float dist;
vec2 relativeToRectangleLoc;
vec2 absoluteLoc;
float alpha;

in vec4 lok;

uniform float u_radius;
uniform vec2 u_resolution;
uniform vec2 u_location;
uniform vec2 u_size;

float calculatedRadius;
float distanceToBorder;

float distanceToPoint(vec2 origin, vec2 loc)
{
    return float(sqrt(pow(origin.x-loc.x, 2.0) + pow(origin.y-loc.y, 2.0)));
}

void main(){
    color = vec4(lok.x, lok.y, 1.0, 1.0);
};