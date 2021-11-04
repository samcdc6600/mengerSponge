#version 400 core


layout (location = 0) in vec3 aPos;


void main()
{
    gl_Position	= vec4(aPos.x / 0.2, aPos.y / 0.2, aPos.z / 0.2, 1.0);
}
/*#version 400


//layout (location = 0) in vec3 in_position;
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
out vec3 v_color;


//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;


void main()
{
//gl_Position = projection * view * model * vec4(in_position, 1.0);
 v_color = vec3(1.0, 0.0, 0.5);//vertex_color;
 gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);
}*/