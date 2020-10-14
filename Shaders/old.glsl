//shader vertex
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main(){
    gl_Position = position;
};


//shader fragment
#version 330 core
layout(location = 0) out vec4 color;

float dist;
vec2 relativeToRectangleLoc;
vec2 absoluteLoc;
float alpha;

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
    calculatedRadius = clamp(clamp(u_radius, 0, u_size.x/2), 0, u_size.y/2);


    relativeToRectangleLoc = (gl_FragCoord.xy - u_location) / (u_resolution*0.5);
    absoluteLoc = relativeToRectangleLoc*u_size;
    alpha = 1.0;

    if(!(absoluteLoc.x > calculatedRadius && absoluteLoc.x < u_size.x - calculatedRadius && absoluteLoc.y > calculatedRadius && absoluteLoc.y < u_size.y-calculatedRadius))
    {
        if(absoluteLoc.x < (calculatedRadius))
        {
            if(absoluteLoc.y < (calculatedRadius))
            {
                if(distanceToPoint(vec2(calculatedRadius, calculatedRadius), absoluteLoc) > calculatedRadius)
                {
                    alpha = 0.0;
                }
            }
        }
        if(absoluteLoc.x > (u_size.x - calculatedRadius))
        {
            if(absoluteLoc.y < (calculatedRadius))
            {
                if(distanceToPoint(vec2((u_size.x - calculatedRadius), calculatedRadius), absoluteLoc) > calculatedRadius)
                {
                    alpha = 0.0;
                }
            }
        }

        if(absoluteLoc.x < (calculatedRadius))
        {
            if(absoluteLoc.y > (u_size.y - calculatedRadius))
            {
                if(distanceToPoint(vec2((calculatedRadius), (u_size.y - calculatedRadius)), absoluteLoc) > calculatedRadius)
                {
                    alpha = 0.0;
                }
            }
        }
        if(absoluteLoc.x > (u_size.x - calculatedRadius))
        {
            if(absoluteLoc.y > (u_size.y - calculatedRadius))
            {
                if(distanceToPoint(vec2((u_size.x - calculatedRadius), (u_size.y - calculatedRadius)), absoluteLoc) > calculatedRadius)
                {
                    alpha = 0.0;
                }
            }
        }
    }
    else
    {
        alpha = 1.0f;
        //distanceToBorder = 
    }
    color = vec4(1.0, 1.0, 1.0, alpha);
};